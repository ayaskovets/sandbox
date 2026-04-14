import itertools
import time
import typing

import requests

import logging
import models


def __filter_to_query_params(
    fltr: models.AreaRange | models.PriceRange | models.YearRange | models.BoundingBox,
):
    if isinstance(fltr, models.AreaRange):
        return {"area[min]": fltr.min, "area[max]": fltr.max}
    elif isinstance(fltr, models.PriceRange):
        return {"price[min]": fltr.min, "price[max]": fltr.max}
    elif isinstance(fltr, models.YearRange):
        return {
            "building_year[min]": fltr.min,
            "building_year[max]": fltr.max,
        }
    elif isinstance(fltr, models.BoundingBox):
        return {
            "bounds[lb][lat]": fltr.bottom_left.lat,
            "bounds[lb][long]": fltr.bottom_left.lon,
            "bounds[rt][lat]": fltr.top_right.lat,
            "bounds[rt][long]": fltr.top_right.lon,
        }


def fetch_apartments(
    filters: typing.List[
        models.AreaRange | models.PriceRange | models.YearRange | models.BoundingBox
    ],
    settings: models.RequestSettings,
):
    """
    Fetch optionally filtered apartments from onliner.by
    """

    URL = "https://r.onliner.by/sdapi/pk.api/search/apartments"
    PARAMS = {"currency": "usd", "v": 0.9904402120685976}

    params = PARAMS
    for fltr in filters:
        params.update(__filter_to_query_params(fltr))

    logging.info(f"fetching apartments from {URL}...")

    apartments = []

    for page in itertools.count(start=1):
        url = URL
        params = PARAMS | {"page": page}

        try:
            response = requests.get(url=url, params=params)
            response_json = response.json()
        except:
            logging.error(f"failed request page={page} from url={response.request.url}")
            continue

        total = response_json["total"]
        on_page = response_json["page"]["items"]
        last_page = response_json["page"]["last"]

        apartments.extend(response_json["apartments"])

        logging.debug(f"received={len(apartments)}/{total}")

        if page == last_page or on_page <= 0:
            break

        time.sleep(settings.backoff_interval.microseconds / 1000000)

    logging.info(f"got {len(apartments)} apartments from {URL}")

    return apartments
