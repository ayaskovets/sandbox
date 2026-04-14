import datetime
import json
import typing
import dataclasses

import logging
import models


def store_snapshot(path: str, source: str, apartments):
    """
    Store apartments to json file
    """

    snapshot = {
        "created_at": datetime.datetime.now().isoformat(),
        "source": source,
        "apartments": apartments,
    }

    with open(path, "w") as f:
        json.dump(snapshot, f)

    logging.info(f"created new snapshot of {len(apartments)} apartments at {path}")


def load_snapshot(path: str) -> models.Snapshot:
    """
    Load apartments from json file
    """

    with open(path, "r") as f:
        snapshot_json = json.load(f)
        snapshot = models.Snapshot(
            created_at=snapshot_json["created_at"],
            source=snapshot_json["source"],
            apartments=snapshot_json["apartments"],
        )

        logging.info(
            f"loaded snapshot of {len(snapshot.apartments)} apartments at {path} "
        )

        return snapshot


def dump_apartments(apartments: typing.List[models.ParsedApartment], path: str):
    with open(path, "w") as f:
        json.dump(
            list(map(dataclasses.asdict, apartments)), f, indent=2, ensure_ascii=False
        )
