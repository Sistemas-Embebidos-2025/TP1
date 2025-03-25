from flask import Flask, render_template, request, jsonify
import serial
from threading import Thread, Lock
import time

app = Flask(__name__)
ser = serial.Serial('COM3', 9600, timeout=1)  # Opens the serial port COM3 (WINDOWS) with a baud rate of 9600.
lock = Lock()

# This dictionary stores the latest values received from the Arduino.
current_data = {
    # L1, L2, L3: Represent LED states (ON/OFF).
    'L1': 0,
    'L2': 0,
    'L3': 0,
    # D13: Digital pin 13 status.
    'D13': 0,
    # A3: Analog pin A3 value (sensor reading).
    'A3': 0
}

def serial_reader():
    """
    Continuously reads data from the serial port, parses it, and updates the current_data dictionary.
    Expected data format from the Arduino: "key1:value1;key2:value2;..."
    """
    while True:
        try:
            # Checks if there's data in the serial buffer.
            if ser.in_waiting:
                # Reads a full line of data, decodes the bytes to a string, and removes leading/trailing whitespaces.
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

# Starts serial_reader() in a separate background thread (daemon=True makes it stop when the program exits).
Thread(target=serial_reader, daemon=True).start()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/data')
def get_data():
    """
    Returns the latest sensor data in JSON format.
    """
    return jsonify(current_data)

@app.route('/control', methods=['POST'])
def set_control():
    """
    Accepts POST requests to set the state of LEDs or digital pin 13.
    Expects JSON payload: {"key": "L1", "value": 1}
    """
    req = request.get_json()
    key = req.get('key')
    value = req.get('value')
    if key in ['L1', 'L2', 'L3', 'D13']:
        if key in ['L1', 'L2', 'L3']:
            value = max(0, min(255, int(value)))
        elif key == 'D13':
            value = bool(value)
        with lock:
            # Sends a command to the Arduino via the serial port.
            # Example: Sending {"key": "L1", "value": 1} will send "L1:1\n" to the Arduino.
            ser.write(f"{key}:{int(value)}\n".encode())
        return jsonify(success=True)
    return jsonify(success=False), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
