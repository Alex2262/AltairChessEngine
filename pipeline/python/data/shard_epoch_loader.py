"""Shard-wise training loader that prepares whole shard chunks at once."""

from __future__ import annotations

import math
import queue
import random
import threading
from pathlib import Path
from typing import Sequence

import numpy as np
import torch

from .batching import records_to_batch
from .shard_reader import list_shards, read_shard_records


class ShardEpochLoader:
    def __init__(
            self,
            shard_paths: Sequence[str | Path],
            batch_size: int,
            prepare_batch_fn=None,
            shuffle_shards: bool = True,
            shuffle_records: bool = True,
            seed: int = 0,
            prepare_chunk_size: int = 262144,
            prefetch_chunks: int = 0,
    ):
        self.shard_paths = [Path(path) for path in shard_paths]
        self.batch_size = batch_size
        self.prepare_batch_fn = prepare_batch_fn
        self.shuffle_shards = shuffle_shards
        self.shuffle_records = shuffle_records
        self.seed = seed
        self.prepare_chunk_size = prepare_chunk_size
        self.prefetch_chunks = prefetch_chunks
        self._epoch = 0
        self._shard_sizes = [len(read_shard_records(path, copy=False)) for path in self.shard_paths]
        self._total_records = sum(self._shard_sizes)

    def __len__(self) -> int:
        return math.ceil(self._total_records / self.batch_size)

    @property
    def total_records(self) -> int:
        return self._total_records

    def __iter__(self):
        chunk_iterator = self._iter_prepared_chunks()
        if self.prefetch_chunks > 0:
            chunk_iterator = _PrefetchedChunkIterator(chunk_iterator, self.prefetch_chunks)

        for prepared in chunk_iterator:
            chunk_records_count = self._batch_size_from_prepared(prepared)
            for batch_start in range(0, chunk_records_count, self.batch_size):
                batch_stop = min(batch_start + self.batch_size, chunk_records_count)
                yield self._slice_prepared(prepared, batch_start, batch_stop)

    def _iter_prepared_chunks(self):
        rng = random.Random(self.seed + self._epoch)
        self._epoch += 1

        shard_paths = list(self.shard_paths)
        if self.shuffle_shards:
            rng.shuffle(shard_paths)

        for shard_path in shard_paths:
            records = read_shard_records(shard_path, copy=False)
            num_records = len(records)
            if num_records == 0:
                continue

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
                yield prepared

    @staticmethod
    def _batch_size_from_prepared(prepared: dict) -> int:
        for value in prepared.values():
            if isinstance(value, torch.Tensor) and value.ndim > 0:
                return int(value.shape[0])
        return 0

    @staticmethod
    def _slice_prepared(prepared: dict, start: int, stop: int) -> dict:
        sliced = {}
        for key, value in prepared.items():
            if isinstance(value, torch.Tensor) and value.ndim > 0:
                sliced[key] = value[start:stop]
            else:
                sliced[key] = value
        return sliced


def create_shard_epoch_loader(
        shard_paths: Sequence[str | Path] | str | Path,
        batch_size: int,
        prepare_batch_fn=None,
        shuffle_shards: bool = True,
        shuffle_records: bool = True,
        seed: int = 0,
        prepare_chunk_size: int = 262144,
        prefetch_chunks: int = 0,
) -> ShardEpochLoader:
    if isinstance(shard_paths, (str, Path)):
        shard_paths = list_shards(shard_paths)
    return ShardEpochLoader(
        shard_paths=shard_paths,
        batch_size=batch_size,
        prepare_batch_fn=prepare_batch_fn,
        shuffle_shards=shuffle_shards,
        shuffle_records=shuffle_records,
        seed=seed,
        prepare_chunk_size=prepare_chunk_size,
        prefetch_chunks=prefetch_chunks,
    )


_END = object()


class _PrefetchedChunkIterator:
    def __init__(self, source_iterator, prefetch_chunks: int):
        self.source_iterator = source_iterator
        self.prefetch_chunks = max(prefetch_chunks, 1)

    def __iter__(self):
        result_queue: queue.Queue = queue.Queue(maxsize=self.prefetch_chunks)

        def worker():
            try:
                for item in self.source_iterator:
                    result_queue.put(item)
            except BaseException as exc:  # pragma: no cover - propagated to consumer
                result_queue.put(exc)
            finally:
                result_queue.put(_END)

        thread = threading.Thread(target=worker, daemon=True)
        thread.start()

        while True:
            item = result_queue.get()
            if item is _END:
                break
            if isinstance(item, BaseException):
                raise item
            yield item
