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
#include <CapacitiveSensor.h>

#define Y_COORDINATE_THR 30 //thresholds for x cooordinate on the joystick
#define X_COORDINATE_THR 30 //threshold for y coordinate on the joystick
#define VIBRATO_AVG_SAMPLE 5 //number of samples to compound for the vibrato joystick
#define MIDI_OUTPUT_SERIAL 0 //defines which midi output to use


#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endifs

//define the npr121 sensors 
Adafruit_MPR121 cap1 = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();

// define the individual cap sensor 
//the sensor busses arent sensitive enough so need individual
CapacitiveSensor   pBUpSensor = CapacitiveSensor(2, 4);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   pBDownSensor = CapacitiveSensor(2, 3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired


// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;
uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;

boolean pressedKey[24] ; //array for storing pressed keys
int keyValue[] =      {-5, -2, -1, -3,  2,  1, 4} ;  //how much to change pitch for each pitch key K1, K2, K3, K4, K5, K6, K7
int octaveValue[] =   {0, 12, 24, 36, 48, 60, 72} ;  //which ovtave to be in, adds to the base pitch
int transpositionPitch = 22 ; //starting pitch when no keys pressed

int pitch[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ; //array for storing which pitches should be played
boolean pitchState[128] ; //array of which pitch is currently on
int lastPitch[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ; //array of which pitch was last on
int pitchNum = 0 ; //which pitch in the array to set 
int pitchStateNum = 0 ; //im not sure possibly depracated
boolean pitchStateCounter = false ; //possibly depracted

int chordPitch[4][16] ; //array storing the pitches for each chord key 
boolean chordSetToggle[] = {0, 0, 0, 0} ; //toggle to not set chord more than once
boolean chordClearToggle[] = {0, 0, 0, 0} ; //toggle to not clear chord more than once
boolean chordOnToggle[] = {0, 0, 0, 0} ; //toggle to not play chord more than once
boolean chordAddToggle = true ;
int chordNum[] = {0, 0, 0, 0} ; //which chord to set/clear/activate
int chordMode = 0 ;
                        //tone shifts from original pitch in preset chord last column is size of chord
int chordPreset[][5] =  { {0, 4, 7, 0, 3}, //major triad
                          {0, 3, 7, 0, 3}, //minor triad
                          {0, 4, 7,10, 4}, //dominent chord
                          {0, 3, 6, 0, 3}, //diminished triad
                          {0, 7,14, 0, 3}, //open chord
                          {0, 4, 8, 0, 3}, //augmented triad
                          {4, 7,12, 0, 3}, //first inversion major
                          {3, 7,12, 0, 3}  //first inversion minor
                        } ;
int chordPresetNum = 0 ; 
int chordPresetNumLast = 0 ;  
int chordPresetBase = 0 ;    
boolean chordPresetToggle = false ;                 

long pBUpRaw ; //raw data from the cap sensor used for pitchbend, nearest to the mouthpeice
long pBDownRaw ; //raw data from the cap sensor 
int pBUp = 0 ; //adjusted pitchbend data
int pBDown = 0 ; //adjusted pitchbend data
int pitchBend = 8192 ; //actual pitchbend data used to send; base value 8192, max 16383 min 0
long pitchBendChange = 0 ; //difference from base value
int pitchBendMode = 0 ; //case to go to in pitchbend
boolean pBToggle = false ; //to not set the pBUp and pBDown more than once when off
int pBUpTHR = 1000 ; //threshold for pitch bend
int pBUpMAX = 4000 ; //max pitchbend
int pBDownTHR = 1000 ; //threshold pitchbend
int pBDownMAX = 4000 ; //max pitchbend

boolean pitchBendToggle = false ; //toggle to set pitchbend only when necessary

byte commandByte= 0x00 ; //byte for thr register to access in the joystick
int joystickSelectPin = 6 ; //pin joystick select is hooked into 
boolean joystickSelect = false ;
boolean joystickSelectToggle = false ;
int joystickCase = 1 ;

int8_t xCoord = 0 ; //joystick coordinate data
int8_t yCoord = 0 ; //joystick coordinate data
int vibAVG[VIBRATO_AVG_SAMPLE] ; //array to hold the data samples for vibrato 
int vibAVGNum = 0 ; //number to set the vibrato value into the array
int vibCurrentVal = 0 ; //current adjusted vibrato value
long vibratoVal = 0 ; //cumulative vibrato val actually used
boolean vibratoToggle = false ; //to set vibrato when necessary

//depracated for now
int pressureSensorPin = A0 ;
int pressureRaw = 0 ;
int pressureOnTHR = 70 ;
int pressureOffTHR = 50 ;
int pressureMAX = 400 ;
int pressureVal = 0 ;


unsigned long pitchDebounceTime = 40 ; //time between pitch sampling
unsigned long pitchLastTime = 0 ; //keeps track of current time
unsigned long midiEffectDebounce = 5 ;
unsigned long pressureLastTime = 0 ;

boolean noteStateToggle = false ;
int eviState = 0 ;

void setup() {
  Serial.begin(9600); 
  Serial1.begin(31250) ; //second serial port for midi and serial communication

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10) ;
  } 
  while (!Serial1) {
    delay(10) ;
  }
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap1.begin(0x5B)) {
    while (1);
  }
  if (!cap2.begin(0x5A)) {
    while (1);
  }

  joystickBegin(5, 0x40) ; //function to i2c communication with joystick
  

  pitch[0] = transpositionPitch ; //sets initial pitch so its not an empty value
  
}

