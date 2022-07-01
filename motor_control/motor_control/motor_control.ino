/*
IBT-2 Motor Control Board driven by Arduino.
Borrowed from Hessmer Tutorial, modified for consumption
 
Speed and direction controlled by a potentiometer attached to analog input 0.
One side pin of the potentiometer (either one) to ground; the other side pin to +5V
 
Connection to the IBT-2 board:
IBT-2 pin 1 (RPWM) > Arduino pin 5(PWM)
IBT-2 pin 2 (LPWM) > Arduino pin 6(PWM)
IBT-2 pin 3 (R_EN) > Arduino 5V pin
IBT-2 pin 4 (L_EN) > Arduino 5V pin
IBT-2 pin 7 (VCC)  > Arduino 5V pin
IBT-2 pin 8 (GND)  > Arduino GND
IBT-2 pin 5 (R_IS) > Not Connected 
IBT-2 pin 6 (L_IS) > Not connected
Potentiometer RED  > Arduino 5V pin
Potentiometer BLA  > Arduino Ground
Potentiometer YEL  > Arduino Analog 0
*/

// Comment this out if you want to give hard coded values
int SENSOR_PIN = 0; // center pin of the potentiometer
 
int RPWM_Output = 5; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output = 6; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)

void setup()
{
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);
}
 
void loop()
{

// Change this line to if you want to give hard coded values.
// SENSOR_PIN becomes a value from 0 - 1023 based on required speed and direction
// There is a deadband in the middle 512 +/- 47

  int sensorValue = analogRead(SENSOR_PIN);
 
  // sensor value is in the range 0 to 1023
  // the lower half of it we use for reverse rotation; the upper half for forward rotation
  if (sensorValue < 512)
  {
    // reverse rotation
    int reversePWM = -(sensorValue - 511) / 2;
    analogWrite(LPWM_Output, 0);
    analogWrite(RPWM_Output, reversePWM);
  }
  else
  {
    // forward rotation
    int forwardPWM = (sensorValue - 512) / 2;
    analogWrite(RPWM_Output, 0);
    analogWrite(LPWM_Output, forwardPWM);
  }
}
