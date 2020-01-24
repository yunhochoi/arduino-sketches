/*
   Microstepping demo

   This requires that M0, M1 be connected in addition to STEP,DIR

   Copyright (C)2015 Laurentiu Badea

   This file may be redistributed under the terms of the MIT license.
   A copy of this license has been included with this distribution in the file LICENSE.
*/
#include <Arduino.h>
#include "A4988.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// 2-wire basic config, microstepping is hardwired on the driver
A4988 stepper1(MOTOR_STEPS, 30, 31);
A4988 stepper2(MOTOR_STEPS, 32, 33);

/*********************
  global variables
*********************/
unsigned long time_since_last_reset = 0;
int interval_five  = 6000;        //6 seconds


void setup() {

  stepper1.begin(3, 16);
  stepper2.begin(3, 16);
  // rpm: doesn't affect to rotation
  /* microstep
      1ms  = 200  steps for 1 revolution
      4ms  = 800  steps for 1 revolution
      8ms  = 1600 steps for 1 revolution
      16ms = 3200 steps for 1 revolution
      but speed are same
  */

}

void loop() {

  //stepper1.rotate(90);
  //stepper2.rotate(90);// automacally fit with various microstep
  // went more

  time_since_last_reset = millis();
  //while ((millis() - time_since_last_reset) < interval_five) {
    for (int i = 0; i < 800; i++) {
//      myMotor_one->step(1, FORWARD, SINGLE);      //single coil actuation (whole steps)
//      myMotor_two->step(1, BACKWARD, SINGLE);      //both motors advance one
      stepper1.move(1);
      stepper2.move(1);
    }                                           //step each time through for
  //}                                              // loop, simulates both running
  //simultaneously
  //pause 1/2 second
  delay(500);

}
