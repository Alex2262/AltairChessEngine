# configs

This directory contains Python config files for `pipeline/train.py`.

Each config should define either:
- `build_run() -> TrainingRun`
- or `RUN`, which is already a `TrainingRun`

The config is normal Python, so it can construct:
- datasets and loaders
- the model
- bucket layouts and bucket policy
- the optimizer
- the loss objective
- reported criteria and metrics
- trainer settings

This is the recommended place to define experiments.

A config can be:
- a tiny one-off smoke test
- a baseline training run
- a longer serious experiment with custom scheduler or optimizer logic

Because the config is just Python, it can also:
- import local helpers
- branch on machine or environment
- reuse common functions across experiments

Run with:

```bash
python pipeline/train.py --config pipeline/python/configs/example_train.py
```
