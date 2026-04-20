# core

`core/` contains the minimal chess representation used by the pipeline.

This is not the engine's full `Position` class. It is a smaller, pipeline-oriented representation intended for:
- parsing
- validation
- analytics
- hashing
- shard serialization

## Main Files

- [types.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/core/types.h:1)
  - core enums and helpers for colors, pieces, squares, and labels
- [canonical_position.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/core/canonical_position.h:1)
  - board storage and small helper methods
- [canonical_position.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/core/canonical_position.cpp:1)
  - structural validation and material summaries
- [canonical_zobrist.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/core/canonical_zobrist.h:1)
  - hashing interface
- [canonical_zobrist.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/core/canonical_zobrist.cpp:1)
  - deterministic hash table setup

## Why A Separate Pipeline Position Type Exists

Sharing the full engine `Position` class would pull in a lot of engine-only state and behavior:
- NNUE state
- move-generation concerns
- make/undo machinery
- search-oriented invariants

The pipeline only needs a clean, validated board representation, so `CanonicalPosition` exists to keep that boundary sharp.
