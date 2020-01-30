void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  delay(1000);
   
  int  i = 1234;
  Serial.print(i, DEC);
  Serial.print('\n');
 
  float f = 321.7;
  Serial.print(f);
  Serial.print('\n');
}
