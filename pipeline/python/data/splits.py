"""Helpers for manually selecting training/validation/test shard pools."""

from __future__ import annotations

from pathlib import Path
from typing import Iterable

from .shard_reader import list_shards


def shard_paths_from_directory(directory: str | Path) -> list[Path]:
    return list_shards(directory)


def shard_paths_from_directories(directories: Iterable[str | Path]) -> list[Path]:
    paths: list[Path] = []
    for directory in directories:
        paths.extend(list_shards(directory))
    return sorted(paths)
