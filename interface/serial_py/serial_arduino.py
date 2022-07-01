import serial
import time

if __name__=='__main__':
    ser = serial.Serial('/dev/ttyACM0',9600,timeout=1)
    ser.flush()
    time.sleep(1)
    while True:
        print("Movement command Syntax              : MovementType.MovementPowerLevel.MovementDuration")
        print("Example Movement                     : 5.2.6")
        print("Movement Range (F/R/U/D/CCW/CW/SL/SR): 0 - 8")
        print("Power Range (Full/Half/Quarter)      : 0 - 2")
        print("Duration Range (sec)                 : 1 - 9")
        print (" ")
        user_input = input("Enter movement command (0-7) : ")
        print ("Processing Input")
        print (" ")
        string_input = user_input + '\n'
        ser.write(string_input.encode())