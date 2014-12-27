#define SENSOR_PIN A0

#define TIMES 10
#define DELAY_MS 10
#define TOLERANCE 10

#define NEWLINE '\n'  

enum mode{
  CALIBRATION,
  STANDBY,
  WAITING,
  MEASURING 
};

struct {
  char operand[4];
  int argument;
} command;

struct {
  unsigned int near = 0;
  unsigned int distant = 0;
  unsigned int tolerance = 10; 
} 
threshold;

mode currentMode = CALIBRATION;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  if(Serial.available() > 0) {
    parseCommand(); 
  }
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

void parseCommand() {
  Serial.readBytes(command.operand, 3);
  Serial.println(command.operand);
  if(Serial.available() >= 3 ) {
    char arg[3];
    Serial.readBytes(arg, Serial.available());
    command.argument = atoi(arg);
    Serial.println(command.argument);
  }
}
