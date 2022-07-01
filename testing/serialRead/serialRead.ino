#include <Wire.h>
#include <stdlib.h>

int delay_constant = 1000;
int test_type = 0;
int level = 2;
// 0 - Drive forward
// 1 - Drive reverse
// 2 - Surface
// 3 - Dive
// 4 - Turn Left
// 5 - Turn Right
// 6 - Strafe Left
// 7 - Strafe Right

void setup() {
    Serial.begin(9600);
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

void loop() {
    if (Serial.available()>0)
    {
        String state = Serial.readStringUntil('\n');
        Serial.println(state);
        test_type = parse(state,1);
        level = parse(state,2);
        delay_constant = parse(state,3)*1000;
        Serial.println("Motion Type : ");
        Serial.println(test_type);
        Serial.println("Power Level : ");
        Serial.println(level);
        Serial.println("Time for action (sec): ");
        Serial.println(delay_constant/1000);

        if (test_type>=0)
        {
            switch(test_type)
            {
                case 0:
                    Serial.println("Moving Forward: FR, FL Motors");
                    delay(delay_constant);
                    break;
                case 1:
                    Serial.println("Moving Reverse: RR, RL Motors");
                    delay(delay_constant);
                    break;
                case 2:
                    Serial.println("Diving: Dive Motors");
                    delay(delay_constant);
                    break;
                case 3:
                    Serial.println("Surfacing: Dive Motors");
                    delay(delay_constant);
                    break;
                case 4:
                    Serial.println("Turning Right: RL, FR Motors");
                    delay(delay_constant);
                    break;
                case 5:
                    Serial.println("Turning Left: RR, FL Motors");
                    delay(delay_constant);
                    break;
                case 6:
                    Serial.println(print_strafe());
                    delay(delay_constant);
                    break;
                case 7:
                    Serial.println("Strafe Right: RL, FL Motors");
                    delay(delay_constant);
                    break;
                default:
                Serial.println("Invalid TestCase");
            }
        }
    }
}

String print_strafe()
{
return "Strafe Left: RR, FR Motors";
}