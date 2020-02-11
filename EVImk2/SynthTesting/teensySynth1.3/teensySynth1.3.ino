#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dcTuner1;            //xy=59.5,648.7142906188965
AudioSynthWaveformDc     dcTuner2; //xy=60.5,689.7142906188965
AudioSynthWaveform       pitchLFO;      //xy=64,742.7142906188965
AudioMixer4              mixerOsc2;         //xy=243.5,758.7142906188965
AudioMixer4              mixerOsc1;         //xy=247.5,676.7142906188965
AudioSynthWaveformModulated osc1Voice1;   //xy=424.3333333333333,395.99999999999994
AudioSynthWaveformModulated osc1Voice3; //xy=422.96429443359375,782.7857360839844
AudioSynthNoiseWhite     noiseVoice3; //xy=423.7738405863445,877.3571186065674
AudioSynthWaveformDc     dcFilter;            //xy=425.00001525878906,724.2857360839844
AudioSynthWaveformModulated osc2Voice3; //xy=424.7738405863445,832.3571186065674
AudioSynthWaveformModulated osc1Voice4;  //xy=426.10717391967773,945.3571186065674
AudioSynthNoiseWhite     noiseVoice1;         //xy=428,482
AudioSynthWaveformModulated osc1Voice2; //xy=428,544
AudioSynthWaveform       filterLFO;      //xy=427.8571319580078,688.035737991333
AudioSynthWaveformModulated osc2Voice1; //xy=429,437
AudioSynthNoiseWhite     noiseVoice4; //xy=429.7738405863445,1031.3571186065674
AudioSynthNoiseWhite     noiseVoice2; //xy=431.66666666666674,630
AudioSynthWaveformModulated osc2Voice4; //xy=430.7738405863445,986.3571186065674
AudioSynthWaveformModulated osc2Voice2; //xy=432.66666666666674,585
AudioMixer4              mixerVoice1;         //xy=673.4642639160156,454.42853927612305
AudioEffectEnvelope      envelopeFilter3; //xy=677.3214378356934,914.2856645584106
AudioMixer4              mixerVoice2; //xy=679.6309509277344,603.6785430908203
AudioMixer4              mixerVoice3; //xy=679.2381248474121,852.2856636047363
AudioEffectEnvelope      envelopeFilter4; //xy=678.5714378356934,1068.0356674194336
AudioEffectEnvelope      envelopeFilter2; //xy=684.4642639160156,658.9285430908203
AudioMixer4              mixerVoice4; //xy=683.9881248474121,1005.0356674194336
AudioEffectEnvelope      envelopeFilter1;      //xy=686.9642639160156,518.9285411834717
AudioEffectEnvelope      envelopeVoice3; //xy=860.4880968729656,851.5356521606445
AudioEffectEnvelope      envelopeVoice1;      //xy=864.7142562866211,456.17853355407715
AudioMixer4              mixerFilterMod4; //xy=866.0714454650879,1073.0356674194336
AudioEffectEnvelope      envelopeVoice4; //xy=866.4880968729656,1005.5356521606445
AudioEffectEnvelope      envelopeVoice2; //xy=868.3809229532878,604.1785335540771
AudioMixer4              mixerFilterMod3; //xy=868.5714416503906,919.2856636047363
AudioMixer4              mixerFilterMod2; //xy=875.7142715454102,663.9285430908203
AudioMixer4              mixerFilterMod1;         //xy=884.4642715454102,525.1785411834717
AudioFilterStateVariable filterVoice3; //xy=1028.4880968729656,858.5356521606445
AudioFilterStateVariable filterVoice1;        //xy=1032.714256286621,463.17853355407715
AudioFilterStateVariable filterVoice4; //xy=1034.4880968729656,1012.5356521606445
AudioFilterStateVariable filterVoice2; //xy=1036.3809229532878,611.1785335540771
AudioMixer4              mixerFilter3; //xy=1175.4880968729656,863.5356521606445
AudioMixer4              mixerFilter1;         //xy=1179.714256286621,468.17853355407715
AudioMixer4              mixerFilter4; //xy=1181.4880968729656,1017.5356521606445
AudioMixer4              mixerFilter2; //xy=1183.3809229532878,616.1785335540771
AudioMixer4              mixerMaster;         //xy=1426.2856407165527,740.2856426239014
AudioSynthWaveform       ampLFO;      //xy=1432.8572273254395,824.285719871521
AudioEffectMultiply      multiplyAmpLFO;      //xy=1604.2855682373047,785.7142543792725
AudioMixer4              mixerAmp;         //xy=1785.7142715454102,754.285701751709
AudioOutputI2S           i2s1;           //xy=1939.2102584838867,755.0038414001465
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
AudioConnection          patchCord13(osc1Voice1, 0, mixerVoice1, 0);
AudioConnection          patchCord14(osc1Voice3, 0, mixerVoice3, 0);
AudioConnection          patchCord15(noiseVoice3, 0, mixerVoice3, 2);
AudioConnection          patchCord16(dcFilter, envelopeFilter1);
AudioConnection          patchCord17(dcFilter, envelopeFilter2);
AudioConnection          patchCord18(dcFilter, envelopeFilter3);
AudioConnection          patchCord19(dcFilter, envelopeFilter4);
AudioConnection          patchCord20(osc2Voice3, 0, mixerVoice3, 1);
AudioConnection          patchCord21(osc1Voice4, 0, mixerVoice4, 0);
AudioConnection          patchCord22(noiseVoice1, 0, mixerVoice1, 2);
AudioConnection          patchCord23(osc1Voice2, 0, mixerVoice2, 0);
AudioConnection          patchCord24(filterLFO, 0, mixerFilterMod1, 0);
AudioConnection          patchCord25(filterLFO, 0, mixerFilterMod2, 0);
AudioConnection          patchCord26(filterLFO, 0, mixerFilterMod3, 0);
AudioConnection          patchCord27(filterLFO, 0, mixerFilterMod4, 0);
AudioConnection          patchCord28(osc2Voice1, 0, mixerVoice1, 1);
AudioConnection          patchCord29(noiseVoice4, 0, mixerVoice4, 2);
AudioConnection          patchCord30(noiseVoice2, 0, mixerVoice2, 2);
AudioConnection          patchCord31(osc2Voice4, 0, mixerVoice4, 1);
AudioConnection          patchCord32(osc2Voice2, 0, mixerVoice2, 1);
AudioConnection          patchCord33(mixerVoice1, envelopeVoice1);
AudioConnection          patchCord34(envelopeFilter3, 0, mixerFilterMod3, 1);
AudioConnection          patchCord35(mixerVoice2, envelopeVoice2);
AudioConnection          patchCord36(mixerVoice3, envelopeVoice3);
AudioConnection          patchCord37(envelopeFilter4, 0, mixerFilterMod4, 1);
AudioConnection          patchCord38(envelopeFilter2, 0, mixerFilterMod2, 1);
AudioConnection          patchCord39(mixerVoice4, envelopeVoice4);
AudioConnection          patchCord40(envelopeFilter1, 0, mixerFilterMod1, 1);
AudioConnection          patchCord41(envelopeVoice3, 0, filterVoice3, 0);
AudioConnection          patchCord42(envelopeVoice1, 0, filterVoice1, 0);
AudioConnection          patchCord43(mixerFilterMod4, 0, filterVoice4, 1);
AudioConnection          patchCord44(envelopeVoice4, 0, filterVoice4, 0);
AudioConnection          patchCord45(envelopeVoice2, 0, filterVoice2, 0);
AudioConnection          patchCord46(mixerFilterMod3, 0, filterVoice3, 1);
AudioConnection          patchCord47(mixerFilterMod2, 0, filterVoice2, 1);
AudioConnection          patchCord48(mixerFilterMod1, 0, filterVoice1, 1);
AudioConnection          patchCord49(filterVoice3, 0, mixerFilter3, 0);
AudioConnection          patchCord50(filterVoice3, 1, mixerFilter3, 1);
AudioConnection          patchCord51(filterVoice3, 2, mixerFilter3, 2);
AudioConnection          patchCord52(filterVoice1, 0, mixerFilter1, 0);
AudioConnection          patchCord53(filterVoice1, 1, mixerFilter1, 1);
AudioConnection          patchCord54(filterVoice1, 2, mixerFilter1, 2);
AudioConnection          patchCord55(filterVoice4, 0, mixerFilter4, 0);
AudioConnection          patchCord56(filterVoice4, 1, mixerFilter4, 1);
AudioConnection          patchCord57(filterVoice4, 2, mixerFilter4, 2);
AudioConnection          patchCord58(filterVoice2, 0, mixerFilter2, 0);
AudioConnection          patchCord59(filterVoice2, 1, mixerFilter2, 1);
AudioConnection          patchCord60(filterVoice2, 2, mixerFilter2, 2);
AudioConnection          patchCord61(mixerFilter3, 0, mixerMaster, 2);
AudioConnection          patchCord62(mixerFilter1, 0, mixerMaster, 0);
AudioConnection          patchCord63(mixerFilter4, 0, mixerMaster, 3);
AudioConnection          patchCord64(mixerFilter2, 0, mixerMaster, 1);
AudioConnection          patchCord65(mixerMaster, 0, multiplyAmpLFO, 0);
AudioConnection          patchCord66(mixerMaster, 0, mixerAmp, 0);
AudioConnection          patchCord67(ampLFO, 0, multiplyAmpLFO, 1);
AudioConnection          patchCord68(multiplyAmpLFO, 0, mixerAmp, 1);
AudioConnection          patchCord69(mixerAmp, 0, i2s1, 0);
AudioConnection          patchCord70(mixerAmp, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1514.1745567321777,618.952299118042
// GUItool: end automatically generated code

#define BUFFER 8
#define VOICE_NUM 4
#define DETUNE_RANGE 2
#define DETUNE_CONSTANT (float) 1/DETUNE_RANGE
#define MIXER_CONSTANT (float) 0.25 
#define FILTER_MOD_RANGE 3
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)

