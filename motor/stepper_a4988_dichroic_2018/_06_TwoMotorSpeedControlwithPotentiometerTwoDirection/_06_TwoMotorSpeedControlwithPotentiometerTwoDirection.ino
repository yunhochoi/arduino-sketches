/*
   Microstepping demo

   This requires that M0, M1 be connected in addition to STEP,DIR

   Copyright (C)2015 Laurentiu Badea

   This file may be redistributed under the terms of the MIT license.
   A copy of this license has been included with this distribution in the file LICENSE.
*/
#include <Arduino.h>
#include "A4988.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 m1_degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
// 2-wire basic config, microstepping is hardwired on the driver
// BasicStepperDriver stepper(DIR, STEP);

// microstep control for A4988
#define M1_DIR 2
#define M1_STEP 3
#define M1_ENBL 7
#define M1_MS1 4
#define M1_MS2 5
#define M1_MS3 6

#define M2_DIR 8
#define M2_STEP 9
#define M2_ENBL 13
#define M2_MS1 10
#define M2_MS2 11
#define M2_MS3 12

A4988 stepper1(MOTOR_STEPS, M1_DIR, M1_STEP, M1_MS1, M1_MS2, M1_MS3);
A4988 stepper2(MOTOR_STEPS, M2_DIR, M2_STEP, M2_MS1, M2_MS2, M2_MS3);

int m1_potPin = A0;    // select the input pin for the potentiometer
int m1_potVal = 0;  // variable to store the value coming from the sensor
int m1_spd = 0;
int m1_rot = 45;
int m1_deg = 1;
int m1_rpm = 1;

bool m1_enabled = true;

int m2_potPin = A1;    // select the input pin for the potentiometer
int m2_potVal = 0;  // variable to store the value coming from the sensor
int m2_spd = 0;
int m2_rot = 45;
int m2_deg = 1;
int m2_rpm = 2;

bool m2_enabled = true;

void setup() {
  /*
     Set target motor m1_rpm.
     These motors can do up to about 200m1_rpm.
     Too high will result in a high pitched whine and the motor does not move.
  */
  // stepper.setm1_rpm(1);
  stepper1.begin(1, 16);
  //stepper2.begin(1, 16);

  Serial.begin(9600);

}

void loop() {
  m1_potVal = analogRead(m1_potPin);
  m1_potVal = map(m1_potVal, 0, 1023, 0, 8);
  m1_spd = (m1_potVal + 1) * 2;
  Serial.println(m1_spd);

  stepper1.setRPM(m1_rpm);
  // rotate: move (num * 200 * microstep / 360)
  stepper1.rotate(m1_rot); // automacally fit with various microstep


//  m2_potVal = analogRead(m2_potPin);
//  m2_potVal = map(m2_potVal, 0, 1023, 0, 8);
//  m2_spd = (m2_potVal + 1) * 2;
//  Serial.println(m2_spd);

  //stepper2.setRPM(m2_rpm);
  //stepper2.rotate(m2_rot); // automacally fit with various microstep


  if (m1_spd == 2 ) {
    m1_rpm = 8;
    m1_rot = m1_deg;
    digitalWrite(M1_ENBL, LOW);
    m1_enabled = true;
  } else if (m1_spd == 4 ) {
    digitalWrite(M1_ENBL, LOW);
    m1_rpm = 6;
    m1_rot = m1_deg;
    m1_enabled = true;
  } else if (m1_spd == 6 ) {
    digitalWrite(M1_ENBL, LOW);
    m1_rpm = 4;
    m1_rot = m1_deg;
    m1_enabled = true;
  } else if (m1_spd == 8 ) {
    digitalWrite(M1_ENBL, LOW);
    m1_rpm = 2;
    m1_rot = m1_deg;
    m1_enabled = true;
  } else if (m1_spd == 10 && m1_enabled == true) {
    Serial.println("disabled");
    digitalWrite(M1_ENBL, HIGH);
    m1_enabled = false;
  // stepper2.rotate(m2_rot); // automacally fit with various microstep

  } else if (m1_spd == 12) {
    digitalWrite(M1_ENBL, LOW);
    m1_rpm = 2;
    m1_rot = m1_deg * -1;
    m1_enabled = true;
  } else if (m1_spd == 14) {
    digitalWrite(M1_ENBL, LOW);
    m1_rpm = 4;
    m1_rot = m1_deg * -1;
    m1_enabled = true;
  } else if (m1_spd == 16) {
    digitalWrite(M1_ENBL, LOW);
    m1_enabled = true;
    m1_rpm = 6;
    m1_rot = m1_deg * -1;
  } else if (m1_spd == 18) {
    digitalWrite(M1_ENBL, LOW);
    m1_enabled = true;
    m1_rpm = 8;
    m1_rot = m1_deg * -1;
  }


  //
  
  // rotate: move (num * 200 * microstep / 360)
//  if (m1_enabled = false) {
    //stepper2.rotate(m2_rot); // automacally fit with various microstep
//  }
  //
  //  if (m2_spd == 2) {
  //    m2_rpm = 8;
  //    m2_rot = m2_deg;
  //  } else if (m2_spd == 4) {
  //    digitalWrite(M2_ENBL, LOW);
  //    m2_rpm = 6;
  //    m2_rot = m2_deg;
  //  } else if (m2_spd == 6) {
  //    digitalWrite(M2_ENBL, LOW);
  //    m2_rpm = 4;
  //    m2_rot = m2_deg;
  //  } else if (m2_spd == 8) {
  //    digitalWrite(M2_ENBL, LOW);
  //    m2_rpm = 2;
  //    m2_rot = m2_deg;
  //  } else if (m2_spd == 10 ) {
  //    //Serial.println("disabled");
  //    digitalWrite(M2_ENBL, HIGH);
  //    m2_enabled = false;
  //
  //  } else if (m2_spd == 12) {
  //    digitalWrite(M2_ENBL, LOW);
  //    m2_rpm = 2;
  //    m2_rot = m2_deg * -1;
  //  } else if (m2_spd == 14) {
  //    digitalWrite(M2_ENBL, LOW);
  //    m2_rpm = 4;
  //    m2_rot = m2_deg * -1;
  //  } else if (m2_spd == 16) {
  //    digitalWrite(M2_ENBL, LOW);
  //    m2_rpm = 6;
  //    m2_rot = m2_deg * -1;
  //  } else if (m2_spd == 18) {
  //    digitalWrite(M2_ENBL, LOW);
  //    m2_rpm = 8;
  //    m2_rot = m2_deg * -1;
  //  }

  //    /*
  //     * Microstepping mode: 1,2,4,8,16 or 32(DRV8834 only)
  //     * Mode 1 is full speed.
  //     * Mode 32 is 32 microsteps per step.
  //     * The motor should rotate just as fast (set m1_rpm),
  //     * but movement precision is increased.
  //     */
  //
  //    // 180 m1_degrees now takes 100 * 8 microsteps
  //    stepper.move(100*16);
  //    stepper.rotate(180);
  //
  //    // as you can see, using m1_degrees is easier
  //    stepper.move(-100*16);
  //    stepper.rotate(-180);

}
