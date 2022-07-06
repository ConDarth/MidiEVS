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

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t currTouched = 0 ;
uint16_t lastTouched = 0 ;

unsigned long t0 = 0 ;
unsigned long t = 0 ;

IntervalTimer touchTimer ; 
volatile bool touchFlag = false ;         //Flag for the interrupt
unsigned long touchTimeInterval = 10000 ; //Interval before sampling in microseconds

#define P_HIGH_OFFSET 40
#define P_LOW_OFFSET 10
int pTHRBase = 0 ;
volatile int pTHRHigh = 0 ;
volatile int pTHRLow = 0 ;
volatile bool pressureFlag = false ;
volatile bool pressureState = false ;
volatile bool pressureResetFlag = false ;

#define BREATH_CONTROL_CHANNEL 2
IntervalTimer pressureTimer ;
unsigned long pressureTimeInterval = 5000 ; 
int rawPressure = 0 ;
int pressure = 0 ;
volatile int pRange = 1000 ;
volatile bool breathControlFlag = false ;
bool noteChangeFlag = false ;

uint8_t noteLast = 0 ;
uint8_t note = 60 ;
uint8_t velocity = 127 ;
uint8_t channel = 1 ;
uint8_t breathControl = 0 ;
int baseNote = 24 ;
int keyNote= -2  ;
int keyVal[7]             = {   -2,    -1,    -3,     2,     1,     4,    -5} ;  //Adjustments for the valves pressed
uint16_t keyValMask[7]    = {0x001, 0x002, 0x004, 0x008, 0x010, 0x020, 0x040} ;  //Masks to determine which valves are pressed
int octaveVal[6]          = {   60,    72,    48,    36,    24,    12} ;         //Adjustments for which octave used
uint16_t octaveValMask[6] = {0xC00, 0x800, 0x400, 0x200, 0x200, 0x100} ;         //Masks for determining which octave to use


void setup() {
  Serial.begin(9600);
    
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    while (1);
  }

  pinMode(16, INPUT) ;
  pinMode(17, INPUT) ;
  pinMode(20, INPUT) ;
  pinMode(13, OUTPUT) ;

  attachInterrupt(digitalPinToInterrupt(17), touchInterrupt, FALLING) ;
  attachInterrupt(digitalPinToInterrupt(16), pressureInterrupt, CHANGE) ;
  attachInterrupt(digitalPinToInterrupt(20), pressureInterruptReset, FALLING) ;


  pTHRBase = analogRead(14) ;
  pTHRLow = pTHRBase + P_LOW_OFFSET ;
  pTHRHigh = pTHRBase + P_HIGH_OFFSET ;
  analogWriteResolution(10) ;
  analogWrite(A14, pTHRHigh) ;

  usbMIDI.send_now() ;
}

void loop() {

  if (pressureResetFlag) {
      pTHRBase = analogRead(14) ;
      pTHRLow = pTHRBase + P_LOW_OFFSET ;
      pTHRHigh = pTHRBase + P_HIGH_OFFSET ;
      analogWriteResolution(10) ;
      analogWrite(A14, pTHRHigh) ;

      pressureResetFlag = false ;
  }
  
  if (touchFlag) {
    //Notes change
    touchFlag = false ;

    lastTouched = currTouched ;
    currTouched = cap.touched();
    if (lastTouched != currTouched) {
      updateNote() ;
      noteChangeFlag = true ;
    }
  } 

  if (pressureFlag) {
    //Notes turn on or off
    pressureFlag = false ;
         
    if (pressureState) {
      noteChangeFlag = false ;
      
      usbMIDI.sendNoteOn(note, velocity, channel) ;
      pressureTimer.begin(pressureTimerInterrupt, pressureTimeInterval) ;
      
    } else {
      usbMIDI.sendNoteOn(note, 0, channel) ;
      pressureTimer.end() ;
    }
  }

  if (pressureState) {
    // Program to run when playng notes
    
    if (breathControlFlag) {
      rawPressure = analogRead(14) ;
      pressure = constrain( (rawPressure-pTHRLow), 0, pRange) ;
      breathControl = ( (pressure)*127 )/pRange ;
      usbMIDI.sendControlChange(BREATH_CONTROL_CHANNEL, breathControl, channel) ;
      breathControlFlag = false ;
    }

    if (noteChangeFlag) {
      noteChangeFlag = false ;

      usbMIDI.sendNoteOn(note, velocity, channel) ;
      usbMIDI.sendNoteOn(noteLast, 0, channel) ;
    }
    
  } else {

  }

  // MIDI Controllers should discard incoming MIDI messages.
  while (usbMIDI.read()) {
    // read & ignore incoming messages
  }
}

void touchInterrupt() {
  touchTimer.begin(touchTimerInterrupt, touchTimeInterval) ;
}

void touchTimerInterrupt() {
  touchTimer.end() ;
  touchFlag = true ;
}

void pressureInterrupt() {
  pressureFlag = true ;
  pressureState = digitalRead(16) ;
  if (pressureState) {
    analogWrite(A14, pTHRLow) ;
  } else {
    analogWrite(A14, pTHRHigh) ;
  }
}

void pressureInterruptReset() {
  pressureResetFlag = true ;
}

void pressureTimerInterrupt() {
  breathControlFlag = true ;
}

void updateNote() {
  noteLast = note ;
  note = baseNote + keyNote ;

  for (byte i=0; i<6; i++) {
    if ( (currTouched & octaveValMask[i]) == octaveValMask[i] ) {
      note += octaveVal[i] ;
      break;
    }
  }
  
  for (byte i=0; i<7; i++) {
    if ( (currTouched & keyValMask[i]) == keyValMask[i] ) {
      note += keyVal[i] ;
    }
  }
}
