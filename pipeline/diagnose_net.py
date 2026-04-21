#!/usr/bin/env python3
"""Diagnose NNUE validation behavior and collapse toward drawish predictions."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

import torch
from tqdm.auto import tqdm

REPO_ROOT = Path(__file__).resolve().parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from pipeline.python.data import DirectoryShardDataset, EMPTY, create_data_loader
from pipeline.python.models import SparseBucketNNUE
from pipeline.python.train import EvalMAE, WDLCriterion, WDLAccuracy


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

PIECE_MAP = {
    "P": 0, "N": 1, "B": 2, "R": 3, "Q": 4, "K": 5,
    "p": 6, "n": 7, "b": 8, "r": 9, "q": 10, "k": 11,
}

SANITY_FENS = [
    ("8/4k3/8/8/8/8/4K3/4R3 w - - 0 1", "KRK, clearly winning for white"),
    ("8/4k3/8/8/8/8/4K3/4Q3 w - - 0 1", "KQK, clearly winning for white"),
    ("8/4k3/8/8/8/8/4K3/8 w - - 0 1", "Bare kings, should be near draw"),
    ("4r3/4k3/8/8/8/8/4K3/8 w - - 0 1", "White to move down a rook, clearly bad"),
]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Diagnose NNUE validation behavior and draw-collapse")
    parser.add_argument("--net", default="src/ceres-net.bin", help="Path to engine NNUE binary")
    parser.add_argument("--shards", default="shards/val", help="Directory containing validation shards")
    parser.add_argument("--device", default="cuda" if torch.cuda.is_available() else "cpu")
    parser.add_argument("--batch-size", type=int, default=8192)
    parser.add_argument("--num-workers", type=int, default=0)
    parser.add_argument("--hidden-size", type=int, default=1024)
    parser.add_argument("--num-output-buckets", type=int, default=8)
    parser.add_argument("--output-bucket-divisor", type=int, default=4)
    parser.add_argument("--max-records", type=int, default=0, help="Optional cap for quick spot checks")
    parser.add_argument("--collapse-window", type=float, default=0.05, help="Window around 0.5 to count as draw-collapse")
    parser.add_argument("--hist-bins", type=int, default=10, help="Number of histogram bins over [0, 1]")
    return parser.parse_args()


def pack_fen(fen: str) -> tuple[torch.Tensor, torch.Tensor]:
    board_part, stm, *_ = fen.split()
    squares = [EMPTY] * 64
    rank = 7
    file = 0

    for char in board_part:
        if char == "/":
            rank -= 1
            file = 0
        elif char.isdigit():
            file += int(char)
        else:
            squares[rank * 8 + file] = PIECE_MAP[char]
            file += 1

    packed = []
    for index in range(0, 64, 2):
        packed.append((squares[index] & 0x0F) | ((squares[index + 1] & 0x0F) << 4))

    stm_tensor = torch.tensor([0 if stm == "w" else 1], dtype=torch.long)
    packed_tensor = torch.tensor([packed], dtype=torch.uint8)
    return packed_tensor, stm_tensor


def evaluate_sanity_positions(model: SparseBucketNNUE, device: str) -> list[dict[str, float | str]]:
    results = []
    with torch.no_grad():
        for fen, note in SANITY_FENS:
            packed_boards, stm = pack_fen(fen)
            packed_boards = packed_boards.to(device)
            stm = stm.to(device)
            predictions = model({"packed_boards": packed_boards, "stm": stm})
            win_prob = float(torch.sigmoid(predictions["value_logit"])[0].item())
            results.append({
                "fen": fen,
                "note": note,
                "value_cp": float(predictions["value_cp"][0].item()),
                "value_logit": float(predictions["value_logit"][0].item()),
                "win_prob": win_prob,
            })
    return results


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
    accuracy = WDLAccuracy()
    eval_mae = EvalMAE()

    total_records = 0
    total_wdl_mse = 0.0
    total_wdl_accuracy = 0.0
    total_eval_mae = 0.0
    total_pred_sum = 0.0
    total_cp_sum = 0.0
    class_pred_sum = [0.0, 0.0, 0.0]
    class_counts = [0, 0, 0]
    hist_counts = torch.zeros(args.hist_bins, dtype=torch.long)

    lower = 0.5 - args.collapse_window
    upper = 0.5 + args.collapse_window
    collapse_count = 0

    total_target = min(len(dataset), args.max_records) if args.max_records > 0 else len(dataset)
    progress_bar = tqdm(total=total_target, unit="pos", desc="Diagnosing")

    with torch.no_grad():
        for batch in loader:
            batch = {key: value.to(args.device, non_blocking=True) for key, value in batch.items()}
            predictions = model(batch)
            win_prob = torch.sigmoid(predictions["value_logit"])

            batch_size = int(batch["stm"].shape[0])
            total_records += batch_size
            total_wdl_mse += float(criterion(predictions, batch).item()) * batch_size
            total_wdl_accuracy += float(accuracy(predictions, batch).item()) * batch_size
            total_eval_mae += float(eval_mae(predictions, batch).item()) * batch_size
            total_pred_sum += float(win_prob.sum().item())
            total_cp_sum += float(predictions["value_cp"].sum().item())

            collapse_count += int(((win_prob >= lower) & (win_prob <= upper)).sum().item())

            scaled = torch.clamp((win_prob * args.hist_bins).to(torch.long), min=0, max=args.hist_bins - 1)
            hist_counts += torch.bincount(scaled.cpu(), minlength=args.hist_bins)

            for class_index in range(3):
                mask = batch["wdl"] == class_index
                count = int(mask.sum().item())
                if count == 0:
                    continue
                class_counts[class_index] += count
                class_pred_sum[class_index] += float(win_prob[mask].sum().item())

            running = {
                "wdl_mse": total_wdl_mse / total_records,
                "wdl_acc": total_wdl_accuracy / total_records,
                "mean_p": total_pred_sum / total_records,
                "mid_frac": collapse_count / total_records,
            }
            progress_bar.update(batch_size)
            progress_bar.set_postfix({key: f"{value:.4f}" for key, value in running.items()})

            if 0 < args.max_records <= total_records:
                break

    progress_bar.close()

    sanity = evaluate_sanity_positions(model, args.device)

    histogram = []
    for index, count in enumerate(hist_counts.tolist()):
        left = index / args.hist_bins
        right = (index + 1) / args.hist_bins
        histogram.append({
            "range": f"[{left:.2f}, {right:.2f}{')' if index + 1 < args.hist_bins else ']'}",
            "count": count,
            "fraction": count / max(total_records, 1),
        })

    per_class = []
    class_names = ["loss", "draw", "win"]
    for class_index, name in enumerate(class_names):
        per_class.append({
            "class": name,
            "count": class_counts[class_index],
            "mean_predicted_win_prob": class_pred_sum[class_index] / max(class_counts[class_index], 1),
        })

    summary = {
        "net": args.net,
        "shards": args.shards,
        "device": args.device,
        "records": total_records,
        "wdl_mse": total_wdl_mse / max(total_records, 1),
        "wdl_accuracy": total_wdl_accuracy / max(total_records, 1),
        "eval_mae": total_eval_mae / max(total_records, 1),
        "mean_predicted_win_prob": total_pred_sum / max(total_records, 1),
        "mean_value_cp": total_cp_sum / max(total_records, 1),
        "fraction_near_0_5": collapse_count / max(total_records, 1),
        "collapse_window": args.collapse_window,
        "per_class_mean_prediction": per_class,
        "prediction_histogram": histogram,
        "sanity_positions": sanity,
    }

    print(json.dumps(summary, indent=2))


if __name__ == "__main__":
    main()
