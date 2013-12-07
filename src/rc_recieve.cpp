#include <Arduino.h>
#include <RCSwitch.h>

#include "RCRecord.h"

#include "motor_shield.h"
#include "ultrasound.h"
#include "rc_recieve.h"

#define DEBUG false

RCRecord mySwitch = RCRecord();

#define TURN_SPEED_ADJ 0.95 
#define STOP_DELAY 100

byte SPEEDS[] = { .35 * 255, .50 * 255, .75 * 255, 1.0 * 255 };

// Set initial speed
byte speed = SPEEDS[1];

void rc_setup() {
  // Receiver on interrupt 0 => that is pin #2
  mySwitch.enableReceive(0);
}

void rc_recieve() {
  if (mySwitch.available()) {
    
    char recieved_value = mySwitch.getReceivedValue();

    if(DEBUG) {
        Serial.print("RC recieved: "); Serial.println(recieved_value);
    }

    bool do_record = true;

    switch(recieved_value) {
    case 'w':
        // straight forward
        //if (!ultrasound_stop(25)) {
        forward(speed);
        //}
        break;
    case 's':
        // straight backward
        backward(speed);
        break;
    case 'a':
        // Turn left on axis by spinning both
        // motors in opposite directions
        left(speed * TURN_SPEED_ADJ);
        break;
    case 'q':
        // Turn left spinning only right motor
        // So move slightly forward
        left(0, speed * TURN_SPEED_ADJ);
        break;
    case 'z':
        // Turn left spinning only left motor
        // So move slightly backward
        left(speed * TURN_SPEED_ADJ, 0);
        break;
    case 'd':
        // Turn right on axis by spinning both
        // motors in opposite directions
        right(speed * TURN_SPEED_ADJ);
        break;
    case 'e':
        // Turn right spinning only left motor
        // So move slightly forward
        right(speed * TURN_SPEED_ADJ, 0);
        break;
    case 'c':
        // Turn right spinning only right motor
        // So move slightly backward
         right(0, speed * TURN_SPEED_ADJ);
        break;
    case char(32): // <space>
        brake();
        break;
    case '1':
    case '2':
    case '3':
    case '4':
        speed = SPEEDS[int(recieved_value) - 49];
        break;
    case 'o':
        delay(STOP_DELAY);
        break;
    case 'x':
        mySwitch.clear();
        do_record = false;
        break;
    case 'p':
        // Debug by printing values to serial
        if(DEBUG)
            mySwitch.print_values();
        mySwitch.play_back();
        do_record = false;
        break;
    default:
        // If a value is not handled, do not record it
        do_record = false;
    }

    // Don't record debugging and recording control characters
    if(do_record && mySwitch.can_record()) {
        mySwitch.record_value(recieved_value);
    }

    mySwitch.resetAvailable();
  } else {
      delay(STOP_DELAY);
      stop();
  }
}
