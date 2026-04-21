"""Sparse dual-perspective NNUE model matching Altair's engine layout."""

from __future__ import annotations

import functools
import os
from typing import Sequence

import torch
from torch import nn
import torch.nn.functional as F

from ..data.feature_extractor import (
    extract_input_buckets,
    extract_output_buckets,
    extract_stm_ntm_compact_features,
    extract_stm_ntm_features,
    unpack_packed_boards_torch,
)
from ..data.shard_format import INPUT_FEATURES
from .base import ValueNet


def _aligned_struct_size(size_bytes: int, alignment: int = 64) -> int:
    remainder = size_bytes % alignment
    return size_bytes if remainder == 0 else size_bytes + alignment - remainder


def prepare_sparse_bucket_batch(
        batch: dict,
        king_bucket_map: Sequence[int],
        num_output_buckets: int,
        output_bucket_divisor: int,
) -> dict:
    with torch.no_grad():
        boards = unpack_packed_boards_torch(batch["packed_boards"])
        square_indices = torch.arange(64, dtype=torch.long, device=boards.device)
        flipped_square_indices = square_indices ^ 56
        king_bucket_tensor = torch.tensor(tuple(int(x) for x in king_bucket_map), dtype=torch.long, device=boards.device)
        compact_features = extract_stm_ntm_compact_features(
            boards,
            batch["stm"],
            squares=square_indices,
            flipped_squares=flipped_square_indices,
        )
        input_buckets = extract_input_buckets(
            boards,
            batch["stm"],
            king_bucket_tensor=king_bucket_tensor,
        )
        output_bucket = extract_output_buckets(boards, num_output_buckets, output_bucket_divisor)

    return {
        "stm_padded": compact_features.stm_padded.to(torch.int32),
        "ntm_padded": compact_features.ntm_padded.to(torch.int32),
        "counts": compact_features.counts.to(torch.int16),
        "stm_input_bucket": input_buckets.stm.to(torch.int16),
        "ntm_input_bucket": input_buckets.ntm.to(torch.int16),
        "output_bucket": output_bucket.to(torch.int16),
        "stm": batch["stm"],
        "wdl": batch["wdl"],
        "eval": batch["eval"],
    }

