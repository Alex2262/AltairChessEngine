# parsing

`parsing/` turns raw text datagen records into validated pipeline records.

## Input Format

The raw datagen format is:

```text
{FEN} | {EVAL} | {WDL}
```

Where:
- `FEN` is a chess position
- `EVAL` is the scalar engine evaluation
- `WDL` is one of the expected training targets such as `1.0`, `0.5`, or `0.0`

## Main Files

- [record_parser.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/parsing/record_parser.h:1)
- [record_parser.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/parsing/record_parser.cpp:1)
  - parse the outer datagen line
- [fen_parser.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/parsing/fen_parser.h:1)
- [fen_parser.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/parsing/fen_parser.cpp:1)
  - parse the FEN payload into `CanonicalPosition`
- [raw_record.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/src/parsing/raw_record.h:1)
  - compact parsed record representation

## Important Detail: Historical FEN Compatibility

The parser intentionally includes compatibility handling for older Altair datagen output where the final-rank empty count could be omitted in certain cases.

That support exists so historical datasets remain usable, but it is scoped to the known old engine bug patterns rather than opening the door to broad malformed-FEN acceptance.
