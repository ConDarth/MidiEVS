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
#include <MIDI.h>

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
volatile int pRange = 400 ;
volatile bool breathControlFlag = false ;
bool noteChangeFlag = false ;

IntervalTimer peripheralTimer ;
bool peripheralFlag = false ;
uint8_t peripheralState = 0 ;
int peripheralTimerInterval = 10000 ;

int pbZero = 0 ;
int pbVal = pbZero ;
bool pbFlag = false ;
bool pbStateUp = false ;
bool pbStateDown = false ;
bool pbStateZero = false ;
int touchReadMin = 1200 ;
int touchReadRange = 4500 ;
int touchReadUp = 0 ;
int touchReadDown = 0 ;
float touchReadRaw = 0 ;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
uint8_t noteLast = 0 ;
uint8_t note = 60 ;
uint8_t velocity = 127 ;
uint8_t channel = 1 ;
uint8_t breathControl = 0 ;
int baseNote = 36 ;
int keyNote= -2  ;
int keyVal[7]             = {   -5,     2,     1,     4,    -3,    -1,    -2} ;  //Adjustments for the valves pressed
uint16_t keyValMask[7]    = {0x001, 0x040, 0x080, 0x100, 0x200, 0x400, 0x800} ;  //Masks to determine which valves are pressed
int octaveVal[6]          = {   60,    72,    48,    36,    24,    12} ;         //Adjustments for which octave used
uint16_t octaveValMask[6] = {0x030, 0x020, 0x010, 0x008, 0x004, 0x002} ;         //Masks for determining which octave to use


void setup() {
  Serial.begin(9600);
    
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    while (1);
  }

  pinMode(22, INPUT) ;
  pinMode(21, INPUT) ;
  pinMode(20, INPUT) ;
  pinMode(13, OUTPUT) ;

  attachInterrupt(digitalPinToInterrupt(21), touchInterrupt, FALLING) ;
  attachInterrupt(digitalPinToInterrupt(22), pressureInterrupt, CHANGE) ;
  attachInterrupt(digitalPinToInterrupt(20), pressureInterruptReset, FALLING) ;


  pTHRBase = analogRead(14) ;
  pTHRLow = pTHRBase + P_LOW_OFFSET ;
  pTHRHigh = pTHRBase + P_HIGH_OFFSET ;
  analogWriteResolution(10) ;
  analogWrite(A14, pTHRHigh) ;

  MIDI.begin() ;
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
      if (noteLast != note) {
        noteChangeFlag = true ;    
      }
    }
  } 

  if (pressureFlag) {
    //Notes turn on or off
    pressureFlag = false ;
         
    if (pressureState) {
      noteChangeFlag = false ;

      MIDI.sendNoteOn(note, velocity, channel) ;
      usbMIDI.sendNoteOn(note, velocity, channel) ;
      pressureTimer.begin(pressureTimerInterrupt, pressureTimeInterval) ;
      peripheralTimer.begin(peripheralTimerInterrupt, peripheralTimerInterval) ;
      
    } else {
      MIDI.sendNoteOn(note, 0, channel) ;
      usbMIDI.sendNoteOn(note, 0, channel) ;
      pressureTimer.end() ;
      peripheralTimer.end() ;
    }
  }

  if (pressureState) {
    // Program to run when playng notes
    
    if (breathControlFlag) {
      rawPressure = analogRead(14) ;
      pressure = constrain( (rawPressure-pTHRLow), 0, pRange) ;
      breathControl = ( (pressure)*127 )/pRange ;
      MIDI.sendControlChange(BREATH_CONTROL_CHANNEL, breathControl, channel) ;
      MIDI.sendControlChange(BREATH_CONTROL_CHANNEL, breathControl, channel) ;
      usbMIDI.sendControlChange(BREATH_CONTROL_CHANNEL, breathControl, channel) ;
      usbMIDI.sendControlChange(BREATH_CONTROL_CHANNEL, breathControl, channel) ;
      breathControlFlag = false ;
    }

    if (noteChangeFlag) {
      noteChangeFlag = false ;
      
      MIDI.sendNoteOn(note, velocity, channel) ;
      MIDI.sendNoteOn(noteLast, 0, channel) ;
      usbMIDI.sendNoteOn(note, velocity, channel) ;
      usbMIDI.sendNoteOn(noteLast, 0, channel) ;
    }

    if (peripheralFlag) {
      peripheralFlag = false ;
      
      switch(peripheralState) {
        case 0:
          touchReadUp = touchRead(16) ;
          if ( (touchReadUp >= touchReadMin) && (touchReadUp > touchReadDown) ) {
            pbStateUp = true ;
            pbStateZero = false ;
            
            touchReadRaw = float( constrain( (touchReadUp-touchReadMin), 0, touchReadRange) ) ;
            touchReadRaw = touchReadRaw * 8191 / touchReadRange ;
            pbVal = pbZero + touchReadRaw ;
            MIDI.sendPitchBend(pbVal, channel) ;
            usbMIDI.sendPitchBend(pbVal, channel) ;
          } else {
            pbStateUp = false ;
          }
        break;
        case 1:
          touchReadDown = touchRead(17) ;
          if ( (touchReadDown >= touchReadMin) && (touchReadDown > touchReadUp) ) {
            pbStateDown = true ;
            pbStateZero = false ;
            
            touchReadRaw = float( constrain( (touchReadDown-touchReadMin), 0, touchReadRange) ) ;
            touchReadRaw = touchReadRaw *8191 / touchReadRange ;
            pbVal = pbZero - touchReadRaw;
            MIDI.sendPitchBend(pbVal, channel) ;
            usbMIDI.sendPitchBend(pbVal, channel) ;
          } else {
            pbStateDown = false ;
          }
        break;
      }
      if (!pbStateUp && !pbStateDown) {
        if (!pbStateZero) {
          pbStateZero = true ;
          pbVal = pbZero ;
          MIDI.sendPitchBend(pbVal, channel) ;
          usbMIDI.sendPitchBend(pbVal, channel) ;
        }
      }
      
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
  pressureState = digitalRead(22) ;
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

void peripheralTimerInterrupt() {
  peripheralFlag = true ;
  peripheralState += 1 ;
  peripheralState = peripheralState%2 ;
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
