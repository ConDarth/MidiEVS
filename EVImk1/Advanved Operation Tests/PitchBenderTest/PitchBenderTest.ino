#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   pBUpSensor = CapacitiveSensor(2, 3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   pBDownSensor = CapacitiveSensor(2, 4);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
 
int pBUp = 0 ;
int pBDown = 0 ;
int pitchBend = 8192 ;
boolean pBToggle = false ;

int pBUpTHR = 1000 ;
int pBUpMAX = 4000 ;
int pBDownTHR = 1000 ;
int pBDownMAX = 4000 ;

void setup()                    
{
   Serial.begin(9600);
   midiCommand2(144, 60, 127) ;
}

void loop()                    
{
    long start = millis();
    long total1 =  pBUpSensor.capacitiveSensor(30);
    long total2 = pBDownSensor.capacitiveSensor(30);
    
    if (total1>pBUpTHR || total2>pBDownTHR) {
      if (!pBToggle) {
        pBToggle = true ;
      }
      
      pBUp = map(total1, pBUpTHR, pBUpMAX, 0, 8192) ;
      pBUp = rangeClip(pBUp, 0, 8192) ;
    
      pBDown = map(total2, pBDownTHR, pBDownMAX, 0, 8192) ;
      pBDown = rangeClip(pBDown, 0, 8192) ;
      
      
      pitchBend = 8192 + pBUp - pBDown ;
      pitchBend = rangeClip(pitchBend, 0, 16383) ;
      
      midiCommand2(224, pitchBend&127, pitchBend>>7) ;
    } else if (pBToggle) {
      pBToggle = false ;
      pitchBend = 8192 ;
      midiCommand2(224, pitchBend&127, pitchBend>>7) ;
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

void midiCommand1(int command, int data1) {
  Serial.write(command) ;
  Serial.write(data1) ;
}
void midiCommand2(int command, int data1, int data2) {
  Serial.write(command) ;
  Serial.write(data1) ;
  Serial.write(data2) ;
}
