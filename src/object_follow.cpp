#include <PixyI2C.h>

#include "object_follow.h"

#define X_CENTER    160L
#define Y_CENTER    100L

#define DEBUG false

PixyI2C pixy;
int i = 0;

void object_follow_setup()
{
    Serial.println("Object follow setup");
    pixy.init();
}

void object_follow(MotorShield& motor_shield)
{
    uint16_t blocks = pixy.getBlocks();

    byte speed = 128;

    if (blocks) {
        int32_t panError = X_CENTER - pixy.blocks[0].x;
        int32_t tiltError = pixy.blocks[0].y - Y_CENTER;

        if (panError > 25) {
            motor_shield.right(speed);
        } else if (panError < -25) {
            motor_shield.left(speed);
        } else {
            motor_shield.stop();
        }

        i++;

        if (DEBUG && (i % 10 == 0)) {
            Serial.print("panError: "); Serial.println(panError);
            Serial.print("tiltError: "); Serial.println(tiltError);

            char buf[32];
            sprintf(buf, "Detected %d:\n", blocks);
            Serial.print(buf);

            for (int j = 0; j < blocks; j++) {
                sprintf(buf, "  block %d: ", j);
                Serial.print(buf);
                pixy.blocks[j].print();
                Serial.println();
            }
        }
    }
}

