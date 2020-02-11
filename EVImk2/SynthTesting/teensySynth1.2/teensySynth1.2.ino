#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dcTuner1;            //xy=59.5,603
AudioSynthWaveformDc     dcTuner2; //xy=60.5,644
AudioSynthWaveform       pitchLFO;      //xy=64,697
AudioMixer4              mixerOsc2;         //xy=243.5,713
AudioMixer4              mixerOsc1;         //xy=247.5,631
AudioSynthWaveformModulated osc1Voice3; //xy=421,691
AudioSynthWaveformModulated osc1Voice1;   //xy=424.3333333333333,395.99999999999994
AudioSynthNoiseWhite     noiseVoice3; //xy=424.66666666666674,777
AudioSynthWaveformModulated osc2Voice3; //xy=425.66666666666674,732
AudioSynthNoiseWhite     noiseVoice1;         //xy=428,482
AudioSynthWaveformModulated osc1Voice2; //xy=428,544
AudioSynthWaveformModulated osc1Voice4;  //xy=427,845
AudioSynthWaveformModulated osc2Voice1; //xy=429,437
AudioSynthNoiseWhite     noiseVoice2; //xy=431.66666666666674,630
AudioSynthNoiseWhite     noiseVoice4; //xy=430.66666666666674,931
AudioSynthWaveformModulated osc2Voice2; //xy=432.66666666666674,585
AudioSynthWaveformModulated osc2Voice4; //xy=431.66666666666674,886
AudioMixer4              mixerVoice3; //xy=605.6666666666667,738
AudioMixer4              mixerVoice1;         //xy=609,443
AudioMixer4              mixerVoice2; //xy=612.6666666666667,591
AudioMixer4              mixerVoice4; //xy=611.6666666666667,892
AudioEffectEnvelope      envelopeVoice3; //xy=770.6666666666667,736
AudioEffectEnvelope      envelopeVoice1;      //xy=774,441
AudioEffectEnvelope      envelopeVoice2; //xy=777.6666666666667,589
AudioEffectEnvelope      envelopeVoice4; //xy=776.6666666666667,890
AudioFilterStateVariable filterVoice3; //xy=938.6666666666667,743
AudioFilterStateVariable filterVoice1;        //xy=942,448
AudioFilterStateVariable filterVoice2; //xy=945.6666666666667,596
AudioFilterStateVariable filterVoice4; //xy=944.6666666666667,897
AudioMixer4              mixerFilter3; //xy=1085.6666666666667,748
AudioMixer4              mixerFilter1;         //xy=1089,453
AudioMixer4              mixerFilter2; //xy=1092.6666666666667,601
AudioMixer4              mixerFilter4; //xy=1091.6666666666667,902
AudioMixer4              mixerMaster;         //xy=1312,656
AudioOutputI2S           i2s1;           //xy=1498,656.8888549804688
AudioConnection          patchCord1(dcTuner1, 0, mixerOsc1, 0);
AudioConnection          patchCord2(dcTuner2, 0, mixerOsc2, 0);
AudioConnection          patchCord3(pitchLFO, 0, mixerOsc1, 1);
AudioConnection          patchCord4(pitchLFO, 0, mixerOsc2, 1);
AudioConnection          patchCord5(mixerOsc2, 0, osc2Voice1, 0);
AudioConnection          patchCord6(mixerOsc2, 0, osc2Voice2, 0);
AudioConnection          patchCord7(mixerOsc2, 0, osc2Voice3, 0);
AudioConnection          patchCord8(mixerOsc2, 0, osc2Voice4, 0);
AudioConnection          patchCord9(mixerOsc1, 0, osc1Voice1, 0);
AudioConnection          patchCord10(mixerOsc1, 0, osc1Voice2, 0);
AudioConnection          patchCord11(mixerOsc1, 0, osc1Voice3, 0);
AudioConnection          patchCord12(mixerOsc1, 0, osc1Voice4, 0);
AudioConnection          patchCord13(osc1Voice3, 0, mixerVoice3, 0);
AudioConnection          patchCord14(osc1Voice1, 0, mixerVoice1, 0);
AudioConnection          patchCord15(noiseVoice3, 0, mixerVoice3, 2);
AudioConnection          patchCord16(osc2Voice3, 0, mixerVoice3, 1);
AudioConnection          patchCord17(noiseVoice1, 0, mixerVoice1, 2);
AudioConnection          patchCord18(osc1Voice2, 0, mixerVoice2, 0);
AudioConnection          patchCord19(osc1Voice4, 0, mixerVoice4, 0);
AudioConnection          patchCord20(osc2Voice1, 0, mixerVoice1, 1);
AudioConnection          patchCord21(noiseVoice2, 0, mixerVoice2, 2);
AudioConnection          patchCord22(noiseVoice4, 0, mixerVoice4, 2);
AudioConnection          patchCord23(osc2Voice2, 0, mixerVoice2, 1);
AudioConnection          patchCord24(osc2Voice4, 0, mixerVoice4, 1);
AudioConnection          patchCord25(mixerVoice3, envelopeVoice3);
AudioConnection          patchCord26(mixerVoice1, envelopeVoice1);
AudioConnection          patchCord27(mixerVoice2, envelopeVoice2);
AudioConnection          patchCord28(mixerVoice4, envelopeVoice4);
AudioConnection          patchCord29(envelopeVoice3, 0, filterVoice3, 0);
AudioConnection          patchCord30(envelopeVoice1, 0, filterVoice1, 0);
AudioConnection          patchCord31(envelopeVoice2, 0, filterVoice2, 0);
AudioConnection          patchCord32(envelopeVoice4, 0, filterVoice4, 0);
AudioConnection          patchCord33(filterVoice3, 0, mixerFilter3, 0);
AudioConnection          patchCord34(filterVoice3, 1, mixerFilter3, 1);
AudioConnection          patchCord35(filterVoice3, 2, mixerFilter3, 2);
AudioConnection          patchCord36(filterVoice1, 0, mixerFilter1, 0);
AudioConnection          patchCord37(filterVoice1, 1, mixerFilter1, 1);
AudioConnection          patchCord38(filterVoice1, 2, mixerFilter1, 2);
AudioConnection          patchCord39(filterVoice2, 0, mixerFilter2, 0);
AudioConnection          patchCord40(filterVoice2, 1, mixerFilter2, 1);
AudioConnection          patchCord41(filterVoice2, 2, mixerFilter2, 2);
AudioConnection          patchCord42(filterVoice4, 0, mixerFilter4, 0);
AudioConnection          patchCord43(filterVoice4, 1, mixerFilter4, 1);
AudioConnection          patchCord44(filterVoice4, 2, mixerFilter4, 2);
AudioConnection          patchCord45(mixerFilter3, 0, mixerMaster, 2);
AudioConnection          patchCord46(mixerFilter1, 0, mixerMaster, 0);
AudioConnection          patchCord47(mixerFilter2, 0, mixerMaster, 1);
AudioConnection          patchCord48(mixerFilter4, 0, mixerMaster, 3);
AudioConnection          patchCord49(mixerMaster, 0, i2s1, 0);
AudioConnection          patchCord50(mixerMaster, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1399.888916015625,534.6666564941406
// GUItool: end automatically generated code

#define BUFFER 8
#define VOICE_NUM 4
#define DETUNE_RANGE 2
#define DETUNE_CONSTANT (float) 1/DETUNE_RANGE

const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};

