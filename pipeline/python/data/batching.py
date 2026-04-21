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
