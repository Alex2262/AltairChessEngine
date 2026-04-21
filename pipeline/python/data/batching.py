"""Batch conversion helpers for packed-board shard records."""

from __future__ import annotations

import numpy as np
import torch


def records_to_batch(records: np.ndarray) -> dict:
    packed_boards = torch.from_numpy(np.ascontiguousarray(records["packed_board"]))
    stm = torch.from_numpy(records["stm"].astype(np.int64, copy=False))
    wdl = torch.from_numpy(records["wdl"].astype(np.int64, copy=False))
    evals = torch.from_numpy(records["eval"].astype(np.float32, copy=False))
    return {"packed_boards": packed_boards, "stm": stm, "wdl": wdl, "eval": evals}


def batch_to_numpy(batch: dict) -> dict:
    numpy_batch = {}
    for key, value in batch.items():
        if isinstance(value, torch.Tensor):
            numpy_batch[key] = value.detach().cpu().numpy()
        else:
            numpy_batch[key] = value
    return numpy_batch


def ensure_torch_batch(batch: dict) -> dict:
    torch_batch = {}
    for key, value in batch.items():
        if isinstance(value, torch.Tensor):
            torch_batch[key] = value
        elif isinstance(value, np.ndarray):
            torch_batch[key] = torch.from_numpy(value)
        else:
            torch_batch[key] = value
    return torch_batch
