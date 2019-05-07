/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 13; // Analog output pin that the LED is attached to

int coordX = 0;  // value read from the pot
int coordXZero = 526 ;
int coordY = 0 ;
int vibratoCurve = 0.6 ; //used to give data a curve less that 1 but more than 0 
int vibratoDepth = 500 ;
int vibratoZero = 0 ;
int vibratoTHR = 200 ;
int vibratoMAX = 500 ;
int vibratoRaw = 0 ;
int vibratoVal = 0;   
boolean vibratoToggle = false ;
boolean pitchBendToggle = false ;     
int pitchBend = 8192 ;
int lastPitchBend = 8192 ;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  coordX = analogRead(A0);
  coordY = analogRead(A1) ;
  

  vibratoRaw = coordX - coordXZero ;
  vibratoVal = vibratoVal*0.5 + 0.5*map(rangeClip(vibratoRaw, vibratoZero, vibratoZero), -vibratoMAX, vibratoMAX, -vibratoDepth, vibratoDepth) ;
  vibratoZero = vibratoZero*vibratoCurve + vibratoRaw*(1-vibratoCurve) ;
  pitchBend = 8192 + vibratoVal ;
  if (lastPitchBend != pitchBend) {
    midiCommand(224, pitchBend&127, pitchBend>>7) ;
  }

  lastPitchBend = pitchBend ; 
  //Serial.print(coordX) ;
  //Serial.print("\t") ;
  //Serial.print(coordY) ;
  //Serial.print("\t") ;
  //Serial.println(vibratoVal) ;

  
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(5);
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
