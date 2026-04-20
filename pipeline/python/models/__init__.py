"""Model interfaces and Altair NNUE implementations."""

from .base import ValueNet
from .sparse_bucket_nnue import SparseBucketNNUE

__all__ = ["ValueNet", "SparseBucketNNUE"]
