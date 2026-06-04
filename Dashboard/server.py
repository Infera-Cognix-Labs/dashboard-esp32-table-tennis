import json
import socket
import threading

from flask import Flask, render_template
from flask_socketio import SocketIO

UDP_IP = "0.0.0.0"
UDP_PORT = 5005  # Phải trùng với UDP_SERVER_PORT trên ESP32

app = Flask(__name__)
app.config["SECRET_KEY"] = "secret!"
socketio = SocketIO(app, cors_allowed_origins="*")


@app.route("/")
def index():
    return render_template("index.html")


def udp_listener():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    print(f"Listening UDP on {UDP_IP}:{UDP_PORT}")
    while True:
        data, addr = sock.recvfrom(1024)
        try:
            text = data.decode("utf-8").strip()
            payload = json.loads(text)
            socketio.emit("sensor_data", payload)
        except Exception as e:
            print("Error parsing UDP:", e)


if __name__ == "__main__":
    t = threading.Thread(target=udp_listener, daemon=True)
    t.start()
    socketio.run(app, host="0.0.0.0", port=5000)

