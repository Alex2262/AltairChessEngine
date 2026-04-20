"""Sparse dual-perspective NNUE model matching Altair's engine layout."""

from __future__ import annotations

import os
from typing import Sequence

import torch
from torch import nn
import torch.nn.functional as F

from ..data.feature_extractor import (
    extract_input_buckets,
    extract_output_buckets,
    extract_stm_ntm_features,
    unpack_packed_boards_torch,
)
from ..data.shard_format import INPUT_FEATURES
from .base import ValueNet


def _aligned_struct_size(size_bytes: int, alignment: int = 64) -> int:
    remainder = size_bytes % alignment
    return size_bytes if remainder == 0 else size_bytes + alignment - remainder

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

        nn.init.normal_(self.feature_weights, std=init_std)
        nn.init.normal_(self.output_weights, std=init_std)

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

    def forward(self, batch: dict) -> dict:
        boards = unpack_packed_boards_torch(batch["packed_boards"])
        side_features = extract_stm_ntm_features(boards, batch["stm"])
        input_buckets = extract_input_buckets(boards, batch["stm"], self.king_bucket_map)
        output_bucket = extract_output_buckets(boards, self.num_output_buckets, self.output_bucket_divisor)

        stm_hidden = self._accumulate_side(
            side_features.stm_indices, side_features.stm_offsets, side_features.counts, input_buckets.stm
        )
        ntm_hidden = self._accumulate_side(
            side_features.ntm_indices, side_features.ntm_offsets, side_features.counts, input_buckets.ntm
        )

        stm_hidden_unactivated = stm_hidden
        ntm_hidden_unactivated = ntm_hidden
        stm_hidden = torch.clamp(stm_hidden, 0, self.qa).square()
        ntm_hidden = torch.clamp(ntm_hidden, 0, self.qa).square()
        hidden = torch.cat([stm_hidden, ntm_hidden], dim=1)

        weights = self.output_weights.index_select(0, output_bucket)
        bias = self.output_bias.index_select(0, output_bucket)
        output = hidden.mul(weights).sum(dim=1) / float(self.qa)
        quantized_sum = output + bias
        value_logit = quantized_sum / float(self.qa * self.qb)
        value_cp = value_logit * self.scale

        return {
            "value_logit": value_logit,
            "value_cp": value_cp,
            "stm_hidden": stm_hidden_unactivated,
            "ntm_hidden": ntm_hidden_unactivated,
            "input_bucket": input_buckets.stm,
            "output_bucket": output_bucket,
        }

    def export_engine_format(self, path: str) -> None:
        feature_weights = torch.round(self.feature_weights.detach().cpu()).to(torch.int16).reshape(-1)
        feature_bias = torch.round(self.feature_bias.detach().cpu()).to(torch.int16).reshape(-1)
        output_weights = torch.round(self.output_weights.detach().cpu().transpose(0, 1)).to(torch.int16).reshape(-1)
        output_bias = torch.round(self.output_bias.detach().cpu()).to(torch.int16).reshape(-1)

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
            model.feature_weights.copy_(feature_weights)
            model.feature_bias.copy_(feature_bias)
            model.output_weights.copy_(output_weights)
            model.output_bias.copy_(output_bias)
        model._engine_padding = trailing_padding

        return model

    @classmethod
    def load_from_engine_bin(cls, path: str, **kwargs) -> "SparseBucketNNUE":
        return cls.from_engine_bin(path, **kwargs)
