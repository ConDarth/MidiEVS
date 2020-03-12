#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dcPort3; //xy=55,886.2500123977661
AudioSynthWaveformDc     dcPort4; //xy=57.5000114440918,1033.8888683319092
AudioSynthWaveformDc     dcTuner1;            //xy=59.500003814697266,685.8175020217896
AudioSynthWaveformDc     dcTuner2; //xy=60.50000762939453,724.5952816009521
AudioSynthWaveformDc     dcPort1;            //xy=64.72222900390625,459.3055362701416
AudioSynthWaveform       pitchLFO;      //xy=64.00000762939453,770.928599357605
AudioSynthWaveformDc     pitchBend;            //xy=64.44445037841797,812.4999504089355
AudioSynthWaveformDc     dcPort2; //xy=67.36111450195312,602.2222185134888
AudioMixer4              mixerOsc1Voice1;         //xy=404.5833511352539,399.63097381591797
AudioMixer4              mixerOsc2Voice3; //xy=402.94448471069336,922.9722499847412
AudioMixer4              mixerOsc1Voice3; //xy=405.2778091430664,835.833324432373
AudioMixer4              mixerOsc2Voice1;         //xy=407.8055877685547,466.4920959472656
AudioMixer4              mixerOsc1Voice2; //xy=407.50001525878906,561.6666469573975
AudioMixer4              mixerOsc2Voice2; //xy=407.38892364501953,629.6389274597168
AudioMixer4              mixerOsc2Voice4; //xy=406.2777976989746,1074.0833339691162
AudioMixer4              mixerOsc1Voice4; //xy=408.6111183166504,999.4444122314453
AudioSynthWaveformModulated osc1Voice1;   //xy=604.3333943684895,421.0000743865966
AudioSynthNoiseWhite     noiseVoice1;         //xy=608.0000610351562,507.0000743865967
AudioSynthWaveformModulated osc1Voice2; //xy=608.0000610351562,569.0000743865967
AudioSynthWaveformModulated osc2Voice1; //xy=609.0000610351562,462.0000743865967
AudioSynthNoiseWhite     noiseVoice2; //xy=611.666727701823,655.0000743865967
AudioSynthWaveformModulated osc2Voice2; //xy=612.666727701823,610.0000743865967
AudioSynthWaveformModulated osc1Voice3; //xy=612.9643592834473,847.7858085632324
AudioSynthWaveformDc     dcFilter;            //xy=614.444580078125,731.7857756614685
AudioSynthNoiseWhite     noiseVoice3; //xy=613.773905436198,942.3571910858154
AudioSynthWaveformModulated osc2Voice3; //xy=614.773905436198,897.3571910858154
AudioSynthWaveformModulated osc1Voice4;  //xy=616.1072387695312,1010.3571910858154
AudioSynthWaveform       filterLFO;      //xy=617.301643371582,771.0913805961609
AudioSynthNoiseWhite     noiseVoice4; //xy=619.773905436198,1096.3571910858154
AudioSynthWaveformModulated osc2Voice4; //xy=620.773905436198,1051.3571910858154
AudioMixer4              mixerVoice1;         //xy=858.4643707275391,454.42865562438965
AudioMixer4              mixerVoice2; //xy=864.6310577392578,603.6786594390869
AudioEffectEnvelope      envelopeFilter2; //xy=869.4643707275391,658.9286594390869
AudioEffectEnvelope      envelopeFilter1;      //xy=871.9643707275391,518.9286575317383
AudioEffectEnvelope      envelopeFilter3; //xy=872.3215484619141,954.2857789993286
AudioMixer4              mixerVoice3; //xy=874.2382354736328,892.2857780456543
AudioEffectEnvelope      envelopeFilter4; //xy=873.5715484619141,1108.0357818603516
AudioMixer4              mixerVoice4; //xy=878.9882354736328,1045.0357818603516
AudioEffectEnvelope      envelopeVoice1;      //xy=1049.7143630981445,456.17864990234375
AudioEffectEnvelope      envelopeVoice2; //xy=1053.3810297648113,604.1786499023438
AudioEffectEnvelope      envelopeVoice3; //xy=1055.4882074991863,891.5357666015625
AudioMixer4              mixerFilterMod2; //xy=1060.7143783569336,663.9286594390869
AudioMixer4              mixerFilterMod4; //xy=1061.0715560913086,1113.0357818603516
AudioEffectEnvelope      envelopeVoice4; //xy=1061.4882074991863,1045.5357666015625
AudioMixer4              mixerFilterMod3; //xy=1063.5715522766113,959.2857780456543
AudioMixer4              mixerFilterMod1;         //xy=1069.4643783569336,525.1786575317383
AudioFilterStateVariable filterVoice1;        //xy=1217.7143630981445,463.17864990234375
AudioFilterStateVariable filterVoice2; //xy=1221.3810297648113,611.1786499023438
AudioFilterStateVariable filterVoice3; //xy=1223.4882074991863,898.5357666015625
AudioFilterStateVariable filterVoice4; //xy=1229.4882074991863,1052.5357666015625
AudioMixer4              mixerFilter1;         //xy=1364.7143630981445,468.17864990234375
AudioMixer4              mixerFilter2; //xy=1368.3810297648113,616.1786499023438
AudioMixer4              mixerFilter3; //xy=1370.4882074991863,903.5357666015625
AudioMixer4              mixerFilter4; //xy=1376.4882074991863,1057.5357666015625
AudioMixer4              mixerMaster;         //xy=1611.2857475280762,740.285758972168
AudioSynthWaveform       ampLFO;      //xy=1617.857322692871,808.5716066360474
AudioEffectMultiply      multiplyAmpLFO;      //xy=1796.0714416503906,790.000072479248
AudioMixer4              mixerAmp;         //xy=1975.0000762939453,758.5715236663818
AudioOutputI2S           i2s1;           //xy=2129.924617767334,756.4325113296509
AudioConnection          patchCord1(dcPort3, 0, mixerOsc1Voice3, 2);
AudioConnection          patchCord2(dcPort3, 0, mixerOsc2Voice3, 2);
AudioConnection          patchCord3(dcPort4, 0, mixerOsc1Voice4, 2);
AudioConnection          patchCord4(dcPort4, 0, mixerOsc2Voice4, 2);
AudioConnection          patchCord5(dcTuner1, 0, mixerOsc1Voice1, 0);
AudioConnection          patchCord6(dcTuner1, 0, mixerOsc1Voice2, 0);
AudioConnection          patchCord7(dcTuner1, 0, mixerOsc1Voice3, 0);
AudioConnection          patchCord8(dcTuner1, 0, mixerOsc1Voice4, 0);
AudioConnection          patchCord9(dcTuner2, 0, mixerOsc2Voice1, 0);
AudioConnection          patchCord10(dcTuner2, 0, mixerOsc2Voice2, 0);
AudioConnection          patchCord11(dcTuner2, 0, mixerOsc2Voice3, 0);
AudioConnection          patchCord12(dcTuner2, 0, mixerOsc2Voice4, 0);
AudioConnection          patchCord13(dcPort1, 0, mixerOsc1Voice1, 2);
AudioConnection          patchCord14(dcPort1, 0, mixerOsc2Voice1, 2);
AudioConnection          patchCord15(pitchLFO, 0, mixerOsc1Voice1, 1);
AudioConnection          patchCord16(pitchLFO, 0, mixerOsc2Voice1, 1);
AudioConnection          patchCord17(pitchLFO, 0, mixerOsc1Voice2, 1);
AudioConnection          patchCord18(pitchLFO, 0, mixerOsc2Voice2, 1);
AudioConnection          patchCord19(pitchLFO, 0, mixerOsc1Voice3, 1);
AudioConnection          patchCord20(pitchLFO, 0, mixerOsc2Voice3, 1);
AudioConnection          patchCord21(pitchLFO, 0, mixerOsc1Voice4, 1);
AudioConnection          patchCord22(pitchLFO, 0, mixerOsc2Voice4, 1);
AudioConnection          patchCord23(pitchBend, 0, mixerOsc1Voice1, 3);
AudioConnection          patchCord24(pitchBend, 0, mixerOsc2Voice1, 3);
AudioConnection          patchCord25(pitchBend, 0, mixerOsc1Voice2, 3);
AudioConnection          patchCord26(pitchBend, 0, mixerOsc2Voice2, 3);
AudioConnection          patchCord27(pitchBend, 0, mixerOsc1Voice3, 3);
AudioConnection          patchCord28(pitchBend, 0, mixerOsc2Voice3, 3);
AudioConnection          patchCord29(pitchBend, 0, mixerOsc1Voice4, 3);
AudioConnection          patchCord30(pitchBend, 0, mixerOsc2Voice4, 3);
AudioConnection          patchCord31(dcPort2, 0, mixerOsc1Voice2, 2);
AudioConnection          patchCord32(dcPort2, 0, mixerOsc2Voice2, 2);
AudioConnection          patchCord33(mixerOsc1Voice1, 0, osc1Voice1, 0);
AudioConnection          patchCord34(mixerOsc2Voice3, 0, osc2Voice3, 0);
AudioConnection          patchCord35(mixerOsc1Voice3, 0, osc1Voice3, 0);
AudioConnection          patchCord36(mixerOsc2Voice1, 0, osc2Voice1, 0);
AudioConnection          patchCord37(mixerOsc1Voice2, 0, osc1Voice2, 0);
AudioConnection          patchCord38(mixerOsc2Voice2, 0, osc2Voice2, 0);
AudioConnection          patchCord39(mixerOsc2Voice4, 0, osc2Voice4, 0);
AudioConnection          patchCord40(mixerOsc1Voice4, 0, osc1Voice4, 0);
AudioConnection          patchCord41(osc1Voice1, 0, mixerVoice1, 0);
AudioConnection          patchCord42(noiseVoice1, 0, mixerVoice1, 2);
AudioConnection          patchCord43(osc1Voice2, 0, mixerVoice2, 0);
AudioConnection          patchCord44(osc2Voice1, 0, mixerVoice1, 1);
AudioConnection          patchCord45(noiseVoice2, 0, mixerVoice2, 2);
AudioConnection          patchCord46(osc2Voice2, 0, mixerVoice2, 1);
AudioConnection          patchCord47(osc1Voice3, 0, mixerVoice3, 0);
AudioConnection          patchCord48(dcFilter, envelopeFilter1);
AudioConnection          patchCord49(dcFilter, envelopeFilter2);
AudioConnection          patchCord50(dcFilter, envelopeFilter3);
AudioConnection          patchCord51(dcFilter, envelopeFilter4);
AudioConnection          patchCord52(noiseVoice3, 0, mixerVoice3, 2);
AudioConnection          patchCord53(osc2Voice3, 0, mixerVoice3, 1);
AudioConnection          patchCord54(osc1Voice4, 0, mixerVoice4, 0);
AudioConnection          patchCord55(filterLFO, 0, mixerFilterMod1, 0);
AudioConnection          patchCord56(filterLFO, 0, mixerFilterMod2, 0);
AudioConnection          patchCord57(filterLFO, 0, mixerFilterMod3, 0);
AudioConnection          patchCord58(filterLFO, 0, mixerFilterMod4, 0);
AudioConnection          patchCord59(noiseVoice4, 0, mixerVoice4, 2);
AudioConnection          patchCord60(osc2Voice4, 0, mixerVoice4, 1);
AudioConnection          patchCord61(mixerVoice1, envelopeVoice1);
AudioConnection          patchCord62(mixerVoice2, envelopeVoice2);
AudioConnection          patchCord63(envelopeFilter2, 0, mixerFilterMod2, 1);
AudioConnection          patchCord64(envelopeFilter1, 0, mixerFilterMod1, 1);
AudioConnection          patchCord65(envelopeFilter3, 0, mixerFilterMod3, 1);
AudioConnection          patchCord66(mixerVoice3, envelopeVoice3);
AudioConnection          patchCord67(envelopeFilter4, 0, mixerFilterMod4, 1);
AudioConnection          patchCord68(mixerVoice4, envelopeVoice4);
AudioConnection          patchCord69(envelopeVoice1, 0, filterVoice1, 0);
AudioConnection          patchCord70(envelopeVoice2, 0, filterVoice2, 0);
AudioConnection          patchCord71(envelopeVoice3, 0, filterVoice3, 0);
AudioConnection          patchCord72(mixerFilterMod2, 0, filterVoice2, 1);
AudioConnection          patchCord73(mixerFilterMod4, 0, filterVoice4, 1);
AudioConnection          patchCord74(envelopeVoice4, 0, filterVoice4, 0);
AudioConnection          patchCord75(mixerFilterMod3, 0, filterVoice3, 1);
AudioConnection          patchCord76(mixerFilterMod1, 0, filterVoice1, 1);
AudioConnection          patchCord77(filterVoice1, 0, mixerFilter1, 0);
AudioConnection          patchCord78(filterVoice1, 1, mixerFilter1, 1);
AudioConnection          patchCord79(filterVoice1, 2, mixerFilter1, 2);
AudioConnection          patchCord80(filterVoice2, 0, mixerFilter2, 0);
AudioConnection          patchCord81(filterVoice2, 1, mixerFilter2, 1);
AudioConnection          patchCord82(filterVoice2, 2, mixerFilter2, 2);
AudioConnection          patchCord83(filterVoice3, 0, mixerFilter3, 0);
AudioConnection          patchCord84(filterVoice3, 1, mixerFilter3, 1);
AudioConnection          patchCord85(filterVoice3, 2, mixerFilter3, 2);
AudioConnection          patchCord86(filterVoice4, 0, mixerFilter4, 0);
AudioConnection          patchCord87(filterVoice4, 1, mixerFilter4, 1);
AudioConnection          patchCord88(filterVoice4, 2, mixerFilter4, 2);
AudioConnection          patchCord89(mixerFilter1, 0, mixerMaster, 0);
AudioConnection          patchCord90(mixerFilter2, 0, mixerMaster, 1);
AudioConnection          patchCord91(mixerFilter3, 0, mixerMaster, 2);
AudioConnection          patchCord92(mixerFilter4, 0, mixerMaster, 3);
AudioConnection          patchCord93(mixerMaster, 0, multiplyAmpLFO, 0);
AudioConnection          patchCord94(mixerMaster, 0, mixerAmp, 0);
AudioConnection          patchCord95(ampLFO, 0, multiplyAmpLFO, 1);
AudioConnection          patchCord96(multiplyAmpLFO, 0, mixerAmp, 1);
AudioConnection          patchCord97(mixerAmp, 0, i2s1, 0);
AudioConnection          patchCord98(mixerAmp, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2030.6031951904297,657.5238227844238
// GUItool: end automatically generated code

#define BUFFER 8
#define VOICE_NUM 4
#define DETUNE_RANGE 12
#define DETUNE_CONSTANT (float) 1/DETUNE_RANGE
#define MIXER_CONSTANT (float) 0.25 
#define FILTER_MOD_RANGE 3
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)

