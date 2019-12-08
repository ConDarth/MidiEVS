#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   biteSensor = CapacitiveSensor(2,7);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

int biteRaw = 0 ;
int biteOnTHR = 1400 ;
int biteOffTHR = 1350 ;
int biteMAX = 2200 ;
int portamentoVal = 0 ;
boolean portamentoToggle = false ;
int pressureDebounce = 5 ;
int pressureLastTime = 0 ;

void setup()                    
{
   Serial.begin(9600);
}

void loop()                    
{
    biteRaw =  biteSensor.capacitiveSensor(10);
    if ( biteRaw > biteOnTHR) {
      if (!portamentoToggle) {
        midiCommand(176, 65, 127) ;
      }
      portamentoVal = rangeClip(biteRaw, biteOffTHR, biteMAX) ;
      portamentoVal = map(portamentoVal, biteOffTHR, biteMAX, 0, 127) ;
      if (millis() - pressureLastTime > pressureDebounce) {
        midiCommand(176, 5, portamentoVal) ;
       // midiCommand(176, 37, portamentoVal>>7) ;
        pressureLastTime = millis() ;
      }
      portamentoToggle = true ;
    } else if ((biteRaw < biteOffTHR) &&(portamentoToggle)) {
      portamentoToggle = false ;
      midiCommand(176, 65, 0) ;
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
