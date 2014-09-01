//. Motor driver shield- 2012 Copyright (c) Seeed Technology Inc.
// 
//  Original Author: Jimbo.we
//  Contribution: LG
//  
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include <Arduino.h>

#include "seeed_motor_shield.h"

// define I1 interface
#define pinI1 8

// enable motor A
#define speedpinA 9

// define I2 interface 
#define pinI2 11

// define I3 interface 
#define pinI3 12

// enable motor B
#define speedpinB 10

// define I4 interface 
#define pinI4 13

SeeedMotorShield::SeeedMotorShield()
{
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);
}
 
void SeeedMotorShield::forward(byte speed)
{
     analogWrite(speedpinA,speed);//input a simulation value to set the speed
     analogWrite(speedpinB,speed);
     digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
     digitalWrite(pinI1,HIGH);
}

void SeeedMotorShield::backward(byte speed)
{
     analogWrite(speedpinA,speed);//input a simulation value to set the speed
     analogWrite(speedpinB,speed);
     digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
     digitalWrite(pinI1,LOW);
}

void SeeedMotorShield::left(byte speedA, byte speedB)
{
     analogWrite(speedpinA,speedA);//input a simulation value to set the speed
     analogWrite(speedpinB,speedB);
     digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
     digitalWrite(pinI1,LOW);
}

void SeeedMotorShield::left(byte speed)
{
    left(speed, speed);
}

void SeeedMotorShield::right(byte speedA, byte speedB)
{
     analogWrite(speedpinA,speedA);//input a simulation value to set the speed
     analogWrite(speedpinB,speedB);
     digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI2,LOW);//turn DC Motor A move clockwise
     digitalWrite(pinI1,HIGH);
}

void SeeedMotorShield::right(byte speed)
{
    right(speed, speed);
}

void SeeedMotorShield::stop()
{
     // Unenable the pin, to stop the motor. this should be done to avid damaging the motor. 
     digitalWrite(speedpinA,LOW);
     digitalWrite(speedpinB,LOW);
}

void SeeedMotorShield::brake()
{
     // Braking
     digitalWrite(pinI4,HIGH);
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI2,HIGH);
     digitalWrite(pinI1,HIGH);
}
