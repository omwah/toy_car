#ifndef MOTOR_SHIELD_H
#define MOTOR_SHIELD_H

void motor_shield_setup();

void forward(byte speed);
void backward(byte speed);

void left(byte speed);
void right(byte speed);

void left(byte speedA, byte speedB);
void right(byte speedA, byte speedB);

void stop();
void brake();

#endif
