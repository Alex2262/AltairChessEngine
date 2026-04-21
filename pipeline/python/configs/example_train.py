"""Example config for pipeline/train.py."""

from __future__ import annotations

import torch

from pipeline.python.data import DirectoryShardDataset, create_data_loader
from pipeline.python.models import SparseBucketNNUE
from pipeline.python.train import (
    BlendedValueObjective,
    EvalMAE,
    LinearInterpolationSchedule,
    TrainerConfig,
    TrainingRun,
    WDLCriterion,
    WDLAccuracy,
)

KING_BUCKET_MAP = (
    0, 0, 0, 1, 1, 2, 2, 2,
    0, 0, 1, 1, 1, 1, 2, 2,
    0, 3, 3, 3, 4, 4, 4, 2,
    3, 3, 3, 3, 4, 4, 4, 4,
    3, 3, 3, 3, 4, 4, 4, 4,
    3, 3, 3, 3, 4, 4, 4, 4,
    3, 3, 3, 3, 4, 4, 4, 4,
    3, 3, 3, 3, 4, 4, 4, 4,
)

NUM_OUTPUT_BUCKETS = 8
OUTPUT_BUCKET_DIVISOR = 4  # 32 / 8

EPOCHS = 5
BATCH_SIZE = 65536
NUM_WORKERS = 4

HIDDEN_SIZE = 1024

LR = 1e-3
WDL_PROPORTION_START = 0.75
WDL_PROPORTION_END = 0.75
EVAL_SCALE = 400.0


def build_run() -> TrainingRun:
    train_dataset = DirectoryShardDataset("shards/train", preload=False)
    val_dataset = DirectoryShardDataset("shards/val", preload=False)

    train_loader = create_data_loader(
        train_dataset,
        batch_size=BATCH_SIZE,
        shuffle=True,
        num_workers=NUM_WORKERS,
        pin_memory=True,
    )
    val_loader = create_data_loader(
        val_dataset,
        batch_size=BATCH_SIZE,
        shuffle=False,
        num_workers=NUM_WORKERS,
        pin_memory=True,
    )

    model = SparseBucketNNUE(
        hidden_size=HIDDEN_SIZE,
        king_bucket_map=KING_BUCKET_MAP,
        num_output_buckets=NUM_OUTPUT_BUCKETS,
        output_bucket_divisor=OUTPUT_BUCKET_DIVISOR,
    )
    optimizer = torch.optim.AdamW(model.parameters(), lr=LR)
    objective = BlendedValueObjective(
        wdl_schedule=LinearInterpolationSchedule(WDL_PROPORTION_START, WDL_PROPORTION_END),
        eval_scale=EVAL_SCALE,
    )

    return TrainingRun(
        name="example_sparse_bucket_nnue",
        train_loader=train_loader,
        val_loader=val_loader,
        model=model,
        optimizer=optimizer,
        objective=objective,
        criteria=[WDLCriterion()],
        metrics=[WDLAccuracy(), EvalMAE()],
        trainer_config=TrainerConfig(
            epochs=EPOCHS,
            device="cuda",
            grad_clip_norm=1.0,
            log_every=100,
            checkpoint_dir=None,
        ),
        export_engine_path="checkpoints/example_sparse_bucket_nnue.bin",
    )
