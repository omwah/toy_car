// Location of central setup / loop routines
// Connects together functionality

#include <Arduino.h>
#include "motor_shield.h"
//#include "photo_sensors.h"
#include "ultrasound.h"
#include "rc_recieve.h"

void setup()
{
    motor_shield_setup();
//    photo_sensors_setup();
    ultrasound_setup();
    rc_setup();

    // serial for debugging
    Serial.begin(9600);
}

void loop()
{
    const int mode = 2;
    switch(mode) {
    case 0:
        // Photo sensors
        //photo_sensors_actions();
        delay(50);
        break;
    case 1:
        // Ultrasound
        ultrasound_test();
        delay(50);
        break;
    case 2:
        rc_recieve();
        break;
    }
}
