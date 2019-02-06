#include <Wire.h>


byte commandByte= 0x00 ;
byte xCoord = 0 ;
byte yCoord = 0 ;

void setup() {
  // put your setup code here, to run once:
  Wire.begin() ;
  Serial.begin(9600) ;

  joyStickBegin(12, 0x40) ;
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if (getData(0x40, 0x10, 1)) {
    xCoord = Wire.read() ;
    Serial.print(int8_t(xCoord)) ;
   }
   Serial.print("\t\t") ;
  if (getData(0x40, 0x11, 1)) {
    yCoord = Wire.read() ;
    Serial.println(int8_t(yCoord)) ;
   }
  
}

void joyStickBegin(byte resetPin, byte address) {
  
  pinMode(resetPin, INPUT_PULLUP) ;
  digitalWrite(resetPin, LOW) ;
  delay(10) ;
  digitalWrite(resetPin, HIGH) ;
  delay(100) ;


  Wire.beginTransmission(address) ;
  Wire.write(0x0f) ;
  Wire.endTransmission() ;

  Wire.requestFrom(address, 1) ;
  while((commandByte != 0xf0) && (commandByte != 0xf1)) {
    if (1<= Wire.available()) {
      commandByte = Wire.read() ;

      Wire.beginTransmission(address) ;
      Wire.write(0x0f) ;
      Wire.endTransmission() ;
      Wire.requestFrom(address, 1) ;
      
      Serial.print("recieved data byte ") ;
      Serial.println(commandByte) ;
    }
  }
  writeData(0x40, 0x2b, 0x00) ;
  writeData(0x40, 0x2c, 0x06) ;
  writeData(0x40, 0x2d, 0x09) ;
  writeData(0x40, 0x0f, B11110000) ;

    
  Serial.println("joystick reset correctly") ;
}

boolean getData(byte address, byte reg, int byteNum) {
  Wire.beginTransmission(address) ;
  Wire.write(reg) ;
  Wire.endTransmission() ;
  Wire.requestFrom(address, byteNum) ;
  return (byteNum<=Wire.available()) ;
}
void writeData(byte address, byte reg, byte info) {
  Wire.beginTransmission(address) ;
  Wire.write(reg) ;
  Wire.write(info) ;
  Wire.endTransmission() ;
}
