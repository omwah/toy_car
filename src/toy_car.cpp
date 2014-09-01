// Location of central setup / loop routines
// Connects together functionality

#include <Arduino.h>
#include <Pixy.h>
#include "tinker_motor_shield.h"
#include "rc_recieve.h"
#include "object_follow.h"

TinkerMotorShield motor_shield = TinkerMotorShield();

void setup()
{
    // serial for debugging
    Serial.begin(9600);
    Serial.println("Toy Car Beginning");

    rc_setup();
    object_follow_setup();
}

void loop()
{
    rc_recieve(motor_shield);
    object_follow(motor_shield);
}
