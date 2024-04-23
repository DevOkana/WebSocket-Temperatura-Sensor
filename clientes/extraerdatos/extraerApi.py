import openmeteo_requests

import requests_cache
import pandas as pd
from retry_requests import retry
import os
from datetime import datetime
import csv
import pandas as pd

class Extract:
    hourly_dataframe = ""
    def __init__(self, data):
        # Setup the Open-Meteo API client with cache and retry on error
        cache_session = requests_cache.CachedSession('.cache', expire_after = 3600)
        retry_session = retry(cache_session, retries = 5, backoff_factor = 0.2)
        openmeteo = openmeteo_requests.Client(session = retry_session)

        # Make sure all required weather variables are listed here
        # The order of variables in hourly or daily is important to assign them correctly below
        url = "https://api.open-meteo.com/v1/forecast"
        params = {
            "latitude": 42.438598,
            "longitude": -8.654263,
            "hourly": ["temperature_2m", "relative_humidity_2m", "wind_speed_10m", "wind_speed_80m", "wind_direction_10m", "wind_direction_80m", "temperature_80m"],
            "daily": ["temperature_2m_max", "temperature_2m_min"],
            "timezone": "auto",
            "forecast_days": 1

        }
        responses = openmeteo.weather_api(url, params=params)

        # Process first location. Add a for-loop for multiple locations or weather models
        response = responses[0]
        """print(f"Coordinates {response.Latitude()}°N {response.Longitude()}°E")
        print(f"Elevation {response.Elevation()} m asl")
        print(f"Timezone {response.Timezone()} {response.TimezoneAbbreviation()}")
        print(f"Timezone difference to GMT+0 {response.UtcOffsetSeconds()} s")"""

        # Process hourly data. The order of variables needs to be the same as requested.
        hourly = response.Hourly()
        hourly_temperature_2m = hourly.Variables(0).ValuesAsNumpy()
        hourly_relative_humidity_2m = hourly.Variables(1).ValuesAsNumpy()
        hourly_wind_speed_10m = hourly.Variables(2).ValuesAsNumpy()
        hourly_wind_speed_80m = hourly.Variables(3).ValuesAsNumpy()
        hourly_wind_direction_10m = hourly.Variables(4).ValuesAsNumpy()
        hourly_wind_direction_80m = hourly.Variables(5).ValuesAsNumpy()
        hourly_temperature_80m = hourly.Variables(6).ValuesAsNumpy()


        hourly_data = {"date": pd.date_range(
            start = pd.to_datetime(hourly.Time(), unit = "s", utc = False),
            end = pd.to_datetime(hourly.TimeEnd(), unit = "s", utc = False),
            freq = pd.Timedelta(seconds = hourly.Interval()),
            inclusive = "left"
        )}
        hourly_data["temperature_2m"] = hourly_temperature_2m
        hourly_data["temperature_80m"] = hourly_temperature_80m
        hourly_data["relative_humidity_2m"] = hourly_relative_humidity_2m
        hourly_data["wind_speed_10m"] = hourly_wind_speed_10m
        hourly_data["wind_speed_80m"] = hourly_wind_speed_80m
        hourly_data["wind_direction_10m"] = hourly_wind_direction_10m
        hourly_data["wind_direction_80m"] = hourly_wind_direction_80m

        self.hourly_dataframe = pd.DataFrame(data = hourly_data)
        columna = 'date'
        # Obtiene la fecha y hora actual en formato UTC
        fecha_actual_utc = datetime.now()
        buscar = fecha_actual_utc.strftime("%Y-%m-%d %H:00:00")
        resultado= self.hourly_dataframe[columna].apply(lambda x: buscar in str(x))
        self.hourly_dataframe = self.hourly_dataframe[resultado]
        self.hourly_dataframe = pd.concat([self.hourly_dataframe.reset_index(drop=True), data.reset_index(drop=True)], axis=1)

    
    
    
    def crearCSV(self):
        print(type(self.hourly_dataframe))
        self.hourly_dataframe.to_csv('datos_diarios.csv', mode='a', index=False, header=not os.path.exists('datos_diarios.csv'))