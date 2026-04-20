#!/usr/bin/env python3
"""Evaluate an engine NNUE binary on a shard directory using WDL metrics."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

import torch
try:
    from tqdm import tqdm
except ImportError:  # pragma: no cover - optional dependency
    tqdm = None

REPO_ROOT = Path(__file__).resolve().parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from pipeline.python.data import DirectoryShardDataset, create_data_loader
from pipeline.python.models import SparseBucketNNUE
from pipeline.python.train import WDLCriterion, WDLAccuracy


DEFAULT_KING_BUCKET_MAP = (
    0, 0, 0, 1, 1, 2, 2, 2,
    0, 0, 1, 1, 1, 1, 2, 2,
    0, 3, 3, 3, 4, 4, 4, 2,
    3, 3, 3, 3, 4, 4, 4, 4,
    3, 3, 3, 3, 4, 4, 4, 4,
    3, 3, 3, 3, 4, 4, 4, 4,
    3, 3, 3, 3, 4, 4, 4, 4,
    3, 3, 3, 3, 4, 4, 4, 4,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Evaluate ceres-net style NNUE on shard WDL targets")
    parser.add_argument("--net", default="src/ceres-net.bin", help="Path to engine NNUE binary")
    parser.add_argument("--shards", default="shards/val", help="Directory containing validation shards")
    parser.add_argument("--device", default="cuda" if torch.cuda.is_available() else "cpu")
    parser.add_argument("--batch-size", type=int, default=8192)
    parser.add_argument("--num-workers", type=int, default=0)
    parser.add_argument("--hidden-size", type=int, default=1024)
    parser.add_argument("--num-output-buckets", type=int, default=8)
    parser.add_argument("--output-bucket-divisor", type=int, default=4)
    parser.add_argument("--progress-every", type=int, default=1_000_000, help="Print progress every N records")
    parser.add_argument("--max-records", type=int, default=0, help="Optional cap for quick spot checks")
    return parser.parse_args()


def main() -> None:
    args = parse_args()

    dataset = DirectoryShardDataset(args.shards, preload=False)
    if len(dataset) == 0:
        raise ValueError(f"No shard records found in {args.shards}")

    loader = create_data_loader(
        dataset,
        batch_size=args.batch_size,
        shuffle=False,
        num_workers=args.num_workers,
        pin_memory=args.device.startswith("cuda"),
    )

    model = SparseBucketNNUE.load_from_engine_bin(
        args.net,
        hidden_size=args.hidden_size,
        king_bucket_map=DEFAULT_KING_BUCKET_MAP,
        num_output_buckets=args.num_output_buckets,
        output_bucket_divisor=args.output_bucket_divisor,
    )
    model.to(args.device)
    model.eval()

    criterion = WDLCriterion()
    metric = WDLAccuracy()

    total_records = 0
    total_wdl_mse = 0.0
    total_wdl_accuracy = 0.0
    total_target = min(len(dataset), args.max_records) if args.max_records > 0 else len(dataset)
    progress_bar = tqdm(total=total_target, unit="pos", desc="Evaluating") if tqdm is not None else None

    with torch.no_grad():
        for batch in loader:
            batch = {key: value.to(args.device, non_blocking=True) for key, value in batch.items()}
            predictions = model(batch)

            batch_size = int(batch["stm"].shape[0])
            total_records += batch_size
            total_wdl_mse += float(criterion(predictions, batch).item()) * batch_size
            total_wdl_accuracy += float(metric(predictions, batch).item()) * batch_size
            running_mse = total_wdl_mse / max(total_records, 1)
            running_accuracy = total_wdl_accuracy / max(total_records, 1)

            if progress_bar is not None:
                progress_bar.update(batch_size)
                progress_bar.set_postfix(
                    wdl_mse=f"{running_mse:.6f}",
                    wdl_acc=f"{running_accuracy:.4f}",
                )
            elif args.progress_every > 0 and total_records % args.progress_every < batch_size:
                print(f"Processed {total_records:,} / {len(dataset):,} records...", file=sys.stderr)
                print(
                    f"  running wdl_mse={running_mse:.6f} wdl_accuracy={running_accuracy:.4f}",
                    file=sys.stderr,
                )

            if 0 < args.max_records <= total_records:
                break

    if progress_bar is not None:
        progress_bar.close()

    results = {
        "net": args.net,
        "shards": args.shards,
        "device": args.device,
        "records": total_records,
        "wdl_mse": total_wdl_mse / max(total_records, 1),
        "wdl_accuracy": total_wdl_accuracy / max(total_records, 1),
    }

    print(json.dumps(results, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
