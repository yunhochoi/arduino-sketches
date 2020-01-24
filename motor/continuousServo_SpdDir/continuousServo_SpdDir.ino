/* Speed and Direction Test for Continuous Servo Motor 
 by AV&C <http://av-controls.com>
 
 modified 21 June 2017
 by Yunho Choi
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(10);  // attaches the servo on pin 10 to the servo object
}

void loop() {

  myservo.write(99);   // sets the servo speed and direction
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
