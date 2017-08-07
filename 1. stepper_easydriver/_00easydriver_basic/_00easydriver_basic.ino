void setup() {                
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void loop() {
  digitalWrite(3, HIGH);
  delayMicroseconds(500); 
  //delay(10);         
  digitalWrite(3, LOW); 
  delayMicroseconds(500);
//  delay(10);
  }

