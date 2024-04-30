# pylint: disable=missing-module-docstring
# pylint: disable=missing-function-docstring
# pylint: disable=invalid-name

from algo.context import Context
from algo.operations import Metric


def merge_sort(items, ctx: Context):
    n = len(items)

    ctx.account(Metric.COMPARISONS)
    if n < 2:
        return items

    m = n // 2
    l, r = items[:m], items[m:]

    merge_sort(l, ctx=ctx)
    merge_sort(r, ctx=ctx)

    i = j = 0
    for k in range(n):
        ctx.account(Metric.COMPARISONS)
        if i >= len(l):
            items[k] = r[j]
            j += 1
            continue

        ctx.account(Metric.COMPARISONS)
        if j >= len(r):
            items[k] = l[i]
            i += 1
            continue

        ctx.account(Metric.COMPARISONS)
        if l[i] < r[j]:
            items[k] = l[i]
            i += 1
        else:
            items[k] = r[j]
            j += 1

    return items
