from typing import List
from dataclasses import dataclass

from avby.definitions import Advert


@dataclass
class FiltersApplyResponse:
    count: int
    pageCount: int
    page: int
    adverts: List[Advert]
    advertsPerPage: int
    initialValue: str


@dataclass
class FiltersApplyError:
    message: str
