# models

This directory contains interchangeable training networks for Altair.

Right now the important model is [SparseBucketNNUE](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/models/sparse_bucket_nnue.py:1), which is designed to mirror the structure of the engine NNUE in [src/nnue.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/src/nnue.h:1) and [src/nnue.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/src/nnue.cpp:1).

This README explains both:
- the mathematical architecture
- how that architecture is implemented in the Python model

## Purpose

`SparseBucketNNUE` is the current training-time representation of the engine's value network.

It is built around the same ideas as the engine:
- sparse piece-square inputs
- king-bucketed first layer
- dual perspective accumulators
- SCReLU activation
- material-bucketed output layer
- quantized engine export format

The model is not meant to be a generic dense PyTorch MLP. It is a fairly direct training analogue of the engine's accumulator-style NNUE.

## Input Representation

The model does not read dense `768`-dimensional one-hot vectors from disk.

Instead, the training batch provides:
- `packed_boards`
- `stm`
- `wdl`
- `eval`

From the packed board, the model derives sparse active features on-device.

### Why not store features in shards?

Because the shard format is intended to stay architecture-agnostic.

Packed boards:
- are smaller on disk
- are easy to validate
- can support future feature mappings
- avoid storing redundant white/black perspective data

## Mathematical Architecture

The engine architecture is:

1. sparse piece-square features
2. king bucket selection for each perspective
3. accumulator sum into a hidden vector
4. SCReLU activation
5. concatenate side-to-move and non-side-to-move hidden activations
6. select an output bucket based on material
7. single scalar output

### Feature basis

There are `768` input features:

- `2` colors
- `6` piece types
- `64` squares

So:

```text
768 = 2 * 6 * 64
```

Each active piece on the board corresponds to exactly one feature index per perspective.

### Dual perspective

The network keeps two first-layer accumulator views:
- white perspective
- black perspective

At inference time, those become:
- `our`
- `opp`

depending on side to move.

This is exactly what the engine does in [src/nnue.cpp](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/src/nnue.cpp:44):
- if `color == WHITE`, evaluate `(white_accumulator, black_accumulator)`
- else evaluate `(black_accumulator, white_accumulator)`

### King buckets

The first layer is bucketed by king square.

The current Altair-style config uses `5` king buckets. The selected bucket depends on:
- white king square for the white perspective
- vertically mirrored black king square for the black perspective

This matches:
- `KING_BUCKET_MAP` in the engine
- `KING_BUCKET_MAP` in the Python data layer

The first-layer weights are therefore shaped as:

```text
[KING_BUCKETS, INPUT_FEATURES, HIDDEN_SIZE]
```

For the current Altair-style config:

```text
[5, 768, 1024]
```

### Hidden accumulator

For one perspective, the pre-activation hidden vector is:

```text
h = b0 + sum(W0[bucket, feature_i])
```

where:
- `b0` is the first-layer bias
- `feature_i` are the active sparse feature ids for that perspective
- `bucket` is the king bucket for that perspective

This is exactly the accumulator idea used by the engine.

### SCReLU

The activation is squared clipped ReLU:

```text
screlu(x) = clamp(x, 0, QA)^2
```

with:
- `QA = 255`

This matches the engine definition in [src/nnue.h](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/src/nnue.h:91).

The Python model performs:

```text
stm_hidden = clamp(stm_hidden, 0, QA)^2
ntm_hidden = clamp(ntm_hidden, 0, QA)^2
```

### Concatenation

After SCReLU, the two perspective activations are concatenated:

```text
hidden = concat(stm_hidden, ntm_hidden)
```

That gives a vector of size:

```text
2 * HIDDEN_SIZE
```

For the default model:

```text
2048
```

### Output buckets

The output layer is bucketed by material count.

The current Altair-style config uses `8` output buckets, chosen by:

```text
bucket = (piece_count - 2) / 4
```

since:
- there are at most `32` pieces total
- the two kings are always present
- `32 / 8 = 4`

This mirrors the engine's:

```cpp
(popcount(position.all_pieces) - 2) / MATERIAL_OUTPUT_BUCKET_DIVISOR
```

### Scalar output

The model outputs a single scalar.

In engine-style quantized math:

```text
raw = sum(hidden * W1[bucket]) / QA
quantized_sum = raw + b1[bucket]
value_logit = quantized_sum / (QA * QB)
value_cp = value_logit * SCALE
```

with:
- `QA = 255`
- `QB = 64`
- `SCALE = 400`

