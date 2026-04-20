"""Torch-native feature extraction from packed boards."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Sequence

import numpy as np
import torch

from .shard_format import EMPTY, INPUT_FEATURES


def unpack_boards(packed_boards: np.ndarray) -> np.ndarray:
    """Unpack `(batch, 32)` packed nibble boards into `(batch, 64)` uint8 boards."""
    low = packed_boards & 0x0F
    high = packed_boards >> 4
    boards = np.empty((packed_boards.shape[0], 64), dtype=np.uint8)
    boards[:, 0::2] = low
    boards[:, 1::2] = high
    return boards


def unpack_packed_boards_torch(packed_boards: torch.Tensor) -> torch.Tensor:
    """Unpack `(batch, 32)` packed nibble boards into `(batch, 64)` long boards."""
    packed_boards = packed_boards.to(torch.long)
    batch_size = packed_boards.shape[0]
    boards = torch.empty(batch_size, 64, dtype=torch.long, device=packed_boards.device)
    boards[:, 0::2] = packed_boards & 0x0F
    boards[:, 1::2] = packed_boards >> 4
    return boards


@dataclass
class PerspectiveFeatureBatch:
    white_padded: torch.Tensor
    black_padded: torch.Tensor
    counts: torch.Tensor


@dataclass
class SideFeatureBatch:
    stm_indices: torch.Tensor
    stm_offsets: torch.Tensor
    ntm_indices: torch.Tensor
    ntm_offsets: torch.Tensor
    counts: torch.Tensor
    stm_is_white: torch.Tensor


@dataclass
class InputBucketBatch:
    white: torch.Tensor
    black: torch.Tensor
    stm: torch.Tensor
    ntm: torch.Tensor


def _perspective_feature_indices(boards: torch.Tensor) -> tuple[torch.Tensor, torch.Tensor, torch.Tensor]:
    valid_mask = boards.ne(EMPTY)
    counts = valid_mask.sum(dim=1, dtype=torch.long)
    if torch.any(counts > 32):
        raise ValueError("Board has more than 32 active pieces")

    batch_size = boards.shape[0]
    device = boards.device
    squares = torch.arange(64, device=device, dtype=torch.long).unsqueeze(0).expand(batch_size, -1)
    piece_type = boards.remainder(6)
    color = torch.div(boards, 6, rounding_mode="floor").clamp(0, 1)

    white_indices = color * 384 + piece_type * 64 + squares
    black_indices = (1 - color) * 384 + piece_type * 64 + (squares ^ 56)
    return white_indices, black_indices, counts


def _offsets_from_counts(counts: torch.Tensor) -> torch.Tensor:
    return torch.cat([
        torch.zeros(1, dtype=torch.long, device=counts.device),
        counts.cumsum(dim=0)[:-1],
    ])


def extract_perspective_features(boards: torch.Tensor) -> PerspectiveFeatureBatch:
    """Extract white/black perspective sparse feature lists from unpacked boards."""
    white_indices, black_indices, counts = _perspective_feature_indices(boards)
    valid_mask = boards.ne(EMPTY)
    white_padded = torch.full_like(white_indices, -1)
    black_padded = torch.full_like(black_indices, -1)
    white_padded[valid_mask] = white_indices[valid_mask]
    black_padded[valid_mask] = black_indices[valid_mask]
    return PerspectiveFeatureBatch(
        white_padded=white_padded,
        black_padded=black_padded,
        counts=counts,
    )


def extract_stm_ntm_features(boards: torch.Tensor, stm: torch.Tensor) -> SideFeatureBatch:
    """Extract STM/NTM sparse feature lists from unpacked boards."""
    perspective = extract_perspective_features(boards)
    stm_is_white = stm.eq(0)
    valid_mask = perspective.white_padded.ge(0)
    stm_padded = torch.where(stm_is_white.unsqueeze(1), perspective.white_padded, perspective.black_padded)
    ntm_padded = torch.where(stm_is_white.unsqueeze(1), perspective.black_padded, perspective.white_padded)

    counts = perspective.counts
    stm_offsets = _offsets_from_counts(counts)
    ntm_offsets = stm_offsets

    return SideFeatureBatch(
        stm_indices=stm_padded.masked_select(valid_mask),
        stm_offsets=stm_offsets,
        ntm_indices=ntm_padded.masked_select(valid_mask),
        ntm_offsets=ntm_offsets,
        counts=counts,
        stm_is_white=stm_is_white,
    )


def extract_input_buckets(boards: torch.Tensor, stm: torch.Tensor, king_bucket_map: Sequence[int]) -> InputBucketBatch:
    """Extract white/black and STM/NTM input buckets from unpacked boards."""
    if len(king_bucket_map) != 64:
        raise ValueError("king_bucket_map must contain 64 entries")

    device = boards.device
    king_bucket_tensor = torch.tensor(list(king_bucket_map), dtype=torch.long, device=device)
    white_king_mask = boards.eq(5)
    black_king_mask = boards.eq(11)
    if torch.any(white_king_mask.sum(dim=1) != 1) or torch.any(black_king_mask.sum(dim=1) != 1):
        raise ValueError("Board is missing a king during input bucket extraction")

    white_king_squares = white_king_mask.to(torch.long).argmax(dim=1)
    black_king_squares = black_king_mask.to(torch.long).argmax(dim=1)
    white = king_bucket_tensor.index_select(0, white_king_squares)
    black = king_bucket_tensor.index_select(0, black_king_squares ^ 56)
    stm_is_white = stm.eq(0)
    return InputBucketBatch(
        white=white,
        black=black,
        stm=torch.where(stm_is_white, white, black),
        ntm=torch.where(stm_is_white, black, white),
    )


def extract_output_buckets(boards: torch.Tensor, num_buckets: int, bucket_divisor: int) -> torch.Tensor:
    """Extract output buckets from unpacked boards."""
    if num_buckets <= 0:
        raise ValueError("num_buckets must be positive")
    if bucket_divisor <= 0:
        raise ValueError("bucket_divisor must be positive")

    valid_mask = boards.ne(EMPTY)
    piece_counts = valid_mask.sum(dim=1, dtype=torch.long)
    return ((piece_counts - 2).clamp_min(0) // bucket_divisor).clamp_max(num_buckets - 1)


def board_to_dense_features(packed_boards: torch.Tensor) -> torch.Tensor:
    """Debug helper for dense 768-feature materialization."""
    boards = unpack_packed_boards_torch(packed_boards)
    batch_size = boards.shape[0]
    dense = torch.zeros(batch_size, INPUT_FEATURES, dtype=torch.float32, device=boards.device)
    valid_mask = boards.ne(EMPTY)
    squares = torch.arange(64, device=boards.device, dtype=torch.long).unsqueeze(0).expand(batch_size, -1)
    piece_type = boards.remainder(6)
    color = torch.div(boards, 6, rounding_mode="floor").clamp(0, 1)
    white_indices = (color * 384 + piece_type * 64 + squares).masked_select(valid_mask)
    batch_indices = torch.arange(batch_size, device=boards.device).unsqueeze(1).expand(-1, 64).masked_select(valid_mask)
    dense[batch_indices, white_indices] = 1.0
    return dense
