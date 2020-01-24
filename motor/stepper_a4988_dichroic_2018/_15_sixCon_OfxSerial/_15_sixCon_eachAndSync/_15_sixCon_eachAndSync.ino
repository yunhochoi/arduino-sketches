/*
   Microstepping demo
   This requires that M0, M1 be connected in addition to STEP,DIR
   Copyright (C)2015 Laurentiu Badea

   This file may be redistributed under the terms of the MIT license.
   A copy of this license has been included with this distribution in the file LICENSE.
*/
#include <Arduino.h>
#include "A4988.h"
#include "BasicStepperDriver.h"
#include "SyncDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define M1_DIR  12
#define M1_STEP 13
#define M2_DIR  10
#define M2_STEP 11
#define M3_DIR  8
#define M3_STEP 9
#define M4_DIR  6
#define M4_STEP 7
#define M5_DIR  4
#define M5_STEP 5
#define M6_DIR  2
#define M6_STEP 3

#define M1_ENBL 22
#define M2_ENBL 23


// 2-wire basic config, microstepping is hardwired on the driver
// BasicStepperDriver stepper(DIR, STEP);

// microstep control for A4988
// #define MS1 4
// #define MS2 5
// #define MS3 6

A4988 m1(MOTOR_STEPS, M1_DIR, M1_STEP, M1_ENBL);
A4988 m2(MOTOR_STEPS, M2_DIR, M2_STEP, M2_ENBL);
A4988 m3(MOTOR_STEPS, M3_DIR, M3_STEP);
A4988 m4(MOTOR_STEPS, M4_DIR, M4_STEP);
A4988 m5(MOTOR_STEPS, M5_DIR, M5_STEP);
A4988 m6(MOTOR_STEPS, M6_DIR, M6_STEP);
A4988 stepper[] = {m1, m2, m3, m4, m5, m6};
int stepperNum = 6;
int rpm = 15;

SyncDriver controller1(stepper[0], stepper[1]);
SyncDriver controller2(stepper[2], stepper[3]);
SyncDriver controller3(stepper[4], stepper[5]);

void setup() {
  Serial.begin(9600);
  //     stepper.setRPM(1);
  for ( int i = 0; i < stepperNum ; i++) {
    stepper[i].begin(rpm, 16); // must be using Array, not m1, m2..
  }
}

void loop() {

  char inByte = 0;
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();

    // byte read, send three characters
    Serial.print(inByte);
    if (inByte == 'a') {
      rotateEach();
    }
  } else {
    moveAllSlow();

  }
}


void moveAllSlow() {
  //for ( int i = 0; i < stepperNum ; i++) {
  //stepper[i].setRPM(rpm);
  stepper[0].move(1);
  stepper[1].move(1);
  stepper[2].move(1);
  stepper[3].move(1);
  stepper[4].move(1);
  stepper[5].move(1);

  //}
}

void rotateEach() {
  for ( int i = 0; i < stepperNum ; i++) {
    stepper[i].setRPM(20);
    stepper[i].rotate(30);
  }
}

void rotatePair() {
  controller1.rotate(90, 90);
  controller2.rotate(90, 90);
  controller3.rotate(90, 90);
  delay(1000);
}

