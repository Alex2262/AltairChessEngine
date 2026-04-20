# compilation

`compilation/` turns validated parsed records into packed-board training shards.

## Current Format

The current shard format is `ALTR` version `2`.

Each record is fixed-size:
- 32 bytes of packed board data
- 1 byte for side to move
- 1 byte for WDL
- 2 bytes for eval

This is intentionally much simpler than the older sparse-feature shard idea.

## Main Files

- [shard_format.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/compilation/shard_format.h:1)
  - binary layout plus pack/unpack helpers
- [shard_writer.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/compilation/shard_writer.h:1)
- [shard_writer.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/compilation/shard_writer.cpp:1)
  - low-level fixed-record writer
- [shard_compiler.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/compilation/shard_compiler.h:1)
- [shard_compiler.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/compilation/shard_compiler.cpp:1)
  - raw datagen to shard conversion and shuffle-buffer mixing

## Shuffle Buffer

Shard compilation supports a shuffle buffer so shard-local record order is not just raw sequential game order.

That improves training behavior without forcing the shard format itself to own split logic or model-specific preprocessing.

## Design Note

This layer deliberately does not choose train/validation/test splits. That is a Python-side responsibility.
