uint8_t note = 64 ;
uint8_t velocity = 127 ;
uint8_t channel = 1 ;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  usbMIDI.sendNoteOn(note, velocity, channel) ;
  delay(1000) ;
  usbMIDI.sendNoteOn(note, 0, channel) ;
  delay(1000) ;
  
  
}
