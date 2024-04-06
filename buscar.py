import socket
import asyncio
import websockets

async def connect_to_websocket(uri):
    try:
        async with websockets.connect(uri) as websocket:
            print("Conexión establecida con el servidor WebSocket en", uri)
            # Aquí puedes enviar y recibir mensajes con el servidor WebSocket según tus necesidades
            await websocket.send("tmp")
            response = await websocket.recv()
            print("Respuesta del servidor:", response)
    except websockets.exceptions.InvalidURI:
        print("URI WebSocket no válida:", uri)
    except ConnectionRefusedError:
        print("No se pudo conectar al servidor WebSocket en", uri)

async def scan_for_websockets():
    for i in range(80, 85):  # Escanea las direcciones IP de 192.168.1.1 a 192.168.1.254
        host = f"192.168.0.{i}"
        uri = f"ws://{host}:80/ws"
        try:
            # Intenta conectar con el host en el puerto 80
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.settimeout(1)  # Establece un tiempo de espera corto para la conexión
                result = s.connect_ex((host, 80))
                if result == 0:  # Si el puerto está abierto
                    print(f"Se encontró un servidor WebSocket en {host}")
                    await connect_to_websocket(uri)
        except socket.error:
            pass
        except websockets.InvalidStatusCode as x:
            print("No es el que buscamos")

asyncio.run(scan_for_websockets())
