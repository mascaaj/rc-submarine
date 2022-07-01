/*
IBT-2 Motor Control Board driven by Arduino.

05 May 2022 - AJM
Borrowed from Hessmer Tutorial, modified for consumption

25 May 2022 - AJM
Added Functions to control motor groups.
Added switch statement for bench testing.
Added string parsing.

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

#include <stdlib.h>
#include <Wire.h>

// Use for testing:
int delay_value = 1000; // in milliseconds
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

int level_type = 2;
// 0 - Max Speed
// 1 - Half Speed
// 2 - Quarter Speed (Default)

int serialInput = 0;
/*######################################
Define all the pin values for the motors
#######################################*/

// Comment this out if you want to give hard coded values
int SENSOR_PIN = 0; // center pin of the potentiometer
// Dive motor pins (2 motors, single control input)
int RPWM_Output_Dive = 2; // Arduino PWM output pin 2; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output_Dive = 3; // Arduino PWM output pin 3; connect to IBT-2 pin 2 (LPWM)
// Front Right motor pins
int RPWM_Output_FR = 4; // Arduino PWM output pin 4; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output_FR = 5; // Arduino PWM output pin 5; connect to IBT-2 pin 2 (LPWM)
// Front Left motor pins
int RPWM_Output_FL = 6; // Arduino PWM output pin 6; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output_FL = 7; // Arduino PWM output pin 7; connect to IBT-2 pin 2 (LPWM)
// Rear Right motor pins
int RPWM_Output_RR = 8; // Arduino PWM output pin 8; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output_RR = 9; // Arduino PWM output pin 9; connect to IBT-2 pin 2 (LPWM)
// Rear Left motor pins
int RPWM_Output_RL = 10; // Arduino PWM output pin 10; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output_RL = 11; // Arduino PWM output pin 11; connect to IBT-2 pin 2 (LPWM)


/*###############################
Function Definitions
################################*/
void drive_forward(int level=2, int delay_constant=1000){
  analogWrite(RPWM_Output_FR, 0);
  analogWrite(RPWM_Output_FL, 0);
  if(level==0)
  {
    analogWrite(LPWM_Output_FR,255);
    analogWrite(LPWM_Output_FL,255);
  }
  else if (level==1)
  {
    analogWrite(LPWM_Output_FR,255/2);
    analogWrite(LPWM_Output_FL,255/2);
  }
  else
  {
    analogWrite(LPWM_Output_FR,255/4);
    analogWrite(LPWM_Output_FL,255/4);
  }
  delay(delay_constant);
}

// Rear thusters point forward.
// To move in reverse, they must thrust similar to forward motion
// except angled reverse.
void drive_reverse(int level=2, int delay_constant=1000){
  analogWrite(RPWM_Output_RR, 0);
  analogWrite(RPWM_Output_RL, 0);
  if(level==0)
  {
    analogWrite(LPWM_Output_RR,255);
    analogWrite(LPWM_Output_RL,255);
  }
  else if (level==1)
  {
    analogWrite(LPWM_Output_RR,255);
    analogWrite(LPWM_Output_RL,255);
  }
  else 
  {
    analogWrite(LPWM_Output_RR,255);
    analogWrite(LPWM_Output_RL,255);
  }
  delay(delay_constant);
}

// Dive thrusters are shorted together.
// they take 1 common input.
void dive(int level=2, int delay_constant=1000){
  analogWrite(RPWM_Output_Dive, 0);
  if(level==0){analogWrite(LPWM_Output_Dive,255);}
  else if (level==1){analogWrite(LPWM_Output_Dive,255/2);}
  else {analogWrite(LPWM_Output_Dive,255/4);}
  delay(delay_constant);
}

void surface(int level=2, int delay_constant=1000){
  analogWrite(LPWM_Output_Dive, 0);
  if(level==0){analogWrite(RPWM_Output_Dive,255);}
  else if (level==1){analogWrite(RPWM_Output_Dive,255/2);}
  else {analogWrite(RPWM_Output_Dive,255/4);}
  delay(delay_constant);
}

// Front right thrust backward direction
// Rear left thrust forward direction
// moment should result in twist clockwise
void turn_right(int level=2, int delay_constant=1000){
  analogWrite(RPWM_Output_FR, 0);
  analogWrite(RPWM_Output_RL, 0);
  if(level==0)
  {
    analogWrite(LPWM_Output_FR,255);
    analogWrite(LPWM_Output_RL,255);
  }
  else if (level==1)
  {
    analogWrite(LPWM_Output_FR,255);
    analogWrite(LPWM_Output_RL,255);
  }
  else 
  {
    analogWrite(LPWM_Output_FR,255);
    analogWrite(LPWM_Output_RL,255);
  }
  delay(delay_constant);
}

// Front left thrust backward direction
// Rear right thrust forward direction
// moment should result in twist counter clockwise
void turn_left(int level=2, int delay_constant=1000){
  analogWrite(RPWM_Output_FL, 0);
  analogWrite(RPWM_Output_RR, 0);
  if(level==0)
  {
    analogWrite(LPWM_Output_FL,255);
    analogWrite(LPWM_Output_RR,255);
  }
  else if (level==1)
  {
    analogWrite(LPWM_Output_FL,255);
    analogWrite(LPWM_Output_RR,255);
  }
  else 
  {
    analogWrite(LPWM_Output_FL,255);
    analogWrite(LPWM_Output_RR,255);
  }
  delay(delay_constant);
}

