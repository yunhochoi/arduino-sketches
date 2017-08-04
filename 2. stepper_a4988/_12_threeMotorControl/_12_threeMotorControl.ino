#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "SyncDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// A motor
#define DIR_A 11
#define STEP_A 10
//#define ENABLE_A 3

// B motor
#define DIR_B 23
#define STEP_B 12
//#define ENABLE_B 4

// C motor
#define DIR_C 24
#define STEP_C 11
//#define ENABLE_C 2

// D motor
#define DIR_D 25
#define STEP_D 10
//#define ENABLE_D 2

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 16

// 2-wire basic config, microstepping is hardwired on the driver
// Other drivers can be mixed and matched but must be configured individually
BasicStepperDriver stepperA(MOTOR_STEPS, DIR_A, STEP_A);
BasicStepperDriver stepperB(MOTOR_STEPS, DIR_B, STEP_B);
BasicStepperDriver stepperC(MOTOR_STEPS, DIR_C, STEP_C);
BasicStepperDriver stepperD(MOTOR_STEPS, DIR_D, STEP_D);

SyncDriver controller(stepperA, stepperB);
SyncDriver controller2(stepperC, stepperD);

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


  if (phaseValue == 0) {
    controller.move(1, 1);
    controller2.move(1, 1);
  } else if (phaseValue == 1) {
    controller.move(-1, -1);
    controller2.move(-1, -1);
  } else if (phaseValue == 2) {
    controller.rotate(60, 60);
    controller2.rotate(60, 60);
    delay(500);
  }

}

