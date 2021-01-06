#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dcPort1;            //xy=55,400.97221660614014
AudioSynthWaveformDc     dcPort2; //xy=55,593.8888988494873
AudioSynthWaveformDc     dcPort3; //xy=55,896.2499942779541
AudioSynthWaveformDc     dcPort4; //xy=55,1157.22220993042
AudioSynthWaveform       pitchLFO;      //xy=58.5,834.2618741989136
AudioSynthWaveformDc     dcTuner1;            //xy=59.5,669.8174915313721
AudioSynthWaveformDc     dcTuner2; //xy=59.5,703.928617477417
AudioSynthWaveformDc     dcTuner3;            //xy=59.5,744.666675567627
AudioSynthWaveformDc     pitchBend;            //xy=61.5,785.8332443237305
AudioMixer4              mixerOsc1Voice1;         //xy=409.5833282470703,326.2976903915405
AudioMixer4              mixerOsc2Voice1;         //xy=409.4722366333008,388.1587677001953
AudioMixer4              mixerSin1Voice1;         //xy=410.3333206176758,449.66667556762695
AudioMixer4              mixerSin1Voice2; //xy=419.3333282470703,667.6666107177734
AudioMixer4              mixerOsc1Voice2; //xy=422.49999237060547,541.6665515899658
AudioMixer4              mixerOsc2Voice2; //xy=422.38890838623047,602.9721775054932
AudioMixer4              mixerOsc1Voice3; //xy=423.6111297607422,825.833324432373
AudioMixer4              mixerOsc2Voice3; //xy=424.61116790771484,891.3055534362793
AudioMixer4              mixerSin1Voice3; //xy=425,952.6666641235352
AudioMixer4              mixerSin1Voice4; //xy=429.99999237060547,1226.0000076293945
AudioMixer4              mixerOsc2Voice4; //xy=431.2777557373047,1160.7500534057617
AudioMixer4              mixerOsc1Voice4; //xy=431.9444122314453,1092.7777614593506
AudioSynthNoiseWhite     noiseVoice1;         //xy=600.0000114440918,475.00000858306885
AudioSynthWaveformModulated osc1Voice1;   //xy=604.333386739095,354.33342170715326
AudioSynthWaveformModulated osc1Voice2; //xy=608.0000610351562,569.0000743865967
AudioSynthWaveformModulated osc2Voice1; //xy=609.0000534057617,395.3334217071533
AudioSynthWaveformModulated sin1Voice1;   //xy=609.9999847412109,434.9999761581421
AudioSynthNoiseWhite     noiseVoice2; //xy=611.6667709350586,685.0000667572021
AudioSynthWaveformModulated osc2Voice2; //xy=612.666727701823,610.0000743865967
AudioSynthWaveformModulated osc1Voice4;  //xy=611.1072158813477,1115.3572177886963
AudioSynthWaveformModulated sin1Voice2; //xy=613.3333129882812,648.3333129882812
AudioSynthWaveformModulated osc1Voice3; //xy=612.9643592834473,847.7858085632324
AudioSynthWaveformModulated osc2Voice3; //xy=614.773905436198,897.3571910858154
AudioSynthWaveformModulated sin1Voice3; //xy=614.9999465942383,938.3332901000977
AudioSynthWaveform       filterLFO;      //xy=615.634952545166,784.424693107605
AudioSynthNoiseWhite     noiseVoice3; //xy=615.4405975341797,982.3571758270264
AudioSynthWaveformModulated osc2Voice4; //xy=615.7738825480144,1156.3572177886963
AudioSynthWaveformDc     dcFilter;            //xy=617.7779159545898,741.7857761383057
AudioSynthWaveformModulated sin1Voice4; //xy=618.3333129882812,1198.333251953125
AudioSynthNoiseWhite     noiseVoice4; //xy=619.7738876342773,1243.0238103866577
AudioMixer4              mixerVoice1;         //xy=858.4643630981445,387.7620029449463
AudioMixer4              mixerVoice2; //xy=864.6310577392578,603.6786594390869
AudioEffectEnvelope      envelopeFilter2; //xy=869.4643707275391,658.9286594390869
AudioEffectEnvelope      envelopeFilter4; //xy=868.5715255737305,1213.0358085632324
AudioEffectEnvelope      envelopeFilter1;      //xy=871.9643630981445,452.2620048522949
AudioEffectEnvelope      envelopeFilter3; //xy=872.3215484619141,954.2857789993286
AudioMixer4              mixerVoice3; //xy=874.2382354736328,892.2857780456543
AudioMixer4              mixerVoice4; //xy=873.9882125854492,1150.0358085632324
AudioEffectEnvelope      envelopeVoice1;      //xy=1049.71435546875,389.5119972229004
AudioEffectEnvelope      envelopeVoice2; //xy=1053.3810297648113,604.1786499023438
AudioEffectEnvelope      envelopeVoice3; //xy=1055.4882074991863,891.5357666015625
AudioMixer4              mixerFilterMod3; //xy=1056.90482711792,962.6191215515137
AudioMixer4              mixerFilterMod4; //xy=1056.071533203125,1218.0358085632324
AudioEffectEnvelope      envelopeVoice4; //xy=1056.4881846110027,1150.5357933044434
AudioMixer4              mixerFilterMod2; //xy=1060.7143783569336,663.9286594390869
AudioMixer4              mixerFilterMod1;         //xy=1069.464370727539,458.5120048522949
AudioFilterStateVariable filterVoice1;        //xy=1217.71435546875,396.5119972229004
AudioFilterStateVariable filterVoice2; //xy=1221.3810297648113,611.1786499023438
AudioFilterStateVariable filterVoice3; //xy=1223.4882074991863,898.5357666015625
AudioFilterStateVariable filterVoice4; //xy=1224.4881846110027,1157.5357933044434
AudioMixer4              mixerFilter1;         //xy=1364.71435546875,401.5119972229004
AudioMixer4              mixerFilter2; //xy=1368.3810297648113,616.1786499023438
AudioMixer4              mixerFilter3; //xy=1370.4882074991863,903.5357666015625
AudioMixer4              mixerFilter4; //xy=1371.4881846110027,1162.5357933044434
AudioMixer4              mixerMaster;         //xy=1611.2857475280762,740.285758972168
AudioSynthWaveform       ampLFO;      //xy=1617.857322692871,808.5716066360474
AudioEffectMultiply      multiplyAmpLFO;      //xy=1797.0714111328125,773.0000610351562
AudioMixer4              mixerAmp;         //xy=1976.0001220703125,758.571533203125
AudioSynthWaveform       digitalFXWave;      //xy=2031,1071
AudioEffectDelay         delayFX;         //xy=2037,930
AudioSynthWaveformDc     dcFX;            //xy=2044,1026
AudioMixer4              mixerFXIn;        //xy=2198,1032
AudioEffectDigitalCombine digitalFX;       //xy=2224,804
AudioMixer4              mixerDigitalFX;        //xy=2399,781
AudioEffectFreeverb      freeverb;      //xy=2569,825.5833740234375
AudioMixer4              mixerFreeverb;         //xy=2747,800.1666870117188
AudioOutputI2S           i2s1;           //xy=2955.008102416992,789.4325065612793
AudioConnection          patchCord1(dcPort1, 0, mixerOsc1Voice1, 2);
AudioConnection          patchCord2(dcPort1, 0, mixerOsc2Voice1, 2);
AudioConnection          patchCord3(dcPort1, 0, mixerSin1Voice1, 2);
AudioConnection          patchCord4(dcPort2, 0, mixerOsc1Voice2, 2);
AudioConnection          patchCord5(dcPort2, 0, mixerOsc2Voice2, 2);
AudioConnection          patchCord6(dcPort2, 0, mixerSin1Voice2, 2);
AudioConnection          patchCord7(dcPort3, 0, mixerOsc1Voice3, 2);
AudioConnection          patchCord8(dcPort3, 0, mixerOsc2Voice3, 2);
AudioConnection          patchCord9(dcPort3, 0, mixerSin1Voice3, 2);
AudioConnection          patchCord10(dcPort4, 0, mixerOsc1Voice4, 2);
AudioConnection          patchCord11(dcPort4, 0, mixerOsc2Voice4, 2);
AudioConnection          patchCord12(dcPort4, 0, mixerSin1Voice4, 2);
AudioConnection          patchCord13(pitchLFO, 0, mixerOsc1Voice1, 1);
AudioConnection          patchCord14(pitchLFO, 0, mixerOsc2Voice1, 1);
AudioConnection          patchCord15(pitchLFO, 0, mixerOsc1Voice2, 1);
AudioConnection          patchCord16(pitchLFO, 0, mixerOsc2Voice2, 1);
AudioConnection          patchCord17(pitchLFO, 0, mixerOsc1Voice3, 1);
AudioConnection          patchCord18(pitchLFO, 0, mixerOsc2Voice3, 1);
AudioConnection          patchCord19(pitchLFO, 0, mixerOsc1Voice4, 1);
AudioConnection          patchCord20(pitchLFO, 0, mixerOsc2Voice4, 1);
AudioConnection          patchCord21(pitchLFO, 0, mixerSin1Voice1, 1);
AudioConnection          patchCord22(pitchLFO, 0, mixerSin1Voice2, 1);
AudioConnection          patchCord23(pitchLFO, 0, mixerSin1Voice3, 1);
AudioConnection          patchCord24(pitchLFO, 0, mixerSin1Voice4, 1);
AudioConnection          patchCord25(dcTuner1, 0, mixerOsc1Voice1, 0);
AudioConnection          patchCord26(dcTuner1, 0, mixerOsc1Voice2, 0);
AudioConnection          patchCord27(dcTuner1, 0, mixerOsc1Voice3, 0);
AudioConnection          patchCord28(dcTuner1, 0, mixerOsc1Voice4, 0);
AudioConnection          patchCord29(dcTuner2, 0, mixerOsc2Voice1, 0);
AudioConnection          patchCord30(dcTuner2, 0, mixerOsc2Voice2, 0);
AudioConnection          patchCord31(dcTuner2, 0, mixerOsc2Voice3, 0);
AudioConnection          patchCord32(dcTuner2, 0, mixerOsc2Voice4, 0);
AudioConnection          patchCord33(dcTuner3, 0, mixerSin1Voice1, 0);
AudioConnection          patchCord34(dcTuner3, 0, mixerSin1Voice2, 0);
AudioConnection          patchCord35(dcTuner3, 0, mixerSin1Voice3, 0);
AudioConnection          patchCord36(dcTuner3, 0, mixerSin1Voice4, 0);
AudioConnection          patchCord37(pitchBend, 0, mixerOsc1Voice1, 3);
AudioConnection          patchCord38(pitchBend, 0, mixerOsc2Voice1, 3);
AudioConnection          patchCord39(pitchBend, 0, mixerOsc1Voice2, 3);
AudioConnection          patchCord40(pitchBend, 0, mixerOsc2Voice2, 3);
AudioConnection          patchCord41(pitchBend, 0, mixerOsc1Voice3, 3);
AudioConnection          patchCord42(pitchBend, 0, mixerOsc2Voice3, 3);
AudioConnection          patchCord43(pitchBend, 0, mixerOsc1Voice4, 3);
AudioConnection          patchCord44(pitchBend, 0, mixerOsc2Voice4, 3);
AudioConnection          patchCord45(pitchBend, 0, mixerSin1Voice1, 3);
AudioConnection          patchCord46(pitchBend, 0, mixerSin1Voice2, 3);
AudioConnection          patchCord47(pitchBend, 0, mixerSin1Voice3, 3);
AudioConnection          patchCord48(pitchBend, 0, mixerSin1Voice4, 3);
AudioConnection          patchCord49(mixerOsc1Voice1, 0, osc1Voice1, 0);
AudioConnection          patchCord50(mixerOsc2Voice1, 0, osc2Voice1, 0);
AudioConnection          patchCord51(mixerSin1Voice1, 0, sin1Voice1, 0);
AudioConnection          patchCord52(mixerSin1Voice2, 0, sin1Voice2, 0);
AudioConnection          patchCord53(mixerOsc1Voice2, 0, osc1Voice2, 0);
AudioConnection          patchCord54(mixerOsc2Voice2, 0, osc2Voice2, 0);
AudioConnection          patchCord55(mixerOsc1Voice3, 0, osc1Voice3, 0);
AudioConnection          patchCord56(mixerOsc2Voice3, 0, osc2Voice3, 0);
AudioConnection          patchCord57(mixerSin1Voice3, 0, sin1Voice3, 0);
AudioConnection          patchCord58(mixerSin1Voice4, 0, sin1Voice4, 0);
AudioConnection          patchCord59(mixerOsc2Voice4, 0, osc2Voice4, 0);
AudioConnection          patchCord60(mixerOsc1Voice4, 0, osc1Voice4, 0);
AudioConnection          patchCord61(noiseVoice1, 0, mixerVoice1, 3);
AudioConnection          patchCord62(osc1Voice1, 0, mixerVoice1, 0);
AudioConnection          patchCord63(osc1Voice2, 0, mixerVoice2, 0);
AudioConnection          patchCord64(osc2Voice1, 0, mixerVoice1, 1);
AudioConnection          patchCord65(sin1Voice1, 0, mixerVoice1, 2);
AudioConnection          patchCord66(noiseVoice2, 0, mixerVoice2, 3);
AudioConnection          patchCord67(osc2Voice2, 0, mixerVoice2, 1);
AudioConnection          patchCord68(osc1Voice4, 0, mixerVoice4, 0);
AudioConnection          patchCord69(sin1Voice2, 0, mixerVoice2, 2);
AudioConnection          patchCord70(osc1Voice3, 0, mixerVoice3, 0);
AudioConnection          patchCord71(osc2Voice3, 0, mixerVoice3, 1);
AudioConnection          patchCord72(sin1Voice3, 0, mixerVoice3, 2);
AudioConnection          patchCord73(filterLFO, 0, mixerFilterMod1, 0);
AudioConnection          patchCord74(filterLFO, 0, mixerFilterMod2, 0);
AudioConnection          patchCord75(filterLFO, 0, mixerFilterMod3, 0);
AudioConnection          patchCord76(filterLFO, 0, mixerFilterMod4, 0);
AudioConnection          patchCord77(noiseVoice3, 0, mixerVoice3, 3);
AudioConnection          patchCord78(osc2Voice4, 0, mixerVoice4, 1);
AudioConnection          patchCord79(dcFilter, envelopeFilter1);
AudioConnection          patchCord80(dcFilter, envelopeFilter2);
AudioConnection          patchCord81(dcFilter, envelopeFilter3);
AudioConnection          patchCord82(dcFilter, envelopeFilter4);
AudioConnection          patchCord83(sin1Voice4, 0, mixerVoice4, 2);
AudioConnection          patchCord84(noiseVoice4, 0, mixerVoice4, 3);
AudioConnection          patchCord85(mixerVoice1, envelopeVoice1);
AudioConnection          patchCord86(mixerVoice2, envelopeVoice2);
AudioConnection          patchCord87(envelopeFilter2, 0, mixerFilterMod2, 1);
AudioConnection          patchCord88(envelopeFilter4, 0, mixerFilterMod4, 1);
AudioConnection          patchCord89(envelopeFilter1, 0, mixerFilterMod1, 1);
AudioConnection          patchCord90(envelopeFilter3, 0, mixerFilterMod3, 1);
AudioConnection          patchCord91(mixerVoice3, envelopeVoice3);
AudioConnection          patchCord92(mixerVoice4, envelopeVoice4);
AudioConnection          patchCord93(envelopeVoice1, 0, filterVoice1, 0);
AudioConnection          patchCord94(envelopeVoice2, 0, filterVoice2, 0);
AudioConnection          patchCord95(envelopeVoice3, 0, filterVoice3, 0);
AudioConnection          patchCord96(mixerFilterMod3, 0, filterVoice3, 1);
AudioConnection          patchCord97(mixerFilterMod4, 0, filterVoice4, 1);
AudioConnection          patchCord98(envelopeVoice4, 0, filterVoice4, 0);
AudioConnection          patchCord99(mixerFilterMod2, 0, filterVoice2, 1);
AudioConnection          patchCord100(mixerFilterMod1, 0, filterVoice1, 1);
AudioConnection          patchCord101(filterVoice1, 0, mixerFilter1, 0);
AudioConnection          patchCord102(filterVoice1, 1, mixerFilter1, 1);
AudioConnection          patchCord103(filterVoice1, 2, mixerFilter1, 2);
AudioConnection          patchCord104(filterVoice2, 0, mixerFilter2, 0);
AudioConnection          patchCord105(filterVoice2, 1, mixerFilter2, 1);
AudioConnection          patchCord106(filterVoice2, 2, mixerFilter2, 2);
AudioConnection          patchCord107(filterVoice3, 0, mixerFilter3, 0);
AudioConnection          patchCord108(filterVoice3, 1, mixerFilter3, 1);
AudioConnection          patchCord109(filterVoice3, 2, mixerFilter3, 2);
AudioConnection          patchCord110(filterVoice4, 0, mixerFilter4, 0);
AudioConnection          patchCord111(filterVoice4, 1, mixerFilter4, 1);
AudioConnection          patchCord112(filterVoice4, 2, mixerFilter4, 2);
AudioConnection          patchCord113(mixerFilter1, 0, mixerMaster, 0);
AudioConnection          patchCord114(mixerFilter2, 0, mixerMaster, 1);
AudioConnection          patchCord115(mixerFilter3, 0, mixerMaster, 2);
AudioConnection          patchCord116(mixerFilter4, 0, mixerMaster, 3);
AudioConnection          patchCord117(mixerMaster, 0, multiplyAmpLFO, 0);
AudioConnection          patchCord118(mixerMaster, 0, mixerAmp, 0);
AudioConnection          patchCord119(ampLFO, 0, multiplyAmpLFO, 1);
AudioConnection          patchCord120(multiplyAmpLFO, 0, mixerAmp, 1);
AudioConnection          patchCord121(mixerAmp, 0, mixerDigitalFX, 0);
AudioConnection          patchCord122(mixerAmp, 0, digitalFX, 0);
AudioConnection          patchCord123(mixerAmp, delayFX);
AudioConnection          patchCord124(digitalFXWave, 0, mixerFXIn, 2);
AudioConnection          patchCord125(delayFX, 0, mixerFXIn, 0);
AudioConnection          patchCord126(dcFX, 0, mixerFXIn, 1);
AudioConnection          patchCord127(mixerFXIn, 0, digitalFX, 1);
AudioConnection          patchCord128(digitalFX, 0, mixerDigitalFX, 1);
AudioConnection          patchCord129(mixerDigitalFX, 0, mixerFreeverb, 0);
AudioConnection          patchCord130(mixerDigitalFX, freeverb);
AudioConnection          patchCord131(freeverb, 0, mixerFreeverb, 1);
AudioConnection          patchCord132(mixerFreeverb, 0, i2s1, 0);
AudioConnection          patchCord133(mixerFreeverb, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=3019.603271484375,713.5238037109375
// GUItool: end automatically generated code

#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI) ;

#define BUFFER 8
#define VOICE_NUM 4
#define DETUNE_RANGE 12
#define DETUNE_CONSTANT (float) 1/DETUNE_RANGE
#define MIXER_CONSTANT (float) 0.25 
#define FILTER_MOD_RANGE 3
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)

