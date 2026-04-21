"""Training framework pieces for Altair NNUE experiments."""

from .config import TrainingRun, build_run_from_module
from .criteria import Criterion, EvalCriterion, WDLCriterion
from .metrics import EvalMAE, Metric, WDLAccuracy
from .objectives import BlendedValueObjective, LossObjective
from .schedules import ConstantSchedule, LinearInterpolationSchedule
from .trainer import Trainer, TrainerConfig

__all__ = [
    "TrainingRun",
    "build_run_from_module",
    "Criterion",
    "EvalCriterion",
    "WDLCriterion",
    "Metric",
    "EvalMAE",
    "WDLAccuracy",
    "LossObjective",
    "BlendedValueObjective",
    "ConstantSchedule",
    "LinearInterpolationSchedule",
    "Trainer",
    "TrainerConfig",
]
