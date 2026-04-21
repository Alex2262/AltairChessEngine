#!/usr/bin/env python3
"""Evaluate an engine NNUE binary on a shard directory using WDL metrics."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

import torch
from tqdm import tqdm

REPO_ROOT = Path(__file__).resolve().parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from pipeline.python.data import create_shard_loader
from pipeline.python.models import SparseBucketNNUE
from pipeline.python.train import WDLCriterion, WDLAccuracy, EvalMAE

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
    parser.add_argument("--hidden-size", type=int, default=1024)
    parser.add_argument("--num-output-buckets", type=int, default=8)
    parser.add_argument("--output-bucket-divisor", type=int, default=4)
    parser.add_argument("--max-records", type=int, default=0, help="Optional cap for quick spot checks")
    parser.add_argument("--prepare-chunk-size", type=int, default=2 ** 18)
    parser.add_argument("--num-workers", type=int, default=0)
    parser.add_argument("--prefetch-factor", type=int, default=2)
    return parser.parse_args()


def main() -> None:
    args = parse_args()

    model = SparseBucketNNUE.load_from_engine_bin(
        args.net,
        hidden_size=args.hidden_size,
        king_bucket_map=DEFAULT_KING_BUCKET_MAP,
        num_output_buckets=args.num_output_buckets,
        output_bucket_divisor=args.output_bucket_divisor,
    )
    model.to(args.device)
    model.eval()

    loader = create_shard_loader(
        args.shards,
        batch_size=args.batch_size,
        prepare_batch_fn=model.create_batch_preparer(),
        shuffle_shards=False,
        shuffle_records=False,
        prepare_chunk_size=args.prepare_chunk_size,
        num_workers=args.num_workers,
        pin_memory=args.device.startswith("cuda"),
        persistent_workers=True,
        prefetch_factor=args.prefetch_factor,
    )
    if loader.total_records == 0:
        raise ValueError(f"No shard records found in {args.shards}")

    criteria = [WDLCriterion()]
    metrics = [WDLAccuracy(), EvalMAE()]

    total_records = 0

    criterion_totals = {criterion.name: 0.0 for criterion in criteria}
    metric_totals = {metric.name: 0.0 for metric in metrics}

    total_target = min(loader.total_records, args.max_records) if args.max_records > 0 else loader.total_records
    progress_bar = tqdm(total=total_target, unit="pos", desc="Evaluating")

    total_batches = 0

    with torch.no_grad():
        for batch in loader:
            batch = {key: value.to(args.device, non_blocking=True) for key, value in batch.items()}
            predictions = model(batch)

            batch_size = int(batch["stm"].shape[0])
            total_records += batch_size
            total_batches += 1

            for criterion in criteria:
                value = float(criterion(predictions, batch).detach().cpu().item())
                criterion_totals[criterion.name] += value

            for metric in metrics:
                value = float(metric(predictions, batch).detach().cpu().item())
                metric_totals[metric.name] += value

            avg_criteria = {
                name: value / total_batches for name, value in criterion_totals.items()
            }
            avg_metrics = {
                name: value / total_batches for name, value in metric_totals.items()
            }

            postfix = {}
            for name, value in avg_criteria.items():
                postfix[name] = f"{value:.4f}"
            for name, value in avg_metrics.items():
                postfix[name] = f"{value:.4f}"

            progress_bar.update(batch_size)
            progress_bar.set_postfix(postfix)

            if 0 < args.max_records <= total_records:
                break

    progress_bar.close()

if __name__ == "__main__":
    main()