const int16_t myWaveform[256] = {
     0,  1895,  3748,  5545,  7278,  8934, 10506, 11984, 13362, 14634,
 15794, 16840, 17769, 18580, 19274, 19853, 20319, 20678, 20933, 21093,
 21163, 21153, 21072, 20927, 20731, 20492, 20221, 19929, 19625, 19320,
 19022, 18741, 18486, 18263, 18080, 17942, 17853, 17819, 17841, 17920,
 18058, 18254, 18507, 18813, 19170, 19573, 20017, 20497, 21006, 21538,
 22085, 22642, 23200, 23753, 24294, 24816, 25314, 25781, 26212, 26604,
 26953, 27256, 27511, 27718, 27876, 27986, 28049, 28068, 28047, 27989,
 27899, 27782, 27644, 27490, 27326, 27159, 26996, 26841, 26701, 26582,
 26487, 26423, 26392, 26397, 26441, 26525, 26649, 26812, 27012, 27248,
 27514, 27808, 28122, 28451, 28787, 29124, 29451, 29762, 30045, 30293,
 30495, 30643, 30727, 30738, 30667, 30509, 30254, 29897, 29433, 28858,
 28169, 27363, 26441, 25403, 24251, 22988, 21620, 20150, 18587, 16939,
 15214, 13423, 11577,  9686,  7763,  5820,  3870,  1926,     0, -1895,
 -3748, -5545, -7278, -8934,-10506,-11984,-13362,-14634,-15794,-16840,
-17769,-18580,-19274,-19853,-20319,-20678,-20933,-21093,-21163,-21153,
-21072,-20927,-20731,-20492,-20221,-19929,-19625,-19320,-19022,-18741,
-18486,-18263,-18080,-17942,-17853,-17819,-17841,-17920,-18058,-18254,
-18507,-18813,-19170,-19573,-20017,-20497,-21006,-21538,-22085,-22642,
-23200,-23753,-24294,-24816,-25314,-25781,-26212,-26604,-26953,-27256,
-27511,-27718,-27876,-27986,-28049,-28068,-28047,-27989,-27899,-27782,
-27644,-27490,-27326,-27159,-26996,-26841,-26701,-26582,-26487,-26423,
-26392,-26397,-26441,-26525,-26649,-26812,-27012,-27248,-27514,-27808,
-28122,-28451,-28787,-29124,-29451,-29762,-30045,-30293,-30495,-30643,
-30727,-30738,-30667,-30509,-30254,-29897,-29433,-28858,-28169,-27363,
-26441,-25403,-24251,-22988,-21620,-20150,-18587,-16939,-15214,-13423,
-11577, -9686, -7763, -5820, -3870, -1926
};

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

  
  AudioMemory(100) ;
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandlePitchChange(myPitchBend);

  MIDI.begin() ;

  MIDI.setHandleControlChange(myControlChange);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandlePitchBend(myPitchBend);
  
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

  mixerSin1Voice1.gain(0, 1.0) ;
  mixerSin1Voice1.gain(1, 1.0) ;
  mixerSin1Voice1.gain(2, 1.0) ;
  mixerSin1Voice1.gain(3, 1.0) ;

  mixerOsc1Voice2.gain(0, 1.0) ;
  mixerOsc1Voice2.gain(1, 1.0) ;
  mixerOsc1Voice2.gain(2, 1.0) ;
  mixerOsc1Voice2.gain(3, 1.0) ;

  mixerOsc2Voice2.gain(0, 1.0) ;
  mixerOsc2Voice2.gain(1, 1.0) ;
  mixerOsc2Voice2.gain(2, 1.0) ;
  mixerOsc2Voice2.gain(3, 1.0) ;

  mixerSin1Voice2.gain(0, 1.0) ;
  mixerSin1Voice2.gain(1, 1.0) ;
  mixerSin1Voice2.gain(2, 1.0) ;
  mixerSin1Voice2.gain(3, 1.0) ;

  mixerOsc1Voice3.gain(0, 1.0) ;
  mixerOsc1Voice3.gain(1, 1.0) ;
  mixerOsc1Voice3.gain(2, 1.0) ;
  mixerOsc1Voice3.gain(3, 1.0) ;

  mixerOsc2Voice3.gain(0, 1.0) ;
  mixerOsc2Voice3.gain(1, 1.0) ;
  mixerOsc2Voice3.gain(2, 1.0) ;
  mixerOsc2Voice3.gain(3, 1.0) ;

  mixerSin1Voice3.gain(0, 1.0) ;
  mixerSin1Voice3.gain(1, 1.0) ;
  mixerSin1Voice3.gain(2, 1.0) ;
  mixerSin1Voice3.gain(3, 1.0) ;

  mixerOsc1Voice4.gain(0, 1.0) ;
  mixerOsc1Voice4.gain(1, 1.0) ;
  mixerOsc1Voice4.gain(2, 1.0) ;
  mixerOsc1Voice4.gain(3, 1.0) ;

  mixerOsc2Voice4.gain(0, 1.0) ;
  mixerOsc2Voice4.gain(1, 1.0) ;
  mixerOsc2Voice4.gain(2, 1.0) ;
  mixerOsc2Voice4.gain(3, 1.0) ;

  mixerSin1Voice4.gain(0, 1.0) ;
  mixerSin1Voice4.gain(1, 1.0) ;
  mixerSin1Voice4.gain(2, 1.0) ;
  mixerSin1Voice4.gain(3, 1.0) ;
    
  osc1Voice1.begin(WAVEFORM_SAWTOOTH) ; 
  osc1Voice1.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice1.begin(WAVEFORM_SAWTOOTH) ; 
  osc2Voice1.frequencyModulation(DETUNE_RANGE) ; 
  sin1Voice1.begin(WAVEFORM_SINE) ; 
  sin1Voice1.frequencyModulation(DETUNE_RANGE) ;  
  noiseVoice1.amplitude(1.0) ;
  filterVoice1.octaveControl(2*FILTER_MOD_RANGE) ;

  osc1Voice2.begin(WAVEFORM_SAWTOOTH) ; 
  osc1Voice2.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice2.begin(WAVEFORM_SAWTOOTH) ; 
  osc2Voice2.frequencyModulation(DETUNE_RANGE) ; 
  sin1Voice2.begin(WAVEFORM_SINE) ; 
  sin1Voice2.frequencyModulation(DETUNE_RANGE) ;   
  noiseVoice2.amplitude(1.0) ;
  filterVoice2.octaveControl(2*FILTER_MOD_RANGE) ;

  osc1Voice3.begin(WAVEFORM_SAWTOOTH) ; 
  osc1Voice3.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice3.begin(WAVEFORM_SAWTOOTH) ; 
  osc2Voice3.frequencyModulation(DETUNE_RANGE) ;  
  sin1Voice3.begin(WAVEFORM_SINE) ; 
  sin1Voice3.frequencyModulation(DETUNE_RANGE) ;   
  noiseVoice3.amplitude(1.0) ;
  filterVoice3.octaveControl(2*FILTER_MOD_RANGE) ;

  osc1Voice4.begin(WAVEFORM_SAWTOOTH) ; 
  osc1Voice4.frequencyModulation(DETUNE_RANGE) ;  
  osc2Voice4.begin(WAVEFORM_SAWTOOTH) ; 
  osc2Voice4.frequencyModulation(DETUNE_RANGE) ; 
  sin1Voice4.begin(WAVEFORM_SINE) ; 
  sin1Voice4.frequencyModulation(DETUNE_RANGE) ;    
  noiseVoice4.amplitude(1.0) ;
  filterVoice4.octaveControl(2*FILTER_MOD_RANGE) ;

  osc1Voice1.arbitraryWaveform(myWaveform, 172.0);
  osc2Voice1.arbitraryWaveform(myWaveform, 172.0);
  osc1Voice2.arbitraryWaveform(myWaveform, 172.0);
  osc2Voice2.arbitraryWaveform(myWaveform, 172.0);
  osc1Voice3.arbitraryWaveform(myWaveform, 172.0);
  osc2Voice3.arbitraryWaveform(myWaveform, 172.0);
  osc1Voice4.arbitraryWaveform(myWaveform, 172.0);
  osc2Voice4.arbitraryWaveform(myWaveform, 172.0);
  
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
  dcTuner3.amplitude(-DETUNE_CONSTANT) ;
  pitchBend.amplitude(0.0) ;
  dcPort1.amplitude(0.0) ;
  dcPort2.amplitude(0.0) ;
  dcPort3.amplitude(0.0) ;
  dcPort4.amplitude(0.0) ;

  mixerVoice1.gain(0, MIXER_CONSTANT);
  mixerVoice1.gain(1, MIXER_CONSTANT);
  mixerVoice1.gain(2, MIXER_CONSTANT);
  mixerVoice1.gain(3, 0.0);
  mixerFilter1.gain(0, 1.0);
  mixerFilter1.gain(1, 0.0);
  mixerFilter1.gain(2, 0.0);
  mixerFilterMod1.gain(0, 0.5) ;
  mixerFilterMod1.gain(1, 0.5) ;

  mixerVoice2.gain(0, MIXER_CONSTANT);
  mixerVoice2.gain(1, MIXER_CONSTANT);
  mixerVoice2.gain(2, MIXER_CONSTANT);
  mixerVoice2.gain(3, 0.0);
  mixerFilter2.gain(0, 1.0);
  mixerFilter2.gain(1, 0.0);
  mixerFilter2.gain(2, 0.0);
  mixerFilterMod2.gain(0, 0.5) ;
  mixerFilterMod2.gain(1, 0.5) ;

  mixerVoice3.gain(0, MIXER_CONSTANT);
  mixerVoice3.gain(1, MIXER_CONSTANT);
  mixerVoice3.gain(2, MIXER_CONSTANT);
  mixerVoice3.gain(3, 0.0);
  mixerFilter3.gain(0, 1.0);
  mixerFilter3.gain(1, 0.0);
  mixerFilter3.gain(2, 0.0);
  mixerFilterMod3.gain(0, 0.5) ;
  mixerFilterMod3.gain(1, 0.5) ;

  mixerVoice4.gain(0, MIXER_CONSTANT);
  mixerVoice4.gain(1, MIXER_CONSTANT);
  mixerVoice4.gain(2, MIXER_CONSTANT);
  mixerVoice4.gain(3, 0.0);
  mixerFilter4.gain(0, 1.0);
  mixerFilter4.gain(1, 0.0);
  mixerFilter4.gain(2, 0.0);
  mixerFilterMod4.gain(0, 0.5) ;
  mixerFilterMod4.gain(1, 0.5) ;

  mixerMaster.gain(0, MIXER_CONSTANT) ;
  mixerMaster.gain(1, MIXER_CONSTANT) ;
  mixerMaster.gain(2, MIXER_CONSTANT) ;
  mixerMaster.gain(3, MIXER_CONSTANT) ;

  mixerAmp.gain(0, 1.0) ;
  mixerAmp.gain(1, 0.0) ;

  mixerDigitalFX.gain(0, 1.0) ;
  mixerDigitalFX.gain(1, 0.0) ;
  mixerFXIn.gain(0, 1.0) ;
  mixerFXIn.gain(1, 0.0) ;
  mixerFXIn.gain(2, 0.0) ;

  digitalFX.setCombineMode(0) ;
  delayFX.delay(0, 5) ;
  dcFX.amplitude(0.7) ;

  mixerFreeverb.gain(0, 1.0) ;
  mixerFreeverb.gain(1, 0.0) ;
}

