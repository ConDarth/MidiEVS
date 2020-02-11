#include <Wire.h>
#include <Adafruit_MCP4725.h>

//This is to use to test the effectiveness of an interrupt driven pressure readout
Adafruit_MCP4725 dac1 ;
Adafruit_MCP4725 dac2 ;


uint16_t lowerTHR = 500 ; //both 12 bit numbers to set the thr for pressure
uint16_t upperTHR = 2000 ;

boolean interruptState = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(2, OUTPUT) ;
  digitalWrite(2, HIGH) ; //set to high to allow interrupt, low to disable
  
  dac1.begin(0x62);
  dac2.begin(0x63);

  lowerTHR = constrain(lowerTHR, 0, 4095) ;
  upperTHR = constrain(upperTHR, 0, 4095) ;
  
  dac1.setVoltage(lowerTHR, false);
  dac2.setVoltage(upperTHR, false);

  pinMode(3, INPUT) ;
  attachInterrupt(3, noteUpdate, CHANGE) ;

  interruptState = digitalRead(3) ;

  pinMode(13, OUTPUT) ;
  digitalWrite(13, interruptState) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000) ;
}

void noteUpdate() {
  if (interruptState == 0) {
    interruptState = 1 ;
  } else if (interruptState == 1) {
    interruptState = 0 ;
  }

  digitalWrite(13, interruptState) ;
}
