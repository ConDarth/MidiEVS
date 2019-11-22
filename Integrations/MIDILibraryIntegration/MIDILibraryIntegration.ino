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
#include <MIDI.h>
#include "Adafruit_MPR121.h"
//#include <CapacitiveSensor.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

/**********************************************************************************************************************************************/

#define Y_COORDINATE_THR 30 //thresholds for x cooordinate on the joystick
#define X_COORDINATE_THR 30 //threshold for y coordinate on the joystick
#define VIBRATO_AVG_SAMPLE 5 //number of samples to compound for the vibrato joystick
#define MIDI_OUTPUT_SERIAL 0 //defines which midi output to use (harlessMIDI-0 ; MIDIjack-1 ; SerialPort1-2)
#define SELECTOR_DIAL_PIN A1
#define BITE_SENSOR_PIN A2 

/**********************************************************************************************************************************************/


#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//define the npr121 sensors 
Adafruit_MPR121 cap1 = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
MIDI_CREATE_DEFAULT_INSTANCE();

// define the individual cap sensor 
//the sensor busses arent sensitive enough so need individual
//CapacitiveSensor   pBUpSensor = CapacitiveSensor(2, 4);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor   pBDownSensor = CapacitiveSensor(2, 3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;
uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;

/**********************************************************************************************************************************************/

boolean pressedKey[24] ; //array for storing pressed keys
int keyValue[] =      {-5, -2, -1, -3,  2,  1, 4} ;  //how much to change pitch for each pitch key K1, K2, K3, K4, K5, K6, K7
int octaveValue[] =   {0, 12, 24, 36, 48, 60, 72} ;  //which ovtave to be in, adds to the base pitch
int transpositionPitch = 34 ; //starting pitch when no keys pressed

/**********************************************************************************************************************************************/

