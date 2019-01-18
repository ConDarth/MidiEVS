//command controls
static int noteOff = 128 ;
static int noteOn = 144 ;
static int aftertouch = 160 ;
static int continuousController = 176 ;
static int patchChange = 192 ;
static int pitchBend = 224 ;
static int nonMusicalCommands = 240 ;

//note values
int pitchVal[16] ; //note number
int pitchNumber = 1 ;
int previousPitchVal = 0 ;
                       //K1  K2  K3  K4  K5  K6  K7  octave rollers 6-1 and empty roller
boolean noteButtons[] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1} ;
int noteValues[] =      {-2, -1, -3, -5,  2,  1,  4, 84, 72, 60, 48, 36, 24, 12}
int octaveCounter = 7 ;
int transposedPitch = 10 ; //initialized to key of Bb                          

//sustain key array, on, off, chord buttons 1-4 
boolean sustainKey[] = {0, 0, 0, 0, 0, 0} ;
int chordPitches[16][4] ; //notes in stored chords

//velocity, volume and expression controll
int velocityVal = 0 ; //constant 
int volumeVal = 0 ; // CC#7
int previousVolumeVal = 0 ;
double volumeConstant = 0 ; //adjustable
int expressionVal = 0 ; //CC#11

//controls for volume and expression 
double pressureSensor = 0 ; //analog output of pressure sensor
double pressureScalar = 0 ; //scalar from pressure to volume
double pressureMinimum = 0 ; //minimum pressure reading required to play 

//slurring, pitchbend and portamento 
double pitchBendKey[] = {0, 0, 0} ; // Bend up, Bend down, vibrato
double pitchBendControl[] ={0, 0, 0}  //scalar values for pitchbenders
int pitchbendVal = 0 ; //pitchbend
int portamentoVal = 0 ; //CC#5
boolean portamentoToggle = 0 ; //CC65

//controls for portamento 
double biteSensor = 0 ; //analog output of bite sensor
double biteSensorScalar = 0 ; //scalar from bite sensor to portamento timing
double biteSensorMinimum = 0 ; //minimum bite to activate sensor, and then deactivate it 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(31250) ;
}

void loop() {

  if (pressureSensor > pressureMinimum) {    
    
    //set the octave of the note
    octaveCounter = 7 ;
    while (octaveCounter < 14) {
      if (noteButton[octaveCounter]) {
        pitchVal[1] = transposedPitch + noteValue[octaveCounter] ; //sets the octave by adding a set number to pitch
        octaveCounter = 14 ; //stops while loop
      }
    }
  
    //set what keys are pushed and how they affect the note
    for (int i=0; i <= 6; i++) {
      if (noteButton[i]){
        pitchVal += noteValue[i] ; //adds appropriate numbers to pitch corresponding to keys pressed
      }
    }

    //check for slurring, and set slur scale
    if (previousPitchVal != pitchVal) {
      if (biteSensor > biteSensorMinimum) {
        portamentoToggle = 1 ; //turns on portamento
      }
    }

    //implement portamento 
    if (portamentoToggle) {
      portamentoTime = (int) biteSensor * biteSensorScalar ; //sets the portamento timing
      if (biteSensor < biteSensorMinimum) {
        portamentoToggle = 0 ; //turns off portamento if bite is too weak
      }
    }

    //get vibrato and pitchbend
    for (int i=0; i < 2; i++) {
      pitchBendVal += (int) pitchBendKey[i] * pitchBendControl[i] ; //sets th pitchbend value
    }
    if (pitchBendKey[2] > pitchBendControl[2]) {
    //dont know how to control vibrato yet 
    }

    //set the volume, velocity stays constant
    volumeVal = (int) pressureSensor * pressureScalar ;
      
    // set note and velocity value 
    if (pitchVal[0] != previousPitchVal) {
      for (int i=0; i <= pitchNumber; i++) {
        midiControllerMessage(noteOn, pitchVal[i], velocityVal) ; //set all the notes on 
      }
      midiControllerMessage(noteOff, previousPitchVal, velocityVal) ; //turn off previous note
    }   
    //set the previous values to check against
    previousPitchVal = pitchVal ;
    
  } else {
    //turnOff all notes 
    for (int i=0; i <= pitchNumber; i++) {
       midiControllerMessage(noteOff, pitchVal[i], velocityVal) ;
    }
  }

  //set sustain notes 
  if (sustainKey[0]) {
    if (pitchVal[0] != pitchVal[pitchNumber]) {
      pitchVal[pitchNumber] = pitchVal[0] ;
      pitchNumber ++ ;
    }
  //input the chords
    for (int i=2; i < 6; i++) {
      if (sustainKey[i]) {
        //set the sustained notes into the chord data
        for (int j=1 ; j < sustainNumber; j++) {
          chordPitch[i-2][j] = pitchVal[j] ;
        }
      } else {
        //set the preset chord into the sustain used
        for (int j=1; j < sustainNumber; j++) {
          sustainPitch[j] = chordPitch[i-2][j]
        }
      }
    }
    
  }
  //get rid of sustained notes 
  if (sustainKey[1]) {
    for (int i=1; i <= pitchNumber; i++) {
      //clears all pitches except main pitch
      pitchVal[i] = 0 ;
    }
    //clear chords if both clear key and chord key at same time
    for (int i=2; i < 6; i++) {
      if (sustainKey[i]) {
        for (int j=0; j < sustainNumber; j++) {
          chordPitch[i-2][j] = 0 ;
        }
      }
    }
    pitchNumber = 1 ;
  }
  
}

//function to write to midi port, will need changed for actual midi output
void midiControllerMessage ( int command, int data1, int data2) {
  Serial.write(command) ;
  Serial.write(data1) ;
  Serial.write(data2) ;
}
