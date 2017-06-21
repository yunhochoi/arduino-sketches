/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  myservo.write(99);                  // sets the servo position according to the scaled value
  /*
  0 ~ 80 : Left / full speed
  93 : Left / normal speed
  98 : Left / minimum speed
  99 : NO MOVEMENT
  100 : Right / minimum spd 
  105 : Right / normal speed
  120 ~ 180 : Right / full speed
  */
}

