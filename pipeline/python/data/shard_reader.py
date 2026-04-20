"""Low-level shard readers for packed-board shards."""

from __future__ import annotations

import json
from pathlib import Path
from typing import Iterable, List

import numpy as np

from .shard_format import HEADER_DTYPE, RECORD_DTYPE, RECORD_SIZE, SHARD_MAGIC, SHARD_VERSION


def load_manifest(manifest_path: str | Path) -> dict:
    with open(manifest_path, "r", encoding="utf-8") as handle:
        return json.load(handle)


def list_shards(directory: str | Path) -> List[Path]:
    return sorted(Path(directory).glob("shard_*.bin"))


def _validate_header(header: np.ndarray, path: Path) -> int:
    if header["magic"].item() != SHARD_MAGIC:
        raise ValueError(f"Invalid shard magic in {path}")
    if int(header["version"].item()) != SHARD_VERSION:
        raise ValueError(f"Unsupported shard version in {path}: {int(header['version'].item())}")
    record_size = int(header["record_size"].item())
    if record_size != RECORD_SIZE:
        raise ValueError(f"Unexpected record size in {path}: {record_size}")
    return int(header["record_count"].item())


def read_shard_records(path: str | Path, copy: bool = False) -> np.ndarray:
    shard_path = Path(path)
    with shard_path.open("rb") as handle:
        header = np.fromfile(handle, dtype=HEADER_DTYPE, count=1)
        if header.size != 1:
            raise ValueError(f"Missing shard header in {shard_path}")
        record_count = _validate_header(header[0], shard_path)

    records = np.memmap(shard_path, dtype=RECORD_DTYPE, mode="r", offset=HEADER_DTYPE.itemsize, shape=(record_count,))
    return np.array(records) if copy else records


def concatenate_shards(paths: Iterable[str | Path]) -> np.ndarray:
    arrays = [np.array(read_shard_records(path), copy=True) for path in paths]
    if not arrays:
        return np.empty((0,), dtype=RECORD_DTYPE)
    return np.concatenate(arrays, axis=0)
