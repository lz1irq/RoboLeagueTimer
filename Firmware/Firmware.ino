#define SENSOR_PIN A0

void setup() {
  Serial.begin(9600); 
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  Serial.println(sensorValue); 
}
