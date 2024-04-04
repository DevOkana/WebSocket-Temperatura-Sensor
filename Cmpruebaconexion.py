import websocket
import time

# URL del servidor WebSocket
url = "ws://192.168.0.82:80/ws"  # Reemplaza <dirección_ip_servidor> con la dirección IP de tu servidor

def on_message(ws, message):
    print("Mensaje recibido:", message)

def on_error(ws, error):
    print("Error:", error)

def on_close(ws):
    print("Conexión cerrada")

def on_open(ws):
    print("Conexión abierta")
    # Puedes enviar un mensaje al servidor una vez que la conexión esté abierta
    # ws.send("Hola desde Python")

if __name__ == "__main__":
    # Configurar el cliente WebSocket
    websocket.enableTrace(True)
    ws = websocket.WebSocketApp(url, on_message=on_message, on_error=on_error, on_close=on_close)
    ws.on_open = on_open

    # Conectar al servidor
    ws.run_forever()
