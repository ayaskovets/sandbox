from dataclasses import dataclass
from typing import List

from avby.definitions import RequestProperty, Sorting


@dataclass
class FiltersApplyRequest:
    page: int
    properties: List[RequestProperty]
    sorting: Sorting
