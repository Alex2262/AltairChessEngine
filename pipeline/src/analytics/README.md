# analytics

`analytics/` computes single-pass summaries over parsed records.

The intended use is dataset inspection, not training.

## What It Tracks

The current analytics layer includes:
- basic counts
- parse error summaries
- evaluation histograms
- WDL distribution
- side to move
- castling rights
- king positions
- en passant distribution
- piece-count distributions
- material configuration counts
- material phase summaries
- approximate uniqueness via HyperLogLog

## Main Files

- [metrics.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/analytics/metrics.h:1)
- [metrics.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/analytics/metrics.cpp:1)
  - compact metric structs and CSV writers
- [streaming_stats.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/analytics/streaming_stats.h:1)
- [streaming_stats.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/analytics/streaming_stats.cpp:1)
  - top-level aggregation interface
- [csv_writer.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/analytics/csv_writer.h:1)
- [csv_writer.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/analytics/csv_writer.cpp:1)
  - simple CSV output helper

## Design Note

The metrics are intentionally data-oriented and centralized rather than split into many tiny classes. The aim is to keep the analytics layer easy to scan and cheap to evolve.
