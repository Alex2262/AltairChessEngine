"""Common model interface for Altair training nets."""

from __future__ import annotations

from abc import ABC, abstractmethod

import torch
from torch import nn


class ValueNet(nn.Module, ABC):
    @abstractmethod
    def forward(self, batch: dict) -> dict:
        """Run a forward pass and return a prediction dictionary."""

    def export_engine_format(self, path: str) -> None:
        raise NotImplementedError(f"{self.__class__.__name__} does not support engine export")

    @classmethod
    def load_from_engine_bin(cls, path: str, **kwargs):
        raise NotImplementedError(f"{cls.__name__} does not support loading engine binaries")
