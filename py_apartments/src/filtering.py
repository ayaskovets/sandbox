import collections
import datetime
import typing

import logging
import parsing
import geo
import models


def __apply_filter(
    fltr: (
        models.FloorRange
        | models.RoomsRange
        | models.AreaRange
        | models.PriceRange
        | models.ResaleFlag
        | models.CreatedAtLowerBound
        | models.UpdatedAtLowerBound
        | models.DistrictsSet
    ),
    apartment: models.ParsedApartment,
) -> bool:
    if isinstance(fltr, models.FloorRange):
        return fltr.min <= apartment.floor <= fltr.max
    elif isinstance(fltr, models.RoomsRange):
        return fltr.min <= apartment.rooms <= fltr.max
    elif isinstance(fltr, models.AreaRange):
        return fltr.min <= apartment.area <= fltr.max
    elif isinstance(fltr, models.PriceRange):
        return fltr.min <= apartment.price_usd <= fltr.max
    elif isinstance(fltr, models.ResaleFlag):
        return fltr.resale == apartment.resale
    elif isinstance(fltr, models.CreatedAtLowerBound):
        return fltr.min <= datetime.datetime.fromisoformat(apartment.created_at)
    elif isinstance(fltr, models.UpdatedAtLowerBound):
        return fltr.min <= datetime.datetime.fromisoformat(apartment.updated_at)
    elif isinstance(fltr, models.DistrictsSet):
        return fltr.districts.count(apartment.district)


def __filter_to_reason(fltr: typing.Any):
    return type(fltr).__name__


def filter_apartments(
    snapshot: models.Snapshot,
    filters: typing.List[
        models.FloorRange
        | models.RoomsRange
        | models.AreaRange
        | models.PriceRange
        | models.ResaleFlag
        | models.CreatedAtLowerBound
        | models.UpdatedAtLowerBound
        | models.DistrictsSet
    ],
) -> typing.List[models.ParsedApartment]:
    """
    Make a filter for apartments with fixed parameters
    """

    passed = []
    not_passed_reasons = collections.defaultdict(int)

    for i, apartment in enumerate(snapshot.apartments, start=1):
        if (progress := round(i / len(snapshot.apartments) * 100, 2)) % 5 == 0:
            logging.debug(f"filtered {progress}% of apartments...")

        parsed_apartment = parsing.parse_apartment(apartment, snapshot.source)

        for fltr in filters:
            if not __apply_filter(fltr, parsed_apartment):
                not_passed_reasons[__filter_to_reason(fltr)] += 1
                break
        else:
            passed.append(parsed_apartment)

    logging.info(
        f"filtered {sum(not_passed_reasons.values())}/{len(snapshot.apartments)} apartments: {dict(not_passed_reasons.items())}"
    )

    return passed
