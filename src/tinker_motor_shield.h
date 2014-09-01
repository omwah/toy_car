#ifndef TINKER_MOTOR_SHIELD_H
#define TINKER_MOTOR_SHIELD_H

#include "motor_shield.h"

class TinkerMotorShield : public MotorShield {
public:
    TinkerMotorShield();

    virtual void forward(byte speed);
    virtual void backward(byte speed);

    virtual void left(byte speed);
    virtual void right(byte speed);

    virtual void left(byte speedA, byte speedB);
    virtual void right(byte speedA, byte speedB);

    virtual void stop();
    virtual void brake();
};

#endif
