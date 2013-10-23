// Make the toy car react to photo sensors

#include <Arduino.h>
#include "motor_shield.h"

void photo_sensors_setup()
{
}

// Keep track of a bunch of light levels to keep a running average
const int NUM_LIGHT_VALS = 10;
const int NUM_SENSORS = 2;

// Analog pins which are connected to the photo resistors
int sensors[NUM_SENSORS] = {0, 4}; // A0, A4

int light_levels[NUM_SENSORS][NUM_LIGHT_VALS] = {0};
bool first_time = false;

const int TRIGGER_THRESH = 10;

const int DFLT_SPEED = 127;

// Set up functions to call when sensors are triggered
// Functions defined in motor_shield.ino
// Function pointer array of functions to call
void (*trigger_funcs[NUM_SENSORS]) (int) = {left, right};

// Set all levels
void init_light_levels(int curr_levels[])
{
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        for(int lev = 0; lev < NUM_LIGHT_VALS; lev++) {
          light_levels[sens][lev] = curr_levels[sens];
        }
    }
}

// Record most recent light levels and return averages
void average_light_levels(int curr_levels[], int level_avgs[])
{
    // Shift all values down one index
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        for(int lev = 0; lev < NUM_LIGHT_VALS; lev++) {  
          light_levels[sens][lev-1] = light_levels[sens][lev];
        }
    }

    // Record latest values
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        light_levels[sens][NUM_LIGHT_VALS-1] = curr_levels[sens];
    }

    // Create sum for averages
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        level_avgs[sens] = 0;
        for(int lev = 0; lev < NUM_LIGHT_VALS; lev++) {  
          level_avgs[sens] += light_levels[sens][lev];
        }
        level_avgs[sens] /= NUM_LIGHT_VALS;
    }

}

void print_debug(int curr_levels[], int level_avgs[]) {
    Serial.print("avg vals: ");
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        Serial.print(level_avgs[sens]);
        Serial.print(" ");
    }
    Serial.print(", inst vals: ");
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        Serial.print(curr_levels[sens]);
        Serial.print(" ");
    }
    Serial.println();
}

// Delay a bit when starting up to avoid triggers before
// sensors have stabilized
int trigger_delay = NUM_LIGHT_VALS;

void photo_sensors_actions()
{
    // Record sensor values in array
    int curr_levels[NUM_SENSORS];
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        curr_levels[sens] = analogRead(sensors[sens]);
    }

    // Initialize the array the first time through the loop
    // so our average will === current values
    if(first_time) {
      first_time = false;
      init_light_levels(curr_levels);
    }

    // Average last N samples
    int avg_levels[NUM_SENSORS];
    average_light_levels(curr_levels, avg_levels);

    print_debug(curr_levels, avg_levels);

    // Look for trigger conditions
    int triggered = false;
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        if ((curr_levels[sens] - avg_levels[sens]) > TRIGGER_THRESH && trigger_delay == 0) {
            Serial.print("trigger #");
            Serial.println(sens);
            trigger_funcs[sens](DFLT_SPEED);
            triggered = true;
        } else {
            stop();
        }

    }

    if (trigger_delay > 0) {
        trigger_delay--;
    }

}
