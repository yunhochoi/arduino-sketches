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
#define M3_ENBL 24
#define M4_ENBL 25
#define M5_ENBL 26
#define M6_ENBL 27

int dir  = 1;
int dir2 = 1;
int stp  = 1;
// 2-wire basic config, microstepping is hardwired on the driver
// BasicStepperDriver stepper(DIR, STEP);

// microstep control for A4988
// #define MS1 4
// #define MS2 5
// #define MS3 6

A4988 m1(MOTOR_STEPS, M1_DIR, M1_STEP, M1_ENBL);
A4988 m2(MOTOR_STEPS, M2_DIR, M2_STEP, M2_ENBL);
A4988 m3(MOTOR_STEPS, M3_DIR, M3_STEP, M3_ENBL);
A4988 m4(MOTOR_STEPS, M4_DIR, M4_STEP, M4_ENBL);
A4988 m5(MOTOR_STEPS, M5_DIR, M5_STEP, M5_ENBL);
A4988 m6(MOTOR_STEPS, M6_DIR, M6_STEP, M6_ENBL);
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
    if (inByte == 's') {
      //rotateEach();
      disableAll();
    }
    if (inByte == 'q') {
      enableAll();
      rotatePair();
    }
    if (inByte == 'a') {
      enableAll();
      rotateEach();
    }
    if (inByte == 'e') {
      enableAll();
    }
    if (inByte == 'd') {  //direction
      enableAll();
      dir *= -1;
    }
    if (inByte == 'f') {  //direction
      enableAll();
      dir2 *= -1;
    }
    if (inByte == 'p') {
      rpm += 1;
    } else if (inByte == 'o') {
      if (rpm > 0) {
        rpm -= 1;
      }
    }

  }
  else {
    //moveAllSlow();
   twoDirection();
  }

}

void moveAllSlow() {
  for ( int i = 0; i < stepperNum ; i++) {
    stepper[i].setRPM(rpm);
    stepper[i].move(stp);
  }
}

void twoDirection() {
    for ( int i = 0; i < stepperNum ; i++) {
      stepper[i].setRPM(rpm);
    }
  stepper[0].move(stp*dir);
  stepper[1].move(stp*dir*dir2);
  stepper[2].move(stp*dir);
  stepper[3].move(stp*dir*dir2);
  stepper[4].move(stp*dir);
  stepper[5].move(stp*dir*dir2);
  
//  m1.move(1);
//  m2.move(-1);
//  m3.move(1);
//  m4.move(-1);
//  m5.move(1);
//  m6.move(-1);

}

void rotateEach() {
  for ( int i = 0; i < stepperNum ; i++) {
    stepper[i].setRPM(3);
    stepper[i].rotate(30);
  }
}

void stopAll() {
  digitalWrite(M1_ENBL, HIGH);
  digitalWrite(M2_ENBL, HIGH);
  digitalWrite(M3_ENBL, HIGH);
  digitalWrite(M4_ENBL, HIGH);
  digitalWrite(M5_ENBL, HIGH);
  digitalWrite(M6_ENBL, HIGH);
}

void disableAll() {
  digitalWrite(M1_ENBL, HIGH);
  digitalWrite(M2_ENBL, HIGH);
  digitalWrite(M3_ENBL, HIGH);
  digitalWrite(M4_ENBL, HIGH);
  digitalWrite(M5_ENBL, HIGH);
  digitalWrite(M6_ENBL, HIGH);
}

void enableAll() {
  digitalWrite(M1_ENBL, LOW);
  digitalWrite(M2_ENBL, LOW);
  digitalWrite(M3_ENBL, LOW);
  digitalWrite(M4_ENBL, LOW);
  digitalWrite(M5_ENBL, LOW);
  digitalWrite(M6_ENBL, LOW);
}

void rotatePair() {
  controller1.rotate(90, 90);
  controller2.rotate(90, 90);
  controller3.rotate(90, 90);
  delay(1000);
}

