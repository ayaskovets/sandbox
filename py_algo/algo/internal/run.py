# pylint: disable=missing-module-docstring

import copy
import time

from algo.context import Context
from algo.operations import Metric
from algo.types import Algorithm, Input


NS_IN_MS = 1e6


def run_algorithm(algorithm: Algorithm, inp: Input) -> Context:
    """
        Run the algorithm on the input and return the run context containing
        metainformation and metrics to analyse about the run
    """

    ctx = Context()
    inp = copy.deepcopy(inp)

    start = time.time_ns()
    algorithm(inp, ctx)
    end = time.time_ns()

    ctx.account(Metric.RUNTIME_MS, (end - start) / NS_IN_MS)

    return ctx
