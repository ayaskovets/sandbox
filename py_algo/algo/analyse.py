"""
    Module containing the analyse function to analyse and display
    computational complexity of algorithms
"""

import collections

from algo.internal.aggregation import aggregate
from algo.internal.log import print_info, print_ok, progress
from algo.internal.run import run_algorithm
from algo.internal.show import show_analysis
from algo.internal.weights import calculate_weights

from algo.context import Context
from algo.types import Algorithm, Alias, Amount, Input, Map, Operation, Weights


def analyse(algorithms: list[Algorithm], inputs: list[Input],
            weights: Weights, operations: list[Operation]) -> None:
    """
        Arguments:
          - algorithms: list of functions each taking one input value of
                arbitrary type and return an output of arbitrary type

          - inputs: list of inputs to run the algorithms on

          - weights: list of tuples(alias, function), where function is a
                callable taking a single input from inputs and returning
                the weight of this input, (for example in the context of
                sorting function weight of the sorted list is its length) and
                alias is a name for this function to display on the analysis
                graph

          - operations: list of tuples(aggregation, operation) to use as
                a y axis values for complexity analysis i.e. that depend
                on the input weights

        Returns:
          - None
    """

    weights_by_alias: Map[Alias, list[Amount]] =\
        calculate_weights(inputs, weights)

    ctxs_by_algorithm: Map[Algorithm, list[Context]] =\
        collections.defaultdict(list)
    for algorithm in algorithms:
        print_info(f'RUN ({algorithm.__name__}) [{len(inputs)}]: ', end='',
                   flush=True)

        for inp in progress(inputs):
            ctx = run_algorithm(algorithm, inp)
            ctxs_by_algorithm[algorithm].append(ctx)

        print_ok(f'\nDONE ({algorithm.__name__}) [{len(inputs)}]')

    plots = aggregate(weights_by_alias, ctxs_by_algorithm, operations)

    show_analysis(plots)
