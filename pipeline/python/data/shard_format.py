"""Binary shard format constants for packed-board shards."""

from __future__ import annotations

import numpy as np

SHARD_MAGIC = b"ALTR"
SHARD_VERSION = 2
PIECE_NIBBLE_COUNT = 64
PACKED_BOARD_BYTES = 32
RECORD_SIZE = 36

INPUT_FEATURES = 768
EMPTY = 12

HEADER_DTYPE = np.dtype([
    ("magic", "S4"),
    ("version", "<u2"),
    ("record_count", "<u4"),
    ("record_size", "<u2"),
    ("reserved", "u1", 4),
])

RECORD_DTYPE = np.dtype([
    ("packed_board", "u1", PACKED_BOARD_BYTES),
    ("stm", "u1"),
    ("wdl", "u1"),
    ("eval", "<i2"),
])
