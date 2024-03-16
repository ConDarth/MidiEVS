#include "AudioStream.h"
#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=468.33331298828125,475.00000762939453
AudioOutputPT8211_2      pt8211_2;     //xy=616.3333282470703,474.3333282470703
AudioConnection          patchCord1(sine1, 0, pt8211_2, 0);
AudioConnection          patchCord2(sine1, 0, pt8211_2, 1);
// GUItool: end automatically generated code


void setup() {
  AudioMemory(20);
  sine1.frequency(220);

  Serial.println(AUDIO_BLOCK_SAMPLES) ;
}

void loop() {
  Serial.println(AudioProcessorUsageMax()) ;
}