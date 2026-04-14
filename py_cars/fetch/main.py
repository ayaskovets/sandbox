import json
import sys
import os
import itertools
import time
import random
from dataclasses import asdict

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from avby.client import filters_apply
from avby.definitions import (
    Sorting,
    PriceCurrency,
    MinMax,
    RequestPropertyYear,
    RequestPropertyPriceCurrency,
    RequestPropertyPriceUsd,
    RequestPropertyEngineType,
    RequestPropertyPlaceRegion,
    RequestPropertyPlaceCity,
    EngineType,
    Region,
    City,
    RequestPropertyVinIndicated,
    RequestPropertyRegistrationCountry,
    RegistrationCountry,
    RequestPropertyTransmissionType,
    TransmissionType,
)
from avby.requests import FiltersApplyRequest
from avby.responses import FiltersApplyError


RETRIES = 3


def main():
    pageCount = None

    for page in itertools.count(start=1):
        with open(os.path.join("pages", f"page_{page}.json"), "w") as db:
            for retry in range(RETRIES):
                time.sleep(random.randint(1, 5))

                request = FiltersApplyRequest(
                    page=page,
                    properties=[
                        RequestPropertyYear(value=MinMax(min=2018, max=None)),
                        RequestPropertyPriceUsd(value=MinMax(min="10000", max="35000")),
                        RequestPropertyPriceCurrency(value=PriceCurrency.USD),
                        RequestPropertyEngineType(
                            value=[
                                EngineType.DIESEL,
                                EngineType.GASOLINE,
                                EngineType.GASOLINE_HYBRID,
                                EngineType.DIESEL_HYBRID,
                            ],
                        ),
                        RequestPropertyPlaceRegion(value=[Region.MINSK]),
                        RequestPropertyPlaceCity(value=[City.MINSK]),
                        RequestPropertyVinIndicated(value=True),
                        RequestPropertyRegistrationCountry(
                            value=RegistrationCountry.BELARUS
                        ),
                        RequestPropertyTransmissionType(
                            value=[
                                TransmissionType.AUTOMATIC,
                                TransmissionType.ROBOT,
                                TransmissionType.VARIATOR,
                            ],
                        ),
                    ],
                    sorting=Sorting.UPDATED,
                )
                response = filters_apply(request)

                if not isinstance(response, FiltersApplyError):
                    pageCount = response.pageCount
                    print(f"Loaded page {page}/{pageCount}")
                    break

                if retry == RETRIES - 1:
                    print(
                        f"Failed all retries for page {page}/{pageCount}: {response.message}"
                    )

            db.write(json.dumps(asdict(response)))

        if page >= pageCount:
            print(f"Done on page {page}/{pageCount}")
            break


if __name__ == "__main__":
    main()
