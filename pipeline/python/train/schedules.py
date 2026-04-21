"""Scheduling helpers for training objectives and scalar parameters."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Callable, Protocol, TypeVar

import torch

from .objectives import LossObjective

T = TypeVar("T")


class Schedule(Protocol[T]):
    def __call__(self, progress: float) -> T:
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


class ScheduledObjective(LossObjective):
    def __init__(
            self,
            schedule: Schedule[T],
            objective_fn: Callable[[T, dict, dict, float], torch.Tensor],
            name: str = "scheduled",
    ):
        self.schedule = schedule
        self.objective_fn = objective_fn
        self.name = name

    def __call__(self, predictions: dict, batch: dict, progress: float = 0.0) -> torch.Tensor:
        scheduled_value = self.schedule(progress)
        return self.objective_fn(scheduled_value, predictions, batch, progress)


class InterpolatedObjective(LossObjective):
    def __init__(
            self,
            start_objective: LossObjective,
            end_objective: LossObjective,
            transition: Schedule[float],
    ):
        self.start_objective = start_objective
        self.end_objective = end_objective
        self.transition = transition
        self.name = f"interpolated({start_objective.name}->{end_objective.name})"

    def __call__(self, predictions: dict, batch: dict, progress: float = 0.0) -> torch.Tensor:
        mix = float(self.transition(progress))
        start_loss = self.start_objective(predictions, batch, progress)
        end_loss = self.end_objective(predictions, batch, progress)
        return (1.0 - mix) * start_loss + mix * end_loss
