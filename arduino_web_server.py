from flask import Flask, render_template, request, jsonify
import serial
from threading import Thread, Lock
import time

app = Flask(__name__)
ser = serial.Serial('COM3', 9600, timeout=1)  # Adjust COM port
lock = Lock()

current_data = {
    'L1': 0,
    'L2': 0,
    'L3': 0,
    'D13': 0,
    'A3': 0
}

def serial_reader():
    while True:
        try:
            if ser.in_waiting:
                line = ser.readline().decode('utf-8').strip()
                parts = line.split(';')
                for part in parts:
                    if ':' in part:
                        key, val = part.split(':', 1)
                        if key in current_data:
                            current_data[key] = int(val) if key != 'D13' else int(val)
        except Exception as e:
            print("Serial read error:", e)
        time.sleep(0.1)

Thread(target=serial_reader, daemon=True).start()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/data')
def data():
    return jsonify(current_data)

@app.route('/set_led', methods=['POST'])
def set_led():
    req = request.get_json()
    key = req.get('key')
    value = req.get('value')
    if key in ['L1', 'L2', 'L3', 'D13']:
        with lock:
            ser.write(f"{key}:{value}\n".encode())
        return jsonify(success=True)
    return jsonify(success=False), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