void loop() {
  //update values to all the sensors 
  updateSensors() ;
  getEVIState() ;

  switch(eviState) {
    case 0:
    //if pressure isnt above thr do nothing yet
    break;
    case 1:
    //set aftertouch when thr is reached

    //update the midi values
    getPitchVal() ;
    getMPhonics() ;
    getVibrato() ;
    getJoystickMode() ;
    getPB() ; 
    getPressure() ;
  
    //update all midi values and send them out
    updateNote() ; 
    
    break;  
  }
  
  
  // reset our state
  lasttouched1 = currtouched1 ;  
  lasttouched2 = currtouched2 ;
  for (int i=0; i<pitchNum+1; i++) {
      lastPitch[i] = pitch[i] ;
  }

}

void updateSensors () {
  //update npr121 sensors
  currtouched1 = cap1.touched() ;
  currtouched2 = cap2.touched() ;

  //update the hit keys 
  hitKeys() ;
  
  //update the individual cap sensors
  long start = millis();
  pBUpRaw =  pBUpSensor.capacitiveSensor(30);
  pBDownRaw = pBDownSensor.capacitiveSensor(30);

  //update the joystick values
  updateVibrato() ;
  
  //updates the raw pressure sensor data
  pressureRaw = analogRead(pressureSensorPin) ;

  if (digitalRead(joystickSelectPin) == HIGH) {
    joystickSelect = false ;

  } else {
    joystickSelect = true ;  
  }

}
void getEVIState() {
  if (!noteStateToggle && (pressureRaw > pressureOnTHR)) {
    eviState = 1 ;
    midiCommand(144, 60, 127) ;
    midiCommand(160, 60, pressureVal) ;
    noteStateToggle = true ;
  } else if (noteStateToggle && !(pressureRaw >= pressureOffTHR)) {
    eviState = 0 ;
    noteStateToggle = false ;
    midiCommand(128, 60, 127) ;
    pressureVal = 0 ;
  }
}
void updateNote() {
  //get which notes to turn on, off, and what pb value
  noteOn();
  noteOff();
  updatePb() ;
}
void updatePb() {
  
  if ((pBUp != 0) || (pBDown != 0) || (vibratoVal != 0))  {  //only update if needed
    if (!pitchBendToggle) {
      pitchBendToggle = true ;
    }
    pitchBendChange = pBUp - pBDown + vibratoVal ;
    switch(pitchBendMode) {
      case 0: 
      
      break;
      case 1: 
      pitchBendChange = pitchBendChange/2 ;
      break;
      default:
      
      break;
    }
    pitchBend = 8192  + pitchBendChange ;
    pitchBend = rangeClip(pitchBend, 0, 16383) ;
    midiCommand(224, pitchBend&127, pitchBend>>7) ;
  } else if (pitchBendToggle) {  //set pb to 8192 once
    pitchBendToggle = false ;
    pitchBend = 8192 ;
    midiCommand(224, pitchBend&127, pitchBend>>7) ;
  }
}
void noteOn () {
  //check all pitches that should be on against all pitches that are on to turn on necessary pitches
  for (int i=0; i<=pitchNum; i++) {
    if (!pitchState[pitch[i]]) {
      pitchState[pitch[i]] = true ;
      midiCommand(144, pitch[i], 127) ;
    } else {
      
    }
  }
}
void noteOff(){
  //check all currently on pitches to those that should be on to turn off unnecessary ones
  for (int i=0; i<128; i++) {
    if (pitchState[i]) {
      for (int j=0; j<=pitchNum; j++) {
        if (i == pitch[j]) {
          pitchStateCounter = true ;
        }
      }
      if (!pitchStateCounter) {
        pitchState[i] = false ;
        midiCommand(144, i, 0) ;
      }
      pitchStateCounter = false ;
    }
  }
}

