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

// All the wires needed for full functionality
#define M1_DIR 2
#define M1_STEP 3
#define M1_ENBL 7
#define M2_DIR 8
#define M2_STEP 9
#define M2_ENBL 13

// 2-wire basic config, microstepping is hardwired on the driver
// BasicStepperDriver stepper(DIR, STEP);

// microstep control for A4988
#define M1_MS1 4
#define M1_MS2 5
#define M1_MS3 6
#define M2_MS1 10
#define M2_MS2 11
#define M2_MS3 12

A4988 stepper1(MOTOR_STEPS, M1_DIR, M1_STEP, M1_MS1, M1_MS2, M1_MS3);
A4988 stepper2(MOTOR_STEPS, M2_DIR, M2_STEP, M2_MS1, M2_MS2, M2_MS3);

void setup() {
  /*
     Set target motor RPM.
     These motors can do up to about 200rpm.
     Too high will result in a high pitched whine and the motor does not move.
  */
  //     stepper.setRPM(1);

  stepper1.begin(100, 16);
  stepper2.begin(100, 16);

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
  delay(1000);

  // steps for 1 revolution
  //stepper.move(1600);

  // rotate: move (num * 200 * microstep / 360)

  stepper1.rotate(360); // automacally fit with various microstep
  stepper2.rotate(180); // automacally fit with various microstep
  // went more


  //    // one full reverse rotation
  //    stepper.move(-100);
  //    stepper.rotate(-180);
  //
  //    /*
  //     * Microstepping mode: 1,2,4,8,16 or 32(DRV8834 only)
  //     * Mode 1 is full speed.
  //     * Mode 32 is 32 microsteps per step.
  //     * The motor should rotate just as fast (set RPM),
  //     * but movement precision is increased.
  //     */
  //    stepper.setMicrostep(16);
  //
  //    // 180 degrees now takes 100 * 8 microsteps
  //    stepper.move(100*16);
  //    stepper.rotate(180);
  //
  //    // as you can see, using degrees is easier
  //    stepper.move(-100*16);
  //    stepper.rotate(-180);

  delay(1000);
}