void loop() {
  usbMIDI.read(); 
  MIDI.read() ;
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

  int a ;
  AudioNoInterrupts() ;
  switch (control) {
    case 5:
      if (value <= 64) {
        x = value * DIV64 ;
        x = 600 * DIV12 * x ;
      } else {
        x = (value-64) * DIV64 ;
        x = DIV12 * (600 + (x * 3400)) ;
      }
      portamentoAmt = x ;

      y = 12 * DETUNE_RANGE * portamentoAmt ;
      z = abs(y * dcPort1.read()) ;
      dcPort1.amplitude(dcPort1.read()) ;
      dcPort1.amplitude(0.0, z) ;
      z = abs(y * dcPort2.read()) ;
      dcPort2.amplitude(dcPort2.read()) ;
      dcPort2.amplitude(0.0, z) ;
      z = abs(y * dcPort3.read()) ;
      dcPort3.amplitude(dcPort3.read()) ;
      dcPort3.amplitude(0.0, z) ;
      z = abs(y * dcPort4.read()) ;
      dcPort4.amplitude(dcPort4.read()) ;
      dcPort4.amplitude(0.0, z) ;      
    break;
    case 10: 
      x = value * DIV127 ;
      sgtl5000_1.volume(x) ;
    break;
    case 11:
      x = MIXER_CONSTANT * value * DIV127 ;
      mixerVoice1.gain(2, x);
      mixerVoice2.gain(2, x);
      mixerVoice3.gain(2, x);
      mixerVoice4.gain(2, x);
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
      mixerVoice1.gain(3, x);
      mixerVoice2.gain(3, x);
      mixerVoice3.gain(3, x);
      mixerVoice4.gain(3, x);
    break;
    case 15:
      x = value * DIV127 ;
      a = x * 5 ;
      switch(a) {
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
        case 5: 
          osc1Voice1.begin(WAVEFORM_ARBITRARY) ;
          osc1Voice2.begin(WAVEFORM_ARBITRARY) ;
          osc1Voice3.begin(WAVEFORM_ARBITRARY) ;
          osc1Voice4.begin(WAVEFORM_ARBITRARY) ;
        break;
      }
    break;
    case 16:
      x = value * DIV127 ;
      a = x * 5 ;
      switch(a) {
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
        case 5: 
          osc2Voice1.begin(WAVEFORM_ARBITRARY) ;
          osc2Voice2.begin(WAVEFORM_ARBITRARY) ;
          osc2Voice3.begin(WAVEFORM_ARBITRARY) ;
          osc2Voice4.begin(WAVEFORM_ARBITRARY) ;
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
      if (value <= 100) {
        x = value * DIV100 ;
        x = DETUNE_CONSTANT * DIV12 * x ;
      } else if (value <= 112) {
        x = value - 100 ;
        x = DETUNE_CONSTANT * x * DIV12 ;
      } else {
        x = DETUNE_CONSTANT ;
      }
      dcTuner3.amplitude(x) ;
    break;
    case 32:
      if (value <= 100) {
        x = value * DIV100 ;
        x = -DETUNE_CONSTANT * DIV12 * x ;
      } else if (value <= 112) {
        x = value - 100 ;
        x = -DETUNE_CONSTANT * x * DIV12 ;
      } else {
        x = -DETUNE_CONSTANT ;
      }
      dcTuner3.amplitude(x) ;
    break ;
    case 33:
      x = value * DIV127 ;
      freeverb.roomsize(x) ;
    break ;
    case 34:
      x = value * DIV127 ;
      freeverb.damping(x) ;
    break ;
    case 35:
      x = value * DIV127 ;
      y = 1 - x ;
      mixerFreeverb.gain(0, y) ;
      mixerFreeverb.gain(1, x) ;
    break ;
    case 36:
      a = 3 * value * DIV127 ;
      
      switch(a) {
        case 0:
          digitalFX.setCombineMode(0) ;
        break;
        case 1:
          digitalFX.setCombineMode(1) ;
        break;
        case 2:
          digitalFX.setCombineMode(2) ;
        break;
        case 3:
          digitalFX.setCombineMode(3) ;
        break;   
      }
    break ;
    case 37:
      x = value * DIV127 ;
      y = 1 - x ;
      mixerDigitalFX.gain(0, y) ;
      mixerDigitalFX.gain(1, x) ;
    break ;
    case 38:
      a = 2 * value * DIV127 ;
      switch(a) {
        case 0:
          mixerFXIn.gain(0, 1.0) ;
          mixerFXIn.gain(1, 0.0) ;
          mixerFXIn.gain(2, 0.0) ;
        break;
        case 1:
          mixerFXIn.gain(0, 0.0) ;
          mixerFXIn.gain(1, 1.0) ;
          mixerFXIn.gain(2, 0.0) ;
        break;
        case 2:
          mixerFXIn.gain(0, 0.0) ;
          mixerFXIn.gain(1, 0.0) ;
          mixerFXIn.gain(2, 1.0) ;
        break;
      }
      
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
      x = value * DIV127 ;
      a = x * 5 ;
      switch(a) {
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
        case 5: 
          pitchLFO.begin(WAVEFORM_SAMPLE_HOLD) ;
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
      x = value * DIV127 ;
      a = x * 5 ;
      switch(a) {
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
        case 5: 
          filterLFO.begin(WAVEFORM_SAMPLE_HOLD) ;
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
      x = value * DIV127 ;
      a = x * 5 ;
      switch(a) {
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
        case 5: 
          ampLFO.begin(WAVEFORM_SAMPLE_HOLD) ;
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
    case 75:
      x = value * DIV127 ;
      a = x * 5 ;
      switch(a) {
        case 0: 
         digitalFXWave.begin(WAVEFORM_SINE) ;
        break;
        case 1: 
          digitalFXWave.begin(WAVEFORM_SAWTOOTH) ;
        break;
        case 2: 
          digitalFXWave.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
        break;
        case 3:
          digitalFXWave.begin(WAVEFORM_SQUARE) ;
        break;
        case 4: 
          digitalFXWave.begin(WAVEFORM_TRIANGLE) ;
        break;
        case 5: 
          digitalFXWave.begin(WAVEFORM_SAMPLE_HOLD) ;
        break;
      }
    break;
    case 76:
      x = value * DIV127 ;
      x = pow(4, x) - 1 ;
      x = x * DIV3 ;
      x = x * 25 ;
      digitalFXWave.frequency(x);
    break;
    case 77:
      x = value * DIV127 ;
      
      digitalFXWave.amplitude(x);
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
      sin1Voice1.frequency(noteFreqs[note]) ;
      envelopeVoice1.noteOn() ;
      envelopeFilter1.noteOn() ;
      osc1Voice1.amplitude(amp) ;
      osc2Voice1.amplitude(amp) ;
      sin1Voice1.amplitude(amp) ;
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
      sin1Voice2.frequency(noteFreqs[note]) ;
      osc1Voice2.amplitude(amp) ;
      osc2Voice2.amplitude(amp) ;
      sin1Voice2.amplitude(amp) ;
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
      sin1Voice3.frequency(noteFreqs[note]) ;
      osc1Voice3.amplitude(amp) ;
      osc2Voice3.amplitude(amp) ;
      sin1Voice3.amplitude(amp) ;
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
      sin1Voice4.frequency(noteFreqs[note]) ;
      osc1Voice4.amplitude(amp) ;
      osc2Voice4.amplitude(amp) ;
      sin1Voice4.amplitude(amp) ;
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
