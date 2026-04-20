"""Packed-board shard data pipeline for Altair NNUE training."""

from .feature_extractor import (
    extract_input_buckets,
    extract_output_buckets,
    extract_perspective_features,
    extract_stm_ntm_features,
    unpack_packed_boards_torch,
)
from .shard_format import EMPTY, INPUT_FEATURES, PIECE_NIBBLE_COUNT, RECORD_DTYPE, SHARD_MAGIC, SHARD_VERSION
from .shard_reader import list_shards, load_manifest, read_shard_records
from .shard_dataset import DirectoryShardDataset, ShardListDataset, create_data_loader
from .splits import shard_paths_from_directories, shard_paths_from_directory

__all__ = [
    "EMPTY",
    "INPUT_FEATURES",
    "PIECE_NIBBLE_COUNT",
    "RECORD_DTYPE",
    "SHARD_MAGIC",
    "SHARD_VERSION",
    "extract_perspective_features",
    "extract_stm_ntm_features",
    "extract_input_buckets",
    "extract_output_buckets",
    "list_shards",
    "load_manifest",
    "read_shard_records",
    "DirectoryShardDataset",
    "ShardListDataset",
    "create_data_loader",
    "shard_paths_from_directory",
    "shard_paths_from_directories",
    "unpack_packed_boards_torch",
]