short chorusDelayLine[CHORUS_DELAY_LENGTH];

const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};

float DIV8192 = 1.0 / 8192.0 ;
float DIV127 = 1.0 / 127.0 ;
float DIV100 = 1.0 / 100.0 ;
float DIV64 = 1.0 / 64.0 ;
float DIV12 = 1.0 / 12.0 ;
float DIV3 = 1.0 / 3.0 ;

static byte noteBuff[BUFFER] = {255, 255, 255, 255, 255, 255, 255, 255} ;
static byte velBuff[BUFFER] = {255, 255, 255, 255, 255, 255, 255, 255} ;
static byte voiceBuff[BUFFER] = {255, 255, 255, 255, 255, 255, 255, 255} ;
static byte lastNote = 255 ;
static boolean voiceTally[VOICE_NUM] = {0, 0, 0, 0} ;
static byte buffSize = 0;

float filterFrequency = 6000 ;
float filterEnvelopeAmt = 0 ;
float portamentoAmt = 0 ;
boolean portamentoToggle = true ;
float pitchBendRange = 2 ;

unsigned long lastTime = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;

  
  AudioMemory(30) ;
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandlePitchChange(myPitchBend);
  sgtl5000_1.enable() ;
  sgtl5000_1.volume(0.3) ;

  mixerOsc1Voice1.gain(0, 1.0) ;
  mixerOsc1Voice1.gain(1, 1.0) ;
  mixerOsc1Voice1.gain(2, 1.0) ;
  mixerOsc1Voice1.gain(3, 1.0) ;

  mixerOsc2Voice1.gain(0, 1.0) ;
  mixerOsc2Voice1.gain(1, 1.0) ;
  mixerOsc2Voice1.gain(2, 1.0) ;
  mixerOsc2Voice1.gain(3, 1.0) ;

  mixerOsc1Voice2.gain(0, 1.0) ;
  mixerOsc1Voice2.gain(1, 1.0) ;
  mixerOsc1Voice2.gain(2, 1.0) ;
  mixerOsc1Voice2.gain(3, 1.0) ;

  mixerOsc2Voice2.gain(0, 1.0) ;
  mixerOsc2Voice2.gain(1, 1.0) ;
  mixerOsc2Voice2.gain(2, 1.0) ;
  mixerOsc2Voice2.gain(3, 1.0) ;

  mixerOsc1Voice3.gain(0, 1.0) ;
  mixerOsc1Voice3.gain(1, 1.0) ;
  mixerOsc1Voice3.gain(2, 1.0) ;
  mixerOsc1Voice3.gain(3, 1.0) ;

  mixerOsc2Voice3.gain(0, 1.0) ;
  mixerOsc2Voice3.gain(1, 1.0) ;
  mixerOsc2Voice3.gain(2, 1.0) ;
  mixerOsc2Voice3.gain(3, 1.0) ;

  mixerOsc1Voice4.gain(0, 1.0) ;
  mixerOsc1Voice4.gain(1, 1.0) ;
  mixerOsc1Voice4.gain(2, 1.0) ;
  mixerOsc1Voice4.gain(3, 1.0) ;

  mixerOsc2Voice4.gain(0, 1.0) ;
  mixerOsc2Voice4.gain(1, 1.0) ;
  mixerOsc2Voice4.gain(2, 1.0) ;
  mixerOsc2Voice4.gain(3, 1.0) ;
    
  osc1Voice1.begin(WAVEFORM_SAWTOOTH) ; 
  osc1Voice1.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice1.begin(WAVEFORM_SAWTOOTH) ; 
  osc2Voice1.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice1.amplitude(1.0) ;
  filterVoice1.octaveControl(2*FILTER_MOD_RANGE) ;

  osc1Voice2.begin(WAVEFORM_SAWTOOTH) ; 
  osc1Voice2.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice2.begin(WAVEFORM_SAWTOOTH) ; 
  osc2Voice2.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice2.amplitude(1.0) ;
  filterVoice2.octaveControl(2*FILTER_MOD_RANGE) ;

  osc1Voice3.begin(WAVEFORM_SAWTOOTH) ; 
  osc1Voice3.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice3.begin(WAVEFORM_SAWTOOTH) ; 
  osc2Voice3.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice3.amplitude(1.0) ;
  filterVoice3.octaveControl(2*FILTER_MOD_RANGE) ;

  osc1Voice4.begin(WAVEFORM_SAWTOOTH) ; 
  osc1Voice4.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice4.begin(WAVEFORM_SAWTOOTH) ; 
  osc2Voice4.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice4.amplitude(1.0) ;
  filterVoice4.octaveControl(2*FILTER_MOD_RANGE) ;

  filterVoice1.frequency(filterFrequency) ;
  filterVoice2.frequency(filterFrequency) ;
  filterVoice3.frequency(filterFrequency) ;
  filterVoice4.frequency(filterFrequency) ;
 
  filterVoice1.resonance(2) ;
  filterVoice2.resonance(2) ;
  filterVoice3.resonance(2) ;
  filterVoice4.resonance(2) ;

  pitchLFO.begin(WAVEFORM_SINE) ;
  pitchLFO.amplitude(0.0) ;
  filterLFO.begin(WAVEFORM_SINE) ;
  filterLFO.amplitude(0.0) ;
  ampLFO.begin(WAVEFORM_SINE) ;
  ampLFO.amplitude(0.0) ;
  ampLFO.offset(1.0) ;

  dcFilter.amplitude(0.0) ;
  dcTuner1.amplitude(0.0) ;
  dcTuner2.amplitude(0.0) ;
  pitchBend.amplitude(0.0) ;
  dcPort1.amplitude(0.0) ;
  dcPort2.amplitude(0.0) ;
  dcPort3.amplitude(0.0) ;
  dcPort4.amplitude(0.0) ;

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

