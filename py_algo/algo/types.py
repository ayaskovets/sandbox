"""
    Module containing common type definitions for the library
"""

import typing

from algo.operations import Aggregation, Metric

Maybe = typing.Optional
Map = typing.Dict

Input = typing.Any
Output = typing.Any
Algorithm = typing.Callable[[Input], Output]

Operation = tuple[Aggregation, Metric]

Predicate = typing.Callable[[Input], bool]

Amount = float
Alias = str
Weights = tuple[Alias, typing.Callable[[Input], Amount]]
Plot = tuple[list[Amount], list[Amount]]