float DIV127 = 1.0 / 127.0 ;
float DIV100 = 1.0 / 100.0 ;
float DIV12 = 1.0 / 12.0 ;

static byte noteBuff[BUFFER] = {255, 255, 255, 255, 255, 255, 255, 255} ;;
static byte velBuff[BUFFER] = {255, 255, 255, 255, 255, 255, 255, 255} ;;
static byte voiceBuff[BUFFER] = {255, 255, 255, 255, 255, 255, 255, 255} ;
static boolean voices[VOICE_NUM] = {0, 0, 0, 0} ;
static byte buffSize = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;

  
  AudioMemory(100) ;
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);
  sgtl5000_1.enable() ;
  sgtl5000_1.volume(0.3) ;
    
  osc1Voice1.begin(WAVEFORM_SINE) ; 
  osc1Voice1.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice1.begin(WAVEFORM_SINE) ; 
  osc2Voice1.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice1.amplitude(1.0) ;

  osc1Voice2.begin(WAVEFORM_SINE) ; 
  osc1Voice2.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice2.begin(WAVEFORM_SINE) ; 
  osc2Voice2.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice2.amplitude(1.0) ;

  osc1Voice3.begin(WAVEFORM_SINE) ; 
  osc1Voice3.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice3.begin(WAVEFORM_SINE) ; 
  osc2Voice3.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice3.amplitude(1.0) ;

  osc1Voice4.begin(WAVEFORM_SINE) ; 
  osc1Voice4.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice4.begin(WAVEFORM_SINE) ; 
  osc2Voice4.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice4.amplitude(1.0) ;

  pitchLFO.begin(WAVEFORM_SINE) ;
  
  dcTuner1.amplitude(0.0) ;
  mixerOsc1.gain(0, 1.0);
  mixerOsc1.gain(1, 1.0);
  
  dcTuner2.amplitude(0.0) ;
  mixerOsc2.gain(0, 1.0);
  mixerOsc2.gain(1, 1.0);

  mixerVoice1.gain(0, 1.0);
  mixerVoice1.gain(1, 1.0);
  mixerVoice1.gain(2, 0.0);
  mixerFilter1.gain(0, 1.0);
  mixerFilter1.gain(1, 0.0);
  mixerFilter1.gain(2, 0.0);

  mixerVoice2.gain(0, 1.0);
  mixerVoice2.gain(1, 1.0);
  mixerVoice2.gain(2, 0.0);
  mixerFilter2.gain(0, 1.0);
  mixerFilter2.gain(1, 0.0);
  mixerFilter2.gain(2, 0.0);

  mixerVoice3.gain(0, 1.0);
  mixerVoice3.gain(1, 1.0);
  mixerVoice3.gain(2, 0.0);
  mixerFilter3.gain(0, 1.0);
  mixerFilter3.gain(1, 0.0);
  mixerFilter3.gain(2, 0.0);

  mixerVoice4.gain(0, 1.0);
  mixerVoice4.gain(1, 1.0);
  mixerVoice4.gain(2, 0.0);
  mixerFilter4.gain(0, 1.0);
  mixerFilter4.gain(1, 0.0);
  mixerFilter4.gain(2, 0.0);

  mixerMaster.gain(0, 0.5) ;
  mixerMaster.gain(1, 0.5) ;
  mixerMaster.gain(2, 0.5) ;
  mixerMaster.gain(3, 0.5) ;
}

