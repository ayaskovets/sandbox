import models
import geo


def parse_apartment(apartment, source: str) -> models.ParsedApartment:
    return models.ParsedApartment(
        link=apartment["url"],
        floor=apartment["floor"],
        rooms=apartment["number_of_rooms"],
        area=apartment["area"]["total"],
        price_usd=float(apartment["price"]["amount"]),
        resale=apartment["resale"],
        created_at=apartment["created_at"],
        updated_at=apartment["last_time_up"],
        district=(
            geo.location_to_district(
                models.Location(
                    lon=apartment["location"]["longitude"],
                    lat=apartment["location"]["latitude"],
                )
            )
        ),
    )
