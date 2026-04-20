"""Loss objectives used to optimize Altair NNUE models."""

from __future__ import annotations

from abc import ABC, abstractmethod

import torch
import torch.nn.functional as F


def wdl_target(batch: dict) -> torch.Tensor:
    return batch["wdl"].to(torch.float32) * 0.5


class LossObjective(ABC):
    name = "loss"

    @abstractmethod
    def __call__(self, predictions: dict, batch: dict, progress: float = 0.0) -> torch.Tensor:
        raise NotImplementedError


class PureWDLObjective(LossObjective):
    name = "pure_wdl"

    def __call__(self, predictions: dict, batch: dict, progress: float = 0.0) -> torch.Tensor:
        return F.mse_loss(torch.sigmoid(predictions["value_logit"]), wdl_target(batch))


class MixedEvalWDLObjective(LossObjective):
    def __init__(self, eval_weight: float = 0.5, wdl_weight: float = 0.5):
        self.eval_weight = eval_weight
        self.wdl_weight = wdl_weight
        self.name = f"mixed_eval_wdl({eval_weight:.2f},{wdl_weight:.2f})"

    def __call__(self, predictions: dict, batch: dict, progress: float = 0.0) -> torch.Tensor:
        eval_loss = F.smooth_l1_loss(predictions["value_cp"], batch["eval"])
        wdl_loss = F.mse_loss(torch.sigmoid(predictions["value_logit"]), wdl_target(batch))
        return self.eval_weight * eval_loss + self.wdl_weight * wdl_loss
