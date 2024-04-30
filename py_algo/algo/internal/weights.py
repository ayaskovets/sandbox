# pylint: disable=missing-module-docstring

import collections

from algo.types import Alias, Amount, Input, Map, Weights


def calculate_weights(inputs: list[Input],
                      weights: Weights) -> Map[Alias, list[Amount]]:
    """
        Calculates weights taken from weights parameter for each input
    """

    weights_by_alias: Map[Alias, list[Amount]] = collections.defaultdict(list)

    for alias, function in weights:
        for inp in inputs:
            weights_by_alias[alias].append(function(inp))

    return weights_by_alias
