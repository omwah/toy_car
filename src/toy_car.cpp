// Location of central setup / loop routines
// Connects together functionality

#include <Arduino.h>
#include <Pixy.h>
#include "motor_shield.h"
#include "rc_recieve.h"

void setup()
{
    motor_shield_setup();
    rc_setup();
    object_follow_setup();

    // serial for debugging
    Serial.begin(9600);
    Serial.println("Toy Car Beginning");
}

void loop()
{
    rc_recieve();
}
