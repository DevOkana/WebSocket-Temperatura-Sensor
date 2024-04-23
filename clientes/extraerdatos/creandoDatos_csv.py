import asyncio
import websockets as wb
import json as js
import csv
import re
import os
import datetime as dt
import pandas as pd
from extraerApi import Extract


async def send_command(websocket):         
    await websocket.send(js.dumps({"command": "tmp"}))        
    response = await websocket.recv()    
    # Encuentra todos los números en el string
    numbers = re.findall(r'\d+\.\d+', response)
    # Convierte los números de cadena a punto flotante
    numbers = [float(num) for num in numbers]
    print("Números escritos en el CSV:", numbers)
    print(type(numbers))
    print(numbers)
    # Crear DataFrame a partir de los números
    df = pd.DataFrame([numbers], columns=['humedad', 'temperatura'])  # Usar una lista de listas, donde cada lista representa una fila
    return df
        



async def main():
    uri = "ws://192.168.0.82:80/ws"
    while True:
        try:
            async with wb.connect(uri) as websocket:
                salida = await send_command(websocket)
                tmp = Extract(salida)
                tmp.crearCSV()
        except Exception as e:
            # Imprime el error
            print(f"Se ha producido un error: {e}")
            # Esperar un tiempo antes de volver a intentar
            await asyncio.sleep(60)  # Esperar 1 minuto antes de intentar de nuevo
        await asyncio.sleep(3600)  
asyncio.run(main())
