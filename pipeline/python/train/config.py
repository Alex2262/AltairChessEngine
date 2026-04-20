"""Helpers for config-driven training runs."""

from __future__ import annotations

from dataclasses import dataclass, field

from .trainer import TrainerConfig


@dataclass
class TrainingRun:
    train_loader: object
    val_loader: object | None
    model: object
    optimizer: object
    objective: object
    trainer_config: TrainerConfig = field(default_factory=TrainerConfig)
    criteria: list[object] = field(default_factory=list)
    metrics: list[object] = field(default_factory=list)
    name: str = "unnamed_run"


def build_run_from_module(module) -> TrainingRun:
    if hasattr(module, "build_run"):
        run = module.build_run()
    elif hasattr(module, "RUN"):
        run = module.RUN
    else:
        raise ValueError("Training config must define build_run() or RUN")

    if not isinstance(run, TrainingRun):
        raise TypeError("Training config must return a TrainingRun instance")

    return run
