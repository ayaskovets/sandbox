# pylint: disable=missing-module-docstring
# pylint: disable=missing-class-docstring

import enum


class Colors(enum.Enum):
    OK = '\033[92m'
    INFO = '\033[94m'
    ERROR = '\033[91m'
    END = '\033[0m'


def print_info(*args, **kwargs) -> None:
    """
        Print with blue color
    """

    print(Colors.INFO.value, sep='', end='')
    print(*args, **kwargs)
    print(Colors.END.value, sep='', end='')


def print_ok(*args, **kwargs) -> None:
    """
        Print with green color
    """
    print(Colors.OK.value, sep='', end='')
    print(*args, **kwargs)
    print(Colors.END.value, sep='', end='')


def print_error(*args, **kwargs) -> None:
    """
        Print with red color
    """
    print(Colors.ERROR.value, sep='', end='')
    print(*args, **kwargs)
    print(Colors.END.value, sep='', end='')


def progress(items, length=10):
    for i, item in enumerate(items):
        yield item
        if (i + 1) % (len(items) // min(len(items), length)) == 0:
            print_info('.', sep='', end='', flush=True)
