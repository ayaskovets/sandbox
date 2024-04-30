# pylint: disable=missing-module-docstring
# pylint: disable=missing-function-docstring
# pylint: disable=invalid-name

from algo.context import Context
from algo.operations import Metric


def selection_sort(items, ctx: Context):
    n = len(items)

    for i in range(n):
        min_j = i
        for j in range(i + 1, n):
            ctx.account(Metric.COMPARISONS)
            if items[min_j] > items[j]:
                min_j = j
        ctx.account(Metric.SWAPS)
        items[min_j], items[i] = items[i], items[min_j]

    return items
