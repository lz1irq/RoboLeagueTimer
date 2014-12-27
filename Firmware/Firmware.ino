#define SENSOR_PIN A0

#define TIMES 10
#define DELAY_MS 10

void setup() {
  Serial.begin(9600); 
}

void loop() {
  Serial.println(sensorAverage()); 
  delay(100);
}

int sensorAverage() {
  int readings = 0;
  for(int i=0; i<TIMES; i++) {
    readings += analogRead(SENSOR_PIN);
    delay(DELAY_MS); 
  }
  return readings/TIMES;
}
