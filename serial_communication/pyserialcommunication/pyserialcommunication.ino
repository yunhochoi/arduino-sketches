String serData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("arduino is ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0){
    char rec = Serial.read();
    serData += rec;

    if (rec == '\n'){
      Serial.print("Message received: ");
      Serial.println(serData);
      serData = "";
    }
  }
  delay(10);
}
 