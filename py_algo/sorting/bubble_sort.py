# pylint: disable=missing-module-docstring
# pylint: disable=missing-function-docstring
# pylint: disable=invalid-name

from algo.context import Context
from algo.operations import Metric


def bubble_sort(items, ctx: Context):
    n = len(items)

    for i in range(n):
        for j in range(i + 1, n):
            ctx.account(Metric.COMPARISONS)
            if items[j] < items[i]:
                ctx.account(Metric.SWAPS)
                items[i], items[j] = items[j], items[i]

    return items
