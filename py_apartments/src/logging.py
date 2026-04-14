class __Colors:
    GREEN = "\033[92m"
    YELLOW = "\033[93m"
    RED = "\033[91m"
    ENDC = "\033[0m"


def __log(*args, **kwargs):
    print(*args, **kwargs)


def debug(*args, **kwargs):
    __log(*args, **kwargs)


def info(*args, **kwargs):
    __log(__Colors.GREEN, sep="", end="", flush=False)
    __log(*args, **kwargs)
    __log(__Colors.ENDC, sep="", end="", flush=False)


def warning(*args, **kwargs):
    __log(__Colors.YELLOW, sep="", end="", flush=False)
    __log(*args, **kwargs)
    __log(__Colors.ENDC, sep="", end="", flush=False)


def error(*args, **kwargs):
    __log(__Colors.RED, sep="", end="", flush=False)
    __log(*args, **kwargs)
    __log(__Colors.ENDC, sep="", end="", flush=False)