void getPitchVal() {
  //assigns which note to play based on keys pressed
  if (millis() - pitchLastTime > pitchDebounceTime) {
    //make sure that the pitch is only set every so often 
    pitch[pitchNum] = transpositionPitch ;
    getOctaveVal() ;
    getFingeringVal() ;

    pitchLastTime = millis() ;
  }  
}

void getOctaveVal() {
  //finds which octave to play in based on rollers
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
  //adjusts the ovtave based on keys
  for (uint8_t i=0; i<7; i++) {
    if (pressedKey[i+12]) {
      pitch[pitchNum] += keyValue[i] ;
    }
  }
}
void getMPhonics() {
  //gives the multiphonics that should be played
  //also assigns chords to buttons
  //second mode to make chord off of current pitch
  switch(chordMode) {
    case 0:
    if (pressedKey[4]) {
      //need to fix adds cuurent pitch to the chord when set, only want the stored pitches
      addPitch() ;
      setChord() ;
    } else if (pressedKey[5]) {
      clearMPhonic() ;
      clearChord() ;
    } else if (!pressedKey[4] && !pressedKey[5]) {
      applyChord() ;
    }
  break;
  case 1: 
    presetChordSet() ;
    if (pressedKey[5]) {
      clearMPhonic() ;
    } 
  break;
  }
}

