#ifndef SEEED_MOTOR_SHIELD_H
#define SEEED_MOTOR_SHIELD_H

#include "motor_shield.h"

class SeeedMotorShield : public MotorShield {
public:
    SeeedMotorShield();

    void forward(byte speed);
    void backward(byte speed);

    void left(byte speed);
    void right(byte speed);

    void left(byte speedA, byte speedB);
    void right(byte speedA, byte speedB);

    void stop();
    void brake();
};

#endif
