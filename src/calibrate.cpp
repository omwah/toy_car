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

        // Delay after button press before running
        delay(200);

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

void forward_cal(int speed, int duration){
    Serial.print("Forward calibration: ");
    Serial.print("Speed = ");
    Serial.print(speed);
    Serial.print(", Duration = ");
    Serial.print(duration);

    forward(speed);
    delay(duration);
    stop();
}

void forward_cal_64_200() {
    forward_cal(64, 200);
}

void forward_cal_64_500() {
    forward_cal(64, 500);
}

void forward_cal_128_200() {
    forward_cal(128, 200);
}

void forward_cal_128_500() {
    forward_cal(128, 500);
}

void forward_cal_64_1000() {
    forward_cal(64, 1000);
}

void forward_cal_128_1000() {
    forward_cal(128, 1000);
}


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
            do_step(forward_cal_64_1000);
            break;
        case 2:
            do_step(forward_cal_128_1000);
            break;
        default:
            do_step(end);
            step = 0;
            break;
    }
}
