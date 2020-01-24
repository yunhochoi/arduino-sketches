#include <AccelStepper.h>
AccelStepper stepper(1,13,12);//initialise accelstepper for a two wire board, pin 5 step, pin 4 dir

void setup() {
  Serial.begin(9600);
  pinMode(7,OUTPUT); // Enable
  digitalWrite(7,LOW); // Set Enable low
}

void loop() {
  digitalWrite(7,LOW); // Set Enable low
  if (stepper.distanceToGo() == 0)
  {  // Random change to speed, position and acceleration
    // Make sure we dont get 0 speed or accelerations
    delay(1000);
    stepper.moveTo(10000);
    stepper.setMaxSpeed(10000);
    stepper.setAcceleration(1000);
  }

//Serial.println(stepper.distanceToGo());
stepper.run();  // Actually makes stepper move
}