This is designed to match:

```cpp
(output + output_bias[bucket]) * SCALE / (QA * QB)
```

from the engine.

## How WDL Is Handled

The network itself does not produce a 3-class WDL head.

Instead it produces one scalar `value_logit`.

Training objectives and criteria can interpret that scalar in different ways.

Current WDL objectives use:

```text
sigmoid(value_logit)
```

and compare it against scalar WDL targets:
- loss = `0.0`
- draw = `0.5`
- win = `1.0`

This is closer to the Bullet-style training setup you previously used than a fake 3-logit classifier would be.

## Implementation Details

### Sparse feature extraction

Feature extraction happens in [pipeline/python/data/feature_extractor.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/data/feature_extractor.py:1).

Important points:
- packed boards remain compact through the dataloader
- unpacking is done in torch, not NumPy, for the training path
- STM/NTM feature extraction is separate from bucket extraction
- input bucket extraction uses a caller-supplied king-bucket map
- output bucket extraction uses caller-supplied bucket policy
- the active features are flattened across the batch
- offsets are computed so the model can use batched sparse accumulation

This avoids:
- storing dense 768-vectors
- Python per-sample unpacking at runtime
- architecture-specific preprocessing in the shard format

### Accumulation implementation

The current implementation uses `embedding_bag`-style accumulation.

Conceptually:

```text
for each sample:
    hidden = bias + sum(weight_rows_for_active_features)
```

Implementation-wise:
- first-layer weights are flattened from `[bucket, feature, hidden]` into `[bucket * feature, hidden]`
- each active feature index is shifted by its king bucket
- `torch.nn.functional.embedding_bag(..., mode="sum")` sums the rows for each sample efficiently

This is much better than:
- materializing dense one-hot inputs
- looping over batch items in Python

### Shared first-layer weights

There are not separate first-layer weights for STM and NTM.

That is intentional and correct.

The engine also uses one shared first-layer tensor. The difference between the two perspectives comes from:
- different feature ids
- different king buckets
- different ordering at the output stage (`our` vs `opp`)

### Export and load

`SparseBucketNNUE` owns its own engine binary I/O:
- `export_engine_format(path)`
- `from_engine_bin(path, ...)`
- `load_from_engine_bin(path, ...)`

This is on the model itself because:
- binary layout is model-specific
- quantization/scaling assumptions are model-specific
- another model may need a different export format or no export at all

The loader validates:
- hidden size compatibility
- exact expected parameter payload size
- engine trailing struct padding

The exporter writes the same layout as the engine `NNUE_Params` blob, including padding preservation when a model was loaded from an existing engine binary.

### Exact engine round-trip

The current implementation has been checked against the real engine net file:
- load `src/ceres-net.bin`
- export back out
- compare bytes

That round trip now matches exactly.

## Performance Notes

The current path is designed to be GPU-friendly:
- packed boards remain compact until batch time
- feature extraction is torch-native
- accumulation is batched and sparse

This is much better than the earlier prototype that:
- converted boards through NumPy in the forward path
- looped over samples in Python for first-layer accumulation

That said, this is still a PyTorch implementation of an accumulator network, not a custom fused CUDA kernel. If training throughput becomes the bottleneck later, the next possible step would be profiling and deciding whether a more specialized kernel is worthwhile.

## Key Shapes

Current Altair-style configuration:

- first-layer weights: `[5, 768, 1024]`
- first-layer bias: `[1024]`
- output weights: `[8, 2048]`
- output bias: `[8]`

Per batch:

- packed boards: `[B, 32]`
- white hidden: `[B, 1024]`
- black hidden: `[B, 1024]`
- concatenated hidden: `[B, 2048]`
- scalar output: `[B]`

## How To Use

### Instantiate a fresh model

```python
from pipeline.python.models import SparseBucketNNUE

model = SparseBucketNNUE(hidden_size=1024)
```

### Load the engine net

```python
model = SparseBucketNNUE.load_from_engine_bin("src/ceres-net.bin")
```

### Export a trained model

```python
model.export_engine_format("my-net.bin")
```

### Use in a training config

See:
- [pipeline/python/configs/example_train.py](/Users/alexandertian/workspace/projects/games/chess/dev/Altair/pipeline/python/configs/example_train.py:1)

That config shows how to:
- construct shard datasets
- build dataloaders
- instantiate the model
- define optimizer/objective/metrics
- launch through `pipeline/train.py`
