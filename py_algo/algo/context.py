"""
    Module containing a wrapper for a single algorithm run context
"""

from algo.operations import Metric
from algo.types import Amount, Map, Maybe


class Context:
    """
        Context is a summary of the BigO y axis metrics that describe a single
        run of some algorithm
    """

    def __init__(self) -> None:
        self._operations: Map[Metric, Amount] = {}

    def account(self, metric: Metric, amount: Amount = 1.0) -> None:
        """
            Arguments:
              - metric: an metric to account

              - amount: amount of the metric to account

            Returns:
              - None
        """

        self._operations[metric] =\
            self._operations.get(metric, 0.0) + amount

    def get(self, metric: Metric,
            default: Maybe[Amount] = None) -> Maybe[Amount]:
        """
            Arguments:
              - metric: an metric to get the amount of

              - default: the same as default in dict.get

            Returns:
              - the amount of the metric
        """
        return self._operations.get(metric, default)
