import asyncio
import websockets

async def send_command(websocket):
    while True:
        command = input("Ingrese el comando a enviar al servidor (o 'exit' para salir): ")
        if command.lower() == "exit":
            break
        await websocket.send(command)
        response = await websocket.recv()
        print("Respuesta del servidor:", response)

async def main():
    uri = "ws://192.168.0.82:80/ws"
    async with websockets.connect(uri) as websocket:
        await send_command(websocket)

asyncio.run(main())
