#include "object_follow.h"

#include <PixyI2C.h>
#include <PID_v1.h>

#define X_CENTER 160
#define X_MIN 1
#define X_MAX 320

#define Y_CENTER 100
#define Y_MIN 1
#define Y_MAX 200

#define Kp 1.2
#define Ki 0
#define Kd 0

#define DEBUG false

PixyI2C pixy;
int debug_count = 0;

double left_setpoint, left_input, left_output;
double right_setpoint, right_input, right_output;

PID left_pid(&left_input, &left_output, &left_setpoint, Kp, Ki, Kd, DIRECT);
PID right_pid(&right_input, &right_output, &right_setpoint, Kp, Ki, Kd, DIRECT);

void object_follow_setup()
{
    Serial.println("Object follow setup");
    pixy.init();

    left_input = X_CENTER;
    left_setpoint = X_CENTER;

    right_input = X_CENTER;
    right_setpoint = X_CENTER;

    left_pid.SetMode(AUTOMATIC);
    right_pid.SetMode(AUTOMATIC);

    left_pid.SetControllerDirection(REVERSE);
}

void object_follow(MotorShield& motor_shield)
{
    uint16_t blocks = pixy.getBlocks();

    byte speed = 128;

    if (blocks) {
        left_input = pixy.blocks[0].x;
        right_input = pixy.blocks[0].x;
    } else {
        left_input = X_CENTER;
        right_input = X_CENTER;
    }
    left_pid.Compute();
    right_pid.Compute();

    motor_shield.left(left_output);
    motor_shield.right(right_output);
      
    if (DEBUG && blocks && (debug_count++ % 10 == 0)) {
        Serial.print("left_input: "); Serial.println(left_input);
        Serial.print("left_output: "); Serial.println(left_output);

        Serial.print("right_input: "); Serial.println(right_input);
        Serial.print("right_output: "); Serial.println(right_output);

        char buf[32];
        sprintf(buf, "Detected %d:\n", blocks);
        Serial.print(buf);

        for (int j = 0; j < blocks; j++) {
            sprintf(buf, "  block %d: ", j);
            Serial.print(buf);
            pixy.blocks[j].print();
            Serial.println();
        }
    }
}
