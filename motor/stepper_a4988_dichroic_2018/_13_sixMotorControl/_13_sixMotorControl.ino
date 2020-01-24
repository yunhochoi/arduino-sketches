#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "SyncDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

#define DIR_A 10
#define DIR_B 12
#define DIR_C 11
#define DIR_D 10
#define DIR_E 9
#define DIR_F 8

#define STEP_A 11
#define STEP_B 6
#define STEP_C 5
#define STEP_D 22
#define STEP_E 3
#define STEP_F 2

#define ENABLE_F 5

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 16

// 2-wire basic config, microstepping is hardwired on the driver
// Other drivers can be mixed and matched but must be configured individually
BasicStepperDriver stepperA(MOTOR_STEPS, DIR_A, STEP_A);
BasicStepperDriver stepperB(MOTOR_STEPS, DIR_B, STEP_B);
BasicStepperDriver stepperC(MOTOR_STEPS, DIR_C, STEP_C);
BasicStepperDriver stepperD(MOTOR_STEPS, DIR_D, STEP_D);
BasicStepperDriver stepperE(MOTOR_STEPS, DIR_E, STEP_E);
BasicStepperDriver stepperF(MOTOR_STEPS, DIR_F, STEP_F);

SyncDriver controller(stepperA, stepperB);
SyncDriver controller2(stepperC, stepperD);
SyncDriver controller3(stepperE, stepperF);

int buttonPin = 2;     // the number of the pushbutton pin
int sensorPin = A1;    // select the input pin for the potentiometer
int phasePin = A0;    // select the input pin for the potentiometer

int sensorValue = 0;  // variable to store the value coming from the sensor
int phaseValue = 0;

int phase = 1;
int buttonState = 0;         // variable for reading the pushbutton status
int motorSpeed = 0;

int rpm = 1;
bool disabled = false;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  stepperA.begin(rpm, MICROSTEPS);
  stepperB.begin(rpm, MICROSTEPS);
  stepperC.begin(rpm, MICROSTEPS);
  stepperD.begin(rpm, MICROSTEPS);
  stepperE.begin(rpm, MICROSTEPS);
  stepperF.begin(rpm, MICROSTEPS);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(sensorPin);
  phaseValue = analogRead(phasePin);
  sensorValue = map(sensorValue, 0, 1000, 1, 100);
  phaseValue = map(phaseValue, 0, 1000, 0, 4);

  Serial.print(sensorValue);
  Serial.print(",");
  Serial.println(phaseValue);

  rpm = sensorValue;
  stepperA.setRPM(rpm);
  stepperB.setRPM(rpm);
  stepperC.setRPM(rpm);
  stepperD.setRPM(rpm);
  stepperE.setRPM(rpm);
  stepperF.setRPM(rpm);


  if (phaseValue == 0) {
    controller.move(1, 1);
    controller2.move(1, 1);
    controller3.move(1, 1);

  } else if (phaseValue == 1) {
    controller.move(-1, -1);
    controller2.move(-1, -1);
    controller3.move(-1, -1);
  } else if (phaseValue == 2) {
    controller.rotate(60, 60);
    controller2.rotate(60, 60);
    controller3.rotate(60, 60);
    delay(500);
  }

}

