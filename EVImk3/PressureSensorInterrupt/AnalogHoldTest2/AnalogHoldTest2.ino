//Version 2 to incorporate the schmitt trigger components
//Analog in gives our variable value 
//DAC out gives baseline for rising schmitt edge

//Schmitt edge uneccessary??
//Comparator has small one built in, so perhaps can just use one of those


#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

int readPin = A0 ;
int resetPin = 2 ;

bool resetFlag = false ;
int holdVal = 0 ;

void setup() {
  // put your setup code here, to run once:
  dac.begin(0x62);

  Serial.begin(9600);
  Serial.println("Starting!");

  holdVal = (analogRead(readPin) + 10)*4 ;
  Serial.print("Hold Val is ") ;
  Serial.println(holdVal) ;

  dac.setVoltage(holdVal, false) ;
  Serial.println("Volatge Set") ;

  attachInterrupt(digitalPinToInterrupt(resetPin), resetVoltage, RISING) ;
  pinMode(resetPin, INPUT) ;

}

void loop() {
  if (resetFlag == true) {
    holdVal = (analogRead(readPin) + 10)*4 ;
    Serial.print("Hold Val is ") ;
    Serial.println(holdVal) ;

    dac.setVoltage(holdVal, false) ;
    resetFlag = false ; 
  }
  delay(100) ;
}

void resetVoltage() {
  resetFlag = true ;
  Serial.println("Interrupt") ;
}
