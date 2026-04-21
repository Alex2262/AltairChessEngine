"""Loss objectives used to optimize Altair NNUE models."""

from __future__ import annotations

from abc import ABC, abstractmethod
from typing import Protocol

import torch
import torch.nn.functional as F


class FloatSchedule(Protocol):
    def __call__(self, progress: float) -> float:
        ...


def wdl_target(batch: dict) -> torch.Tensor:
    return batch["wdl"].to(torch.float32) * 0.5


def eval_target(batch: dict, eval_scale: float = 400.0) -> torch.Tensor:
    return torch.sigmoid(batch["eval"].to(torch.float32) / eval_scale)


class LossObjective(ABC):
    name = "loss"

    @abstractmethod
    def __call__(self, predictions: dict, batch: dict, progress: float = 0.0) -> torch.Tensor:
        raise NotImplementedError


class BlendedValueObjective(LossObjective):
    def __init__(self, wdl_schedule: FloatSchedule, eval_scale: float = 400.0):
        self.wdl_schedule = wdl_schedule
        self.eval_scale = eval_scale
        self.name = f"blended_value(scale={eval_scale:.1f})"

    def __call__(self, predictions: dict, batch: dict, progress: float = 0.0) -> torch.Tensor:
        wdl_proportion = float(self.wdl_schedule(progress))
        wdl = wdl_target(batch)
        eval_prob = eval_target(batch, self.eval_scale)
        target = wdl_proportion * wdl + (1.0 - wdl_proportion) * eval_prob
        return F.mse_loss(torch.sigmoid(predictions["value_logit"]), target)