void myPitchBend(byte channel, int bend) {
  float b ;
  b = bend * DIV8192 ;
  b = b * DETUNE_CONSTANT ;
  b = b * DIV12 * pitchBendRange;
  pitchBend.amplitude(b) ;
}

void myControlChange(byte channel, byte control, byte value) {
  float x ;
  float y ;
  float z ;
  AudioNoInterrupts() ;
  switch (control) {
    case 5:
      x = value * DIV127 ;
      x = pow(4, x) - 1 ;
      x = x * DIV3 ;
      x = 6000 * DIV12 * x ;
      portamentoAmt = x ;

      y = 12 * DETUNE_RANGE * portamentoAmt ;
      z = y * dcPort1.read() ;
      dcPort1.amplitude(dcPort1.read()) ;
      dcPort1.amplitude(0.0, z) ;
      z = y * dcPort2.read() ;
      dcPort2.amplitude(dcPort2.read()) ;
      dcPort2.amplitude(0.0, z) ;
      z = y * dcPort3.read() ;
      dcPort3.amplitude(dcPort3.read()) ;
      dcPort3.amplitude(0.0, z) ;
      z = y * dcPort4.read() ;
      dcPort4.amplitude(dcPort4.read()) ;
      dcPort4.amplitude(0.0, z) ;      
    break;
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
    case 65:
      if (value <= 64) {
        portamentoToggle = false ;
      } else {
        portamentoToggle = true ;
      }
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
      x = pow(4, x) - 1 ;
      x = x * DIV3 ;
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
      x = pow(4, x) - 1 ;
      x = x * DIV3 ;
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
      x = pow(4, x) - 1 ;
      x = x * DIV3 ;
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
    case 101:
      x = value ;
      if (x <= 24) {
        pitchBendRange = x ;
      }
    break;
  }
  AudioInterrupts() ;
}

