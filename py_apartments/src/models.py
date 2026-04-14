import datetime
import dataclasses
import typing


@dataclasses.dataclass
class AreaRange:
    min: float
    max: float


@dataclasses.dataclass
class PriceRange:
    min: int
    max: int


@dataclasses.dataclass
class YearRange:
    min: int
    max: int


@dataclasses.dataclass
class Location:
    lon: float
    lat: float


@dataclasses.dataclass
class BoundingBox:
    bottom_left: Location
    top_right: Location


@dataclasses.dataclass
class FloorRange:
    min: int
    max: int


@dataclasses.dataclass
class RoomsRange:
    min: int
    max: int


@dataclasses.dataclass
class ResaleFlag:
    resale: bool


@dataclasses.dataclass
class CreatedAtLowerBound:
    min: datetime.datetime


@dataclasses.dataclass
class UpdatedAtLowerBound:
    min: datetime.datetime


@dataclasses.dataclass
class DistrictsSet:
    districts: typing.List[str]


@dataclasses.dataclass
class RequestSettings:
    backoff_interval = datetime.timedelta(milliseconds=500)


@dataclasses.dataclass
class ParsedApartment:
    link: str
    floor: int
    rooms: int
    area: float
    price_usd: float
    resale: bool
    created_at: str
    updated_at: str
    district: str


@dataclasses.dataclass
class Snapshot:
    created_at: str
    source: str
    apartments: typing.List[typing.Any]
