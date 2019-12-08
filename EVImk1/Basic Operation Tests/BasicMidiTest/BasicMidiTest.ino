
/*
MIDI On/Off Messages
By Amanda Ghassaei
July 2012
https://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

*/
 
 int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
 //higher velocity usually makes MIDI instruments louder
 
 int noteON = 144;//144 = 10010000 in binary, note on command
 int noteOFF = 128;//128 = 10000000 in binary, note off command



void setup() {
  //  Set MIDI baud rate:
  Serial.begin(31250);
    pinMode(LED_BUILTIN, OUTPUT);

  

}

void loop() {
  for (int note=20;note<21;note++) {
    MIDImessage(144, note, 127) ;
    digitalWrite(LED_BUILTIN, HIGH) ;
    delay(500);//hold note for 300ms
    MIDImessage(144, note, 0) ;
    digitalWrite(LED_BUILTIN, LOW) ;
    delay(500) ;
  }
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
  
}
