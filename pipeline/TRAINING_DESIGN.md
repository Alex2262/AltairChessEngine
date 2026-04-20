# Packed-Board Shards and Modular Training

This document explains the intended design of the current training stack at a higher level than the directory READMEs.

The key goal is to keep:
- shard format stable and model-agnostic
- split selection manual and experiment-driven
- training components modular
- the current NNUE close to engine inference semantics

## Core Principles

### 1. Shards store positions, not model-specific tensors

The shard format stores:
- packed board
- side to move
- WDL
- eval

It does not store:
- white perspective feature tensors
- black perspective feature tensors
- king buckets
- output buckets

Those are derived in Python by the current model.

### 2. Splits are chosen in Python, not at compile time

You decide train/validation/test by choosing shard directories or shard lists in the config.

That supports workflows like:
- training on large selfplay shards
- validating on a manually reserved directory
- testing on a much higher-quality search dataset

### 3. Training is config-driven

There is one main entrypoint:

```bash
python pipeline/train.py --config path/to/config.py
```

The config is ordinary Python and constructs the entire run.

## Shard Format

Header:
- magic: `ALTR`
- version: `2`
- record count: `u32`
- record size: `u16`
- reserved bytes

Record:
- `packed_board[32]`
- `stm`
- `wdl`
- `eval`

Square encoding:
- `0..11`: real piece values
- `12`: empty

Two squares are packed into each byte using 4-bit nibbles.

## Data Flow

### Raw text to shards

```text
{FEN} | {EVAL} | {WDL}
    ->
RecordParser
    ->
FenParser
    ->
CanonicalPosition
    ->
PackedBoardRecord
    ->
ALTR v2 shards
```

### Shards to training tensors

```text
packed boards
    ->
torch-native unpacking
    ->
sparse white/black perspective feature ids
    ->
king buckets and output buckets
    ->
SparseBucketNNUE
```

## Batch Contract

The dataloader returns:
- `packed_boards`
- `stm`
- `wdl`
- `eval`

The model is responsible for extracting its own features from `packed_boards`.

That keeps the trainer model-agnostic and prevents the dataset layer from hardcoding one specific architecture.

## Current Model Contract

`SparseBucketNNUE` currently returns:
- `value_logit`
- `value_cp`
- `white_hidden`
- `black_hidden`
- `output_bucket`

Training objectives can interpret `value_logit` however they want.

Current WDL-style training uses:

```text
sigmoid(value_logit)
```

against scalar WDL targets.

## Objective / Criterion / Metric Split

The training stack deliberately separates three concepts:

### Objective

What the optimizer minimizes.

Examples:
- pure WDL objective
- mixed eval/WDL objective
- scheduled blend from mixed to pure WDL

### Criterion

The main reported measure used to judge progress.

This can differ from the objective.

### Metric

Auxiliary reporting only.

Examples:
- WDL accuracy
- eval MAE

## Why This Design

This split keeps experiments clean:
- the C++ pipeline remains small
- the shard format stays stable
- training configs remain expressive
- models can evolve without forcing a shard-format rewrite

It also matches how you actually want to work:
- build datasets once
- choose split directories by hand
- iterate on model and training logic in Python

## Current Limitations

The current `SparseBucketNNUE` is much more efficient than the original prototype, but it is still a PyTorch implementation of accumulator logic rather than a custom fused kernel.

That means:
- the architecture is right
- the binary import/export path is right
- the data path is reasonably GPU-friendly
- but there is still room for performance tuning later if throughput becomes the bottleneck

## Canonical Example

See:
- [pipeline/python/configs/example_train.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/configs/example_train.py:1)

Run it with:

```bash
python pipeline/train.py --config pipeline/python/configs/example_train.py
```
