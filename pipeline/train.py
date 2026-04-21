#!/usr/bin/env python3
"""Config-driven training entry point for Altair NNUE experiments."""

from __future__ import annotations

import argparse
import importlib.util
import json
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from pipeline.python.train import Trainer, build_run_from_module


def load_config_module(config_path: Path):
    spec = importlib.util.spec_from_file_location("altair_train_config", config_path)
    if spec is None or spec.loader is None:
        raise ValueError(f"Failed to load training config from {config_path}")

    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main() -> None:
    parser = argparse.ArgumentParser(description="Train Altair NNUE from a Python config file")
    parser.add_argument("--config", required=True, help="Path to a Python config file")
    args = parser.parse_args()

    config_path = Path(args.config).resolve()
    module = load_config_module(config_path)
    run = build_run_from_module(module)

    trainer = Trainer(
        model=run.model,
        optimizer=run.optimizer,
        objective=run.objective,
        criteria=run.criteria,
        metrics=run.metrics,
        config=run.trainer_config,
    )
    history = trainer.fit(run.train_loader, run.val_loader)

    if run.export_engine_path is not None:
        export_path = Path(run.export_engine_path).resolve()
        export_path.parent.mkdir(parents=True, exist_ok=True)
        run.model.export_engine_format(str(export_path))
        print(f"Exported engine net to {export_path}")

    print(f"Run: {run.name}")
    for epoch, results in enumerate(history, 1):
        print(f"Epoch {epoch}")
        for split, result in results.items():
            print(
                f"  {split}: loss={result.loss:.6f} "
                f"criteria={json.dumps(result.criterion, sort_keys=True)} "
                f"metrics={json.dumps(result.metrics, sort_keys=True)}"
            )


if __name__ == "__main__":
    main()
