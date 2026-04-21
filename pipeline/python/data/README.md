# data

This directory is the Python-side input pipeline for training.

Its job is to take compact packed-board shards and turn them into tensors that a model can consume efficiently.

## Responsibilities

`data/` is responsible for:
- reading shard metadata and binary records
- building shard-wise training/evaluation DataLoaders
- unpacking packed boards
- deriving sparse white/black perspective features
- exposing helpers for manual train/validation/test shard selection

It is not responsible for:
- model architecture
- optimizer logic
- loss definitions
- training schedules

## Files

- [shard_format.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/shard_format.py:1)
  - binary constants shared by the reader and feature code
- [shard_reader.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/shard_reader.py:1)
  - low-level shard loading and manifest reading
- [batching.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/batching.py:1)
  - record-to-batch conversion helpers
- [shard_loader.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/shard_loader.py:1)
  - shard-wise `IterableDataset` and `DataLoader` helpers with worker-aware shard partitioning and batch-wise preparation
- [feature_extractor.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/feature_extractor.py:1)
  - torch-native packed-board unpacking and sparse feature extraction
- [splits.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/splits.py:1)
  - helpers for selecting shard sets by directory

## Shard Reading

The low-level format is fixed-size `ALTR` v2.

Each record stores:
- packed board
- side to move
- WDL
- eval

The reader can:
- read a manifest
- list shard files in a directory
- memory-map or load shard records

## Loader Contract

The active training and evaluation path is [create_shard_loader(...)](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/shard_loader.py:84).

It works like this:
- PyTorch starts `num_workers` worker processes
- each worker gets a disjoint subset of shard files
- shard order can be shuffled once per epoch
- record order inside each shard can also be shuffled
- each worker reads one minibatch worth of raw records at a time
- optional model-aware preparation then converts that minibatch into the tensors the model actually wants

The raw batch shape is:
- `packed_boards`
- `stm`
- `wdl`
- `eval`

This is deliberate.

The loader does not emit:
- white dense 768-vectors
- black dense 768-vectors
- precomputed king buckets

Those are derived later in a model-aware way.

### Main tuning knobs

- `batch_size`
  - how many positions the model trains on at once
- `num_workers`
  - how many CPU worker processes prepare future minibatches
- `prefetch_factor`
  - how many minibatches each worker tries to keep queued ahead
- `pin_memory`
  - whether PyTorch places CPU batches in pinned memory before GPU transfer

This keeps the system much easier to reason about than the older chunk-based loader experiments:
- workers prepare batches
- the DataLoader queues batches
- the trainer copies batches to GPU

## Sparse Feature Extraction

The feature path is deliberately split into separate reusable steps.

### 1. STM/NTM feature extraction

- `extract_stm_ntm_features(...)`

This takes unpacked boards plus side to move and returns the sparse feature ids for:
- side to move
- non-side to move

This is the reusable base if a model only wants perspective features and no buckets.

### 2. Input bucket extraction

- `extract_input_buckets(...)`

This takes unpacked boards, side to move, and a caller-supplied king-bucket map.

It returns:
- white perspective input buckets
- black perspective input buckets
- STM input bucket
- NTM input bucket

### 3. Output bucket extraction

- `extract_output_buckets(...)`

This takes unpacked boards plus a caller-supplied bucket count and divisor.

That means output-bucket policy is a model/config decision, not a hidden data-layer constant.

### 4. Lower-level perspective extraction

- `extract_perspective_features(...)`

This returns white and black perspective sparse features without reordering them into STM/NTM.

This keeps the input path:
- compact on disk
- sparse in memory
- GPU-friendly at training time

## Manual Split Selection

The training split is not baked into compilation.

Use:
- `shard_paths_from_directory(...)`
- `shard_paths_from_directories(...)`

or instantiate shard loaders directly from the directories you want.

That lets you keep:
- train shards
- validation shards
- high-quality test shards

as separate physical directories if you want.
