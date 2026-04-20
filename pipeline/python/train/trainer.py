"""Minimal modular trainer for Altair NNUE experiments."""

from __future__ import annotations

import logging
from dataclasses import dataclass, field
from pathlib import Path

import torch
from tqdm.auto import tqdm


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
    def __init__(
            self,
            model,
            optimizer,
            objective,
            criteria=None,
            metrics=None,
            config: TrainerConfig | None = None,
    ):
        self.model = model
        self.optimizer = optimizer
        self.objective = objective
        self.criteria = list(criteria or [])
        self.metrics = list(metrics or [])
        self.config = config or TrainerConfig()
        self.device = torch.device(self.config.device)
        self.model.to(self.device)

        self.logger = self._build_logger()

    def _build_logger(self) -> logging.Logger:
        logger = logging.getLogger(f"{__name__}.{self.__class__.__name__}")
        logger.setLevel(logging.INFO)

        if not logger.handlers:
            handler = logging.StreamHandler()
            handler.setLevel(logging.INFO)
            formatter = logging.Formatter(
                "[%(asctime)s] %(levelname)s - %(message)s",
                datefmt="%H:%M:%S",
            )
            handler.setFormatter(formatter)
            logger.addHandler(handler)

        logger.propagate = False
        return logger

    def fit(self, train_loader, val_loader=None) -> list[dict[str, EpochResult]]:
        history = []

        self.logger.info(
            "Starting training for %d epoch(s) on device=%s",
            self.config.epochs,
            self.device,
        )

        for epoch in range(self.config.epochs):
            self.logger.info("Epoch %d/%d", epoch + 1, self.config.epochs)

            train_result = self._run_epoch(train_loader, training=True, epoch=epoch)
            epoch_result = {"train": train_result}

            self.logger.info(
                "Epoch %d train | loss=%.6f%s%s",
                epoch + 1,
                train_result.loss,
                self._format_named_values(" | criteria", train_result.criterion),
                self._format_named_values(" | metrics", train_result.metrics),
                )

            if val_loader is not None:
                val_result = self._run_epoch(val_loader, training=False, epoch=epoch)
                epoch_result["val"] = val_result

                self.logger.info(
                    "Epoch %d val   | loss=%.6f%s%s",
                    epoch + 1,
                    val_result.loss,
                    self._format_named_values(" | criteria", val_result.criterion),
                    self._format_named_values(" | metrics", val_result.metrics),
                    )

            history.append(epoch_result)

        self.logger.info("Training complete.")
        return history

    def _run_epoch(self, loader, training: bool, epoch: int) -> EpochResult:
        split = "train" if training else "val"
        self.model.train(training)

        total_loss = 0.0
        total_batches = 0
        criterion_totals = {criterion.name: 0.0 for criterion in self.criteria}
        metric_totals = {metric.name: 0.0 for metric in self.metrics}

        num_batches = len(loader)

        iterator = enumerate(loader, start=1)
        iterator = tqdm(
            iterator,
            total=num_batches,
            desc=f"Epoch {epoch + 1}/{self.config.epochs} [{split}]",
        )

        for batch_index, batch in iterator:
            batch = {key: value.to(self.device, non_blocking=True) for key, value in batch.items()}

            epoch_progress = (epoch + ((batch_index - 1) / max(num_batches, 1))) / max(self.config.epochs, 1)

            with torch.set_grad_enabled(training):
                predictions = self.model(batch)
                loss = self.objective(predictions, batch, epoch_progress)

                if training:
                    self.optimizer.zero_grad(set_to_none=True)
                    loss.backward()
                    if self.config.grad_clip_norm is not None:
                        torch.nn.utils.clip_grad_norm_(self.model.parameters(), self.config.grad_clip_norm)
                    self.optimizer.step()

            loss_value = float(loss.detach().cpu().item())
            total_loss += loss_value
            total_batches += 1

            batch_criteria = {}
            for criterion in self.criteria:
                value = float(criterion(predictions, batch).detach().cpu().item())
                criterion_totals[criterion.name] += value
                batch_criteria[criterion.name] = value

            batch_metrics = {}
            for metric in self.metrics:
                value = float(metric(predictions, batch).detach().cpu().item())
                metric_totals[metric.name] += value
                batch_metrics[metric.name] = value

            avg_loss = total_loss / total_batches
            avg_criteria = {
                name: value / total_batches for name, value in criterion_totals.items()
            }
            avg_metrics = {
                name: value / total_batches for name, value in metric_totals.items()
            }

            postfix = {"loss": f"{avg_loss:.4f}"}
            for name, value in avg_criteria.items():
                postfix[name] = f"{value:.4f}"
            for name, value in avg_metrics.items():
                postfix[name] = f"{value:.4f}"
            iterator.set_postfix(postfix)

            if self.config.log_every > 0 and (batch_index % self.config.log_every == 0):
                batch_total = num_batches if num_batches is not None else "?"
                self.logger.info(
                    "Epoch %d [%s] batch %s/%s | loss=%.6f%s%s",
                    epoch + 1,
                    split,
                    batch_index,
                    batch_total,
                    avg_loss,
                    self._format_named_values(" | criteria", avg_criteria),
                    self._format_named_values(" | metrics", avg_metrics),
                    )

        return EpochResult(
            split=split,
            loss=total_loss / total_batches,
            criterion={name: value / total_batches for name, value in criterion_totals.items()},
            metrics={name: value / total_batches for name, value in metric_totals.items()},
        )

    @staticmethod
    def _format_named_values(prefix: str, values: dict[str, float]) -> str:
        if not values:
            return ""
        formatted = ", ".join(f"{name}={value:.6f}" for name, value in values.items())
        return f"{prefix}: {formatted}"