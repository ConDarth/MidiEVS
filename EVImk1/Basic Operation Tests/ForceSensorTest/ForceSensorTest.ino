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
const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to

int sensorVal = 0;        // value read from the pot
int sensorOnTHR = 350 ;
int sensorOffTHR = 300 ;
int sensorMAX = 600 ;
int sensorStateToggle = false ;
int portamentoToggle = false ;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorVal = analogRead(analogInPin);
  if ((sensorVal > sensorOnTHR)&&(!sensorStateToggle)) {
    sensorStateToggle = true ;
    portamentoToggle = true ;
  } else if ((sensorVal < sensorOffTHR)&&(sensorStateToggle)) {
    sensorStateToggle = false ;
    portamentoToggle = true ;
  }
  if (sensorStateToggle) {
    if (portamentoToggle) {
      midiCommand(176, 65, 127) ;
      portamentoToggle = false ;
    }
    sensorVal = rangeClip(sensorVal, sensorOffTHR, sensorMAX) ;
    sensorVal = map(sensorVal, sensorOffTHR, sensorMAX, 0, 16383) ;
    midiCommand(176, 5, sensorVal>>7) ;
    midiCommand(176, 37, sensorVal&127) ;
  } else if (!sensorStateToggle && portamentoToggle) {
    midiCommand(176, 65, 0) ;
    portamentoToggle = false ;
  }
  
  delay(5) ;
  
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
