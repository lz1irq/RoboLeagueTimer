#define SENSOR_PIN A0

#define BEGIN_MEASURING "BMS"
#define STOP_MEASURING "SMS"

#define THRESHOLD_NEAR "NER"
#define THRESHOLD_DISTANT "DST"
#define TOLERANCE "TOL"

#define TIMES "TMS"
#define DELAY "DLY"

enum mode{
  STANDBY,
  WAITING,
  MEASURING 
};

struct {
  char name[4];
  int argument;
} 
command;

struct {
  unsigned int near = 0;
  unsigned int distant = 0;
  unsigned int tolerance = 10; 
} 
threshold;

struct {
  unsigned int times = 10;
  unsigned int msDelay = 10;
  unsigned int current = 0;
} 
reading;

mode currentMode = STANDBY;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  reading.current = sensorAverage();
  if(Serial.available() > 0) {
    parseCommand();
    interpretCommand();
  }
  delay(100);
}

int sensorAverage() {
  int readings = 0;
  for(int i=0; i<reading.times; i++) {
    readings += analogRead(SENSOR_PIN);
    delay(reading.msDelay); 
  }
  return readings/reading.times;
}

void parseCommand() {
  Serial.readBytes(command.name, 3);
  if(Serial.available() >= 3 ) {
    char arg[3];
    Serial.readBytes(arg, 3);
    command.argument = atoi(arg);
  }
}

void interpretCommand() {
  if(!strcmp(command.name, BEGIN_MEASURING) {
    currentMode = WAITING; 
  }
  else if(!strcmp(command, STOP_MEASURING)) {
    currentMode = STANDBY;
  }
  else if(!strcmp(command.name, THRESHOLD_NEAR)) {
    setAndReport(&threshold.near);
  }
  else if(!strcmp(command.name, THRESHOLD_DISTANT)) {
    setAndReport(&threshold.distant);
  }
  else if(!strcmp(command.name, TOLERANCE)) {
    setAndReport(&threshold.tolerance);
  }
  else if(!strcmp(command.name, TIMES)) {
    setAndReport(&reading.times);
  } 
  else if(!strcmp(command.name, DELAY)) {
    setAndReport(&reading.msDelay);
  }
}

void setAndReport(unsigned int* argument) {
  if(command.argument != 0) *argument = command.argument;
  Serial.print(command.name);
  Serial.println(*argument);
}