void presetChordSet() {
  if (pressedKey[4]) {
    if (!chordPresetToggle) {
      chordPresetBase = pitch[pitchNum] ;
      pitchNum = 0 ;
      for (int i=0; i<chordPreset[chordPresetNum][4]; i++) {
        pitch[pitchNum] = chordPresetBase + chordPreset[chordPresetNum][i] ;
        pitchNum ++ ;
      }
      chordPresetToggle = true ;
    } else if (pitch[pitchNum] != lastPitch[pitchNum]) {
      chordPresetToggle = false ;
    } else if (chordPresetNum != chordPresetNumLast) {
      chordPresetToggle = false ;

    }
    chordPresetNum = chordPresetNumLast ;
    getPresetChordQuality() ;
  } else if (!pressedKey[4] && chordPresetToggle) {
    chordPresetToggle = false ; 
  }
}
void getPresetChordQuality() {
  chordPresetNum = 0 ;
  for (int i=0; i<3; i++) {
    if (pressedKey[i]) {
      chordPresetNum += pow(2, i) ;
    }
  }
}
void setChord() {
  //assigns the current mPhonics to chords
  for (int i=0; i<4; i++) {
    if (pressedKey[i] && !chordSetToggle[i]) {
      
      chordSetToggle[i] = true ;
      chordNum[i] = pitchNum  ;
      for (int j=0; j<chordNum[i]; j++) {
        chordPitch[i][j] = pitch[j] ;
      }
    } else if (!pressedKey[i] && chordSetToggle[i]) {
      chordSetToggle[i] = false ;
    }
  }
}
void applyChord() {
  //takes stored chords in buttons and implements them 
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
  //takes the stored chords and clears them to 0
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
  //adds a pitch to the multiphonics
  chordAddToggle = true ;
  for (int i=0; i<4; i++) {
    if (pressedKey[i]) {
      chordAddToggle = false ;
    }
  }
  if (chordAddToggle) {
    if (pitchNum==0) {
      pitchNum ++ ;
      pitch[pitchNum] = pitch[pitchNum - 1] ;
    } else if (pitch[pitchNum] != pitch[(pitchNum-1)]) {
      pitchNum ++ ;
      pitch[pitchNum] = pitch[pitchNum - 1] ;
    }
  }
}
void clearMPhonic() {
  //clears the current multiphonics
  pitch[0] = pitch[pitchNum] ;
  pitchNum = 0 ;
}
void hitKeys() {
  //gets the keys that are currently hit 
  //assigns them to an array
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

void getPB() {
  
  if (pBUpRaw>pBUpTHR || pBDownRaw>pBDownTHR) {
    if (!pBToggle) {
      pBToggle = true ;
    }
    
    pBUp = map(pBUpRaw, pBUpTHR, pBUpMAX, 0, 8192) ;
    pBUp = rangeClip(pBUp, 0, 8192) ;
    
    pBDown = map(pBDownRaw, pBDownTHR, pBDownMAX, 0, 8192) ;
    pBDown = rangeClip(pBDown, 0, 8192) ;
      
    //pitchBend = 8192 + pBUp - pBDown ;
    //pitchBend = rangeClip(pitchBend, 0, 16383) ;
      
    //midiCommand(224, pitchBend&127, pitchBend>>7) ;
  } else if (pBToggle) {
    pBToggle = false ;
    //pitchBend = 8192 ;
    //midiCommand(224, pitchBend&127, pitchBend>>7) ;
    pBUp = 0 ;
    pBDown = 0 ;
  }
}
void getJoystickMode() {
  
  switch(joystickCase) {
    case 0:
      if (joystickSelect) {
        if (!joystickSelectToggle) {
          pitchBendMode ++ ;
        if (pitchBendMode >= 2) {
          pitchBendMode = 0 ;
        }
        joystickSelectToggle = true ;
        }
      } else if (!joystickSelect) {
        if (joystickSelectToggle) {
          joystickSelectToggle  = false ;
        }
      }
    break;
    case 1: 
      if (joystickSelect) {
        if (!joystickSelectToggle) {
          chordMode ++ ;
        if (chordMode >= 2) {
          chordMode = 0 ;
        }
        joystickSelectToggle = true ;
        }
      } else if (!joystickSelect) {
        if (joystickSelectToggle) {
          joystickSelectToggle  = false ;
        }
      }
    break;
  }
  
}
void getPressure() {
      pressureRaw = rangeClip(pressureRaw, pressureOnTHR, pressureMAX) ;
      pressureVal = map(pressureRaw, pressureOnTHR, pressureMAX, 0, 127) ;
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
void joystickBegin(int resetPin, byte address) {
  
  pinMode(resetPin, INPUT_PULLUP) ;
  pinMode(joystickSelectPin, INPUT) ;
  
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

int rangeClip(int number, int minimum, int maximum) {
  if (number >= maximum) {
    number = maximum ;
  } else if (number <= minimum) {
    number = minimum ;
  }
  return number ;
}
void midiCommand(int command, int data1, int data2) {
  switch(MIDI_OUTPUT_SERIAL) {
    case 0: 
      Serial.write(command);//send midi command byte
      Serial.write(data1);//send first data byte
      Serial.write(data2);//send second data byte
    break;
    case 1:
      Serial1.write(command);//send midi command byte
      Serial1.write(data1);//send first data byte
      Serial1.write(data2);//send second data byte
    break;
  } 
}
