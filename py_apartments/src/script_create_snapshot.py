import datetime

import onliner
import storage
import models

if __name__ == "__main__":
    """
    Fetch all apartments with the given filters and store them to a json file
    """

    path = f"data/snapshot_{datetime.date.today().strftime('%d_%m_%Y')}.json"
    filters = [
        models.AreaRange(min=55, max=100),
        models.PriceRange(min=60000, max=140000),
        models.YearRange(min=2000, max=2024),
        models.BoundingBox(
            bottom_left=models.Location(lon=27.206474840641025, lat=53.802830495764155),
            top_right=models.Location(lon=27.79973655939102, lat=54.000252434283986),
        ),
    ]
    settings = models.RequestSettings()

    apartments = onliner.fetch_apartments(filters, settings)
    storage.store_snapshot(path, apartments)
