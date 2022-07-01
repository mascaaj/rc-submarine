from flask import Flask, render_template, Response, request
from camera_pi import Camera
import serial
import time
import sys

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('indexTest.html')

def gen(camera):
    while True:
        frame = camera.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(gen(Camera()), mimetype='multipart/x-mixed-replace;boundary=frame')

@app.route('/', methods=['POST'])
def my_form_post():
    movement_type = request.form['movementType']
    power_level = request.form['powerLevel']
    duration = request.form['duration']
    message_packet = movement_type + '.' + power_level + '.' + duration
    print(message_packet)
    send_serial(message_packet)
    return render_template('indexTest.html')

def send_serial(message):
    string_input = message + '\n'
    ser.write(string_input.encode())

if __name__ == '__main__':
    if len(sys.argv)>1:
        port = sys.argv[1]
    else:
        port = '/dev/ttyACM0'
    ser = serial.Serial(port, 9600, timeout=1)
    ser.flush()
    time.sleep(1)
    app.run(host='0.0.0.0', port=5000, debug=True, threaded=True)
