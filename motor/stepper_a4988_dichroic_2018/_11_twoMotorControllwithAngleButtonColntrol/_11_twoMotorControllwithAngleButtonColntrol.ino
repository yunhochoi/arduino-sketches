#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "SyncDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// X motor
#define DIR_X 5
#define STEP_X 9
#define ENABLE_X 3

// Y motor
#define DIR_Y 8
#define STEP_Y 6
#define ENABLE_Y 4

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 16

// 2-wire basic config, microstepping is hardwired on the driver
// Other drivers can be mixed and matched but must be configured individually
BasicStepperDriver stepperX(MOTOR_STEPS, DIR_X, STEP_X, ENABLE_X);
BasicStepperDriver stepperY(MOTOR_STEPS, DIR_Y, STEP_Y, ENABLE_Y);

SyncDriver controller(stepperY, stepperX);

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
  stepperX.begin(rpm, MICROSTEPS);
  stepperY.begin(rpm, MICROSTEPS);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(sensorPin);
  phaseValue = analogRead(phasePin);
  sensorValue = map(sensorValue, 0, 1000, 0, 4);
  phaseValue = map(phaseValue, 0, 1000, 0, 4);

  Serial.print(sensorValue);
  Serial.print(",");
  Serial.println(phaseValue);

  rpm = sensorValue;
  stepperX.setRPM(rpm);
  stepperY.setRPM(rpm);


  if (phaseValue == 0) {
    controller.move(1, 1);
  } else if (phaseValue == 1) {
    controller.move(-1, -1);
  } else if (phaseValue == 2) {
    controller.rotate(60, 60);
    delay(500);
  }

}

