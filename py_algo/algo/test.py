"""
    Module containing the test function to unit-test algorithms before running
    analyser on them
"""


import copy

from algo.internal.log import print_error, print_info, print_ok, progress
from algo.internal.fake_context import FakeContext

from algo.types import Algorithm, Input, Predicate


def test(algorithms: list[Algorithm], inputs: list[Input],
         predicate: Predicate) -> None:
    """
        Arguments:
          - algoritms: list of functions each taking one input value of
                arbitrary type and return an output of arbitrary type

          - inputs: list of inputs to run the algorithms on

          - predicate: callable taking the output of each algorithm and
                returning bool that indicates whether the algorithm executed
                correctly

        Returns:
          - None
    """

    for algorithm in algorithms:
        print_info(f'TEST ({algorithm.__name__}) [{len(inputs)}]: ',
                   end='', flush=True)

        for i, inp in enumerate(progress(inputs)):
            ctx = FakeContext()
            out = algorithm(copy.deepcopy(inp), ctx)

            if not predicate(out):
                print_error(
                    f'\nERROR ({algorithm.__name__}) at {i}: {inp} -> {out}')
                assert False

        print_ok(f'\nOK ({algorithm.__name__}) [{len(inputs)}]')
