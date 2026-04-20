# tests

This directory contains the focused pipeline test suite.

The tests are intentionally minimal, but they target the parts of the pipeline most likely to cause bad datasets or incorrect training inputs.

## Current Coverage

The current test file checks:
- canonical position validation
- FEN parsing
- FRC castling parsing
- record parsing from raw datagen lines
- analytics aggregation behavior
- packed-board record packing and unpacking

## Philosophy

These tests are not trying to exhaustively prove all chess correctness.

Instead they are meant to catch the highest-risk failures:
- malformed position acceptance
- incorrect compatibility behavior for historical FEN bugs
- broken packed-board serialization
- obvious analytics regressions
