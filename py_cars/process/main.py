from dacite import from_dict
from typing import Mapping, Any, List, Dict, Callable
import csv
import datetime
import json
import os
import sys

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from avby.definitions import Advert
from avby.responses import FiltersApplyResponse


def get_property(advert: Advert, name: str):
    for property in advert.properties:
        if property.name == name:
            return property.value
    return None


def get_option(advert: Advert, name: str):
    for option in advert.metadata.options:
        if option.name == name:
            return True
    return False


CSV_HEADER: Dict[str, Callable[[Advert], Any]] = {
    "_advertType": lambda advert: advert.advertType,
    "_id": lambda advert: advert.id,
    "_bodyType": lambda advert: get_property(advert, "body_type"),
    "_brand": lambda advert: get_property(advert, "brand"),
    "_brandId": lambda advert: advert.metadata.brandId,
    "_brandSlug": lambda advert: advert.metadata.brandSlug,
    "_color": lambda advert: get_property(advert, "color"),
    "_condition": lambda advert: get_property(advert, "condition"),
    "_driveType": lambda advert: get_property(advert, "drive_type"),
    "_engineCapacity": lambda advert: get_property(advert, "engine_capacity"),
    "_enginePower": lambda advert: get_property(advert, "engine_power"),
    "_engineType": lambda advert: get_property(advert, "engine_type"),
    "_generation": lambda advert: get_property(advert, "generation"),
    "_generationId": lambda advert: advert.metadata.generationId,
    "_interiorColor": lambda advert: get_property(advert, "interior_color"),
    "_interiorMaterial": lambda advert: get_property(advert, "interior_material"),
    "_isRent": lambda advert: advert.isRent,
    "_mileageKm": lambda advert: get_property(advert, "mileage_km"),
    "_mixedDriveFuelConsumption": lambda advert: get_property(
        advert, "mixed_drive_fuel_consumption"
    ),
    "_model": lambda advert: get_property(advert, "model"),
    "_modelId": lambda advert: advert.metadata.modelId,
    "_modelSlug": lambda advert: advert.metadata.modelSlug,
    "_priceByn": lambda advert: advert.price.byn.amount,
    "_priceUsd": lambda advert: advert.price.usd.amount,
    "_publicUrl": lambda advert: advert.publicUrl,
    "_publishedAt": lambda advert: datetime.datetime.fromisoformat(advert.publishedAt),
    "_refreshedAt": lambda advert: datetime.datetime.fromisoformat(advert.refreshedAt),
    "_registrationCountry": lambda advert: get_property(advert, "registration_country"),
    "_shortLocationName": lambda advert: advert.shortLocationName,
    "_status": lambda advert: advert.status,
    "_transmissionType": lambda advert: get_property(advert, "transmission_type"),
    "_vinStartsWith": lambda advert: (
        advert.metadata.vinInfo.vin if advert.metadata.vinInfo else None
    ),
    "_year": lambda advert: get_property(advert, "year"),
    "110V": lambda advert: get_option(advert, "Розетка 110V"),
    "12V": lambda advert: get_option(advert, "Розетка 12V"),
    "360camera": lambda advert: get_option(advert, "Камера 360"),
    "ABS": lambda advert: get_option(advert, "ABS"),
    "adaptiveCruiseControl": lambda advert: get_option(
        advert, "Круиз-контроль адаптивный"
    ),
    "adaptiveLights": lambda advert: get_option(advert, "Адаптивное освещение"),
    "airbagKnees": lambda advert: get_option(advert, "Подушки коленные"),
    "airConditioner": lambda advert: get_option(advert, "Кондиционер"),
    "alarm": lambda advert: get_option(advert, "Сигнализация"),
    "alloyWheels": lambda advert: get_option(advert, "Легкосплавные диски"),
    "androidAuto": lambda advert: get_option(advert, "Android Auto"),
    "appleCarPlay": lambda advert: get_option(advert, "Apple CarPlay"),
    "autolaunch": lambda advert: get_option(advert, "Автозапуск двигателя"),
    "autoLightsCorrection": lambda advert: get_option(
        advert, "Автоматический корректор фар"
    ),
    "automaticHighBeams": lambda advert: get_option(
        advert, "Автоматический дальный свет"
    ),
    "autonomousHeater": lambda advert: get_option(advert, "Автономный отопитель"),
    "autoParking": lambda advert: get_option(advert, "Автопарковка"),
    "AUX": lambda advert: get_option(advert, "AUX"),
    "backAirbag": lambda advert: get_option(advert, "Подушки задние"),
    "backdoorsLocks": lambda advert: get_option(
        advert, "Блокировка замков задних дверей"
    ),
    "backElectricWindow": lambda advert: get_option(
        advert, "Задние электро-стеклоподъёмники"
    ),
    "BCW": lambda advert: get_option(advert, "Контроль мертвых зон на зеркалах"),
    "bluetooth": lambda advert: get_option(advert, "Bluetooth"),
    "bottomShields": lambda advert: get_option(advert, "Защита картера"),
    "cdOrMp3": lambda advert: get_option(advert, "CD или MP3"),
    "climateControlMany": lambda advert: get_option(
        advert, "Климат-контроль многозонный"
    ),
    "climateControlOne": lambda advert: get_option(
        advert, "Климат-контроль однозонный"
    ),
    "compactingMirrors": lambda advert: get_option(advert, "Электроскладывание зеркал"),
    "cruiseControl": lambda advert: get_option(advert, "Круиз-контроль"),
    "curtains": lambda advert: get_option(advert, "Штатные шторки на окна"),
    "diodeLights": lambda advert: get_option(advert, "Фары светодиодные"),
    "electricPanel": lambda advert: get_option(advert, "Электронная приборная панель"),
    "emergencyStop": lambda advert: get_option(
        advert, "Система экстренного торможения"
    ),
    "ESP": lambda advert: get_option(advert, "ESP"),
    "fogLights": lambda advert: get_option(advert, "Фары противотуманные"),
    "frontAirbag": lambda advert: get_option(advert, "Подушки передние"),
    "frontElectricWindowControl": lambda advert: get_option(
        advert, "Передние электро-стеклоподъёмники"
    ),
    "frontviewCamera": lambda advert: get_option(advert, "Камера переднего вида"),
    "helpOnAscend": lambda advert: get_option(advert, "Система помощи при подъеме"),
    "helpOnDescend": lambda advert: get_option(advert, "Система помощи при спуске"),
    "immobilizer": lambda advert: get_option(advert, "Иммобилайзер"),
    "isofix": lambda advert: get_option(advert, "isofix"),
    "keylessEntry": lambda advert: get_option(advert, "Беcключевой доступ"),
    "laneKeeping": lambda advert: get_option(advert, "Удержание в полосе"),
    "massage": lambda advert: get_option(advert, "Массаж сидений"),
    "mirrorsHeating": lambda advert: get_option(advert, "Обогрев зеркал"),
    "multimediaNavigation": lambda advert: get_option(advert, "Штатная навигация"),
    "multimediaScreen": lambda advert: get_option(advert, "Мультимедийный экран"),
    "nightVision": lambda advert: get_option(advert, "Ночное видение"),
    "originalDaysOnSale": lambda advert: advert.originalDaysOnSale,
    "panoramicSunroof": lambda advert: get_option(advert, "Панорамная крыша"),
    "parktronics": lambda advert: get_option(advert, "Парктроники"),
    "pedestrianDetection": lambda advert: get_option(advert, "Обнаружение пешеходов"),
    "pneuma": lambda advert: get_option(advert, "Пневмоподвеска"),
    "rainSensor": lambda advert: get_option(advert, "Датчик дождя"),
    "rearviewCamera": lambda advert: get_option(advert, "Камера заднего вида"),
    "rearviewMirrorDimmer": lambda advert: get_option(
        advert, "Самозатемняющееся зеркало заднего вида"
    ),
    "roadsingsDetection": lambda advert: get_option(
        advert, "Распознование дорожных знаков"
    ),
    "roofRailings": lambda advert: get_option(advert, "Рейлинги на крыше"),
    "seatsElectricAdjustment": lambda advert: get_option(
        advert, "Электрорегулировка сидений"
    ),
    "seatsHeating": lambda advert: get_option(advert, "Обогрев сидений"),
    "seatsMemory": lambda advert: get_option(advert, "Память положения сидений"),
    "seatVents": lambda advert: get_option(advert, "Вентиляция сидений"),
    "sideAirbag": lambda advert: get_option(advert, "Подушки боковые"),
    "startStop": lambda advert: get_option(advert, "Старт-стоп"),
    "sunroof": lambda advert: get_option(advert, "Люк"),
    "tailgateElectric": lambda advert: get_option(
        advert, "Электропривод двери багажника"
    ),
    "TCS": lambda advert: get_option(advert, "Антипробуксовочная"),
    "tinting": lambda advert: get_option(advert, "Заводская тонировка"),
    "tirePressureSensors": lambda advert: get_option(
        advert, "Датчики давления в шинах"
    ),
    "towbar": lambda advert: get_option(advert, "Фаркоп"),
    "USB": lambda advert: get_option(advert, "USB"),
    "voiceControl": lambda advert: get_option(advert, "Голосовое управление"),
    "wheelHeating": lambda advert: get_option(advert, "Обогрев руля"),
    "wheelMultimediaControls": lambda advert: get_option(
        advert, "Управление мультимедиа с руля"
    ),
    "WIFI": lambda advert: get_option(advert, "wi-fi"),
    "windShieldHeater": lambda advert: get_option(advert, "Обогрев лобового стекла"),
    "windshieldProjection": lambda advert: get_option(
        advert, "Проекция на лобовое стекло"
    ),
    "wirelessCharger": lambda advert: get_option(advert, "Беспроводная зарядка"),
    "xenonLights": lambda advert: get_option(advert, "Фары ксеноновые"),
}


def advert_to_dict(advert: Advert) -> Mapping[str, Any]:
    return {key: value_getter(advert) for key, value_getter in CSV_HEADER.items()}


def pages_to_csv(path):
    pages: List[FiltersApplyResponse] = []
    for page in os.listdir("pages"):
        with open(os.path.join("pages", page), "r") as page:
            pages.append(
                from_dict(data_class=FiltersApplyResponse, data=json.loads(page.read()))
            )

    with open(path, "w") as outfile:
        writer = csv.DictWriter(outfile, fieldnames=CSV_HEADER.keys())
        writer.writeheader()

        for i, page in enumerate(pages, start=1):
            for advert in page.adverts:
                writer.writerow(advert_to_dict(advert))
        print(f"Processed {i}/{len(pages)} pages")


def main():
    path = os.path.join("intermediate", "out.csv")
    pages_to_csv(path)


if __name__ == "__main__":
    main()
