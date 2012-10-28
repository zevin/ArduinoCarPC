/*
Badillac Computer System by Kevin Bidwell
*/
// Define All my Digital Input Pins
int lineLock = 2;
int raceMode = 3;
int launchMode = 4;
int speedo = 5;
// Define Analog Input Pins
int oilTemp = A0;
int waterTemp = A1;
int nosTemp = A2;
int airTemp = A3;
int oilPressure = A4;
//Define Digital Output Pins
int nosHeater = 13;
int nos = 12;
int lineLockFront = 11;
int lineLockRear = 10;
int nosTempLED = 9;
int shiftLED = 8;
int oilPressureLED = 7;
char nosOn[] = "Off";
//Define varibles for printing to PC
String data = "";
String OT = "Oil Temp";
String AT = "Air Temp";
String NT = "NOS Temp";
String WT = "Water Temp";
String OP = "Oil Pres";

void setup() {
  //Define the mode for all the input pins
  pinMode(lineLock, INPUT_PULLUP);
  pinMode(raceMode, INPUT_PULLUP);
  pinMode(launchMode, INPUT_PULLUP);
  pinMode(speedo, INPUT_PULLUP);
  //Define the mode for all the output pins
  pinMode(nosHeater, OUTPUT);
  pinMode(nos, OUTPUT);
  pinMode(lineLockFront, OUTPUT);
  pinMode(lineLockRear, OUTPUT);
  pinMode(nosTempLED, OUTPUT);
  pinMode(shiftLED, OUTPUT);
  pinMode(oilPressureLED, OUTPUT);
  //Start Serial Communication
  Serial.begin(9600);
}

void loop() {
  printToPC();
  brakeControls();
  monitorTemps();
  checkRaceMode();
  delay(200);
}

void printToPC(){
  data = "";
  //Send all Data to PC for Logging
  Serial.print(String(map(analogRead(oilTemp), 0, 1023, 0, 255)) + " Oil Temp ");
  Serial.print(String(map(analogRead(airTemp), 0, 1023, 0, 255)) + " Air Temp ");
  Serial.print(",");
  Serial.print(String(map(analogRead(nosTemp), 0, 1023, 0, 255)) + " Nos Temp ");
  Serial.print("NOS " + String(nosOn));
  Serial.print("|");
  Serial.print(String(map(analogRead(oilPressure), 0, 1023, 0, 255)) + " Oil Pres ");
  Serial.print(".");
}

void brakeControls(){
  //Define Launch Mode and Line Lock Functions
  if((digitalRead(lineLock) == LOW) && (digitalRead(launchMode) == LOW)){
    digitalWrite(lineLockFront, HIGH);
    digitalWrite(lineLockRear, HIGH);
  }
  
  else if((digitalRead(lineLock) == LOW) && (digitalRead(launchMode) == HIGH)){
    digitalWrite(lineLockFront, HIGH);
    digitalWrite(lineLockRear, LOW);
  }
  
  else {
    digitalWrite(lineLockFront, LOW);
    digitalWrite(lineLockRear, LOW);
  }
}

void monitorTemps(){
  //Check critial temps and pressures
  if(map(analogRead(oilPressure), 0, 1023, 0, 255) > 100){
    digitalWrite(oilPressureLED, HIGH);
  }
  else {
    digitalWrite(oilPressureLED, LOW);
  }
  
  if(map(analogRead(nosTemp), 0, 1023, 0, 255) > 100){
    digitalWrite(nosTempLED, HIGH);
  }
  else {
    digitalWrite(nosTempLED, LOW);
  }
}

void checkRaceMode(){
    if(digitalRead(raceMode) == LOW){
    if(analogRead(nosTemp) < 512){
      digitalWrite(nosHeater, HIGH);
    } else {
      digitalWrite(nosHeater, LOW);
    }
    
    if((analogRead(nosTemp) > 505) && (analogRead(nosTemp)) < 600){
      digitalWrite(nosTempLED, HIGH);
    } else { 
      digitalWrite(nosTempLED, LOW);
    }
    
    if(digitalRead(speedo) == LOW){
      digitalWrite(nos, HIGH);
      char nosOn[] = "On";
    } else {
      digitalWrite(nos, LOW);
      char nosOn[] = "Off";
    }
  }
}

