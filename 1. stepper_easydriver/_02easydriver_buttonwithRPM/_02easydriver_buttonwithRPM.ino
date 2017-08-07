
 
//#define RPMS                104.0
#define RPMS                104.0
#define STEP_PIN                9
#define DIRECTION_PIN           8
#define GO_PIN                  3

#define STEPS_PER_REV         200
#define MICROSTEPS_PER_STEP     8
#define MICROSECONDS_PER_MICROSTEP   (1000000/(STEPS_PER_REV * MICROSTEPS_PER_STEP)/(RPMS / 60))

uint32_t LastStepTime = 0;
uint32_t CurrentTime = 0;

void setup() {                
  pinMode(STEP_PIN, OUTPUT);     
  pinMode(DIRECTION_PIN, OUTPUT);
  digitalWrite(STEP_PIN, LOW);
  digitalWrite(DIRECTION_PIN, LOW);
  pinMode(GO_PIN,INPUT);
}

void loop() {
  if (digitalRead(GO_PIN) == LOW)
  {
    CurrentTime = micros();
    if ((CurrentTime - LastStepTime) > MICROSECONDS_PER_MICROSTEP)
    {
      LastStepTime = CurrentTime;
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);
      digitalWrite(STEP_PIN, LOW); 
      delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);
    }
  }
}
