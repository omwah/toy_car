// Driver for Arduino Motor Shield and clones: 
// http://arduino.cc/en/Main/ArduinoMotorShieldR3

#include <Arduino.h>

#include "tinker_motor_shield.h"

// Channel A pins
#define DIR_A 12
#define PWM_A 3
#define BRAKE_A 9
#define CURRENT_A 0

// Channel B pins
#define DIR_B 13
#define PWM_B 11
#define BRAKE_B 8
#define CURRENT_B 1

TinkerMotorShield::TinkerMotorShield()
{
    pinMode(DIR_A, OUTPUT);
    pinMode(BRAKE_A, OUTPUT);

    pinMode(DIR_B, OUTPUT);
    pinMode(BRAKE_B, OUTPUT);
}
 
void TinkerMotorShield::forward(byte speed)
{
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, HIGH);
    analogWrite(PWM_A, speed);
    analogWrite(PWM_B, speed);
}

void TinkerMotorShield::backward(byte speed)
{
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, LOW);
    analogWrite(PWM_A, speed);
    analogWrite(PWM_B, speed);
}

void TinkerMotorShield::left(byte speedA, byte speedB)
{
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, HIGH);
    analogWrite(PWM_A, speedA);
    analogWrite(PWM_B, speedB);
}

void TinkerMotorShield::left(byte speed)
{
    left(speed, speed);
}

void TinkerMotorShield::right(byte speedA, byte speedB)
{
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, LOW);
    analogWrite(PWM_A, speedA);
    analogWrite(PWM_B, speedB);
}

void TinkerMotorShield::right(byte speed)
{
    right(speed, speed);
}

void TinkerMotorShield::stop()
{
    digitalWrite(BRAKE_A, LOW);
    digitalWrite(BRAKE_B, LOW);
    analogWrite(PWM_A, 0);
    analogWrite(PWM_B, 0);
}

void TinkerMotorShield::brake()
{
    digitalWrite(BRAKE_A, HIGH);
    digitalWrite(BRAKE_B, HIGH);
}
