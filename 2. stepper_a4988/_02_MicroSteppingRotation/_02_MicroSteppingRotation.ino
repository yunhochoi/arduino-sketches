/*
 * Microstepping demo
 *
 * This requires that M0, M1 be connected in addition to STEP,DIR
 *
 * Copyright (C)2015 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "A4988.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
#define ENBL 7

// 2-wire basic config, microstepping is hardwired on the driver
// BasicStepperDriver stepper(DIR, STEP);

// microstep control for A4988
 #define MS1 4
 #define MS2 5 
 #define MS3 6
 A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);

void setup() {
    /*
     * Set target motor RPM.
     * These motors can do up to about 200rpm.
     * Too high will result in a high pitched whine and the motor does not move.
     */
    //     stepper.setRPM(1);

    stepper.begin(2, 16); 
    // rpm: doesn't affect to rotation
    /* microstep
     *  1ms  = 200  steps for 1 revolution
     *  4ms  = 800  steps for 1 revolution 
     *  8ms  = 1600 steps for 1 revolution
     *  16ms = 3200 steps for 1 revolution
     *  but speed are same
     */
    
}

void loop() {
    delay(1000);
    
    // steps for 1 revolution
    //stepper.move(1600); 
    
    // rotate: move (num * 200 * microstep / 360)
    
     stepper.rotate(180); // automacally fit with various microstep
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
