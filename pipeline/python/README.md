# python

This directory contains the Python-side data, model, training, and visualization stack.

The Python side is where experiment policy lives. The C++ side validates and serializes chess data; the Python side decides:
- which shard directories are training vs validation vs test
- which model to use
- how features are derived at training time
- which objective is optimized
- which criteria and metrics are reported

## Subdirectories

### `data/`

Packed-board shard reading and feature extraction.

Use this when you need:
- shard readers
- datasets and collate functions
- train/validation/test shard-directory helpers
- sparse white/black perspective feature derivation

### `configs/`

Experiment definitions for `pipeline/train.py`.

Each config is normal Python and can define every training parameter:
- shard directories
- batch size
- number of workers
- model
- optimizer
- objective
- criteria
- metrics
- trainer settings

### `models/`

Interchangeable training networks.

The main current model is `SparseBucketNNUE`, which mirrors the engine NNUE closely and knows how to import/export engine `.bin` files.

### `train/`

Training framework pieces:
- objectives
- criteria
- metrics
- schedules
- trainer
- config loader helpers

### `visualization/`

Analytics plotting code. This is separate from training so raw dataset inspection stays lightweight.

## How To Set Up

The Python environment is defined by [pyproject.toml](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/pyproject.toml:1).

Typical setup with `uv`:

```bash
cd pipeline/python
uv venv
uv sync
```

Then run training from the repository root:

```bash
python pipeline/train.py --config pipeline/python/configs/example_train.py
```

## Recommended Workflow

1. Build the C++ pipeline.
2. Analyze raw text files if this is a new dataset.
3. Compile packed-board shards.
4. Arrange shard directories manually:
   - `shards/train/`
   - `shards/val/`
   - optionally `shards/test/`
5. Write a config under `python/configs/`.
6. Launch training with `pipeline/train.py`.

## Important Design Choices

### Packed-board shards, not stored features

Shards store boards plus labels, not precomputed NNUE feature indices.

That keeps the format:
- compact
- model-independent
- future-proof if the feature mapping changes

### Config-driven training

There is one training entry point:

```bash
python pipeline/train.py --config path/to/config.py
```

The config is Python, not JSON or YAML, so experiments can construct arbitrary objects directly without building a custom config language.

### Objective vs criterion vs metric

The training stack intentionally separates:
- objective: what is optimized
- criterion: the main quantity you want to report or compare
- metric: auxiliary reporting

This makes it easy to do things like:
- optimize a mixed eval/WDL objective
- report a pure WDL criterion
- also log eval MAE
