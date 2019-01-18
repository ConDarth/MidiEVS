/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
int sensorVal = 0 ;
boolean noteOn = false ;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorVal = analogRead(A0);
  if (sensorVal >= 570) {
    if (!noteOn) {
      midiCommand(144, 60, 127) ;
    }
    sensorVal = map(sensorVal, 570, 1016, 1, 127) ;
    midiCommand(160, 60, sensorVal) ;
    noteOn = true ;
  } else if (noteOn) {
    midiCommand(128, 60, 0) ;
    noteOn = false ;
  }
  
  delay(1);        // delay in between reads for stability
}

void midiCommand(int command, int data1, int data2) {
  Serial.write(command);//send midi command byte
  Serial.write(data1);//send first data byte
  Serial.write(data2);//send second data byte
}

void midiCommand(int command, int data1) {
  Serial.write(command);//send midi command byte
  Serial.write(data1);//send first data byte
}
