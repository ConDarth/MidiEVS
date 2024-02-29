#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=280.33331298828125,302.33331298828125
AudioAmplifier           amp1;           //xy=436.33331298828125,303.33331298828125
AudioOutputI2S           i2s1;           //xy=591.3333129882812,302.33331298828125
AudioConnection          patchCord1(sine1, amp1);
AudioConnection          patchCord2(amp1, 0, i2s1, 0);
AudioConnection          patchCord3(amp1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=464.33331298828125,402.3333435058594
// GUItool: end automatically generated code




int led = LED_BUILTIN ;
int dTime = 500 ;         //ms of delay in blinks
float freq = 440 ;        // frequency to play on speaker

void setup() {

  Serial.begin (9600);
  while (!Serial && millis () < 3000)
    ;

  delay (3000);

  pinMode(led, OUTPUT);

  sgtl5000_1.enable() ;
  AudioMemory (16);

  amp1.gain(0.1) ;
  sine1.amplitude(1.0) ;
  sine1.frequency(440) ;
}

void loop() {
  digitalWrite(led, HIGH);
  amp1.gain(0.1) ;
  delay(dTime);
  digitalWrite(led, LOW);
  amp1.gain(0) ;
  delay(dTime);
}

