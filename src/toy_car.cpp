// Location of central setup / loop routines
// Connects together functionality

#include <Arduino.h>
#include "motor_shield.h"
#include "photo_sensors.h"

void setup()
{
    motor_shield_setup();
    photo_sensors_setup();

    // serial for debugging
    Serial.begin(9600);
}

void loop()
{
    photo_sensors_actions();
    delay(20);
}
