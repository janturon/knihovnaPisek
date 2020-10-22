// Pins
const int trigPin = 2;
const int echoPin = 5;
const int pumpPin = A3;
long duration;
//----------------------HCSR04
void HCSR04_setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
}

void HCSR04_loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); 
}

int HCSR04_CM(){
  duration = pulseIn(echoPin, HIGH);
  Serial.println(duration*0.034/2);
  return duration*0.034/2;
}
//------------------------PUMP
void pump_setup() {
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);  
}

void pump_splash(int dur){
  digitalWrite(pumpPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(dur);
  digitalWrite(pumpPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
HCSR04_setup();
pump_setup();
Serial.begin(9600);
}

void loop() {
HCSR04_loop();
if(HCSR04_CM()<60) pump_splash(1000);
}