short chorusDelayLine[CHORUS_DELAY_LENGTH];

const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};


float DIV127 = 1.0 / 127.0 ;
float DIV100 = 1.0 / 100.0 ;
float DIV64 = 1.0 / 64.0 ;
float DIV12 = 1.0 / 12.0 ;

static byte noteBuff[BUFFER] = {255, 255, 255, 255, 255, 255, 255, 255} ;;
static byte velBuff[BUFFER] = {255, 255, 255, 255, 255, 255, 255, 255} ;;
static byte voiceBuff[BUFFER] = {255, 255, 255, 255, 255, 255, 255, 255} ;
static boolean voiceTally[VOICE_NUM] = {0, 0, 0, 0} ;
static byte buffSize = 0;

float filterFrequency = 0 ;
float filterEnvelopeAmt = 0 ;

unsigned long lastTime = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;

  
  AudioMemory(50) ;
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
  filterVoice1.octaveControl(2*FILTER_MOD_RANGE) ;

  osc1Voice2.begin(WAVEFORM_SINE) ; 
  osc1Voice2.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice2.begin(WAVEFORM_SINE) ; 
  osc2Voice2.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice2.amplitude(1.0) ;
  filterVoice2.octaveControl(2*FILTER_MOD_RANGE) ;

  osc1Voice3.begin(WAVEFORM_SINE) ; 
  osc1Voice3.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice3.begin(WAVEFORM_SINE) ; 
  osc2Voice3.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice3.amplitude(1.0) ;
  filterVoice3.octaveControl(2*FILTER_MOD_RANGE) ;

  osc1Voice4.begin(WAVEFORM_SINE) ; 
  osc1Voice4.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice4.begin(WAVEFORM_SINE) ; 
  osc2Voice4.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice4.amplitude(1.0) ;
  filterVoice4.octaveControl(2*FILTER_MOD_RANGE) ;

  pitchLFO.begin(WAVEFORM_SINE) ;
  pitchLFO.amplitude(0.0) ;
  filterLFO.begin(WAVEFORM_SINE) ;
  filterLFO.amplitude(0.0) ;
  ampLFO.begin(WAVEFORM_SINE) ;
  ampLFO.amplitude(0.0) ;
  ampLFO.offset(1.0) ;
  
  dcTuner1.amplitude(0.0) ;
  mixerOsc1.gain(0, 1.0);
  mixerOsc1.gain(1, 1.0);
  
  dcTuner2.amplitude(0.0) ;
  mixerOsc2.gain(0, 1.0);
  mixerOsc2.gain(1, 1.0);

  dcFilter.amplitude(0.0) ;

  mixerAmp.gain(0, 1.0) ;
  mixerAmp.gain(1, 0.0) ;

  mixerVoice1.gain(0, MIXER_CONSTANT);
  mixerVoice1.gain(1, MIXER_CONSTANT);
  mixerVoice1.gain(2, 0.0);
  mixerFilter1.gain(0, 1.0);
  mixerFilter1.gain(1, 0.0);
  mixerFilter1.gain(2, 0.0);
  mixerFilterMod1.gain(0, 0.5) ;
  mixerFilterMod1.gain(1, 0.5) ;

  mixerVoice2.gain(0, MIXER_CONSTANT);
  mixerVoice2.gain(1, MIXER_CONSTANT);
  mixerVoice2.gain(2, 0.0);
  mixerFilter2.gain(0, 1.0);
  mixerFilter2.gain(1, 0.0);
  mixerFilter2.gain(2, 0.0);
  mixerFilterMod2.gain(0, 0.5) ;
  mixerFilterMod2.gain(1, 0.5) ;

  mixerVoice3.gain(0, MIXER_CONSTANT);
  mixerVoice3.gain(1, MIXER_CONSTANT);
  mixerVoice3.gain(2, 0.0);
  mixerFilter3.gain(0, 1.0);
  mixerFilter3.gain(1, 0.0);
  mixerFilter3.gain(2, 0.0);
  mixerFilterMod3.gain(0, 0.5) ;
  mixerFilterMod3.gain(1, 0.5) ;

  mixerVoice4.gain(0, MIXER_CONSTANT);
  mixerVoice4.gain(1, MIXER_CONSTANT);
  mixerVoice4.gain(2, 0.0);
  mixerFilter4.gain(0, 1.0);
  mixerFilter4.gain(1, 0.0);
  mixerFilter4.gain(2, 0.0);
  mixerFilterMod4.gain(0, 0.5) ;
  mixerFilterMod4.gain(1, 0.5) ;

  mixerMaster.gain(0, MIXER_CONSTANT) ;
  mixerMaster.gain(1, MIXER_CONSTANT) ;
  mixerMaster.gain(2, MIXER_CONSTANT) ;
  mixerMaster.gain(3, MIXER_CONSTANT) ;
}

