import json
import requests
from dataclasses import asdict


from dacite import from_dict
from avby.requests import FiltersApplyRequest
from avby.responses import FiltersApplyResponse, FiltersApplyError


def filters_apply(
    request: FiltersApplyRequest,
) -> FiltersApplyResponse | FiltersApplyError:
    try:
        response = requests.post(
            url="https://api.av.by/offer-types/cars/filters/main/apply",
            headers={
                "content-type": "application/json",
                "user-agent": "Mozilla/5.0",
            },
            data=json.dumps(asdict(request)),
        )

        if response.status_code != 200:
            return FiltersApplyError(
                message=f"Error {response.status_code}: {response.content}"
            )

        return from_dict(data_class=FiltersApplyResponse, data=response.json())
    except Exception as e:
        return FiltersApplyError(message=str(e))
