#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PIPELINE_DIR="$ROOT_DIR/pipeline"
BUILD_DIR="$PIPELINE_DIR/build"

DATA_DIR=""
ANALYSIS_DIR=""
FILE_GLOB="*.txt"
QUIET=0
GENERATE_PLOTS=0

usage() {
    cat <<EOF
Usage: $0 --data_dir <dir> --analysis_dir <dir> [options]

Prepare Altair pipeline analytics CSVs from a directory of raw datagen files.

Required:
  --data_dir <dir>       Directory containing raw datagen files
  --analysis_dir <dir>   Output directory for analytics CSVs

Options:
  --glob <pattern>       File glob inside data_dir (default: *.txt)
  --build_dir <dir>      Pipeline build directory (default: pipeline/build)
  --quiet                Suppress analyze_raw progress output
  --plots                Also generate Python plots into analysis_dir/plots
  -h, --help             Show this help message

Examples:
  $0 --data_dir ./data --analysis_dir ./analysis
  $0 --data_dir ./data --analysis_dir ./analysis --glob 'chunk_*.txt' --plots
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --data_dir)
            DATA_DIR="${2:-}"
            shift 2
            ;;
        --analysis_dir)
            ANALYSIS_DIR="${2:-}"
            shift 2
            ;;
        --glob)
            FILE_GLOB="${2:-}"
            shift 2
            ;;
        --build_dir)
            BUILD_DIR="${2:-}"
            shift 2
            ;;
        --quiet)
            QUIET=1
            shift
            ;;
        --plots)
            GENERATE_PLOTS=1
            shift
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1" >&2
            usage >&2
            exit 1
            ;;
    esac
done

if [[ -z "$DATA_DIR" || -z "$ANALYSIS_DIR" ]]; then
    echo "Both --data_dir and --analysis_dir are required." >&2
    usage >&2
    exit 1
fi

if [[ ! -d "$DATA_DIR" ]]; then
    echo "Data directory not found: $DATA_DIR" >&2
    exit 1
fi

mkdir -p "$ANALYSIS_DIR"
mkdir -p "$BUILD_DIR"

echo "==> Configuring pipeline"
cmake -S "$PIPELINE_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release

echo "==> Building analyze_raw"
cmake --build "$BUILD_DIR" --target analyze_raw -j8

INPUT_FILES=()
while IFS= read -r file; do
    INPUT_FILES+=("$file")
done < <(find "$DATA_DIR" -type f -name "$FILE_GLOB" | sort)

if [[ ${#INPUT_FILES[@]} -eq 0 ]]; then
    echo "No input files matched '$FILE_GLOB' under $DATA_DIR" >&2
    exit 1
fi

echo "==> Found ${#INPUT_FILES[@]} input file(s)"
echo "==> Writing analytics CSVs to $ANALYSIS_DIR"

if [[ "$QUIET" -eq 1 ]]; then
    "$BUILD_DIR/analyze_raw" "${INPUT_FILES[@]}" -o "$ANALYSIS_DIR" --quiet
else
    "$BUILD_DIR/analyze_raw" "${INPUT_FILES[@]}" -o "$ANALYSIS_DIR"
fi

if [[ "$GENERATE_PLOTS" -eq 1 ]]; then
    PLOTS_DIR="$ANALYSIS_DIR/plots"
    echo
    echo "==> Generating plots in $PLOTS_DIR"
    python3 "$PIPELINE_DIR/python/visualization/plot_analytics.py" "$ANALYSIS_DIR" -o "$PLOTS_DIR"
fi

echo
echo "Analytics ready in: $ANALYSIS_DIR"
if [[ "$GENERATE_PLOTS" -eq 0 ]]; then
    echo "To generate plots next, run:"
    echo "python3 \"$PIPELINE_DIR/python/visualization/plot_analytics.py\" \"$ANALYSIS_DIR\" -o \"$ANALYSIS_DIR/plots\""
fi