void loop() {
  usbMIDI.read(); 
  if(millis() - lastTime >= 3000) {
    Serial.print("Proc = ");
    Serial.print(AudioProcessorUsage());
    Serial.print(" (");    
    Serial.print(AudioProcessorUsageMax());
    Serial.print("),  Mem = ");
    Serial.print(AudioMemoryUsage());
    Serial.print(" (");    
    Serial.print(AudioMemoryUsageMax());
    Serial.println(")");
    lastTime = millis();
  }
}

void myNoteOff(byte channel, byte note, byte velocity) {
  keyBuff(note, velocity, false) ;
}

void myNoteOn(byte channel, byte note, byte velocity) {
  keyBuff(note, velocity, true) ;
}

void myControlChange(byte channel, byte control, byte value) {
  float x ;
  float y ;
  switch (control) {
    case 10: 
      x = value * DIV127 ;
      sgtl5000_1.volume(x) ;
    break;
    case 12:
      x = MIXER_CONSTANT * value * DIV127 ;
      mixerVoice1.gain(0, x);
      mixerVoice2.gain(0, x);
      mixerVoice3.gain(0, x);
      mixerVoice4.gain(0, x);
    break;
    case 13:
      x = MIXER_CONSTANT * value * DIV127 ;
      mixerVoice1.gain(1, x);
      mixerVoice2.gain(1, x);
      mixerVoice3.gain(1, x);
      mixerVoice4.gain(1, x);
    break;
    case 14:
      x = MIXER_CONSTANT * value * DIV127 ;
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
      filterFrequency = value * DIV127 ;
      filterFrequency = filterFrequency * 10000 ;
      x = filterFrequency * filterEnvelopeAmt ;
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
    case 23:
      y = value - 64 ;
      y = y * DIV64 ;
      dcFilter.amplitude(y) ;
      y = -1 * y * FILTER_MOD_RANGE ;
      filterEnvelopeAmt = pow(2, y) ;
      x = filterFrequency * filterEnvelopeAmt ;
      filterVoice1.frequency(x) ;
      filterVoice2.frequency(x) ;
      filterVoice3.frequency(x) ;
      filterVoice4.frequency(x) ;
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
    case 31: 
    break;
    case 43:
      x = 3000 * value * DIV127 ;
      envelopeFilter1.hold(x) ;
      envelopeFilter2.hold(x) ;
      envelopeFilter3.hold(x) ;
      envelopeFilter4.hold(x) ;
    break;
    case 44:
      x = 3000 * value * DIV127 ;
      envelopeFilter1.attack(x) ;
      envelopeFilter2.attack(x) ;
      envelopeFilter3.attack(x) ;
      envelopeFilter4.attack(x) ;
    break;
    case 45:
      x = 3000 * value * DIV127 ;
      envelopeFilter1.decay(x) ;
      envelopeFilter2.decay(x) ;
      envelopeFilter3.decay(x) ;
      envelopeFilter4.decay(x) ;
    break;
    case 46:
      x = value * DIV127 ;
      envelopeFilter1.sustain(x) ;
      envelopeFilter2.sustain(x) ;
      envelopeFilter3.sustain(x) ;
      envelopeFilter4.sustain(x) ;
    break;
    case 47:
      x = 3000 * value * DIV127 ;
      envelopeFilter1.release(x) ;
      envelopeFilter2.release(x) ;
      envelopeFilter3.release(x) ;
      envelopeFilter4.release(x) ;
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
    case 69:
      switch(value) {
        case 0: 
         filterLFO.begin(WAVEFORM_SINE) ;
        break;
        case 1: 
          filterLFO.begin(WAVEFORM_SAWTOOTH) ;
        break;
        case 2: 
          filterLFO.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
        break;
        case 3:
          filterLFO.begin(WAVEFORM_SQUARE) ;
        break;
        case 4: 
          filterLFO.begin(WAVEFORM_TRIANGLE) ;
        break;
      }
    break;
    case 70:
      x = value * DIV127 ;
      x = pow(2, x) - 1 ;
      x = x * 25 ;
      filterLFO.frequency(x);
    break;
    case 71:
      x = value * DIV127 ;
      filterLFO.amplitude(x);
    break;
    case 72:
      switch(value) {
        case 0: 
         ampLFO.begin(WAVEFORM_SINE) ;
        break;
        case 1: 
          ampLFO.begin(WAVEFORM_SAWTOOTH) ;
        break;
        case 2: 
          ampLFO.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
        break;
        case 3:
          ampLFO.begin(WAVEFORM_SQUARE) ;
        break;
        case 4: 
          ampLFO.begin(WAVEFORM_TRIANGLE) ;
        break;
      }
    break;
    case 73:
      x = value * DIV127 ;
      x = pow(2, x) - 1 ;
      x = x * 25 ;
      ampLFO.frequency(x);
    break;
    case 74:
      x = value * DIV127 ;
      if (x == 0) {
        mixerAmp.gain(0, 1.0) ;
        mixerAmp.gain(1, 0.0) ;
      } else {
        mixerAmp.gain(0, 0.0) ;
        mixerAmp.gain(1, 1.0) ;
        ampLFO.amplitude(x);
      }
    break;
  }
}

