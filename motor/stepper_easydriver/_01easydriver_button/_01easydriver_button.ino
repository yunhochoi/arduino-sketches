#define DISTANCE 3200

int StepCounter = 0;
int Stepping = false;

void setup() {                
  pinMode(3, OUTPUT);     
  pinMode(4, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);

  pinMode(3,INPUT);
}

void loop() {
  if (digitalRead(3) == LOW && Stepping == false)
  {
    Stepping = true;
  }

  if (Stepping == true)
  {
    digitalWrite(9, HIGH);
    //delay(1);
    delayMicroseconds(500);          
    digitalWrite(9, LOW); 
    //delay(1);
    delayMicroseconds(500);

    StepCounter = StepCounter + 1;

    if (StepCounter == DISTANCE)
    {
      StepCounter = 0;
      Stepping = false;
    }
  }
}
