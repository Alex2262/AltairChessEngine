# train

This directory contains the modular training framework used by `pipeline/train.py`.

The code here is intentionally small and composable rather than hidden behind one monolithic trainer script.

## Files

- [config.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/train/config.py:1)
  - defines `TrainingRun`
  - loads a Python config module into a runnable training definition
- [objectives.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/train/objectives.py:1)
  - loss functions that are actually optimized
- [criteria.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/train/criteria.py:1)
  - main reported criteria
- [metrics.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/train/metrics.py:1)
  - auxiliary metrics
- [schedules.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/train/schedules.py:1)
  - schedules used to interpolate or hold scalar values over training
- [trainer.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/train/trainer.py:1)
  - generic fit loop

## Main Concepts

### `TrainingRun`

`TrainingRun` is the full experiment bundle passed into the trainer. It contains:
- train loader
- validation loader
- model
- optimizer
- objective
- trainer config
- criteria
- metrics
- run name

That means a config file can fully define a run without any hidden global state.

### `TrainerConfig`

This is the runtime policy for the trainer itself:
- epochs
- device
- gradient clipping
- logging interval
- optional checkpoint directory

### Objective vs criterion vs metric

This distinction is important.

#### Objective

The objective is what the optimizer minimizes.

Examples:
- pure WDL objective
- mixed eval/WDL objective
- scheduled blend from one objective to another

#### Criterion

The criterion is the main reported measure you care about.

This can be different from the objective.

Example:
- optimize a mixed objective
- report only WDL MSE as the main validation criterion

#### Metric

Metrics are auxiliary reports.

Examples:
- WDL accuracy
- eval MAE

## How Training Is Launched

Training is launched from the repository root with:

```bash
python pipeline/train.py --config pipeline/python/configs/example_train.py
```

The config file can expose either:
- `build_run() -> TrainingRun`
- or `RUN`, which is already a `TrainingRun`

This keeps the entrypoint stable while letting the config remain completely flexible.

## Example

The example config is:

- [pipeline/python/configs/example_train.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/configs/example_train.py:1)

It demonstrates:
- train and validation shard directories
- dataloader construction
- `SparseBucketNNUE`
- AdamW optimizer
- scheduled mixed-to-pure objective
- WDL criterion and auxiliary metrics

## Typical Customization Points

The most common things to change per experiment are:
- shard directories
- batch size
- dataloader worker count
- model hidden size
- optimizer type and learning rate
- objective schedule
- trainer device and epoch count

Because the config is real Python, you can change any of these directly without changing the trainer code.
