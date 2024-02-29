#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <MIDI.h>

// GUItool: begin automatically generated code
AudioSynthWaveformModulated SinWave;   //xy=458.14827728271484,452.59247398376465
AudioSynthWaveformModulated TriWave;   //xy=459.25929260253906,513.7036485671997
AudioSynthWaveformModulated RectWave;   //xy=464.8148307800293,369.2592430114746
AudioSynthWaveformModulated RampWave;   //xy=468.1481399536133,585.9258689880371
AudioMixer4              WaveMix;         //xy=641.4814758300781,492.5925869411892
AudioEffectEnvelope      ClickPop;      //xy=785.9259338378906,491.4814758300781
AudioAmplifier           VolumeAmp;           //xy=932.5926055908203,491.48144483566284
AudioOutputI2S           AudioOut;           //xy=1082.592628479004,490.37036085128784
AudioConnection          patchCord1(SinWave, 0, WaveMix, 1);
AudioConnection          patchCord2(TriWave, 0, WaveMix, 2);
AudioConnection          patchCord3(RectWave, 0, WaveMix, 0);
AudioConnection          patchCord4(RampWave, 0, WaveMix, 3);
AudioConnection          patchCord5(WaveMix, ClickPop);
AudioConnection          patchCord6(ClickPop, VolumeAmp);
AudioConnection          patchCord7(VolumeAmp, 0, AudioOut, 0);
AudioConnection          patchCord8(VolumeAmp, 0, AudioOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1080.3704376220703,544.8148016929626
// GUItool: end automatically generated code



const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI) ;



int currNote = 0 ;
bool currNoteFlag = 0 ;

void setup() {
  Serial.begin(115200) ;

  AudioMemory(200) ;

  MIDI.begin() ;
  Serial1.begin(1000000) ;

  MIDI.setHandleControlChange(myControlChange);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandlePitchBend(myPitchBend);
  
  sgtl5000_1.enable() ;

  //Overall Volume Control
  VolumeAmp.gain(0.5) ;

  //An envelope for suppressing click and pop noise
  ClickPop.delay(0) ;
  ClickPop.attack(2) ;
  ClickPop.hold(0) ;
  ClickPop.decay(0) ;
  ClickPop.sustain(1) ;
  ClickPop.release(2) ;
  ClickPop.releaseNoteOn(2) ;

  //Mix all 4 oscillators together
  WaveMix.gain(0, 0.25) ;
  WaveMix.gain(1, 0.25) ;
  WaveMix.gain(2, 0.25) ;
  WaveMix.gain(3, 0.25) ;


  //Main waveforms used
  SinWave.begin(1, noteFreqs[64], WAVEFORM_SINE) ;
  TriWave.begin(0, noteFreqs[64], WAVEFORM_TRIANGLE) ;
  RectWave.begin(0.1, noteFreqs[64], WAVEFORM_BANDLIMIT_PULSE) ;
  RampWave.begin(0.5, noteFreqs[64], WAVEFORM_BANDLIMIT_SAWTOOTH) ;

}

void loop() {
  // put your main code here, to run repeatedly:
  MIDI.read() ;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void myControlChange(byte channel, byte control, byte value){

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void myNoteOff(byte channel, byte note, byte velocity){
  Serial.print(note) ;
  Serial.println(" Off") ;

  if (note == currNote){
    if (currNoteFlag){
      currNoteFlag = 0 ;
      ClickPop.noteOff() ;
    }
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void myNoteOn(byte channel, byte note, byte velocity){
  Serial.print(note) ;
  Serial.println(" On") ;

  //Stop Audio Interrupts So all effects take place at once
  AudioNoInterrupts() ;

  if (note != currNote){
    currNote = note ;
    SinWave.frequency(noteFreqs[note]) ;
    TriWave.frequency(noteFreqs[note]) ;
    RectWave.frequency(noteFreqs[note]) ;
    RampWave.frequency(noteFreqs[note]) ;
    ClickPop.noteOn() ;

  }

  if (!currNoteFlag){
    currNoteFlag = 1 ;
    ClickPop.noteOn() ;
  }

  AudioInterrupts() ;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void myPitchBend(byte channel, int bend){

}
