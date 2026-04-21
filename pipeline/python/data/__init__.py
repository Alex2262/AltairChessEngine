"""Packed-board shard data pipeline for Altair NNUE training."""

from .batching import records_to_batch
from .feature_extractor import (
    extract_input_buckets,
    extract_output_buckets,
    extract_perspective_features,
    extract_stm_ntm_compact_features,
    extract_stm_ntm_features,
    unpack_packed_boards_torch,
)
from .shard_format import EMPTY, INPUT_FEATURES, PIECE_NIBBLE_COUNT, RECORD_DTYPE, SHARD_MAGIC, SHARD_VERSION
from .shard_loader import ShardIterableDataset, create_shard_loader
from .shard_reader import list_shards, load_manifest, read_shard_records
from .splits import shard_paths_from_directories, shard_paths_from_directory

__all__ = [
    "EMPTY",
    "INPUT_FEATURES",
    "PIECE_NIBBLE_COUNT",
    "RECORD_DTYPE",
    "SHARD_MAGIC",
    "SHARD_VERSION",
    "ShardIterableDataset",
    "records_to_batch",
    "extract_perspective_features",
    "extract_stm_ntm_features",
    "extract_stm_ntm_compact_features",
    "extract_input_buckets",
    "extract_output_buckets",
    "list_shards",
    "load_manifest",
    "read_shard_records",
    "create_shard_loader",
    "shard_paths_from_directory",
    "shard_paths_from_directories",
    "unpack_packed_boards_torch",
]
