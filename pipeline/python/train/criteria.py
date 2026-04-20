"""Evaluation criteria used for reporting model quality."""

from __future__ import annotations

from abc import ABC, abstractmethod

import torch
import torch.nn.functional as F

from .objectives import wdl_target


class Criterion(ABC):
    name = "criterion"

    @abstractmethod
    def __call__(self, predictions: dict, batch: dict) -> torch.Tensor:
        raise NotImplementedError


class WDLCriterion(Criterion):
    name = "wdl_mse"

    def __call__(self, predictions: dict, batch: dict) -> torch.Tensor:
        return F.mse_loss(torch.sigmoid(predictions["value_logit"]), wdl_target(batch))


class EvalCriterion(Criterion):
    name = "eval_mse"

    def __call__(self, predictions: dict, batch: dict) -> torch.Tensor:
        return F.mse_loss(predictions["value_cp"], batch["eval"])