void loop() {
  usbMIDI.read(); 
}

void myNoteOff(byte channel, byte note, byte velocity) {
  keyBuff(note, velocity, false) ;
}

void myNoteOn(byte channel, byte note, byte velocity) {
  keyBuff(note, velocity, true) ;
}

void myControlChange(byte channel, byte control, byte value) {
  float x ;
  switch (control) {
    case 10: 
      x = value * DIV127 ;
      sgtl5000_1.volume(x) ;
    break;
    case 12:
      x = value * DIV127 ;
      mixerVoice1.gain(0, x);
      mixerVoice2.gain(0, x);
      mixerVoice3.gain(0, x);
      mixerVoice4.gain(0, x);
    break;
    case 13:
      x = value * DIV127 ;
      mixerVoice1.gain(1, x);
      mixerVoice2.gain(1, x);
      mixerVoice3.gain(1, x);
      mixerVoice4.gain(1, x);
    break;
    case 14:
      x = value * DIV127 ;
      mixerVoice1.gain(2, x);
      mixerVoice2.gain(2, x);
      mixerVoice3.gain(2, x);
      mixerVoice4.gain(2, x);
    break;
    case 15:
      switch(value) {
        case 0: 
         osc1Voice1.begin(WAVEFORM_SINE) ;
         osc1Voice2.begin(WAVEFORM_SINE) ;
         osc1Voice3.begin(WAVEFORM_SINE) ;
         osc1Voice4.begin(WAVEFORM_SINE) ;
        break;
        case 1: 
          osc1Voice1.begin(WAVEFORM_SAWTOOTH) ;
          osc1Voice2.begin(WAVEFORM_SAWTOOTH) ;
          osc1Voice3.begin(WAVEFORM_SAWTOOTH) ;
          osc1Voice4.begin(WAVEFORM_SAWTOOTH) ;
        break;
        case 2: 
          osc1Voice1.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
          osc1Voice2.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
          osc1Voice3.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
          osc1Voice4.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
        break;
        case 3:
          osc1Voice1.begin(WAVEFORM_SQUARE) ;
          osc1Voice2.begin(WAVEFORM_SQUARE) ;
          osc1Voice3.begin(WAVEFORM_SQUARE) ;
          osc1Voice4.begin(WAVEFORM_SQUARE) ;
        break;
        case 4: 
          osc1Voice1.begin(WAVEFORM_TRIANGLE) ;
          osc1Voice2.begin(WAVEFORM_TRIANGLE) ;
          osc1Voice3.begin(WAVEFORM_TRIANGLE) ;
          osc1Voice4.begin(WAVEFORM_TRIANGLE) ;
        break;
      }
    break;
    case 16:
      switch(value) {
        case 0: 
         osc2Voice1.begin(WAVEFORM_SINE) ;
         osc2Voice2.begin(WAVEFORM_SINE) ;
         osc2Voice3.begin(WAVEFORM_SINE) ;
         osc2Voice4.begin(WAVEFORM_SINE) ;
        break;
        case 1: 
          osc2Voice1.begin(WAVEFORM_SAWTOOTH) ;
          osc2Voice2.begin(WAVEFORM_SAWTOOTH) ;
          osc2Voice3.begin(WAVEFORM_SAWTOOTH) ;
          osc2Voice4.begin(WAVEFORM_SAWTOOTH) ;
        break;
        case 2: 
          osc2Voice1.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
          osc2Voice2.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
          osc2Voice3.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
          osc2Voice4.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
        break;
        case 3:
          osc2Voice1.begin(WAVEFORM_SQUARE) ;
          osc2Voice2.begin(WAVEFORM_SQUARE) ;
          osc2Voice3.begin(WAVEFORM_SQUARE) ;
          osc2Voice4.begin(WAVEFORM_SQUARE) ;
        break;
        case 4: 
          osc2Voice1.begin(WAVEFORM_TRIANGLE) ;
          osc2Voice2.begin(WAVEFORM_TRIANGLE) ;
          osc2Voice3.begin(WAVEFORM_TRIANGLE) ;
          osc2Voice4.begin(WAVEFORM_TRIANGLE) ;
        break;
      }
    break;
    case 17:
      if (value <= 100) {
        x = value * DIV100 ;
        x = DETUNE_CONSTANT * DIV12 * x ;
      } else if (value <= 112) {
        x = value - 100 ;
        x = DETUNE_CONSTANT * x * DIV12 ;
      } else {
        x = DETUNE_CONSTANT ;
      }
      dcTuner1.amplitude(x) ;
    break;
    case 18:
      if (value <= 100) {
        x = value * DIV100 ;
        x = DETUNE_CONSTANT * DIV12 * x ;
      } else if (value <= 112) {
        x = value - 100 ;
        x = DETUNE_CONSTANT * x * DIV12 ;
      } else {
        x = DETUNE_CONSTANT ;
      }
      dcTuner2.amplitude(x) ;
    break;
    case 19:
      switch(value) {
        case 0: 
          mixerFilter1.gain(0, 1.0);
          mixerFilter1.gain(1, 0.0);
          mixerFilter1.gain(2, 0.0);

          mixerFilter2.gain(0, 1.0);
          mixerFilter2.gain(1, 0.0);
          mixerFilter2.gain(2, 0.0);

          mixerFilter3.gain(0, 1.0);
          mixerFilter3.gain(1, 0.0);
          mixerFilter3.gain(2, 0.0);

          mixerFilter4.gain(0, 1.0);
          mixerFilter4.gain(1, 0.0);
          mixerFilter4.gain(2, 0.0);
        break;
        case 1: 
          mixerFilter1.gain(0, 0.0);
          mixerFilter1.gain(1, 1.0);
          mixerFilter1.gain(2, 0.0);

          mixerFilter2.gain(0, 0.0);
          mixerFilter2.gain(1, 1.0);
          mixerFilter2.gain(2, 0.0);

          mixerFilter3.gain(0, 0.0);
          mixerFilter3.gain(1, 1.0);
          mixerFilter3.gain(2, 0.0);

          mixerFilter4.gain(0, 0.0);
          mixerFilter4.gain(1, 1.0);
          mixerFilter4.gain(2, 0.0);
        break;
        case 2: 
          mixerFilter1.gain(0, 0.0);
          mixerFilter1.gain(1, 0.0);
          mixerFilter1.gain(2, 1.0);

          mixerFilter2.gain(0, 0.0);
          mixerFilter2.gain(1, 0.0);
          mixerFilter2.gain(2, 1.0);

          mixerFilter3.gain(0, 0.0);
          mixerFilter3.gain(1, 0.0);
          mixerFilter3.gain(2, 1.0);

          mixerFilter4.gain(0, 0.0);
          mixerFilter4.gain(1, 0.0);
          mixerFilter4.gain(2, 1.0);
        break;
      }
    break;
    case 20:
      x = value * DIV127 ;
      x = x * 10000 ;
      filterVoice1.frequency(x) ;
      filterVoice2.frequency(x) ;
      filterVoice3.frequency(x) ;
      filterVoice4.frequency(x) ;
    break;
    case 21:
      x = value * DIV127 ;
      x = 4.3 * x + 0.7 ;
      filterVoice1.resonance(x) ;
      filterVoice2.resonance(x) ;
      filterVoice3.resonance(x) ;
      filterVoice4.resonance(x) ;
    break;
    case 24:
      x = 3000 * value * DIV127 ;
      envelopeVoice1.attack(x) ;
      envelopeVoice2.attack(x) ;
      envelopeVoice3.attack(x) ;
      envelopeVoice4.attack(x) ;
    break;
    case 25:
      x = 3000 * value * DIV127 ;
      envelopeVoice1.decay(x) ;
      envelopeVoice2.decay(x) ;
      envelopeVoice3.decay(x) ;
      envelopeVoice4.decay(x) ;
    break;
    case 26:
      x = value * DIV127 ;
      envelopeVoice1.sustain(x) ;
      envelopeVoice2.sustain(x) ;
      envelopeVoice3.sustain(x) ;
      envelopeVoice4.sustain(x) ;
    break;
    case 27:
      x = 3000 * value * DIV127 ;
      envelopeVoice1.release(x) ;
      envelopeVoice2.release(x) ;
      envelopeVoice3.release(x) ;
      envelopeVoice4.release(x) ;
    break;
    case 28:
      x = 3000 * value * DIV127 ;
      envelopeVoice1.hold(x) ;
      envelopeVoice2.hold(x) ;
      envelopeVoice3.hold(x) ;
      envelopeVoice4.hold(x) ;
    break;
    case 29:
      if (value <= 100) {
        x = value * DIV100 ;
        x = -DETUNE_CONSTANT * DIV12 * x ;
      } else if (value <= 112) {
        x = value - 100 ;
        x = -DETUNE_CONSTANT * x * DIV12 ;
      } else {
        x = -DETUNE_CONSTANT ;
      }
      dcTuner1.amplitude(x) ;
    break;
    case 30:
      if (value <= 100) {
        x = value * DIV100 ;
        x = -DETUNE_CONSTANT * DIV12 * x ;
      } else if (value <= 112) {
        x = value - 100 ;
        x = -DETUNE_CONSTANT * x * DIV12 ;
      } else {
        x = -DETUNE_CONSTANT ;
      }
      dcTuner2.amplitude(x) ;
    break;
    case 66:
      switch(value) {
        case 0: 
         pitchLFO.begin(WAVEFORM_SINE) ;
        break;
        case 1: 
          pitchLFO.begin(WAVEFORM_SAWTOOTH) ;
        break;
        case 2: 
          pitchLFO.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
        break;
        case 3:
          pitchLFO.begin(WAVEFORM_SQUARE) ;
        break;
        case 4: 
          pitchLFO.begin(WAVEFORM_TRIANGLE) ;
        break;
      }
    break;
    case 67:
      x = value * DIV127 ;
      x = pow(2, x) - 1 ;
      x = x * 25 ;
      pitchLFO.frequency(x);
    break;
    case 68:
      if (value <= 100) {
        x = value * DIV100 ;
        x = DETUNE_CONSTANT * DIV12 * x ;
      } else if (value <= 112) {
        x = value - 100 ;
        x = x * DIV12 * DETUNE_CONSTANT ;
      } else {
        x = DETUNE_CONSTANT ;
      }
      pitchLFO.amplitude(x);
    break;
  }
}

