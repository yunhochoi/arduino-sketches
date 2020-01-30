/*
 Simple in connection from TouchDesigner to Arduino Mega
 Yuno Choi | AV&C 

 How to send data from TouchDesigner: 
 op('serial_arduino').send('1')
 op('serial_arduino').send('0')

 Be sure to turn off Active parameter in the TouchDesigner Serial In DAT
 while uploading new sketches to the board.  Otherwise uploading is disabled
 as the serial connection is in use.
*/

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() { 
  // monitor incoming bytes.
  // in the case of '1' or '0' set LED output accordingly
  if (Serial.available())
  {
    char c = Serial.read();  
    if (c == '1'){
      digitalWrite(LED_BUILTIN, 1);  // turn on
      //Serial.print(c);
    }
    else if (c == '0'){
      digitalWrite(LED_BUILTIN, 0);  // turn off
    }
  }
}