class SparseBucketNNUE(ValueNet):
    def __init__(self,
                 hidden_size: int = 1024,
                 king_bucket_map: Sequence[int] = (),
                 num_output_buckets: int = 0,
                 output_bucket_divisor: int = 0,
                 qa: int = 255,
                 qb: int = 64,
                 scale: float = 400.0,
                 init_std: float = 1.0):
        super().__init__()
        if len(king_bucket_map) != 64:
            raise ValueError("king_bucket_map must contain 64 entries")
        if num_output_buckets <= 0:
            raise ValueError("num_output_buckets must be positive")
        if output_bucket_divisor <= 0:
            raise ValueError("output_bucket_divisor must be positive")

        self.hidden_size = hidden_size
        self.king_bucket_map = tuple(int(x) for x in king_bucket_map)
        self.num_input_buckets = max(self.king_bucket_map) + 1
        self.num_output_buckets = num_output_buckets
        self.output_bucket_divisor = output_bucket_divisor
        self.qa = qa
        self.qb = qb
        self.scale = scale

        self.feature_weights = nn.Parameter(torch.empty(self.num_input_buckets, INPUT_FEATURES, hidden_size))
        self.feature_bias = nn.Parameter(torch.zeros(hidden_size))
        self.output_weights = nn.Parameter(torch.empty(self.num_output_buckets, hidden_size * 2))
        self.output_bias = nn.Parameter(torch.zeros(self.num_output_buckets))
        self._engine_padding = b""
        self.register_buffer("_square_indices", torch.arange(64, dtype=torch.long), persistent=False)
        self.register_buffer("_flipped_square_indices", torch.arange(64, dtype=torch.long) ^ 56, persistent=False)
        self.register_buffer("_king_bucket_tensor", torch.tensor(self.king_bucket_map, dtype=torch.long), persistent=False)

        nn.init.normal_(self.feature_weights, std=init_std)
        nn.init.normal_(self.output_weights, std=init_std)

    def create_batch_preparer(self):
        return functools.partial(
            prepare_sparse_bucket_batch,
            king_bucket_map=self.king_bucket_map,
            num_output_buckets=self.num_output_buckets,
            output_bucket_divisor=self.output_bucket_divisor,
        )

    def _accumulate_side(self,
                         indices: torch.Tensor,
                         offsets: torch.Tensor,
                         counts: torch.Tensor,
                         buckets: torch.Tensor) -> torch.Tensor:
        flat_weights = self.feature_weights.view(self.num_input_buckets * INPUT_FEATURES, self.hidden_size)
        bucketed_indices = indices + buckets.repeat_interleave(counts) * INPUT_FEATURES
        hidden = F.embedding_bag(
            bucketed_indices,
            flat_weights,
            offsets,
            mode="sum",
            include_last_offset=False,
        )
        return hidden + self.feature_bias.unsqueeze(0)

    @staticmethod
    def _flatten_compact_features(padded: torch.Tensor, counts: torch.Tensor) -> tuple[torch.Tensor, torch.Tensor]:
        offsets = torch.cat([
            torch.zeros(1, dtype=torch.long, device=counts.device),
            counts.cumsum(dim=0)[:-1],
        ])
        if padded.shape[1] == 0:
            return padded.reshape(-1), offsets
        valid_mask = torch.arange(padded.shape[1], device=padded.device).unsqueeze(0) < counts.unsqueeze(1)
        return padded.masked_select(valid_mask), offsets

    def prepare_shard_batch(self, batch: dict) -> dict:
        return prepare_sparse_bucket_batch(
            batch,
            king_bucket_map=self.king_bucket_map,
            num_output_buckets=self.num_output_buckets,
            output_bucket_divisor=self.output_bucket_divisor,
        )

    def forward(self, batch: dict) -> dict:
        if "stm_padded" in batch:
            counts = batch["counts"].to(torch.long)
            stm_indices, stm_offsets = self._flatten_compact_features(batch["stm_padded"].to(torch.long), counts)
            ntm_indices, ntm_offsets = self._flatten_compact_features(batch["ntm_padded"].to(torch.long), counts)
            input_bucket_stm = batch["stm_input_bucket"].to(torch.long)
            input_bucket_ntm = batch["ntm_input_bucket"].to(torch.long)
            output_bucket = batch["output_bucket"].to(torch.long)
        else:
            boards = unpack_packed_boards_torch(batch["packed_boards"])
            side_features = extract_stm_ntm_features(
                boards,
                batch["stm"],
                squares=self._square_indices,
                flipped_squares=self._flipped_square_indices,
            )
            input_buckets = extract_input_buckets(
                boards,
                batch["stm"],
                king_bucket_tensor=self._king_bucket_tensor,
            )
            counts = side_features.counts
            stm_indices = side_features.stm_indices
            stm_offsets = side_features.stm_offsets
            ntm_indices = side_features.ntm_indices
            ntm_offsets = side_features.ntm_offsets
            input_bucket_stm = input_buckets.stm
            input_bucket_ntm = input_buckets.ntm
            output_bucket = extract_output_buckets(boards, self.num_output_buckets, self.output_bucket_divisor)

        stm_hidden = self._accumulate_side(
            stm_indices, stm_offsets, counts, input_bucket_stm
        )
        ntm_hidden = self._accumulate_side(
            ntm_indices, ntm_offsets, counts, input_bucket_ntm
        )

        stm_hidden = torch.clamp(stm_hidden, 0.0, 1.0).square()
        ntm_hidden = torch.clamp(ntm_hidden, 0.0, 1.0).square()
        hidden = torch.cat([stm_hidden, ntm_hidden], dim=1)

        weights = self.output_weights.index_select(0, output_bucket)
        bias = self.output_bias.index_select(0, output_bucket)
        value_logit = hidden.mul(weights).sum(dim=1) + bias
        value_cp = value_logit * self.scale

        return {
            "value_logit": value_logit,
            "value_cp": value_cp,
        }

    def export_engine_format(self, path: str) -> None:
        feature_weights = torch.round(self.feature_weights.detach().cpu() * float(self.qa)).to(torch.int16).reshape(-1)
        feature_bias = torch.round(self.feature_bias.detach().cpu() * float(self.qa)).to(torch.int16).reshape(-1)
        output_weights = torch.round(self.output_weights.detach().cpu().transpose(0, 1) * float(self.qb)).to(torch.int16).reshape(-1)
        output_bias = torch.round(self.output_bias.detach().cpu() * float(self.qa * self.qb)).to(torch.int16).reshape(-1)

        with open(path, "wb") as handle:
            handle.write(feature_weights.numpy().tobytes())
            handle.write(feature_bias.numpy().tobytes())
            handle.write(output_weights.numpy().tobytes())
            handle.write(output_bias.numpy().tobytes())
            raw_bytes = (
                feature_weights.numel() +
                feature_bias.numel() +
                output_weights.numel() +
                output_bias.numel()
            ) * 2
            padded_size = _aligned_struct_size(raw_bytes)
            if padded_size > raw_bytes:
                padding = self._engine_padding or (b"\x00" * (padded_size - raw_bytes))
                handle.write(padding[:padded_size - raw_bytes])

    @classmethod
    def from_engine_bin(cls,
                        path: str,
                        hidden_size: int = 1024,
                        king_bucket_map: Sequence[int] = (),
                        num_output_buckets: int = 0,
                        output_bucket_divisor: int = 0,
                        qa: int = 255,
                        qb: int = 64,
                        scale: float = 400.0) -> "SparseBucketNNUE":
        if len(king_bucket_map) != 64:
            raise ValueError("king_bucket_map must contain 64 entries")
        if num_output_buckets <= 0 or output_bucket_divisor <= 0:
            raise ValueError("num_output_buckets and output_bucket_divisor must be positive")
        num_input_buckets = max(king_bucket_map) + 1
        expected_feature_weights = num_input_buckets * INPUT_FEATURES * hidden_size
        expected_feature_bias = hidden_size
        expected_output_weights = hidden_size * 2 * num_output_buckets
        expected_output_bias = num_output_buckets
        expected_total_values = (
            expected_feature_weights +
            expected_feature_bias +
            expected_output_weights +
            expected_output_bias
        )
        expected_total_bytes = expected_total_values * 2
        expected_padded_bytes = _aligned_struct_size(expected_total_bytes)

        actual_size = os.path.getsize(path)
        if actual_size not in {expected_total_bytes, expected_padded_bytes}:
            raise ValueError(
                f"Unexpected NNUE binary size for hidden_size={hidden_size}: "
                f"expected {expected_total_bytes} or {expected_padded_bytes} bytes, found {actual_size}"
            )

        values = torch.from_file(path, shared=False, size=expected_total_values, dtype=torch.int16).to(torch.float32)
        trailing_padding = b""
        if actual_size > expected_total_bytes:
            with open(path, "rb") as handle:
                handle.seek(expected_total_bytes)
                trailing_padding = handle.read(actual_size - expected_total_bytes)

        offset = 0
        feature_weights = values[offset:offset + expected_feature_weights].reshape(num_input_buckets, INPUT_FEATURES, hidden_size)
        offset += expected_feature_weights
        feature_bias = values[offset:offset + expected_feature_bias]
        offset += expected_feature_bias
        output_weights = values[offset:offset + expected_output_weights].reshape(hidden_size * 2, num_output_buckets).transpose(0, 1)
        offset += expected_output_weights
        output_bias = values[offset:offset + expected_output_bias]

        if offset + expected_output_bias != expected_total_values:
            raise ValueError("NNUE binary parse did not consume the expected number of values")

        model = cls(
            hidden_size=hidden_size,
            king_bucket_map=king_bucket_map,
            num_output_buckets=num_output_buckets,
            output_bucket_divisor=output_bucket_divisor,
            qa=qa,
            qb=qb,
            scale=scale,
        )
        with torch.no_grad():
            model.feature_weights.copy_(feature_weights / float(qa))
            model.feature_bias.copy_(feature_bias / float(qa))
            model.output_weights.copy_(output_weights / float(qb))
            model.output_bias.copy_(output_bias / float(qa * qb))
        model._engine_padding = trailing_padding

        return model

    @classmethod
    def load_from_engine_bin(cls, path: str, **kwargs) -> "SparseBucketNNUE":
        return cls.from_engine_bin(path, **kwargs)
