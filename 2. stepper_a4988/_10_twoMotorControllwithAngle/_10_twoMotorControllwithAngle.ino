#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "SyncDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// X motor
#define DIR_X 5
#define STEP_X 9

// Y motor
#define DIR_Y 8
#define STEP_Y 6

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 16

// 2-wire basic config, microstepping is hardwired on the driver
// Other drivers can be mixed and matched but must be configured individually
BasicStepperDriver stepperX(MOTOR_STEPS, DIR_X, STEP_X);
BasicStepperDriver stepperY(MOTOR_STEPS, DIR_Y, STEP_Y);

SyncDriver controller(stepperY, stepperX);

void setup() {
    /*
     * Set target motors RPM.
     */
    stepperX.begin(1, MICROSTEPS);
    stepperY.begin(1, MICROSTEPS);
}

void loop() {

//    controller.rotate(90*5, 60*15);
//    delay(1000);
//    controller.rotate(-90*5, -30*15);
//    delay(1000);
//    controller.rotate(0, -30*15);
//    delay(1000);

    controller.rotate(30, 30);
    delay(1000);
    controller.rotate(-30, -30);
    delay(1000);
//    controller.rotate(0, -30*15);
//    delay(1000);
}