void keyBuff(byte note, byte velocity, bool state) {
 int offVoice ;
 
  // Add Note
  if (state == true && (buffSize < BUFFER) ) {
    for(int i=0; i<VOICE_NUM; i++) {
      if (voices[i] == 0) {
        oscPlay(note, velocity, i);
        noteBuff[buffSize] = note;
        velBuff[buffSize] = velocity ;
        voiceBuff[buffSize] = i ;
        voices[i] = 1 ;

        Serial.print("added note ") ;
        Serial.print(note) ;
        Serial.print(" to voice ") ;
        Serial.println(voiceBuff[buffSize]) ;

        buffSize++;
        
        return ;
      }
    }
    for(int i=0; i<buffSize; i++) {
      if(voiceBuff[i] != 255) {
        oscPlay(note, velocity, voiceBuff[i]);
        voiceBuff[buffSize] = voiceBuff[i] ;
        voiceBuff[i] = 255 ;
        noteBuff[buffSize] = note;
        velBuff[buffSize] = velocity ;

        Serial.print("added note ") ;
        Serial.print(note) ;
        Serial.print(" to voice ") ;
        Serial.println(voiceBuff[buffSize]) ;

        buffSize ++ ;
            
        return;
      }
    }
  }

  // Remove Note
  else if (state == false && buffSize != 0) {
    for (int found = 0; found < buffSize; found++) {
      if (noteBuff[found] == note) {
        oscStop(voiceBuff[found]) ; 
        voices[voiceBuff[found]] = 0 ;
         
        Serial.print("deleted note ") ;
        Serial.print(note) ;
        Serial.print(" from voice ") ;
        Serial.println(voiceBuff[found]) ;
        
        if (voiceBuff[0] == 255) {
          for(int i=1; i<buffSize; i++) {
            if (voiceBuff[i] != 255) {
              for (int j=0; j<VOICE_NUM; j++) {
                if (voices[j] == 0) {
                  oscPlay(noteBuff[i-1], velBuff[i-1], j);
                  voiceBuff[i-1] = j ;
                  voices[j] = 1 ;

                  Serial.print("added note ") ;
                  Serial.print(note) ;
                  Serial.print(" to voice ") ;
                  Serial.println(voiceBuff[i-1]) ;
               
                }
              }
            }
          } 
        }
        
        for (int gap = found; gap < (buffSize - 1); gap++) {
          noteBuff[gap] = noteBuff[gap + 1];
          velBuff[gap] = velBuff[gap + 1];
          voiceBuff[gap] = voiceBuff[gap + 1];
        }
        buffSize--;
        
        noteBuff[buffSize] = 255 ;
        velBuff[buffSize] = 255 ;
        voiceBuff[buffSize] = 255 ;

        for (int i=0; i<BUFFER; i++) {
          Serial.print(noteBuff[i]) ;
          Serial.print("\t") ;
        }
        Serial.println() ;
        for (int i=0; i<BUFFER; i++) {
          Serial.print(voiceBuff[i]) ;
          Serial.print("\t") ;
        }
        Serial.println() ;
        for (int i=0; i<VOICE_NUM; i++) {
          Serial.print(voices[i]) ;
          Serial.print("\t") ;
        }
        Serial.println() ;
        return ;
      }
    }
  }
  return ;
}

