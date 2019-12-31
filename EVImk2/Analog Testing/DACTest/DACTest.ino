//testing to figure out how to use the 12 bit DAC

#include <Wire.h>
#include <Adafruit_MCP4725.h>


float voltageRange = 3.3 ;
float voltage = 0.68 ;
uint16_t dacVal = 0 ;
int16_t analog1 = 0 ;
int16_t analog2 = 0 ;
float voltage1 = 0 ;
float voltage2 = 0 ;
float error1 = 0 ;
float error2 = 0 ;


Adafruit_MCP4725 dac1 ;
Adafruit_MCP4725 dac2 ;

void setup(void) {
  Serial.begin(9600);

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac1.begin(0x62);
  dac2.begin(0x63);
  
  dacVal = voltage * 4095 / voltageRange ;
  constrain(dacVal, 0, 4095) ;
  dac1.setVoltage(dacVal, false);
  dac2.setVoltage(dacVal, false);
}

void loop(void) {
  analog1 = analogRead(A0) ;
  voltage1 = (float) analog1 * 3.3 / 1023 ;
  error1 = voltage1 - voltage ;
  analog2 = analogRead(A1) ;
  voltage2 = (float) analog2 * 3.3 / 1023 ;
  error2 = voltage2 - voltage ;
  
  Serial.print(analog1) ;
  Serial.print("\t") ;
  Serial.print(voltage1) ;
  Serial.print("\t") ;
  Serial.print(error1) ;
  Serial.print("\t") ;
  Serial.print(analog2) ;
  Serial.print("\t") ;
  Serial.print(voltage2) ;
  Serial.print("\t") ;
  Serial.println(error2) ; 
  
  delay(10) ;
}

//DAC work within acceptable ranges
//both are within a 20th of a volt pretty much 
//acceptable to move on to using these for an interrupt
