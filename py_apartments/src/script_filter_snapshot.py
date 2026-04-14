import datetime
import dataclasses

import pytz

import filtering
import storage
import models
import geo


if __name__ == "__main__":
    """
    Load apartments from json file and store filtered to a new file
    """

    geo.set_districts("data/districts.json")

    snapshot_name = "snapshot_05_06_2024"
    path = f"data/{snapshot_name}.json"
    dump_path = f"data/{snapshot_name}_filtered.json"
    filters = [
        models.FloorRange(min=2, max=40),
        models.RoomsRange(min=2, max=6),
        models.PriceRange(min=60000, max=140000),
        models.CreatedAtLowerBound(
            min=datetime.datetime.now(tz=pytz.utc) - datetime.timedelta(days=7)
        ),
        models.UpdatedAtLowerBound(
            min=datetime.datetime.now(tz=pytz.utc) - datetime.timedelta(days=7)
        ),
        models.DistrictsSet(
            districts=[
                "Грушевка",
                "Новая Боровая",
                "Английский Квартал",
                "ЖК Дружба",
                "Петровщина",
                "Михалово",
                "Парк Челюскинцев",
                "Восток",
                "Копище",
                "Московская",
            ]
        ),
    ]

    snapshot = storage.load_snapshot(path)
    passed = filtering.filter_apartments(snapshot, filters)

    storage.dump_apartments(passed, dump_path)
