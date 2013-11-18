#include <Arduino.h>
#include "ultrasound.h"
#include "motor_shield.h"

#define TRIGGER_PIN 6    // Trig_pin
#define ECHO_PIN 7      // Echo_pin

void ultrasound_setup()
{
    pinMode(TRIGGER_PIN, OUTPUT);    // set output for trigger  
    pinMode(ECHO_PIN, INPUT);        // set input for echo
}

long measure_delay()
{                     
    digitalWrite(TRIGGER_PIN, LOW);                    
    delayMicroseconds(2);

    // pull the Trig pin to high level for more than 10us impulse 
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIGGER_PIN, LOW);

    // waits for the pin to go HIGH, and returns the length of the pulse in microseconds 
    long microseconds = pulseIn(ECHO_PIN,HIGH);
    return microseconds;
}

long calculate_distance(long time)
{
    // Distance_CM  = ((Duration of high level)*(Sonic :340m/s))/2
    //              = ((Duration of high level)*(Sonic :0.034 cm/us))/2
    //              = ((Duration of high level)/(Sonic :29.4 cm/us))/2

    long distance = time / 29 / 2;
    return distance;
}

void ultrasound_test()
{
    long microseconds = measure_delay();
    Serial.print("ret=");      //
    Serial.println(microseconds);
    long distance_cm = calculate_distance(microseconds);
    Serial.print("Distacne_CM = ");
    Serial.println(distance_cm);
    delay(200);
}

bool in_motion = false;
void ultrasound_motion_demo()
{
    int stop_distance = 25;
    long distance = calculate_distance(measure_delay());
    if(distance < stop_distance && in_motion) {
        in_motion = false;
        backward(64);
        delay(200);
        stop();
    } else if (distance >= stop_distance && not in_motion) {
        in_motion = true;
        forward(64);
    }
}

bool ultrasound_stop(int stop_distance)
{
    long distance = calculate_distance(measure_delay());
    if(distance < stop_distance) {
        return true;
    } else {
        return false;
    }
}
