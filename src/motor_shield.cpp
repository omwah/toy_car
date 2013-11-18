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

int pinI1=8;//define I1 interface
int speedpinA=9;//enable motor A
int pinI2=11;//define I2 interface 

int pinI3=12;//define I3 interface 
int speedpinB=10;//enable motor B
int pinI4=13;//define I4 interface 

void motor_shield_setup()
{
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);
}
 
void forward(int speed)
{
     analogWrite(speedpinA,speed);//input a simulation value to set the speed
     analogWrite(speedpinB,speed);
     digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
     digitalWrite(pinI1,HIGH);
}

void backward(int speed)
{
     analogWrite(speedpinA,speed);//input a simulation value to set the speed
     analogWrite(speedpinB,speed);
     digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
     digitalWrite(pinI1,LOW);
}
void left(int speed)
{
     analogWrite(speedpinA,speed);//input a simulation value to set the speed
     analogWrite(speedpinB,speed);
     digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
     digitalWrite(pinI1,LOW);
}
void right(int speed)
{
     analogWrite(speedpinA,speed);//input a simulation value to set the speed
     analogWrite(speedpinB,speed);
     digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI2,LOW);//turn DC Motor A move clockwise
     digitalWrite(pinI1,HIGH);
}

void stop()
{
     // Unenable the pin, to stop the motor. this should be done to avid damaging the motor. 
     digitalWrite(speedpinA,LOW);
     digitalWrite(speedpinB,LOW);
}

void brake()
{
     // Braking
     digitalWrite(pinI4,HIGH);
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI2,HIGH);
     digitalWrite(pinI1,HIGH);
}

void test_motors()
{
  int speed = 127;

  left(speed);
  delay(2000);
  stop();
  delay(1000);

  right(speed);
  delay(2000);
  stop();
  delay(1000);

  forward(speed);
  delay(2000);
  stop();
  delay(1000);

  backward(speed);
  delay(2000); 
  stop();
  delay(1000);
}
