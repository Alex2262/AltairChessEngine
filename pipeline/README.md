# Pipeline

This directory contains the full Altair data pipeline: raw datagen parsing, dataset analytics, packed-board shard compilation, and Python-side NNUE training.

The pipeline is intentionally split across:
- a small C++ core for fast parsing, validation, analytics, and shard writing
- a Python stack for model-specific feature extraction, training, visualization, and experiment configuration

The central design choice is that shards store chess positions and labels, not architecture-specific NNUE features. That keeps the binary format compact and stable even if the training model changes.

## What The Pipeline Does

There are three main workflows:

1. Analyze raw text datagen output
   - input: lines of the form `{FEN} | {EVAL} | {WDL}`
   - output: CSV summaries and plots

2. Compile raw text datagen output into training shards
   - input: the same raw datagen text
   - output: fixed-size binary shards with packed boards and labels

3. Train a network from shards
   - input: one or more directories of shards
   - output: checkpoints, logs, and optionally engine-compatible `.bin` exports

## Directory Map

- `src/`
  - C++ library code
  - `core/`, `parsing/`, `analytics/`, `compilation/`
- `cli/`
  - small C++ executables that wrap the library
- `python/`
  - data loading, models, training, configs, visualization
- `tests/`
  - focused pipeline regression tests
- `train.py`
  - config-driven Python training entry point

## Build

### C++ pipeline

From this directory:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j8
```

This produces:
- `build/analyze_raw`
- `build/compile_shards`
- `build/pipeline_tests`

### Python environment

The Python code is set up for `uv` via [python/pyproject.toml](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/pyproject.toml:1).

A typical setup is:

```bash
cd pipeline/python
uv venv
uv sync
```

If you prefer a direct invocation without `uv`, the code also works with a Python environment that has at least:
- Python 3.11
- `torch`
- `numpy`

## Entrypoints

### 1. Run analytics on raw datagen files

Primary executable:

```bash
./build/analyze_raw data*.txt -o analytics_output/
```

What it does:
- parses every raw datagen line
- validates FENs
- collects single-pass statistics
- writes CSV outputs into the chosen directory

Useful outputs:
- `summary.csv`
- `error_summary.csv`
- `eval_histogram.csv`
- `material_distribution.csv`
- `piece_counts.csv`
- `king_positions.csv`
- `castling_rights.csv`

Recommended use:
- run this first on a new dataset before compiling shards
- check `error_summary.csv` immediately if parse errors are nonzero

### 2. Compile packed-board shards

Primary executable:

```bash
./build/compile_shards data*.txt -o shards/ --max-shard-mb 256 --shuffle-buffer 200000
```

Important flags:
- `-o`, `--output`
  - output directory for shard files and manifest
- `--max-shard-mb`
  - shard size target
- `--shuffle-buffer`
  - in-memory mixing buffer used during compilation
- `--seed`
  - deterministic seed for shard mixing

What it does:
- parses and validates raw datagen records
- packs each board into 32 bytes
- writes side-to-move, WDL, and eval labels
- mixes records through a shuffle buffer to reduce sequential correlation

Best practice:
- use a nontrivial shuffle buffer for training shards
- keep validation or test data in separate directories rather than mixing split logic into compilation

### 3. Train from a config file

Primary entrypoint:

```bash
python pipeline/train.py --config pipeline/python/configs/example_train.py
```

The config file is ordinary Python and defines the entire run:
- where the training shards live
- where the validation shards live
- which model to use
- which optimizer to use
- which objective to optimize
- which criteria and metrics to report
- trainer settings such as epochs and device

Recommended workflow:
- keep each experiment in its own config file under `pipeline/python/configs/`
- treat the config as the full experiment definition

## Recommended End-To-End Workflow

### New dataset workflow

1. Build the pipeline:

```bash
cd pipeline
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j8
```

2. Analyze the raw text files:

```bash
./build/analyze_raw ../AltairDataBase/data*.txt -o ../AltairDataBaseAnalysis/
```

3. Inspect:
- `summary.csv`
- `error_summary.csv`
- the generated plots if you use the plotting scripts

4. Compile shards:

```bash
./build/compile_shards ../AltairDataBase/data*.txt -o ../shards/train --max-shard-mb 256 --shuffle-buffer 200000
```

5. Put validation or test shards in separate directories by hand, for example:
- `shards/train/`
- `shards/val/`
- `shards/test/`

6. Launch training:

```bash
python train.py --config python/configs/example_train.py
```

### Why splits are manual

The pipeline does not assign train/validation/test splits during shard compilation.

That is intentional.

It lets you do things like:
- train on standard selfplay shards
- validate on a hand-curated directory of positions
- reserve a separate high-quality search dataset for testing only

In practice, the Python config decides the split simply by choosing which shard directories to open.

## Shard Format

Current format: `ALTR` version `2`.

Header:
- magic: `ALTR`
- version: `u16`
- record count: `u32`
- record size: `u16`
- reserved bytes

Record:
- `packed_board[32]`
- `stm`
- `wdl`
- `eval`

### Packed board layout

Each square is stored in 4 bits:
- `0..11` are the 12 concrete piece values
- `12` is `EMPTY`

So:
- 64 squares
- 4 bits each
- 256 bits total
- 32 bytes per board

This format is intentionally:
- fixed-size
- compact
- architecture-agnostic
- easy to mmap or batch

The shard does not contain:
- white perspective feature indices
- black perspective feature indices
- king buckets
- output buckets

Those are derived in Python at training time.

## Python-Side Training Design

The Python side owns:
- split selection
- feature extraction
- model choice
- loss definition
- validation criteria
- metrics
- export/load behavior for model binaries

The current training path uses:
- packed board shards
- torch-native unpacking and sparse feature construction
- a `SparseBucketNNUE` model that mirrors the engine architecture
- config-driven experiments through `train.py`

## Important Files

### C++

- [src/parsing/record_parser.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/parsing/record_parser.cpp:1)
  - parses `{FEN} | {EVAL} | {WDL}`
- [src/parsing/fen_parser.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/parsing/fen_parser.cpp:1)
  - FEN parser with compatibility handling for older Altair datagen bugs
- [src/analytics/streaming_stats.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/analytics/streaming_stats.cpp:1)
  - single-pass analytics aggregator
- [src/compilation/shard_format.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/compilation/shard_format.h:1)
  - packed-board shard format
- [src/compilation/shard_compiler.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/compilation/shard_compiler.cpp:1)
  - raw text to packed-board shard compilation

### Python

- [python/data/shard_epoch_loader.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/shard_epoch_loader.py:1)
  - shard-wise loader used for training and validation
- [python/data/batching.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/batching.py:1)
  - low-level record-to-batch conversion helpers
- [python/data/feature_extractor.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/feature_extractor.py:1)
  - torch-native unpacking and sparse feature extraction
- [python/models/sparse_bucket_nnue.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/models/sparse_bucket_nnue.py:1)
  - the current NNUE model
- [python/train/trainer.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/train/trainer.py:1)
  - generic trainer
- [python/configs/example_train.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/configs/example_train.py:1)
  - example full training config

## Convenience Scripts In The Repo Root

Outside `pipeline/`, there are two useful helper scripts:

- [prepare_analysis.sh](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/prepare_analysis.sh:1)
  - convenience wrapper for analysis and plotting
- [run_all_tests.sh](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/run_all_tests.sh:1)
  - runs engine and pipeline tests together

If you want the lowest-friction analytics workflow, use `prepare_analysis.sh`.

If you want the most explicit and controllable pipeline workflow, use the C++ executables directly.
