#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "==> Running engine tests"
make -C "$ROOT_DIR" test

echo
echo "==> Building pipeline tests"
cmake -S "$ROOT_DIR/pipeline" -B "$ROOT_DIR/pipeline/build" -DCMAKE_BUILD_TYPE=Release
cmake --build "$ROOT_DIR/pipeline/build" -j8

echo
echo "==> Running pipeline tests"
ctest --test-dir "$ROOT_DIR/pipeline/build" --output-on-failure

echo
echo "All tests passed."
