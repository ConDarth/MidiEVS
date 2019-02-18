int pressureSensorPin = A0 ;
int pressureRaw = 0 ;
int pressureOnTHR = 70 ;
int pressureOffTHR = 50 ;
int pressureMAX = 400 ;
int pressureVal = 0 ;

long lastTime = 0 ;
long midiEffectDebounce = 5 ;

boolean noteStateToggle = false ;
int eviState = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  pressureRaw = analogRead(pressureSensorPin) ;
  if (!noteStateToggle && (pressureRaw > pressureOnTHR)) {
    eviState = 1 ;
    midiCommand(144, 60, 127) ;
    midiCommand(160, 60, pressureVal) ;
    noteStateToggle = true ;
  } else if (noteStateToggle && !(pressureRaw >= pressureOffTHR)) {
    eviState = 0 ;
    noteStateToggle = false ;
    midiCommand(128, 60, 127) ;
    pressureVal = 0 ;
  }
  
  switch(eviState) {
    case 0:
    //if pressure isnt above thr do nothing yet
    break;
    case 1:
    //set aftertouch when thr is reached

    if (millis() - lastTime > midiEffectDebounce) {
      pressureRaw = rangeClip(pressureRaw, pressureOnTHR, pressureMAX) ;
      pressureVal = map(pressureRaw, pressureOnTHR, pressureMAX, 0, 127) ;
      midiCommand(160, 60, pressureVal) ;

      lastTime = millis() ;
    }
    
    break;  
  }

}

int rangeClip(int number, int minimum, int maximum) {
  if (number >= maximum) {
    number = maximum ;
  } else if (number <= minimum) {
    number = minimum ;
  }
  return number ;
}
void midiCommand(int command, int data1, int data2) {
  Serial.write(command);//send midi command byte
  Serial.write(data1);//send first data byte
  Serial.write(data2);//send second data byte
}
void midiCommandShort(int command, int data1) {  
  Serial.write(command);//send midi command byte
  Serial.write(data1);//send first data byte
}
