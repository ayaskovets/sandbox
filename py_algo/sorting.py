# pylint: disable=missing-module-docstring
# pylint: disable=missing-function-docstring
# pylint: disable=unnecessary-lambda-assignment

import random

from algo.analyse import analyse
from algo.operations import Aggregation, Metric
from algo.test import test

from sorting.bubble_sort import bubble_sort
from sorting.merge_sort import merge_sort
from sorting.selection_sort import selection_sort


if __name__ == '__main__':
    # list of algorithms to test and analyse
    algorithms = [
        bubble_sort,
        merge_sort,
        selection_sort,
    ]

    # list of inputs to run the algorithms on
    inputs = [
        random.sample(range(-size, size), size)
        for size in (list(range(0, 3001, 300)))
    ]

    # output predicate to test sorting functions
    is_sorted = lambda out: out == sorted(out)

    # big O x axis (weight calculation for input)
    weights = [
        ('n', len),
        ('sum', sum),
    ]

    # big O y axis (operations to analyse)
    operations = [
        (Aggregation.AVERAGE, Metric.COMPARISONS),
        (Aggregation.AVERAGE, Metric.RUNTIME_MS),
    ]

    # run tests and check that the output satisfies the passed predicate
    test(algorithms, inputs, is_sorted)

    # run analysis and show complexity in the context of passed weights and
    # operations
    analyse(algorithms, inputs, weights, operations)
