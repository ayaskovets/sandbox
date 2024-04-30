"""
    Module containing possible values for complexity analysis of algorithms.
    Generally the enumerations described here can be thought of as selectors
    for BigO y axis
"""

import enum


class Metric(enum.Enum):
    """
        List of metrics available to collect and analyse. The list of manually
        accounted metrics can be extended if necessary
    """

    # manually accounted
    COMPARISONS = 'comparisons'
    SWAPS = 'swaps'

    # automatically accounted
    MEMORY_KB = 'memory (kb)'
    RUNTIME_MS = 'runtime (ms)'


class Aggregation(enum.Enum):
    """
        List of aggregation functions available to analyse. The aggregation
        is applied for all the inputs that have the same weight
    """

    AVERAGE = 'average'
    SUM = 'sum'
