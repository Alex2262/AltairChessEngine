"""Reporting metrics separate from optimization objectives."""

from __future__ import annotations

from abc import ABC, abstractmethod

import torch


def _wdl_prediction_from_logit(value_logit: torch.Tensor) -> torch.Tensor:
    win_prob = torch.sigmoid(value_logit)
    return torch.round(win_prob * 2.0).to(torch.long)


class Metric(ABC):
    name = "metric"

    @abstractmethod
    def __call__(self, predictions: dict, batch: dict) -> torch.Tensor:
        raise NotImplementedError


class WDLAccuracy(Metric):
    name = "wdl_accuracy"

    def __call__(self, predictions: dict, batch: dict) -> torch.Tensor:
        predicted = _wdl_prediction_from_logit(predictions["value_logit"])
        return (predicted == batch["wdl"]).float().mean()


class EvalMAE(Metric):
    name = "eval_mae"

    def __call__(self, predictions: dict, batch: dict) -> torch.Tensor:
        return (predictions["value_cp"] - batch["eval"]).abs().mean()
