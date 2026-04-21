"""Shard-wise IterableDataset and DataLoader helpers."""

from __future__ import annotations

import math
import random
from pathlib import Path
from typing import Callable, Sequence

import numpy as np
from torch.utils.data import DataLoader, IterableDataset, get_worker_info

from .batching import records_to_batch
from .shard_reader import list_shards, read_shard_records


def _identity_collate(item):
    return item


class ShardIterableDataset(IterableDataset):
    def __init__(
            self,
            shard_paths: Sequence[str | Path],
            batch_size: int,
            prepare_batch_fn: Callable[[dict], dict] | None = None,
            shuffle_shards: bool = True,
            shuffle_records: bool = True,
            seed: int = 0,
            prepare_chunk_size: int = 262144,
    ):
        super().__init__()
        self.shard_paths = [Path(path) for path in shard_paths]
        self.batch_size = batch_size
        self.prepare_batch_fn = prepare_batch_fn
        self.shuffle_shards = shuffle_shards
        self.shuffle_records = shuffle_records
        self.seed = seed
        self.prepare_chunk_size = prepare_chunk_size
        self._epoch = 0
        self._shard_sizes = [len(read_shard_records(path, copy=False)) for path in self.shard_paths]
        self._total_records = sum(self._shard_sizes)

    def __len__(self) -> int:
        return math.ceil(self._total_records / self.batch_size)

    @property
    def total_records(self) -> int:
        return self._total_records

    def __iter__(self):
        worker_info = get_worker_info()
        worker_id = worker_info.id if worker_info is not None else 0
        num_workers = worker_info.num_workers if worker_info is not None else 1

        epoch = self._epoch
        self._epoch += 1
        rng = random.Random(self.seed + epoch)

        shard_paths = list(self.shard_paths)
        if self.shuffle_shards:
            rng.shuffle(shard_paths)

        worker_shards = shard_paths[worker_id::num_workers]
        for shard_path in worker_shards:
            yield from self._iter_shard_batches(shard_path, rng)

    def _iter_shard_batches(self, shard_path: Path, rng: random.Random):
        records = read_shard_records(shard_path, copy=False)
        num_records = len(records)
        if num_records == 0:
            return

        shard_indices = np.arange(num_records, dtype=np.int64)
        if self.shuffle_records:
            rng.shuffle(shard_indices)

        chunk_size = self.prepare_chunk_size if self.prepare_chunk_size > 0 else num_records
        chunk_size = max(chunk_size, self.batch_size)

        for start in range(0, num_records, chunk_size):
            stop = min(start + chunk_size, num_records)
            chunk_indices = shard_indices[start:stop]
            chunk_records = records[chunk_indices]
            prepared = records_to_batch(chunk_records)
            if self.prepare_batch_fn is not None:
                prepared = self.prepare_batch_fn(prepared)

            chunk_batch_size = self._batch_size_from_prepared(prepared)
            for batch_start in range(0, chunk_batch_size, self.batch_size):
                batch_stop = min(batch_start + self.batch_size, chunk_batch_size)
                yield self._slice_prepared(prepared, batch_start, batch_stop)

    @staticmethod
    def _batch_size_from_prepared(prepared: dict) -> int:
        for value in prepared.values():
            if hasattr(value, "shape") and len(value.shape) > 0:
                return int(value.shape[0])
        return 0

    @staticmethod
    def _slice_prepared(prepared: dict, start: int, stop: int) -> dict:
        sliced = {}
        for key, value in prepared.items():
            if hasattr(value, "shape") and len(value.shape) > 0:
                sliced[key] = value[start:stop]
            else:
                sliced[key] = value
        return sliced


def create_shard_loader(
        shard_paths: Sequence[str | Path] | str | Path,
        batch_size: int,
        prepare_batch_fn: Callable[[dict], dict] | None = None,
        shuffle_shards: bool = True,
        shuffle_records: bool = True,
        seed: int = 0,
        prepare_chunk_size: int = 262144,
        num_workers: int = 0,
        pin_memory: bool = True,
        persistent_workers: bool = True,
        prefetch_factor: int | None = 2,
) -> DataLoader:
    if isinstance(shard_paths, (str, Path)):
        shard_paths = list_shards(shard_paths)

    dataset = ShardIterableDataset(
        shard_paths=shard_paths,
        batch_size=batch_size,
        prepare_batch_fn=prepare_batch_fn,
        shuffle_shards=shuffle_shards,
        shuffle_records=shuffle_records,
        seed=seed,
        prepare_chunk_size=prepare_chunk_size,
    )

    loader_kwargs = {
        "dataset": dataset,
        "batch_size": None,
        "num_workers": num_workers,
        "pin_memory": pin_memory,
        "collate_fn": _identity_collate,
    }
    if num_workers > 0:
        loader_kwargs["persistent_workers"] = persistent_workers
        if prefetch_factor is not None:
            loader_kwargs["prefetch_factor"] = prefetch_factor

    loader = DataLoader(**loader_kwargs)
    loader.total_records = dataset.total_records
    return loader
