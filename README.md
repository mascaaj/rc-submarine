# RC Submarine

Repository for arduino and interface code for the rc submersible based on [this instructable](https://www.instructables.com/DIY-Submersible-ROV/)

# Device and hardware instructions

## Accelerometer

Arduino : Accelerometer
3.3v   : Red
Ground : Black
SCL    : Orange
SDA    : Yellow

## Motor Control with IBT2

### Deadband
Emperically, this at +/-47 from 0 speed @512
Update : deadband is actually smaller, but motor current is not enough to overcome stiction.
512+/-47 ensure motion

## Connections (Single Motor)
IBT2 Board : Arduino
- IBT-2 pin 1 (RPWM) > Arduino pin 5(PWM)
- IBT-2 pin 2 (LPWM) > Arduino pin 6(PWM)
- IBT-2 pin 3 (R_EN) > Arduino 5V pin
- IBT-2 pin 4 (L_EN) > Arduino 5V pin
- IBT-2 pin 7 (VCC)  > Arduino 5V pin
- IBT-2 pin 8 (GND)  > Arduino GND
- IBT-2 pin 5 (R_IS) > Not Connected
- IBT-2 pin 6 (L_IS) > Not connected
- Potentiometer RED  > Arduino 5V pin
- Potentiometer BLA  > Arduino Ground
- Potentiometer YEL  > Arduino Analog 0

## Connections (multi motor)
IBT2 Board : Arduino

- RPWM_Output_Dive : 2 // Dive motor pins
- LPWM_Output_Dive = 3 // Dive motor pins
- RPWM_Output_FR = 4 // Front Right motor pins
- LPWM_Output_FR = 5 // Front Right motor pins
- RPWM_Output_FL = 6 // Front Left motor pins
- LPWM_Output_FL = 7 // Front Left motor pins
- RPWM_Output_RR = 8 // Rear Right motor pins
- LPWM_Output_RR = 9 // Rear Right motor pins
- RPWM_Output_RL = 10 // Rear Left motor pins
- LPWM_Output_RL = 11 // Rear Left motor pins
- 3: 5V
- 4: 5V
- 5: Not Connected
- 6: Not Connected
- 7: Ground
- 8: 5V

## Use for testing, make changes in sketch:
- Set delay value in milliseconds

```
int delay_value = 1000; // in milliseconds
```

- Set test type as per details below:
```
int test_type = 0;
/* 0 - Drive forward
 1 - Drive reverse
 2 - Surface
 3 - Dive
 4 - Turn Left
 5 - Turn Right
 6 - Strafe Left
 7 - Strafe Right
 8 - All motor control, use potentiometer for speed*/
```

- Set power level per details below:

```
int level_type = 2;
// 0 - Max Speed
// 1 - Half Speed
// 2 - Quarter Speed (Default)
```

- Set if serial input is needed
```
int serialInput = 0;
/* 0 = Not needed - False
1 = Needed -True*/
```

# Arduino cli tips:

## Setup :
- navigate to github page, follow install instructions or run the code below in your user directory. It installs arduino cli at `$PWD/bin`

```
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
```

- add install directory to path, the following snippet shows installation into `/home/pi`

```
nano ~/.bashrc
export PATH=$PATH:/home/pi/bin
```

- run `arduino-cli` to test functionality
- Install cores per board

```
arduino-cli core install arduino:avr
```

## Bootloader setup:

- Install avrdude
``` sudo apt-get install avrdude -y```

- Check which port the arduino is connected on
```arduino-cli board list```

- Add user to the dialout group, change permissions of port
```
sudo adduser <username> dialout
sudo chmod a+rw /dev/ttyACM0
```

## Sketch Actions:
This is all related to arduino-cli. Ignore if you are using the IDE.

- Create new sketch

```arduino-cli sketch new <sketch-name>```

- Compile sketch (As good practice i create a build directory and force build path

```
arduino-cli compile -b arduino:avr:mega --build-path build/
```

- Upload sketch
```
arduino-cli upload -b arduino:avr:mega -p /dev/ttyACM0 --input-dir build/ -v
```

## Arduino Monitor:

- Find out board comm port

``` 
arduino-cli board list
```

- Run the serial monitor that comes with arduino-cli

```
arduino-cli monitor -p /dev/ttyACM0 -l serial
```

# Interfacing with Raspberry Pi

## SSH instructions

There are many tutorials out on the internet, but i will summarise the steps here:

1. With your raspi connected to a monitor and keyboard, enable SSH


```
sudo raspi-config
```

2. Under interfacing options `Enable SSH`

3. Exit the panel and check if your Raspi has ssh daemon started. For the command below, type in ssh, and tab complete to see options avaliable.


```
sudo systemctl status sshd.service
```

4. Figure out your ip address, hostname and user id

```
hostname
ifconfig # Look for wlan or eth0 based on connection type
users
```

5. From your remote machine, ping the Raspi

```
ping <hostname>
ping <ip-address>
```

6. SSH into your Raspi

```
ssh <username@hostname> # OR
ssh <username@ipaddress>
```

## Reading Serial output to terminal
The general syntax for this is :

```stty <baud_rate> -F <arduino_port> raw -echo```

In my usage it looks like this (command should exit with no output):

```stty 9600 -F /dev/ttyACM0 raw -echo```

Once complete, run:

```watch -n 2 cat /dev/ttyACM0```

## Running python serial communication

Order:
1. Compile and upload arduino sketch.
2. Run watch command to monitor serial out.
3. Setup python package below.
4. Run the python file, follow instructions in console, give command
5. look for response in serial out terminal.

### First time usage :
Install serial package. I've tested with python3.
``` pip install pyserial```

### Running the app :

Navigate to the `serial_arduino.py` location.
```python serial_arduino.py```

# Streaming video via VLC

- install vlc player

    ```sudo apt install -y vlc```

- run command on pi in cli

    ```raspivid -o - -t 0 -w 800 -h 600 -fps 12  | cvlc -vvv stream:///dev/stdin --sout '#rtp{sdp=rtsp://:8080/}' :demux=h264```

- Open vlc player on network connected pc
- Media > Open Network Stream > Enter rtsp address and port
  
  ```rtsp://raspberrypi:8080```


# Web server interface for submarine

# First time setup:
- Navigate to the folder called `camWebServer`
- Install dependencies

```
pip3 install -r requirements.txt
```

- Make a note of pi's hostname or ip address

```
ifconfig
hostname
```

## Running the application

- Run application (might want to open another terminal, it will stay running)

```
python3 appCam.py
```

- If the application has not errored out, on any computer on the same network, navigate to `<hostname>:5000` or `<ipaddress>:5000`

## Testing serial port communication

- Load the serialRead sketch onto the Arduino

- Open up the serial monitor, all methods above should work

- Start the webserver

- Enter values into the form and submit

- Arduino serial monitor should reflect the same values input by the webform.

