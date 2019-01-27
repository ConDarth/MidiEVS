/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap1 = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();


// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;
uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;

boolean pressedKey[24] ;
int keyValue[] =      {-5, -2, -1, -3,  2,  1, 4} ;
int octaveValue[] =   {0, 12, 24, 36, 48, 60, 72} ;
int transpositionPitch = 24 ;


int pitch[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ;
boolean pitchState[128] ;
int lastPitch[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ;
int pitchNum = 0 ;
int pitchStateNum = 0 ;
boolean pitchStateCounter = false ;

int chordPitch[4][16] ;
boolean chordSetToggle[] = {0, 0, 0, 0} ;
boolean chordClearToggle[] = {0, 0, 0, 0} ;
boolean chordOnToggle[] = {0, 0, 0, 0} ;
int chordNum[] = {0, 0, 0, 0} ; 

int pressure = 564 ;
int pressureMAX = 1016 ;
int pressureTHR = 580 ;
int breathController = 0 ;
boolean noteCondition = false ;

unsigned long debounceTime = 75 ;
unsigned long lastTime = 0 ;

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  } 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap1.begin(0x5B)) {
    while (1);
  }
  if (!cap2.begin(0x5A)) {
    while (1);
  }

  pitch[0] = transpositionPitch ;
  
}

void loop() {
  // Get the currently touched pads
  updateSensors() ;

  hitKeys() ;
    
  if (millis() - lastTime > debounceTime) {

    getPitchVal() ;

    lastTime = millis() ;
  }

 getMPhonics() ;

  updateNote() ;
  // reset our state
  lasttouched1 = currtouched1 ;  
  lasttouched2 = currtouched2 ;
  for (int i=0; i<pitchNum+1; i++) {
      lastPitch[i] = pitch[i] ;
  }

}

void updateSensors () {
  currtouched1 = cap1.touched() ;
  currtouched2 = cap2.touched() ;
}
void updateNote() {
  noteOn();
  noteOff();
}
void noteOn () {
  for (int i=0; i<=pitchNum; i++) {
    if (!pitchState[pitch[i]]) {
      pitchState[pitch[i]] = true ;
      midiCommand(144, pitch[i], 127) ;
    } else {
      
    }
  }
}
void noteOff(){
  for (int i=0; i<128; i++) {
    if (pitchState[i]) {
      for (int j=0; j<=pitchNum; j++) {
        if (i == pitch[j]) {
          pitchStateCounter = true ;
        }
      }
      if (!pitchStateCounter) {
        pitchState[i] = false ;
        midiCommand(128, i, 127) ;
      }
      pitchStateCounter = false ;
    }
  }
}

void getPitchVal() {
  
  pitch[pitchNum] = transpositionPitch ;
  getOctaveVal() ;
  getFingeringVal() ;
  
}

void getOctaveVal() {
  
  if (pressedKey[11]) {
   pitch[pitchNum] += octaveValue[6] ;
    
  } else if (pressedKey[10]) {
    pitch[pitchNum] += octaveValue[5] ;
    
  } else if (pressedKey[9]) {
    pitch[pitchNum] += octaveValue[4] ;
    
  } else if (pressedKey[8]) {
    pitch[pitchNum] += octaveValue[3] ;
    
  } else if (pressedKey[7]) {
    pitch[pitchNum] += octaveValue[2] ;
    
  } else if (pressedKey[6]) {
    pitch[pitchNum] += octaveValue[1] ;
    
  } else {
    pitch[pitchNum] += octaveValue[0] ;
  }
}

void getFingeringVal() {
  for (uint8_t i=0; i<7; i++) {
    if (pressedKey[i+12]) {
      pitch[pitchNum] += keyValue[i] ;
    }
  }
}
void getMPhonics() {
  applyChord() ;
  
  if (pressedKey[4]) {
    addPitch() ;
    setChord() ;
  }
  if (pressedKey[5]) {
    clearMPhonic() ;
    clearChord() ;
  }
}
void setChord() {
  for (int i=0; i<4; i++) {
    if (pressedKey[i] && !chordSetToggle[i]) {
      
      chordSetToggle[i] = true ;
      chordNum[i] = pitchNum - 1 ;
      for (int j=0; j<chordNum[i]; j++) {
        chordPitch[i][j] = pitch[j] ;
      }
    } else if (!pressedKey[i] && chordSetToggle[i]) {
      chordSetToggle[i] = false ;
    }
  }
}
void applyChord() {
  for (int i=0; i<4; i++) {
    if (chordNum[i] != 0) {
      if (pressedKey[i] && !chordOnToggle[i]) {
        chordOnToggle[i] = true ;
      
        pitch[chordNum[i]] = pitch[pitchNum] ;
        pitchNum = chordNum[i];
        for (int j=0; j<pitchNum; j++) {
          pitch[j] = chordPitch[i][j] ;
        }
      } else if (!pressedKey[i] && chordOnToggle[i]) {
        chordOnToggle[i] = false ;
      }
    } 
  }
}
void clearChord() {
  for (int i=0; i<4; i++) {
    if (pressedKey[i] && !chordClearToggle[i]) {
      for (int j=0; j<chordNum[i]; j++) {
        chordPitch[i][j] = 0 ;
      }
      chordNum[i] = 0 ;
      chordClearToggle[i] = true ;
    } else if (!pressedKey[i] && chordClearToggle[i]) {
      chordClearToggle[i] = false ;
    }
  }
}
void addPitch() {
  if (pitchNum==0) {
    pitchNum ++ ;
    pitch[pitchNum] = pitch[pitchNum - 1] ;
  } else if (pitch[pitchNum] != pitch[(pitchNum-1)]) {
    pitchNum ++ ;
    pitch[pitchNum] = pitch[pitchNum - 1] ;

  }
}
void clearMPhonic() {
  pitch[0] = pitch[pitchNum] ;
  pitchNum = 0 ;
  
}
void hitKeys() {
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
      pressedKey[i] = true ;
      
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
      pressedKey[i] = false ;
      
    }
  }
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched2 & _BV(i)) && !(lasttouched2 & _BV(i)) ) {
      pressedKey[i+12] = true ;
      
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched2 & _BV(i)) && (lasttouched2 & _BV(i)) ) {
      pressedKey[i+12] = false ;
      
    }
  }
}

void midiCommand(int command, int data1, int data2) {
  Serial.write(command);//send midi command byte
  Serial.write(data1);//send first data byte
  Serial.write(data2);//send second data byte

  //comment out if using serial1 on mega only
  //return ; 
  
  Serial1.write(command);//send midi command byte
  Serial1.write(data1);//send first data byte
  Serial1.write(data2);//send second data byte
}
