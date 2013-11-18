#ifndef MOTOR_SHIELD_H
#define MOTOR_SHIELD_H

void motor_shield_setup();
void forward(int speed);
void backward(int speed);
void left(int speed);
void right(int speed);
void stop();
void brake();
void test_motors();

#endif
