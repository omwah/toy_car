// Location of central setup / loop routines
// Connects together functionality

#include <Arduino.h>
#include <Pixy.h>
#include "tinker_motor_shield.h"
#include "rc_recieve.h"

TinkerMotorShield motor_shield = TinkerMotorShield();

void setup()
{
    rc_setup();

    // serial for debugging
    Serial.begin(9600);
    Serial.println("Toy Car Beginning");
}

void loop()
{
    rc_recieve(motor_shield);
}
