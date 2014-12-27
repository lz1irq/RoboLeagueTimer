#define SENSOR_PIN A0

#define TIMES 10
#define DELAY_MS 10
#define TOLERANCE 10

#define NEWLINE '\n'  

enum mode{
  STANDBY,
  WAITING,
  MEASURING 
};

struct {
  char operand[4];
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
  }
}

void interpretCommand() {
  if(!strcmp(command.operand, "NER")) {
    setArgument(&threshold.near);
    Serial.println(threshold.near);
  }
  else if(!strcmp(command.operand, "DST")) {
    setArgument(&threshold.distant);
  }
  else if(!strcmp(command.operand, "TOL")) {
    if(command.argument == 0) Serial.println("TOL" + threshold.tolerance);
    else threshold.tolerance = command.argument; 
  }
}

void setArgument(unsigned int* argument) {
  if(command.argument == 0) *argument = reading.current;
  else *argument = command.argument; 
}



