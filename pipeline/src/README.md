# src

This directory contains the C++ library portion of the pipeline.

Its job is to do the things that are naturally better on the C++ side:
- parse large raw text files quickly
- validate positions
- aggregate analytics in one pass
- write compact binary shards

It intentionally does not contain:
- training split logic
- model-specific feature tensors
- optimizer logic
- experiment configuration

## Structure

- `core/`
  - minimal chess representation and hashing
- `parsing/`
  - raw datagen parsing and FEN parsing
- `analytics/`
  - streaming dataset summaries and CSV output
- `compilation/`
  - packed-board shard writing

## Design Philosophy

Compared to the engine, this layer is intentionally simpler and more data-oriented.

The guiding idea is:
- do just enough chess logic to validate and serialize data correctly
- leave model and experiment policy to Python

That keeps the pipeline code smaller and reduces drift between “dataset format” concerns and “training experiment” concerns.
