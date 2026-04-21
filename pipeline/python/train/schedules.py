"""Scheduling helpers for training objectives and scalar parameters."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol


class FloatSchedule(Protocol):
    def __call__(self, progress: float) -> float:
        ...


@dataclass
class ConstantSchedule:
    value: float

    def __call__(self, progress: float) -> float:
        return self.value


@dataclass
class LinearInterpolationSchedule:
    start: float
    end: float

    def __call__(self, progress: float) -> float:
        progress = min(max(progress, 0.0), 1.0)
        return self.start + (self.end - self.start) * progress
