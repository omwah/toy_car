// Make the toy car react to photo sensors

#include <Arduino.h>
#include "motor_shield.h"

void photo_sensors_setup()
{
}

// Keep track of a bunch of light levels to keep a running average
const int NUM_LIGHT_VALS = 10;
const int NUM_SENSORS = 3;
const int NUM_TRIGGERS = 8; // NUM_SENSORS^2 - 1

// Analog pins which are connected to the photo resistors
// 3 - left
// 2 - right
// 1 - backward
const int sensors[NUM_SENSORS] = {3, 2, 1};
const int trigger_thresh[NUM_SENSORS] = {60, 60, 80};
const int DEFAULT_SPEED = 100;

// Set up functions to call when sensors are triggered
// Functions defined in motor_shield.ino
// Index will be the binary value of the trigger which is
// a binary and of the sensors by posistion index to binary
// index from LSB to MSB
//
// ie.
// 100 sensor 3
// 010 sensor 2
// 001 sensor 1

// Function to meet signature for function array below
void stop_i(int speed) {
    stop();
}

void nothing(int speed) {
}

void (*trigger_funcs[NUM_TRIGGERS]) (int) = { 
    stop_i,   // 0 - 000
    left,     // 1 - 001
    right,    // 2 - 010
    forward,  // 3 - 011
    //backward, // 4 - 100
    //right,    // 5 - 101
    //left,     // 6 - 110
    //backward, // 7 - 111
    nothing,  // 4 - 100
    nothing,  // 5 - 101
    nothing,  // 6 - 110
    nothing,  // 7 - 111
    };


// These variables track persistent data
int light_levels[NUM_SENSORS][NUM_LIGHT_VALS] = {0};
bool first_time = true;

// Set all levels
void init_light_levels(int curr_levels[])
{
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        for(int lev = 0; lev < NUM_LIGHT_VALS; lev++) {
          light_levels[sens][lev] = curr_levels[sens];
        }
    }
}

// Record light level for sensor
void record_light_level(int curr_level, int sens) {
    // Shift all values down one index
    for(int lev = 1; lev < NUM_LIGHT_VALS; lev++) {  
        light_levels[sens][lev-1] = light_levels[sens][lev];
    }

    // Record latest values
    light_levels[sens][NUM_LIGHT_VALS-1] = curr_level;
}

// Returns averages for sensors
void average_light_levels(int curr_levels[], int level_avgs[])
{
    // Create sum for averages
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        word sens_sum = 0; // so we dont overflow
        for(int lev = 0; lev < NUM_LIGHT_VALS; lev++) {  
            sens_sum += light_levels[sens][lev];
        }
        level_avgs[sens] = sens_sum / NUM_LIGHT_VALS;
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

    // Look for trigger value
    // This will be a binary and of all sensors starting
    // from LSB to MSB
    int trigger_value = 0;
    for(int sens = 0; sens < NUM_SENSORS; sens++) {
        if ((curr_levels[sens] - avg_levels[sens]) > trigger_thresh[sens] && trigger_delay == 0) {
            trigger_value = trigger_value | (1 << sens);
        }
        record_light_level(curr_levels[sens], sens);
    }

    if (trigger_delay > 0) {
        trigger_delay--;
    }

    // Perform action based on trigger value
    print_debug(curr_levels, avg_levels);
    if(trigger_value > 0) {
        Serial.print("trigger value: ");
        Serial.println(trigger_value);
    }

    trigger_funcs[trigger_value](DEFAULT_SPEED);

}
