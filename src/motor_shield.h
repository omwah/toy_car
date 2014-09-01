#ifndef MOTOR_SHIELD
#define MOTOR_SHIELD

// Interface for motor shields to implement
class MotorShield {
public:
    virtual void forward(byte speed) = 0;
    virtual void backward(byte speed) = 0;

    virtual void left(byte speed) = 0;
    virtual void right(byte speed) = 0;

    virtual void left(byte speedA, byte speedB) = 0;
    virtual void right(byte speedA, byte speedB) = 0;

    virtual void stop() = 0;
    virtual void brake() = 0;
};

#endif
