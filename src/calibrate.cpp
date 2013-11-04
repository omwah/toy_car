/*
   Runs through a series of maneuvers in an attempt to calibrate
   distances that the robot moves.
 */

#include <Arduino.h>
#include "motor_shield.h"

const int BUTTON_PIN = 2;

void calibrate_setup()
{
    pinMode(BUTTON_PIN, INPUT);
}

bool finished = true;
int step = 0;

// Calls step func when progressed into this step
void do_step( void(*step_func)() ) {
    if (!finished) {
        // Start step
        Serial.print("Step "); Serial.println(step);
        finished = true;

        // Call step function
        step_func();
        
        // Extra delay to seperate button presses
        delay(200);
    } else if (digitalRead(BUTTON_PIN) == HIGH) {
        // Advance to next step
        step++;
        finished = false;
    }
}

void nothing(){
}

void forward_cal(){
    Serial.println("Forward calibration");
    delay(200);
    forward(127);
    delay(500);
    stop();
}

void backwards_cal(){
    Serial.println("Backwards calibration");
    delay(200);
    backward(127);
    delay(500);
    stop();}

void end() {
    Serial.println("End of calibrate");
}

void calibrate()
{
    switch (step)  {
        case 0:
            do_step(nothing);
            break;
        case 1:
            do_step(forward_cal);
            break;
        case 2:
            do_step(backwards_cal);
            break;
        default:
            do_step(end);
            step = 0;
            break;
    }
}
