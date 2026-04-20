# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is the **Altair Chess Engine Data Pipeline** - a C++ pipeline for processing chess training data for NNUE neural network training. It converts raw datagen output (`{FEN} | {EVAL} | {WDL}`) into analytics CSVs and packed-board binary training shards.

The parent directory contains the main Altair chess engine (~3600 ELO, superhuman UCI chess engine).

## Build Commands

### Pipeline (this directory)
```bash
# Build
cd pipeline
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j8

# Clean rebuild
rm -rf build && cmake -B build && cmake --build build
```

### Main Engine (parent directory)
```bash
cd ..
make              # Standard build (clang++, C++20, -O3, LTO)
make pgo          # Profile-guided optimization build
make test         # Build and run tests
```

## CLI Tools

```bash
# Analyze raw datagen files → CSV statistics
./build/analyze_raw data*.txt -o analytics_output/

# Compile to binary shards for training
./build/compile_shards data*.txt -o shards/ --max-shard-mb 256 --shuffle-buffer 200000
```

## Architecture

### Data Flow
```
Raw datagen files ("{FEN} | {EVAL} | {WDL}")
    ↓
RecordParser → FenParser → CanonicalPosition
    ↓
StreamingStats (single-pass analytics aggregation)
    ↓
CSV export OR ShardCompiler (binary format)
```

### Source Layout (`src/`)
- **core/** - Types (Color, Piece, Square), CanonicalPosition, Zobrist hashing
- **parsing/** - FEN parser, record parser for datagen format
- **analytics/** - Streaming stats, histograms, HyperLogLog cardinality estimation
- **compilation/** - Packed-board shard writer (`ALTR` v2 format)

### Binary Shard Format (16-byte header + fixed-size records)
```
Header: "ALTR" + version(2) + record_count(4) + record_size(2) + reserved(4)
Record: packed_board(32) + stm(1) + wdl(1) + eval(2)
```

Boards are stored in an architecture-agnostic 4-bit-per-square format. Python derives sparse white/black perspective features at training time.

### Python (`python/`)
- **data/** - Packed-board shard readers, datasets, feature extraction
- **models/** - NNUE model implementations
- **train/** - Objectives, criteria, schedules, trainer
- **visualization/** - Matplotlib plots for analytics CSVs

## Key Files

| File | Purpose |
|------|---------|
| `src/compilation/shard_compiler.h` | Packed-board shard compilation options |
| `src/parsing/record_parser.cpp` | Parses "{FEN} \| {EVAL} \| {WDL}" format |
| `src/analytics/streaming_stats.cpp` | Single-pass statistics collection |
| `python/data/shard_reader.py` | Python packed-board shard reader |

## NNUE Architecture Context

The main engine uses NNUE with:
- 768 input features (6 piece types × 2 colors × 64 squares)
- 5 king buckets (input layer perspective)
- 8 material output buckets
- Architecture: 768×5 → 768×2 → 1×8

King buckets and sparse white/black perspective features are extracted in PyTorch, not computed in C++ shards.
