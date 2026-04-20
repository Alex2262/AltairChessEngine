# cli

`cli/` contains the thin C++ entry points for the pipeline library.

These files are intentionally small wrappers around the library code in `src/`.

## Current Entrypoints

### `analyze_raw.cpp`

Builds the `analyze_raw` executable.

Use it to:
- parse raw datagen text files
- validate records
- write analytics CSVs

Example:

```bash
./build/analyze_raw data*.txt -o analytics_output/
```

### `compile_shards.cpp`

Builds the `compile_shards` executable.

Use it to:
- parse raw datagen text files
- validate positions
- write packed-board training shards

Example:

```bash
./build/compile_shards data*.txt -o shards/ --max-shard-mb 256 --shuffle-buffer 200000
```

## Why These Files Stay Thin

The CLI files should only:
- parse arguments
- expand globs
- call library entry points

All real logic belongs in `src/` so it stays testable and reusable.
