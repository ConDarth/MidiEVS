// Working!! 
// Next to add in the op amp for the schmitt trigger

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

  holdVal = (analogRead(readPin) + 30)*4 ;
  Serial.print("Hold Val is ") ;
  Serial.println(holdVal) ;

  dac.setVoltage(holdVal, false) ;
  Serial.println("Volatge Set") ;

  attachInterrupt(digitalPinToInterrupt(resetPin), resetVoltage, RISING) ;
  pinMode(resetPin, INPUT) ;

}

void loop() {
  if (resetFlag == true) {
    holdVal = (analogRead(readPin) + 30)*4 ;
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
