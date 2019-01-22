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

#define pressureSensorPin A0

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

boolean pressedKey[] = {0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ;
int keyValue[] = { -5, -2, -1, -3, 2, 1, 4, 0, 0, 0, 0, 0} ;
int initialpitch = 60 ;
int pitch = 0 ;
int lastPitch = 0 ;

int pressure = 564 ;
int pressureMAX = 1016 ;
int pressureTHR = 570 ;
int breathController = 0 ;
boolean noteOn = false ;

unsigned long debounceTime = 40 ;
unsigned long lastTime = 0 ;

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  pitch = initialpitch ;
}

void loop() {
  // Get the currently touched pads
  
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      pressedKey[i] = true ;
      
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      pressedKey[i] = false ;
      
    }
  }

  if (pressure >= pressureTHR) {
    if (!noteOn) {
      noteOn = true ;
      midiCommand(144, pitch, 127) ;
    }

    breathController = map(pressure, pressureTHR, pressureMAX, 0, 127) ;
    midiCommand(160, pitch, breathController) ;
    
    if (millis() - lastTime > debounceTime) {

      pitch = initialpitch ;

      for (uint8_t i=0; i<7; i++) {
        if (pressedKey[i]) {
          pitch += keyValue[i] ;
        }
      }    

      lastTime = millis() ;
    }
  
    if (pitch != lastPitch) {
      midiCommand(128, lastPitch, 100) ;
      midiCommand(144, pitch, 100) ;
    }

  } else if (noteOn) {
    noteOn = false ;
    midiCommand(128, pitch, 127) ;
  }
  
  // reset our state
 lasttouched = currtouched; 
 lastPitch = pitch ;
}

void updateSensors () {
  currtouched = cap.touched();
  pressure = analogRead(pressureSensorPin) ;
}

void midiCommand(int command, int data1, int data2) {
  Serial.write(command);//send midi command byte
  Serial.write(data1);//send first data byte
  Serial.write(data2);//send second data byte
}