// Front left thrust backward direction
// Rear left thrust forward direction
// moment should result in strafe right
void strafe_right(int level=2, int delay_constant=1000)
{
  analogWrite(RPWM_Output_FL, 0);
  analogWrite(RPWM_Output_RL, 0);
  if(level==0)
  {
    analogWrite(LPWM_Output_FL,255);
    analogWrite(LPWM_Output_RL,255);
  }
  else if (level==1)
  {
    analogWrite(LPWM_Output_FL,255);
    analogWrite(LPWM_Output_RL,255);
  }
  else 
  {
    analogWrite(LPWM_Output_FL,255);
    analogWrite(LPWM_Output_RL,255);
  }
  delay(delay_constant);
}

// Front right thrust backward direction
// Rear right thrust forward direction
// moment should result in strafe left
void strafe_left(int level=2, int delay_constant=1000)
{
  analogWrite(RPWM_Output_FR, 0);
  analogWrite(RPWM_Output_RR, 0);
  if(level==0)
  {
    analogWrite(LPWM_Output_FR,255);
    analogWrite(LPWM_Output_RR,255);
  }
  else if (level==1)
  {
    analogWrite(LPWM_Output_FR,255);
    analogWrite(LPWM_Output_RR,255);
  }
  else 
  {
    analogWrite(LPWM_Output_FR,255);
    analogWrite(LPWM_Output_RR,255);
  }
  delay(delay_constant);
}

int parse(String input_string, int position)
{
    String data;
    if(position==1)
    {
        data = input_string.substring(0,1);
    }
    else if (position==2)
    {
        data = input_string.substring(2,3);
    }
    else
    {
        data = input_string.substring(4,5);
    }
    return data.toInt();
}

// Function to actuate all motors with potentiometer input
void all_motor(int potentiometer_input){
  // potentiometer_input is in the range 0 to 1023
  // the lower half of it we use for reverse rotation; the upper half for forward rotation
  if (potentiometer_input < 512)
  {
    // reverse rotation
    int reversePWM = -(potentiometer_input - 511) / 2;
    analogWrite(LPWM_Output_Dive, 0);
    analogWrite(LPWM_Output_FR, 0);
    analogWrite(LPWM_Output_FL, 0);
    analogWrite(LPWM_Output_RR, 0);
    analogWrite(LPWM_Output_RL, 0);
    analogWrite(RPWM_Output_Dive, reversePWM);
    analogWrite(RPWM_Output_FR, reversePWM);
    analogWrite(RPWM_Output_FL, reversePWM);
    analogWrite(RPWM_Output_RR, reversePWM);
    analogWrite(RPWM_Output_RL, reversePWM);
  }
  else
  {
    // forward rotation
    int forwardPWM = (potentiometer_input - 512) / 2;
    analogWrite(RPWM_Output_Dive, 0);
    analogWrite(RPWM_Output_FR, 0);
    analogWrite(RPWM_Output_FL, 0);
    analogWrite(RPWM_Output_RR, 0);
    analogWrite(RPWM_Output_RL, 0);
    analogWrite(LPWM_Output_Dive, forwardPWM);
    analogWrite(LPWM_Output_FR, forwardPWM);
    analogWrite(LPWM_Output_FL, forwardPWM);
    analogWrite(LPWM_Output_RR, forwardPWM);
    analogWrite(LPWM_Output_RL, forwardPWM);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(RPWM_Output_Dive, OUTPUT);
  pinMode(LPWM_Output_Dive, OUTPUT);
  pinMode(RPWM_Output_FR, OUTPUT);
  pinMode(LPWM_Output_FR, OUTPUT);
  pinMode(RPWM_Output_FL, OUTPUT);
  pinMode(LPWM_Output_FL, OUTPUT);
  pinMode(RPWM_Output_RR, OUTPUT);
  pinMode(LPWM_Output_RR, OUTPUT);
  pinMode(RPWM_Output_RL, OUTPUT);
  pinMode(LPWM_Output_RL, OUTPUT);
}
 
void loop()
{
  if(serialInput==1)
  {
    String state = Serial.readStringUntil('\n');
    test_type = parse(state,1);
    level_type = parse(state,2);
    delay_value = parse(state,3)*1000;
    Serial.println("Motion Type : ");
    Serial.println(test_type);
    Serial.println("Power Level : ");
    Serial.println(level_type);
    Serial.println("Time for action (sec): ");
    Serial.println(delay_value/1000);
  }
// Change this line to if you want to give hard coded values.
// SENSOR_PIN becomes a value from 0 - 1023 based on required speed and direction
// There is a deadband in the middle 512 +/- 47

  int sensorValue = analogRead(SENSOR_PIN);

  switch(test_type)
  {
    case 0:
      Serial.println("Moving Forward: FR, FL Motors");
      drive_forward(level_type, delay_value);
      break;
    case 1:
      Serial.println("Moving Reverse: RR, RL Motors");
      drive_reverse(level_type, delay_value);
      break;
    case 2:
      Serial.println("Diving: Dive Motors");
      dive(level_type, delay_value);
      break;
    case 3:
      Serial.println("Surfacing: Dive Motors");
      surface(level_type, delay_value);
      break;
    case 4:
      Serial.println("Turning Right: RL, FR Motors");
      turn_right(level_type, delay_value);
      break;
    case 5:
      Serial.println("Turning Left: RR, FL Motors");
      turn_left(level_type, delay_value);
      break;
    case 6:
      Serial.println("Strafe Left: RR, FR Motors");
      strafe_left(level_type);
      break;
    case 7:
      Serial.println("Strafe Right: RL, FL Motors");
      strafe_right(level_type, delay_value);
      break;
    case 8:
      Serial.println("All motor control, potentiometer input");
      all_motor(sensorValue);
      break;
    default:
      Serial.println("Invalid TestCase");
      exit(0);
  }
}