void keyBuff(byte note, byte velocity, bool state) {
 
  // Add Note
  if (state == true && (buffSize < BUFFER) ) {
    for(int i=0; i<VOICE_NUM; i++) {
      if (voiceTally[i] == 0) {
        oscPlay(note, velocity, i);
        lastNote = note ;
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
        lastNote = note ;
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
                  lastNote = noteBuff[i-1] ;
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

void oscPlay(int note, int velocity, int voice) {
  float amp ;
  float port ;
  float amt ;
  amp = (float) velocity * DIV127 ;
  AudioNoInterrupts() ;
  switch(voice) {
    case 0:
      if ((portamentoToggle) && (lastNote <= 127)) {
        port = lastNote - note ;
        amt = abs(port * portamentoAmt) ;
        port = port * DETUNE_CONSTANT * DIV12 ;
        dcPort1.amplitude(port) ;
        dcPort1.amplitude(0.0, amt) ;
      }
      envelopeVoice1.noteOn() ;
      envelopeFilter1.noteOn() ;
      osc1Voice1.frequency(noteFreqs[note]) ;
      osc2Voice1.frequency(noteFreqs[note]) ;
      envelopeVoice1.noteOn() ;
      envelopeFilter1.noteOn() ;
      osc1Voice1.amplitude(amp) ;
      osc2Voice1.amplitude(amp) ;
      noiseVoice1.amplitude(amp) ;
    break;
    case 1:
      if ((portamentoToggle) && (lastNote <= 127)) {
        port = lastNote - note ;
        amt = abs(port * portamentoAmt) ;
        port = port * DETUNE_CONSTANT * DIV12 ;
        dcPort2.amplitude(port) ;
        dcPort2.amplitude(0.0, amt) ;
      }
      envelopeVoice2.noteOn() ;
      envelopeFilter2.noteOn() ;
      osc1Voice2.frequency(noteFreqs[note]) ;
      osc2Voice2.frequency(noteFreqs[note]) ;
      osc1Voice2.amplitude(amp) ;
      osc2Voice2.amplitude(amp) ;
      noiseVoice2.amplitude(amp) ;
    break;
    case 2:
      if ((portamentoToggle) && (lastNote <= 127)) {
        port = lastNote - note ;
        amt = abs(port * portamentoAmt) ;
        port = port * DETUNE_CONSTANT * DIV12 ;
        dcPort3.amplitude(port) ;
        dcPort3.amplitude(0.0, amt) ;
      }
      envelopeVoice3.noteOn() ;
      envelopeFilter3.noteOn() ;
      osc1Voice3.frequency(noteFreqs[note]) ;
      osc2Voice3.frequency(noteFreqs[note]) ;
      osc1Voice3.amplitude(amp) ;
      osc2Voice3.amplitude(amp) ;
      noiseVoice3.amplitude(amp) ;
    break;
    case 3:
      if ((portamentoToggle) && (lastNote <= 127)) {
        port = lastNote - note ;
        amt = abs(port * portamentoAmt) ;
        port = port * DETUNE_CONSTANT * DIV12 ;
        dcPort4.amplitude(port) ;
        dcPort4.amplitude(0.0, amt) ;
      }
      envelopeVoice4.noteOn() ;
      envelopeFilter4.noteOn() ;
      osc1Voice4.frequency(noteFreqs[note]) ;
      osc2Voice4.frequency(noteFreqs[note]) ;
      osc1Voice4.amplitude(amp) ;
      osc2Voice4.amplitude(amp) ;
      noiseVoice4.amplitude(amp) ;
    break;
  }
  AudioInterrupts() ;
}

void oscStop(int voice) {
  AudioNoInterrupts() ;
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
  AudioInterrupts() ;
}
