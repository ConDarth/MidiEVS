#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

boolean noteOn = false ;
int noteButton = 0 ;
int controllerData = 0 ;
int lastControllerData = 0 ;

void setup() {
  // put your setup code here, to run once:
  MIDI.begin(MIDI_CHANNEL_OFF);
  pinMode(2, INPUT_PULLUP) ;
  pinMode(3, INPUT_PULLUP) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((digitalRead(2) == LOW || digitalRead(3) == LOW) && noteOn == false) {
    noteOn = true ;
    if (digitalRead(2) == LOW) {
      noteButton = 0 ;
    } else if (digitalRead(3) == LOW) {
      noteButton = 1 ;
    }
    MIDI.sendNoteOn(64, 127, 1) ;
  } else if ((digitalRead(2) == HIGH && noteOn == true) && noteButton == 0) {
    noteOn = false ;
    MIDI.sendNoteOn(64, 0, 1) ;
  } else if ((digitalRead(3) == HIGH && noteOn == true) && noteButton == 1) {
    noteOn = false ;
    MIDI.sendNoteOn(64, 0, 1) ;
  }

  controllerData = map(analogRead(A0), 0, 1023, -8192, 8191) ;
  controllerData = constrain(controllerData, -8192, 8191) ;
  
  if (controllerData != lastControllerData) {
    //MIDI.sendControlChange(5, controllerData, 1) ;
    MIDI.sendPitchBend(controllerData, 1) ;
  }

  lastControllerData = controllerData ;

  delay(5) ;
}
