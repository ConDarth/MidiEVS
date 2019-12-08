#include <Wire.h>

#define Y_COORDINATE_THR 30 
#define X_COORDINATE_THR 30 
#define VIBRATO_AVG_SAMPLE 40 

byte commandByte= 0x00 ;
int8_t xCoord = 0 ;
int8_t yCoord = 0 ;
int vibAVG[VIBRATO_AVG_SAMPLE] ;
int vibAVGNum = 0 ;
int vibCurrentVal = 0 ;
long vibratoVal = 0 ;
boolean vibratoToggle = false ;

long pitchBend = 8192 ;

void setup() {
  // put your setup code here, to run once:
  Wire.begin() ;
  Serial.begin(9600) ;

  joyStickBegin(5, 0x40) ;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  updateVibrato() ;
  
  getVibrato() ;

  /*
  vibratoVal = vibratoVal + 1500 ;
  vibratoVal = map(vibratoVal, 0, 3000, 0, 16383) ;
  vibratoVal = vibratoVal - 8192 ;
  */
  if (vibratoVal != 0) {
    if (!vibratoToggle) {
      vibratoToggle = true ;
    }
    //Serial.println(vibratoVal) ;
    vibratoVal = vibratoVal ;
    pitchBend = 8192 + vibratoVal ;
    midiCommand(224, pitchBend&127, pitchBend>>7) ;
  } else if (vibratoToggle) {
    vibratoToggle = false ;
    pitchBend = 8192 + vibratoVal ;
    midiCommand(224, pitchBend&127, pitchBend>>7) ;

    
  }
  
  
}

void getVibrato() {
  getCurrentVibrato() ;
  vibCurrentVal = xCoord + yCoord ;
  vibratoVal = vibratoVal + vibCurrentVal - vibAVG[vibAVGNum] ;
  vibAVG[vibAVGNum] = vibCurrentVal ;
  vibAVGNum ++ ;
  if (vibAVGNum >= VIBRATO_AVG_SAMPLE ) {
    vibAVGNum = 0 ;
  }
}
void getCurrentVibrato() {
  if (abs(xCoord) > X_COORDINATE_THR ) {
    if (xCoord > 0) {
      xCoord = xCoord - X_COORDINATE_THR ;
    } else if (xCoord < 0) {
      xCoord = xCoord + X_COORDINATE_THR ;
    } 
  } else {
    xCoord = 0 ;
  }
  if (abs(yCoord) >Y_COORDINATE_THR ) {
    if (yCoord > 0) {
      yCoord = yCoord - Y_COORDINATE_THR ;
    } else if (yCoord < 0) {
      yCoord = yCoord + Y_COORDINATE_THR ;
    } 
  } else {
    yCoord = 0 ;
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

  for (int i=0; i<VIBRATO_AVG_SAMPLE; i++) {
    vibAVG[i] = 0 ;
  }
    
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
void updateVibrato() {
  if (getData(0x40, 0x10, 1)) {
    xCoord = int8_t(Wire.read()) ;
    //Serial.print(xCoord) ;
    //Serial.print("\t\t") ;
  }
  if (getData(0x40, 0x11, 1)) {
    yCoord = int8_t(Wire.read()) ;
    //Serial.print(yCoord) ;
    //Serial.print("\t\t") ;
  }
}

void midiCommand(int command, int data1, int data2) {
  Serial.write(command);//send midi command byte
  Serial.write(data1);//send first data byte
  Serial.write(data2);//send second data byte
}
