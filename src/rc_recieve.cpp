#include <Arduino.h>
#include <RCSwitch.h>

#include "motor_shield.h"
#include "ultrasound.h"
#include "rc_recieve.h"

RCSwitch mySwitch = RCSwitch();

void rc_setup() {
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

int speed = .25 * 255;

void rc_recieve() {
  if (mySwitch.available()) {
    
    int recieved_value = mySwitch.getReceivedValue();
    switch(recieved_value) {
    case 119: // w
        if (!ultrasound_stop(25)) {
            forward(speed);
            //delay(100);
        }
        break;
    case 115: // s
        backward(speed);
        //delay(100);
        break;
    case 97:  // a
        left(speed);
        //delay(80);
        break;
    case 100: // d
        right(speed);
        //delay(80);
        break;
    case 32: // <space>
        brake();
        break;
    case 49: // 1
        speed = .35 * 255;
        break;
    case 50: // 2
        speed = .50 * 255;
        break;
    case 51: // 3
        speed = .75 * 255;
        break;
    case 52: // 4
        speed = 1.0 * 255;
        break;
    default:
        stop();
    }

    mySwitch.resetAvailable();
  } else {
      delay(100);
      stop();
  }
}
