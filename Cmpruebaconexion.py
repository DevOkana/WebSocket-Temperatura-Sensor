import asyncio
import websockets
import json

async def send_command(websocket):
    while True:
        command = input("Ingrese el comando a enviar al servidor (o 'exit' para salir): ")
        if command.lower() == "exit":
            break
        elif command.lower() == "config_wifi":
            config_data = {
                "ssid": "(((Mariola)))",
                "password": "Resiliencia1*"
            }
            await websocket.send(json.dumps({"command": "config_wifi", "data": config_data}))
            print(F"Comando '{command.lower()}' enviado al servidor.")
        elif command.lower() == "tmp":
            await websocket.send(json.dumps({"command": "tmp"}))
            print(f"Comando '{command.lower()}' enviado al servidor.")
        else:
            await websocket.send(command)
            print(f"Comando '{command}' enviado al servidor.")
        response = await websocket.recv()
        print("Respuesta del servidor:", response)

async def main():
    uri = "ws://192.168.0.82:80/ws"
    async with websockets.connect(uri) as websocket:
        await send_command(websocket)

asyncio.run(main())
