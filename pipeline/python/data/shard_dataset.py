"""Torch datasets for packed-board Altair shards."""

from __future__ import annotations

from pathlib import Path
from typing import Iterable, Sequence

import numpy as np
import torch
from torch.utils.data import DataLoader, Dataset

from .shard_reader import list_shards, read_shard_records
from .shard_format import RECORD_DTYPE


class _BaseShardDataset(Dataset):
    def __init__(self, shard_paths: Sequence[str | Path], preload: bool = False):
        self.shard_paths = [Path(path) for path in shard_paths]
        self.preload = preload
        self._records_cache = None
        self._records_per_shard = []
        self._cumulative = [0]

        for path in self.shard_paths:
            records = read_shard_records(path, copy=preload)
            self._records_per_shard.append(records)
            self._cumulative.append(self._cumulative[-1] + len(records))

        if preload:
            if self._records_per_shard:
                self._records_cache = np.concatenate([np.asarray(records) for records in self._records_per_shard], axis=0)
            else:
                self._records_cache = np.empty((0,), dtype=RECORD_DTYPE)

    def __len__(self) -> int:
        return self._cumulative[-1]

    def __getitem__(self, index: int) -> dict:
        if self._records_cache is not None:
            record = self._records_cache[index]
        else:
            shard_index = int(np.searchsorted(self._cumulative, index, side="right") - 1)
            local_index = index - self._cumulative[shard_index]
            record = self._records_per_shard[shard_index][local_index]

        return {
            "packed_board": np.asarray(record["packed_board"], dtype=np.uint8),
            "stm": np.uint8(record["stm"]),
            "wdl": np.uint8(record["wdl"]),
            "eval": np.int16(record["eval"]),
        }


class DirectoryShardDataset(_BaseShardDataset):
    def __init__(self, directory: str | Path, preload: bool = False):
        super().__init__(list_shards(directory), preload=preload)


class ShardListDataset(_BaseShardDataset):
    def __init__(self, shard_paths: Iterable[str | Path], preload: bool = False):
        super().__init__(list(shard_paths), preload=preload)


def collate_records(batch: list[dict]) -> dict:
    packed_boards = torch.tensor(np.stack([sample["packed_board"] for sample in batch]), dtype=torch.uint8)
    stm = torch.tensor([int(sample["stm"]) for sample in batch], dtype=torch.long)
    wdl = torch.tensor([int(sample["wdl"]) for sample in batch], dtype=torch.long)
    evals = torch.tensor([int(sample["eval"]) for sample in batch], dtype=torch.float32)
    return {"packed_boards": packed_boards, "stm": stm, "wdl": wdl, "eval": evals}


def create_data_loader(dataset: Dataset,
                       batch_size: int = 8192,
                       shuffle: bool = True,
                       num_workers: int = 0,
                       pin_memory: bool = True) -> DataLoader:
    kwargs = {
        "dataset": dataset,
        "batch_size": batch_size,
        "shuffle": shuffle,
        "num_workers": num_workers,
        "pin_memory": pin_memory,
        "collate_fn": collate_records,
    }
    if num_workers > 0:
        kwargs["persistent_workers"] = True
    return DataLoader(**kwargs)
