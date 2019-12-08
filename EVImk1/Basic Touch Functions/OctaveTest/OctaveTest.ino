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
#endif\

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
int pitch = 0 ;
int lastPitch = 0 ;

int pressure = 564 ;
int pressureMAX = 1016 ;
int pressureTHR = 580 ;
int breathController = 0 ;
boolean noteCondition = false ;

unsigned long debounceTime = 40 ;
unsigned long lastTime = 0 ;

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  } 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap1.begin(0x5B)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  if (!cap2.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  pitch = transpositionPitch ;
}

void loop() {
  // Get the currently touched pads
  updateSensors() ;

  hitKeys() ;
    
  if (millis() - lastTime > debounceTime) {

    getPitchVal() ;

    lastTime = millis() ;
  }
  
  noteOn() ;

  // reset our state
  lasttouched1 = currtouched1 ;  
  lasttouched2 = currtouched2 ;
  lastPitch = pitch ;
}

void updateSensors () {
  currtouched1 = cap1.touched() ;
  currtouched2 = cap2.touched() ;
}

void noteOn () {
  if (pitch != lastPitch) {
      midiCommand(128, lastPitch, 127) ;
      midiCommand(144, pitch, 127) ;
    }
}
void noteOff(){
  midiCommand(128, pitch, 127) ;
}

void getPitchVal() {
  
  pitch = transpositionPitch ;
  getOctaveVal() ;
  getFingeringVal() ;
  
}

void getOctaveVal() {
  
  if (pressedKey[5]) {
    pitch += octaveValue[6] ;
    
  } else if (pressedKey[4]) {
    pitch += octaveValue[5] ;
    
  } else if (pressedKey[3]) {
    pitch += octaveValue[4] ;
    
  } else if (pressedKey[2]) {
    pitch += octaveValue[3] ;
    
  } else if (pressedKey[1]) {
    pitch += octaveValue[2] ;
    
  } else if (pressedKey[0]) {
    pitch += octaveValue[1] ;
    
  } else {
    pitch += octaveValue[0] ;
  }
}

void getFingeringVal() {
  for (uint8_t i=0; i<7; i++) {
    if (pressedKey[i+12]) {
      pitch += keyValue[i] ;
    }
  }
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
}
