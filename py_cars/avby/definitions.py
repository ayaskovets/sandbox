from dataclasses import dataclass
from typing import Optional, List
from enum import Enum


class Sorting(int, Enum):
    UPDATED = 1
    CHEAP = 2
    EXPENSIVE = 3
    NEWEST_ADVERTS = 4
    OLDEST_ADVERTS = 5
    NEWEST_CARS = 6
    OLDEST_CARS = 7
    MILEAGE = 8


class Region(int, Enum):
    MINSK = 1005


class City(int, Enum):
    MINSK = 2


class Condition(int, Enum):
    NEW = 5
    USED = 2


class PriceCurrency(int, Enum):
    BYN = 1
    USD = 2


class RegistrationCountry(int, Enum):
    BELARUS = 2


class EngineType(int, Enum):
    GASOLINE = 1
    GASOLINE_PROPANUM = 2
    GASOLINE_METHANE = 3
    GASOLINE_HYBRID = 4
    DIESEL = 5
    DIESEL_HYBRID = 6
    ELECTRIC = 7


class TransmissionType(int, Enum):
    AUTOMATIC = 1
    ROBOT = 3
    VARIATOR = 4


@dataclass
class MinMax:
    max: Optional[object]
    min: Optional[object]


@dataclass
class RequestPropertyYear:
    value: MinMax
    name: str = "year"


@dataclass
class RequestPropertyPriceCurrency:
    value: PriceCurrency
    name: str = "price_currency"


@dataclass
class RequestPropertyPriceUsd:
    value: MinMax
    name: str = "price_usd"


@dataclass
class RequestPropertyPriceByn:
    value: MinMax
    name: str = "price_byn"


@dataclass
class RequestPropertyEngineType:
    value: List[EngineType]
    name: str = "engine_type"


@dataclass
class RequestPropertyVinIndicated:
    value: bool
    name: str = "vin_indicated"


@dataclass
class RequestPropertyPlaceRegion:
    value: List[Region]
    name: str = "place_region"


@dataclass
class RequestPropertyPlaceCity:
    value: List[City]
    name: str = "place_city"


@dataclass
class RequestPropertyPlaceCondition:
    value: List[Condition]
    name: str = "condition"


@dataclass
class RequestPropertyRegistrationCountry:
    value: int
    name: str = "registration_country"


@dataclass
class RequestPropertyTransmissionType:
    value: List[TransmissionType]
    name: str = "transmission_type"


RequestProperty = (
    RequestPropertyYear
    | RequestPropertyEngineType
    | RequestPropertyPriceCurrency
    | RequestPropertyPriceUsd
    | RequestPropertyPriceByn
    | RequestPropertyVinIndicated
    | RequestPropertyPlaceRegion
    | RequestPropertyPlaceCity
    | RequestPropertyPlaceCondition
    | RequestPropertyTransmissionType
)


@dataclass
class PriceDescription:
    currency: str
    amount: int
    amountFiat: float


@dataclass
class Price:
    usd: Optional[PriceDescription]
    byn: Optional[PriceDescription]
    rub: Optional[PriceDescription]
    eur: Optional[PriceDescription]


@dataclass
class ResponsePropertyBrand:
    value: str
    name: str = "brand"


@dataclass
class ResponseProperty:
    value: object
    name: str


@dataclass
class VinInfo:
    vin: str
    checked: bool


@dataclass
class OptionGroup:
    id: int
    name: str


@dataclass
class Option:
    id: int
    name: str
    optionGroup: OptionGroup


@dataclass
class Metadata:
    vinInfo: Optional[VinInfo]
    brandId: int
    brandSlug: str
    modelId: int
    modelSlug: str
    generationId: Optional[int]
    year: int
    onOrder: bool
    options: List[Option]


@dataclass
class Advert:
    id: int
    originalDaysOnSale: int
    isRent: bool
    status: str
    advertType: str
    price: Price
    description: Optional[str]
    publishedAt: str
    refreshedAt: str
    shortLocationName: str
    properties: List[ResponseProperty]
    publicUrl: str
    year: int
    metadata: Metadata
    foreignIp: bool