void keyBuff(byte note, byte velocity, bool state) {
 
  // Add Note
  if (state == true && (buffSize < BUFFER) ) {
    for(int i=0; i<VOICE_NUM; i++) {
      if (voiceTally[i] == 0) {
        oscPlay(note, velocity, i);
        noteBuff[buffSize] = note;
        velBuff[buffSize] = velocity ;
        voiceBuff[buffSize] = i ;
        voiceTally[i] = 1 ;
        
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
        voiceTally[voiceBuff[found]] = 0 ;
        
        if (voiceBuff[0] == 255) {
          for(int i=1; i<buffSize; i++) {
            if (voiceBuff[i] != 255) {
              for (int j=0; j<VOICE_NUM; j++) {
                if (voiceTally[j] == 0) {
                  oscPlay(noteBuff[i-1], velBuff[i-1], j);
                  voiceBuff[i-1] = j ;
                  voiceTally[j] = 1 ;

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

        return ;
      }
    }
  }
  return ;
}

void oscPlay(byte note, byte velocity, int voice) {
  float amp ;
  amp = (float) velocity * DIV127 ;
  switch(voice) {
    case 0:
      osc1Voice1.frequency(noteFreqs[note]) ;
      osc2Voice1.frequency(noteFreqs[note]) ;
      envelopeVoice1.noteOn() ;
      envelopeFilter1.noteOn() ;
      osc1Voice1.amplitude(amp) ;
      osc2Voice1.amplitude(amp) ;
      noiseVoice1.amplitude(amp) ;
    break;
    case 1:
      osc1Voice2.frequency(noteFreqs[note]) ;
      osc2Voice2.frequency(noteFreqs[note]) ;
      envelopeVoice2.noteOn() ;
      envelopeFilter1.noteOn() ;
      osc1Voice2.amplitude(amp) ;
      osc2Voice2.amplitude(amp) ;
      noiseVoice2.amplitude(amp) ;
    break;
    case 2:
      osc1Voice3.frequency(noteFreqs[note]) ;
      osc2Voice3.frequency(noteFreqs[note]) ;
      envelopeVoice3.noteOn() ;
      envelopeFilter1.noteOn() ;
      osc1Voice3.amplitude(amp) ;
      osc2Voice3.amplitude(amp) ;
      noiseVoice3.amplitude(amp) ;
    break;
    case 3:
      osc1Voice4.frequency(noteFreqs[note]) ;
      osc2Voice4.frequency(noteFreqs[note]) ;
      envelopeVoice4.noteOn() ;
      envelopeFilter1.noteOn() ;
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
      envelopeFilter1.noteOff() ;
    break;
    case 1:
      envelopeVoice2.noteOff() ;
      envelopeFilter2.noteOff() ;
    break;
    case 2:
      envelopeVoice3.noteOff() ;
      envelopeFilter3.noteOff() ;
    break;
    case 3:
      envelopeVoice4.noteOff() ;
      envelopeFilter4.noteOff() ;
    break;
  }
}