void oscPlay(byte note, byte velocity, int voice) {
  float amp ;
  
  switch(voice) {
    case 0:
      osc1Voice1.frequency(noteFreqs[note]) ;
      osc2Voice1.frequency(noteFreqs[note]) ;
      envelopeVoice1.noteOn() ;
      amp = (float) velocity * DIV127 ;
      osc1Voice1.amplitude(amp) ;
      osc2Voice1.amplitude(amp) ;
      noiseVoice1.amplitude(amp) ;
    break;
    case 1:
      osc1Voice2.frequency(noteFreqs[note]) ;
      osc2Voice2.frequency(noteFreqs[note]) ;
      envelopeVoice2.noteOn() ;
      amp = (float) velocity * DIV127 ;
      osc1Voice2.amplitude(amp) ;
      osc2Voice2.amplitude(amp) ;
      noiseVoice2.amplitude(amp) ;
    break;
    case 2:
      osc1Voice3.frequency(noteFreqs[note]) ;
      osc2Voice3.frequency(noteFreqs[note]) ;
      envelopeVoice3.noteOn() ;
      amp = (float) velocity * DIV127 ;
      osc1Voice3.amplitude(amp) ;
      osc2Voice3.amplitude(amp) ;
      noiseVoice3.amplitude(amp) ;
    break;
    case 3:
      osc1Voice4.frequency(noteFreqs[note]) ;
      osc2Voice4.frequency(noteFreqs[note]) ;
      envelopeVoice4.noteOn() ;
      amp = (float) velocity * DIV127 ;
      osc1Voice4.amplitude(amp) ;
      osc2Voice4.amplitude(amp) ;
      noiseVoice4.amplitude(amp) ;
    break;
  }
}

void oscStop(int voice) {
  switch(voice) {
    case 0:
      envelopeVoice1.noteOff() ;
    break;
    case 1:
      envelopeVoice2.noteOff() ;
    break;
    case 2:
      envelopeVoice3.noteOff() ;
    break;
    case 3:
      envelopeVoice4.noteOff() ;
    break;
  }
}