int pitch[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ; //array for storing which pitches should be played
int pitchVelocity[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ; //velocity each note should be played at 
boolean pitchState[128] ; //array of which pitch is currently on
int pitchStateVelocity[128] ; //the velocity each pitch in the array should be at 
int lastPitch[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ; //array of which pitch was last on
int pitchNum = 0 ; //which pitch in the array to set 
int pitchStateNum = 0 ; //im not sure possibly depracated
boolean pitchStateCounter = false ; //possibly depracted

/**********************************************************************************************************************************************/

int currentVelocity = 100 ;
int sustainVelocity = 90 ;
int chordVelocity = 90;
boolean velocityToggle = false ;

/**********************************************************************************************************************************************/

int chordPitch[4][16] ; //array storing the pitches for each chord key 
boolean chordSetToggle[] = {0, 0, 0, 0} ; //toggle to not set chord more than once
boolean chordClearToggle[] = {0, 0, 0, 0} ; //toggle to not clear chord more than once
boolean chordOnToggle[] = {0, 0, 0, 0} ; //toggle to not play chord more than once
boolean chordAddToggle = true ;
int chordNum[] = {0, 0, 0, 0} ; //which chord to set/clear/activate
int chordMode = 1 ;
int chordPresetSize = 4 ;
                        //tone shifts from original pitch in preset chord last column is size of chord
int chordPreset[8][5] = { {0, 4, 7, 0}, //major triad
                          {0, 3, 7, 0}, //minor triad
                          {0, 4, 7,10}, //dominent chord
                          {0, 3, 6, 0}, //diminished triad
                          {0, 7,14, 0}, //open chord
                          {0, 4, 8, 0}, //augmented triad
                          {4, 7,12, 0}, //first inversion major
                          {3, 7,12, 0}  //first inversion minor
                        } ;
int chordPresetNum = 0 ; 
int chordPresetNumLast = 0 ;  
int chordPresetBase = 0 ;    
boolean chordPresetToggle = false ;                 

/**********************************************************************************************************************************************/

boolean recievingData = false ;
int newDataNum = 0 ;
int recievedDataSize = 4 ;
byte newData[4] ;
int data1 = 0 ;
int data2 = 0 ;
byte lastByte = 0 ;

/**********************************************************************************************************************************************/

long pBUpRaw ; //raw data from the cap sensor used for pitchbend, nearest to the mouthpeice
long pBDownRaw ; //raw data from the cap sensor 
int pBUp = 0 ; //adjusted pitchbend data
int pBDown = 0 ; //adjusted pitchbend data
int pitchBend = 8192 ; //actual pitchbend data used to send; base value 8192, max 16383 min 0
long pitchBendLast = 0 ; //last value sent
int pitchBendMode = 0 ; //case to go to in pitchbend
boolean pBToggle = false ; //to not set the pBUp and pBDown more than once when off
int pBUpTHR = 1000 ; //threshold for pitch bend
int pBUpMAX = 4000 ; //max pitchbend
int pBDownTHR = 1000 ; //threshold pitchbend
int pBDownMAX = 4000 ; //max pitchbend

boolean pitchBendToggle = false ; //toggle to set pitchbend only when necessary

/**********************************************************************************************************************************************/

byte commandByte= 0x00 ; //byte for thr register to access in the joystick
int joystickSelectPin = 6 ; //pin joystick select is hooked into 
boolean joystickSelect = false ;
boolean joystickSelectToggle = false ;
int joystickCase = 1 ;

/**********************************************************************************************************************************************/

int8_t xCoord = 0 ; //joystick coordinate data
int8_t yCoord = 0 ; //joystick coordinate data
int xCoordZero = 0 ;
int vibratoCurve = 0.6 ; //used to give data a curve less that 1 but more than 0 
int vibratoDepth = 2000 ;
int vibratoZero = 0 ;
int vibratoTHR = 0 ;
int vibratoMAX = 127 ;
int vibratoRaw = 0 ;
int vibratoVal = 0;   
boolean vibratoToggle = false ; //to set vibrato when necessary

/**********************************************************************************************************************************************/

int pressureSensorPin = A0 ;
int pressureOutputState = 0 ;
int pressureRaw = 0 ;
int pressureOnTHR = 170 ;
int pressureOffTHR = 150 ;
int pressureMAX = 520 ;
int pressureVal = 0 ;
int pressureLast = 0 ;

/**********************************************************************************************************************************************/

int biteSensorRaw = 0 ;
int portamentoVal = 0 ;
int biteSensorOnTHR = 350 ;
int biteSensorOffTHR = 300 ;
int biteSensorMAX = 600 ;
boolean biteSensorToggle = false ;
boolean portamentoToggle = false ;

/**********************************************************************************************************************************************/

int equalizer = 0 ; 
int lastEqualizer = 1 ;
boolean equalizerToggle = true ;
int equalizerTHR[2][9] = { {0,    1, 1950, 4000, 6050,  8100, 10150, 12200, 14250}, 
                           {2, 2150, 4200, 6250, 8300, 10350, 12400, 14450, 16500} } ;
int modeSelectRaw = 0 ;
int modeSelectTotal = 0 ;
int modeSelectIndex = 0 ;
int modeSelectSmooth = 0 ;
int modeSelector = 0 ;
int modeSelectTHR[2][4] = { { 740, 510, 300,   0}, 
                            {1010, 760, 530, 320} } ;
int lastModeSelector = 1 ;
boolean selectButton[4] = {1, 0, 1, 0} ;
boolean selectButtonToggle = false ;
boolean indicatorDisplayToggle = true ;

/**********************************************************************************************************************************************/

unsigned long midiDebounceTime = 5 ;
unsigned long midiLastTime = 0 ;
unsigned long pitchDebounceTime = 40 ; //time between pitch sampling
unsigned long pitchLastTime = 0 ; //keeps track of current time
unsigned long pressureDebounce = 5 ;
unsigned long pressureLastTime = 0 ;
unsigned long analogDebounceTime = 2 ;
unsigned long analogLastTime = 0 ;
unsigned long iDisplayDebounceTime = 25 ;
unsigned long iDisplayLastTime = 0 ;

unsigned long lastTime = 0 ;

boolean noteStateToggle = false ;
int eviState = 0 ;

//tester variables 
unsigned long testTimer = 0 ;

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);  //sets up serial 0 for MIDI to be used instead of serial 0
  //Serial.begin(38400) ; //first seial port for hairless midi
  Serial1.begin(31250) ; //second serial port for midi and serial communication
  Serial2.begin(115200) ; //serial for recieving cap sense data

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

  matrix.begin(0x70);  // pass in the address
  matrix.setRotation(3) ;
  matrix.setBrightness(10) ;  

  pitch[0] = transpositionPitch ; //sets initial pitch so its not an empty value
  
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void loop() {
  //update values to all the sensors 
  updateSensors() ;
  getEVIState() ;
  getJoystickMode() ;
  
  testTimer = micros() ;
  

  
  switch(eviState) {
    case 0:
    //if pressure isnt above THR do nothing yet
    break;
    case 1:
    //set aftertouch when THR is reached
    getPitchVal() ;    //update the midi values
    getPB() ; 
    getPressure() ;
  
    //update all midi values and send them out
    updateNote() ; 
    
    break;  
  }
  
  getMPhonics() ;
  
  
  // reset our state
  lasttouched1 = currtouched1 ;  
  lasttouched2 = currtouched2 ;
  for (int i=0; i<pitchNum+1; i++) {
      lastPitch[i] = pitch[i] ;
  }
  lastModeSelector = modeSelector ;
  lastEqualizer = equalizer ;

  //Serial.println(millis() - lastTime) ;
  lastTime = millis() ;

}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void updateSensors () {
  //update npr121 sensors
  currtouched1 = cap1.touched() ;
  currtouched2 = cap2.touched() ;

  //update the hit keys 
  hitKeys() ;

  //update the individual cap sensors
  //pBUpRaw =  pBUpSensor.capacitiveSensor(5);
  //pBDownRaw = pBDownSensor.capacitiveSensor(5);
  getData() ;
  
  //update the joystick values
  //updateVibrato() ;

  pressureRaw = analogRead(pressureSensorPin) ; // pressure must be updated more often because it turns the note on initially
  biteSensorRaw = analogRead(BITE_SENSOR_PIN) ;
  modeSelectRaw = analogRead(SELECTOR_DIAL_PIN) ;
  modeSelectIndex ++ ;
  modeSelectTotal += modeSelectRaw ;
  
  
  if (digitalRead(joystickSelectPin) == HIGH) {
    joystickSelect = false ;

  } else {
    joystickSelect = true ;  
  }
  
  if ((millis() - iDisplayLastTime) >= iDisplayDebounceTime) {
    updateIndicatorDisplay() ;
    iDisplayLastTime = millis() ;
  }
}

/**********************************************************************************************************************************************/

void getEVIState() {
  if (!noteStateToggle && (pressureRaw > pressureOnTHR)) {
    eviState = 1 ;
    noteStateToggle = true ;
  } else if (noteStateToggle && !(pressureRaw >= pressureOffTHR)) {
    eviState = 0 ;
    noteStateToggle = false ;
    //turn all notes off
    allNotesOff() ;
    getPressure() ;
  }
}

/**********************************************************************************************************************************************/

void allNotesOff() {
  for (int i=0; i<128; i++) {
    if (pitchState[i]) {
      midiCommand(144, i, 0) ;
      pitchState[i] = false ;
    }
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void updateNote() {
  //get which notes to turn on, off, and what pb value
  noteOn();
  noteOff();
  if ((millis() - midiLastTime) > midiDebounceTime) {
    updatePressure();
    updatePb() ;
    updatePortamento() ;
    midiLastTime = millis() ;
  }
  
}

/**********************************************************************************************************************************************/

void updatePb() {
  if (pitchBendLast != pitchBend) {
    midiCommand(224, pitchBend&127, pitchBend>>7) ;   
  }
}

/**********************************************************************************************************************************************/

void updatePortamento() {
  int portamentoLast = portamentoVal ;
  getPortamentoVal() ;
  if (biteSensorToggle) {
    if (portamentoToggle) {
     midiCommand(176, 65, 127) ;
     portamentoToggle = false ;
    }
    if (portamentoVal != portamentoLast) {
      midiCommand(176, 5, portamentoVal>>7) ;
    }
  } else if (!biteSensorToggle && portamentoToggle) {
    midiCommand(176, 65, 0) ;
    portamentoToggle = false ;
  }
}

/**********************************************************************************************************************************************/

void updatePressure() {
  if (pressureVal != pressureLast) { // need to allow for tolerances to ease mass transfer of data
    switch(pressureOutputState){
      case 0:
        //output pressure to continuous controller 2
        midiCommand(176, 2, pressureVal>>7) ;
        //midiCommand(176, 34, pressureVal>>7) ;
      break;
      case 1: 
      //output pressure to something else and so on
      break;
    }
    pressureLast = pressureVal ;
  }
}

/**********************************************************************************************************************************************/

void noteOn () {
  //check all pitches that should be on against all pitches that are on to turn on necessary pitches
  for (int i=0; i<=pitchNum; i++) {
    if (!pitchState[pitch[i]]) {
      
      for (int j=0; j<=pitchNum; j++) {
        if ((pitch[j] == pitch[i]) && (j != i)) {
          if (pitchVelocity[j] > pitchVelocity[i]) {
            velocityToggle = true ;
          }
        }
      }
      if (!velocityToggle) {
        pitchState[pitch[i]] = true ;
        pitchStateVelocity[pitch[i]] = pitchVelocity[i] ;
        midiCommand(144, pitch[i], pitchVelocity[i]) ;
      }
      velocityToggle = false ;
      
    } else {
      if (pitchStateVelocity[pitch[i]] != pitchVelocity[i]) {
        for (int j=0; j<=pitchNum; j++) {
          if ((pitch[j] == pitch[i]) && (i != j)) {
            if (pitchVelocity[j] > pitchVelocity[i]) {
              velocityToggle = true ;
            }
          }
        }
        if (!velocityToggle) {
          pitchState[pitch[i]] = true ;
          pitchStateVelocity[pitch[i]] = pitchVelocity[i] ;
          midiCommand(144, pitch[i], pitchVelocity[i]) ;
        }
        velocityToggle = false ;
      }
    }
  }
}

/**********************************************************************************************************************************************/

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

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void getPortamentoVal() {
   if ((biteSensorRaw > biteSensorOnTHR) && (!biteSensorToggle)) {
    biteSensorToggle = true ;
    portamentoToggle = true ;
  } else if ((biteSensorRaw < biteSensorOffTHR) && (biteSensorToggle)) {
    biteSensorToggle = false ;
    portamentoToggle = true ;
  }
  if (biteSensorToggle) {
    portamentoVal = rangeClip(biteSensorRaw, biteSensorOffTHR, biteSensorMAX) ;
    portamentoVal = map(portamentoVal, biteSensorOffTHR, biteSensorMAX, 0, 16383) ;
  } else if (biteSensorToggle && portamentoToggle) {
    portamentoVal = 0 ;
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void getPitchVal() {
  //assigns which note to play based on keys pressed
  if (millis() - pitchLastTime > pitchDebounceTime) {
    //make sure that the pitch is only set every so often 
    pitch[pitchNum] = transpositionPitch ;
    pitchVelocity[pitchNum] = currentVelocity ;
    
    getOctaveVal() ;
    getFingeringVal() ;
    
    pitchLastTime = millis() ;
  }  
}

/**********************************************************************************************************************************************/

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

/**********************************************************************************************************************************************/

void getFingeringVal() {
  //adjusts the ovtave based on keys
  for (uint8_t i=0; i<7; i++) {
    if (pressedKey[i+12]) {
      pitch[pitchNum] += keyValue[i] ;
    }
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

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
  case 2:
    
  break;
  }
}

/**********************************************************************************************************************************************/

void presetChordSet() {
  if (pressedKey[4]) {
    getPresetChordQuality() ;
    if (!chordPresetToggle) {
      chordPresetBase = pitch[pitchNum] ;
      pitchNum = 0 ;
      for (int i=0; i<chordPresetSize; i++) {
        pitch[i] = chordPresetBase + chordPreset[chordPresetNum][i] ;
        pitchVelocity[i] = chordVelocity ;
        pitchNum ++ ;
      }
      pitch[pitchNum] = pitch[0] ;
      pitchVelocity[pitchNum] = currentVelocity ;
      
      chordPresetToggle = true ;
    } 
  } else if (!pressedKey[4] && chordPresetToggle) {
    chordPresetToggle = false ; 
  }
  if (pitch[pitchNum] != lastPitch[pitchNum]) {
    chordPresetToggle = false ;
  }
  if (chordPresetNum != chordPresetNumLast) {
    chordPresetToggle = false ;
  }
  chordPresetNum = chordPresetNumLast ;
}

/**********************************************************************************************************************************************/

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

/**********************************************************************************************************************************************/

void applyChord() {
  //takes stored chords in buttons and implements them 
  for (int i=0; i<4; i++) {
    if (chordNum[i] != 0) {
      if (pressedKey[i] && !chordOnToggle[i]) {
        chordOnToggle[i] = true ;
      
        pitch[chordNum[i]] = pitch[pitchNum] ;
        pitchVelocity[chordNum[i]] = currentVelocity ;
        pitchNum = chordNum[i];
        for (int j=0; j<pitchNum; j++) {
          pitch[j] = chordPitch[i][j] ;
          pitchVelocity[j] = sustainVelocity ;
        }
      } else if (!pressedKey[i] && chordOnToggle[i]) {
        chordOnToggle[i] = false ;
      }
    } 
  }
}

/**********************************************************************************************************************************************/

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

/**********************************************************************************************************************************************/

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
      pitchVelocity[pitchNum-1] = sustainVelocity ;
    } else if (pitch[pitchNum] != pitch[(pitchNum-1)]) {
      pitchNum ++ ;
      pitch[pitchNum] = pitch[pitchNum - 1] ;
      pitchVelocity[pitchNum-1] = sustainVelocity ;
    }
  }
}

/**********************************************************************************************************************************************/

void clearMPhonic() {
  //clears the current multiphonics
  pitch[0] = pitch[pitchNum] ;
  pitchVelocity[0] = currentVelocity ;
  pitchNum = 0 ;
}

/**********************************************************************************************************************************************/

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

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void getPB() {
  getCurrentPitchBend() ;
  getVibrato() ;
  
  int pitchBendDiff = pBUp - pBDown ; 
  int pitchBendSum ;
  pitchBendLast = pitchBend ;
  
  switch(pitchBendMode) {
      case 0: 
      
      break;
      case 1: 
      pitchBendDiff = pitchBendDiff/2 ;
      break;
      default:
      
      break;
    }
    pitchBendSum = 8192 + pitchBendDiff ;
    if (pBToggle) {
      pitchBend = pitchBend*0.6 + pitchBendSum*0.4 ;
    } 
    if (!pBToggle) {
      pitchBend = pitchBend*0.6 + pitchBendSum*0.4 ;
      if ((pitchBend > 8187) && (pitchBend < 8197)) {
        pitchBend = 8192 ;
      }
    }

    pitchBend = pitchBend + vibratoVal ;
    pitchBend = rangeClip(pitchBend, 0, 16383) ;
  
}
void getCurrentPitchBend() {
  if (pBUpRaw>pBUpTHR || pBDownRaw>pBDownTHR) {
    if (!pBToggle) {
      pBToggle = true ;
    }
    
    pBUp = map(pBUpRaw, pBUpTHR, pBUpMAX, 0, 8192) ;
    
    pBDown = map(pBDownRaw, pBDownTHR, pBDownMAX, 0, 8192) ;
      
  
  } else if (pBToggle) {
    pBToggle = false ;

    pBUp = 0 ;
    pBDown = 0 ;
  }
}
/**********************************************************************************************************************************************/

void getVibrato() {
  getCurrentVibrato();
  vibratoRaw = xCoord ;
  vibratoVal = vibratoVal*0.5 + 0.5*map(rangeClip(vibratoRaw, -vibratoZero, vibratoZero), -vibratoMAX, vibratoMAX, -vibratoDepth, vibratoDepth) ;
  vibratoZero = vibratoZero*vibratoCurve + vibratoRaw*(1-vibratoCurve) ;
}

/**********************************************************************************************************************************************/

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

/**********************************************************************************************************************************************/

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

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void updateIndicatorDisplay() {
  modeSelectSmooth = modeSelectTotal/modeSelectIndex ;
  modeSelectTotal = 0 ;
  modeSelectIndex = 0 ;
  if (modeSelectSmooth <= modeSelectTHR[0][modeSelector]) {
    if (modeSelector == 3) {
      
    } else {
      modeSelector += 1 ;
    }
  } else if (modeSelectSmooth >= modeSelectTHR[1][modeSelector]) {
    if (modeSelector == 0) {
      
    } else {
      modeSelector -= 1 ;
    }
  }
  
  if (modeSelector != lastModeSelector) {
    indicatorDisplayToggle = true ;
  }

  if (pressureVal == 0) {
    equalizer = 0 ;
  } else if (pressureVal <= equalizerTHR[0][equalizer]) {
    if (equalizer == 0) { } else {
    equalizer -- ;      
    }
  } else if (pressureVal >= equalizerTHR[1][equalizer]) {
    if (equalizer == 8) { } else {
    equalizer ++ ;      
    }
  }
    
  if (equalizer != lastEqualizer) {
    if (equalizerToggle) {
      indicatorDisplayToggle = true ;
    } else if (!equalizerToggle) {
      if ((equalizer == 0) || (lastEqualizer == 0)) {
        indicatorDisplayToggle = true ;
      }
    }
  }
  writeIndicatorDisplay() ;
}

/**********************************************************************************************************************************************/

void writeIndicatorDisplay() {
  if (indicatorDisplayToggle) {
    matrix.clear() ;
    
    writeEqualizerDisplay() ;
    
    writeModeSelectorDisplay() ;
    
    matrix.writeDisplay() ;

    indicatorDisplayToggle = false ;
  }

}

/**********************************************************************************************************************************************/

void writeEqualizerDisplay() {
  if (equalizerToggle) {
    if (equalizer>7) {
      matrix.fillRect(5, 0, 2, 5, LED_GREEN) ;
      matrix.fillRect(5, 5, 2, 2, LED_YELLOW) ;
      matrix.fillRect(5, 7, 2, (equalizer-7), LED_RED) ;
    } else if (equalizer>5) {
      matrix.fillRect(5, 0, 2, 5, LED_GREEN) ;
      matrix.fillRect(5, 5, 2, (equalizer-5), LED_YELLOW) ;
    } else if (equalizer>0) {
      matrix.fillRect(5, 0, 2, equalizer, LED_GREEN) ;
    } else {
    }
  } else if (!equalizerToggle) {
    if (equalizer > 0) {
      matrix.fillRect(5, 0, 2, 2, LED_GREEN) ;
    } else {
    }
  }
}

/**********************************************************************************************************************************************/

void writeModeSelectorDisplay() {
  matrix.fillRect(2, 0, 2, 8, LED_RED) ;
    
  matrix.fillRect(0, (2*modeSelector), 2, 2, LED_RED) ;

  for (int i=0; i<4; i++) {
    if (selectButton[i]) {
      matrix.fillRect(2, (2*i), 2, 2, LED_GREEN) ;
    }
  }
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void getJoystickMode() {

  if (joystickSelect && !joystickSelectToggle) {
    if (!selectButton[modeSelector]) {
      selectButton[modeSelector] = true ;
      switch(modeSelector) {
        case 0:
        equalizerToggle = true ;
        break;
        case 1:
        pitchBendMode = 1 ;
        break;
        case 2:
        chordMode = 1 ;
        break;
        case 3:
        break;
      }
    } else if (selectButton[modeSelector]) {
      selectButton[modeSelector] = false ;
      switch(modeSelector) {
        case 0:
        equalizerToggle = false ;
        break;
        case 1:
        pitchBendMode = 0 ;
        break;
        case 2:
        chordMode = 0 ;
        break;
        case 3:
        break;
      }
    }
    indicatorDisplayToggle = true ;
    joystickSelectToggle = true ;
  } else if (!joystickSelect && joystickSelectToggle) {
    joystickSelectToggle = false ;
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void getPressure() {
  pressureRaw = rangeClip(pressureRaw, pressureOnTHR, pressureMAX) ;
  pressureVal = map(pressureRaw, pressureOnTHR, pressureMAX, 0, 16383) ;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

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
    
  Serial.println("joystick reset correctly") ;
}

/**********************************************************************************************************************************************/

boolean getData(byte address, byte reg, int byteNum) {
  Wire.beginTransmission(address) ;
  Wire.write(reg) ;
  Wire.endTransmission() ;
  Wire.requestFrom(address, byteNum) ;
  return (byteNum<=Wire.available()) ;
}

/**********************************************************************************************************************************************/

void writeData(byte address, byte reg, byte info) {
  Wire.beginTransmission(address) ;
  Wire.write(reg) ;
  Wire.write(info) ;
  Wire.endTransmission() ;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void getData() {
  while (Serial2.available() > 0) {
    //Serial.println(Serial2.peek()) ;
    byte newByte = Serial2.read() ;

    if (recievingData) {
      newData[newDataNum] = newByte ;
      newDataNum ++ ;
      if (newDataNum >= recievedDataSize) {
        recievingData = false ;
        formatData() ;
      }
    } else if ((newByte == 0xff) && (lastByte == 0xff)) {
      //Serial.println("new message") ;
      recievingData = true ;
      newDataNum = 0 ;
    }

    lastByte = newByte ;
  } 
}

/**********************************************************************************************************************************************/

void formatData() {
  data1 = newData[0] ;
  data1 += newData[1]<<8 ;
  pBUpRaw = data1 ;
  
  data2 = newData[2] ;
  data2 += newData[3]<<8 ;
  pBDownRaw = data2 ;
}

/**********************************************************************************************************************************************/

int rangeClip(int number, int minimum, int maximum) {
  if (number >= maximum) {
    number = maximum ;
  } else if (number <= minimum) {
    number = minimum ;
  }
  return number ;
}

/**********************************************************************************************************************************************/

void midiCommand(int command, int data1, int data2) {
  switch(MIDI_OUTPUT_SERIAL) {
    case 0: 
      Serial.write(command);//send midi command byte
      Serial.write(data1);//send first data byte
      Serial.write(data2);//send second data byte
    break;
    case 1:
      int commandType = command >> 4 ;
      commandType = commandType & 7 ;
      int channel = command & 15 ;
      
      switch(commandType) {
        case 0:
          MIDI.sendNoteOff(data1, data2, channel) ;
          //B1000 note, velocity
        break;
        case 1:
          MIDI.sendNoteOn(data1, data2, channel) ;
          //B1001 note, velocity 
        break;
        case 2:
          MIDI.sendPolyPressure(data1, data2, channel) ; //polyphonic 
          //B1010 note, aftertouch
        break;
        case 3:
          MIDI.sendControlChange(data1, data2, channel) ;
          //B1011 controller#, value
        break;
        case 4:
          MIDI.sendProgramChange(data1, channel) ;
          //B1100 program#
        break;
        case 5:
          MIDI.sendAfterTouch(data1, channel) ; //channel wide
          //B1101 aftertouch
        break;
        case 6:
          int pitchBend = data1 + data2 << 7 ;
          pitchBend = pitchBend - 8192 ;
          MIDI.sendPitchBend(pitchBend, channel) ;
          //B1110 pitchbend(-8192 - 8191)
        break;
      } 
    break;
    case 2:
      Serial1.write(command);//send midi command byte
      Serial1.write(data1);//send first data byte
      Serial1.write(data2);//send second data byte
    break;
  } 
}

/**********************************************************************************************************************************************/
