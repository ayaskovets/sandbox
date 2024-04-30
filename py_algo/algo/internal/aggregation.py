# pylint: disable=missing-module-docstring

import collections
import itertools
import operator

from algo.context import Context
from algo.operations import Aggregation
from algo.types import Algorithm, Alias, Amount, Map, Operation, Plot


# pylint: disable=inconsistent-return-statements
def _aggregate_operation(ctxs: list[Context],
                         operation: Operation) -> Amount:
    aggregation, metric = operation

    if aggregation == Aggregation.AVERAGE:
        return sum(ctx.get(metric, 0.0) for ctx in ctxs) / len(ctxs)

    if aggregation == Aggregation.SUM:
        return sum(ctx.get(metric, 0.0) for ctx in ctxs)

    assert not 'implemented yet!'


def aggregate(weights_by_alias: Map[Alias, list[Amount]],
              ctxs_by_algorithm: Map[Algorithm, list[Context]],
              operations: list[Operation]) ->\
        Map[Operation, Map[Alias, Map[Algorithm, Plot]]]:
    """
        Takes pre-calculated input weights and contexts collected by the
        analysed algorithms, returns data to be plotted on graph
    """

    plots: Map[Operation, Map[Alias, Map[Algorithm, Plot]]] =\
        collections.defaultdict(lambda: collections.defaultdict(
            lambda: collections.defaultdict(Plot)))

    for alias, weights in weights_by_alias.items():
        for algorithm, ctxs in ctxs_by_algorithm.items():
            key = operator.itemgetter(0)
            weights_ctxs = sorted(zip(weights, ctxs), key=key)

            # pylint: disable=invalid-name
            x = [key for key, _ in itertools.groupby(weights_ctxs, key=key)]
            for operation in operations:
                y = [_aggregate_operation(
                    [item[1] for item in group], operation)
                    for _, group in itertools.groupby(weights_ctxs, key=key)]

                plots[operation][alias][algorithm] = (x, y)

    return plots
