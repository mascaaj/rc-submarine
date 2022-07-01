# Deadband
Emperically, this at +/-47 from 0 speed @512
Update : deadband is actually smaller, but motor current is not enough to overcome stiction.
512+/-47 ensure motion

## Connections
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