"""Minimal modular trainer for Altair NNUE experiments."""

from __future__ import annotations

from dataclasses import dataclass, field

import torch


@dataclass
class TrainerConfig:
    epochs: int = 1
    device: str = "cpu"
    grad_clip_norm: float | None = None
    log_every: int = 100
    checkpoint_dir: str | None = None


@dataclass
class EpochResult:
    split: str
    loss: float
    criterion: dict[str, float] = field(default_factory=dict)
    metrics: dict[str, float] = field(default_factory=dict)


class Trainer:
    def __init__(self,
                 model,
                 optimizer,
                 objective,
                 criteria=None,
                 metrics=None,
                 config: TrainerConfig | None = None):
        self.model = model
        self.optimizer = optimizer
        self.objective = objective
        self.criteria = list(criteria or [])
        self.metrics = list(metrics or [])
        self.config = config or TrainerConfig()
        self.device = torch.device(self.config.device)
        self.model.to(self.device)

    def fit(self, train_loader, val_loader=None) -> list[dict[str, EpochResult]]:
        history = []
        for epoch in range(self.config.epochs):
            train_result = self._run_epoch(train_loader, training=True, epoch=epoch)
            epoch_result = {"train": train_result}

            if val_loader is not None:
                epoch_result["val"] = self._run_epoch(val_loader, training=False, epoch=epoch)

            history.append(epoch_result)
        return history

    def _run_epoch(self, loader, training: bool, epoch: int) -> EpochResult:
        self.model.train(training)
        total_loss = 0.0
        total_batches = 0
        criterion_totals = {criterion.name: 0.0 for criterion in self.criteria}
        metric_totals = {metric.name: 0.0 for metric in self.metrics}

        for batch_index, batch in enumerate(loader):
            batch = {key: value.to(self.device, non_blocking=True) for key, value in batch.items()}
            progress = (epoch + batch_index / max(len(loader), 1)) / max(self.config.epochs, 1)

            with torch.set_grad_enabled(training):
                predictions = self.model(batch)
                loss = self.objective(predictions, batch, progress)

                if training:
                    self.optimizer.zero_grad(set_to_none=True)
                    loss.backward()
                    if self.config.grad_clip_norm is not None:
                        torch.nn.utils.clip_grad_norm_(self.model.parameters(), self.config.grad_clip_norm)
                    self.optimizer.step()

            total_loss += float(loss.detach().cpu().item())
            total_batches += 1

            for criterion in self.criteria:
                criterion_totals[criterion.name] += float(criterion(predictions, batch).detach().cpu().item())
            for metric in self.metrics:
                metric_totals[metric.name] += float(metric(predictions, batch).detach().cpu().item())

        divisor = max(total_batches, 1)
        return EpochResult(
            split="train" if training else "val",
            loss=total_loss / divisor,
            criterion={name: value / divisor for name, value in criterion_totals.items()},
            metrics={name: value / divisor for name, value in metric_totals.items()},
        )
