#define trigPin 5
#define echoPin 2
#define pumpPin A3

void HCSR04_setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  int intNo = digitalPinToInterrupt(echoPin);
  attachInterrupt(intNo, HCSR04_response, FALLING);
}

// HCSR04 -------------------------------------------------
unsigned long HCSR04_trigTime = 0L;

void HCSR04_loop() {
  unsigned long now = micros();
  if(now - HCSR04_trigTime < 60000) return;
  HCSR04_trigTime = now;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

volatile unsigned long HCSR04_value = 0;
void HCSR04_response() {
  unsigned long responseTime = micros() - HCSR04_trigTime;
  if(responseTime<10000) HCSR04_value = responseTime;
}

int HCSR04_getCm() {
  if(HCSR04_value==0) return 10000;
  return HCSR04_value/2 * 0.0343; // speed of sound cm/us
}

// pump ---------------------------------------------------
void pump_setup() {
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);
}

void pump_splash(int duration) {
  digitalWrite(pumpPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(duration);
  digitalWrite(pumpPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}


void setup() {
  HCSR04_setup();
  pump_setup();
}

void loop() {
  HCSR04_loop();
  if(HCSR04_getCm()<90) pump_splash(250); //toto je potreba kalibrovat
}
