# pylint: disable=missing-module-docstring


class FakeContext:
    """
        Dummy class to mock Context in unit-tests
    """

    # pylint: disable=too-few-public-methods
    def __init__(self) -> None:
        pass

    def __getattribute__(self, name):
        return lambda *args, **kwargs: None
