import json

import shapely.geometry

import logging
import models

__DISTRICTS = {}


def set_districts(path: str):
    """
    Parse districts from geojson associative array
    """

    __DISTRICTS.clear()

    with open(path, "r") as f:
        districts = json.load(f)

        for district, polygon in districts.items():
            __DISTRICTS[district] = shapely.geometry.shape(polygon)

    logging.info(f"loaded {len(__DISTRICTS)} districts from {path}")


def location_to_district(location: models.Location):
    if not __DISTRICTS:
        logging.warning("districts are empty, probably forgot to call set_districts()")

    for district, polygon in __DISTRICTS.items():
        if polygon.contains(shapely.geometry.Point(location.lon, location.lat)):
            return district
