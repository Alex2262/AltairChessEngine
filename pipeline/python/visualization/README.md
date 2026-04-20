# visualization

`visualization/` contains analytics plotting scripts.

These read CSV output from `analyze_raw` and generate summary plots such as:
- evaluation distributions
- material and phase distributions
- king heatmaps
- castling and side-to-move summaries

This directory is intentionally separate from the training stack so dataset inspection remains lightweight and independent of the model code.

## Typical Use

If you already have analytics CSVs, you can run the plotting entry point directly from Python.

In normal repository usage, the easiest path is usually the root helper script:

```bash
./prepare_analysis.sh --data_dir ./AltairDataBase --analysis_dir ./AltairDataBaseAnalysis --plots
```

That will:
- build the pipeline if needed
- run `analyze_raw`
- generate plots into the chosen analysis directory
