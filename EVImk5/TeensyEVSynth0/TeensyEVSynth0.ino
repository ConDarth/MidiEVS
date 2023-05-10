#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   VibratoLFO;          //xy=65.5,118.75000381469727
AudioSynthWaveformDc     PitchBendDC;            //xy=72,313
AudioSynthWaveformDc     VibratoExpDC;            //xy=74,278.75000381469727
AudioSynthWaveformDc     PortamentoDC;            //xy=76.5,347
AudioEffectEnvelope      VibratoEnv;      //xy=207.50000190734863,118.75000190734863
AudioEffectMultiply      VibratoAmp;      //xy=291.2500190734863,271.25000381469727
AudioMixer4              GlobalPitchMixer;         //xy=463.9999771118164,317
AudioSynthWaveformDc     RectDutyCycleDC;            //xy=601.9999771118164,61
AudioSynthWaveformSine   RectLFO;          //xy=623.9999771118164,20
AudioSynthWaveformDc     TriangleDetuneDC;            //xy=624.9999771118164,464
AudioSynthWaveformDc     RectDetuneDC;            //xy=629.9999771118164,141
AudioSynthWaveformDc     RampDetuneDC;            //xy=629.9999771118164,246
AudioSynthWaveformDc     SquareDetuneDC;            //xy=633.9999771118164,356
AudioSynthWaveformSine   TremeloLFO;          //xy=802.1666946411133,593.1666946411133
AudioMixer4              RectShapeMixer;         //xy=816.9999771118164,49
AudioMixer4              RectPitchMixer;         //xy=819.9999771118164,162
AudioMixer4              RampPitchMixer;         //xy=819.9999771118164,266
AudioMixer4              SquarePitchMixer;         //xy=825.9999771118164,376
AudioMixer4              TrianglePitchMixer;         //xy=831.9999771118164,483
AudioSynthWaveformDc     TremeloExpDC;           //xy=868.7500076293945,631.2500095367432
AudioSynthWaveformDc     BreathExpDC;            //xy=919.9721145629883,813.1388664245605
AudioEffectEnvelope      TremeloEnv;      //xy=950.0000076293945,592.5000085830688
AudioSynthWaveformModulated RectWave;   //xy=1022.9999771118164,167
AudioSynthWaveformModulated SquareWave;   //xy=1025.9999771118164,382
AudioSynthWaveformModulated TriangleWave;   //xy=1025.9999771118164,488
AudioSynthWaveformModulated RampWave;   //xy=1029.9999771118164,272
AudioEffectEnvelope      BreathEnv;      //xy=1070.6944046020508,810.8888673782349
AudioEffectMultiply      TremeloAmp;      //xy=1111.2500076293945,600.0000095367432
AudioMixer4              VolumeMixer;         //xy=1281.6667556762695,607.1666965484619
AudioMixer4              MainMixer;         //xy=1288.9999771118164,321
AudioEffectMultiply      VolumeExpAmp;      //xy=1494.000015258789,327.5000057220459
AudioSynthWaveformDc     ResonanceDC;           //xy=1501.7500190734863,398.5000057220459
AudioFilterLadder        BreathFilter;        //xy=1691.7500190734863,338.5000057220459
AudioSynthWaveformDc     VolumeDC;           //xy=1697.5000228881836,412.5000066757202
AudioEffectMultiply      VolumeAmp;      //xy=1892.5000267028809,345.0000057220459
AudioEffectChorus        Chorus;        //xy=2037.5000305175781,345.0000057220459
AudioEffectDelay         Delay;         //xy=2173.7500324249268,343.75000381469727
AudioMixer4              DelayMixer;         //xy=2322.5000343322754,318.7500057220459
AudioEffectFreeverbStereo Reverb;     //xy=2471.2500381469727,318.7500057220459
AudioOutputI2S           AudioOut;           //xy=2600.0000381469727,318.75000381469727
AudioConnection          patchCord1(VibratoLFO, VibratoEnv);
AudioConnection          patchCord2(PitchBendDC, 0, GlobalPitchMixer, 1);
AudioConnection          patchCord3(VibratoExpDC, 0, VibratoAmp, 1);
AudioConnection          patchCord4(PortamentoDC, 0, GlobalPitchMixer, 2);
AudioConnection          patchCord5(VibratoEnv, 0, VibratoAmp, 0);
AudioConnection          patchCord6(VibratoAmp, 0, GlobalPitchMixer, 0);
AudioConnection          patchCord7(GlobalPitchMixer, 0, RectPitchMixer, 1);
AudioConnection          patchCord8(GlobalPitchMixer, 0, RampPitchMixer, 1);
AudioConnection          patchCord9(GlobalPitchMixer, 0, SquarePitchMixer, 1);
AudioConnection          patchCord10(GlobalPitchMixer, 0, TrianglePitchMixer, 1);
AudioConnection          patchCord11(RectDutyCycleDC, 0, RectShapeMixer, 1);
AudioConnection          patchCord12(RectLFO, 0, RectShapeMixer, 0);
AudioConnection          patchCord13(TriangleDetuneDC, 0, TrianglePitchMixer, 0);
AudioConnection          patchCord14(RectDetuneDC, 0, RectPitchMixer, 0);
AudioConnection          patchCord15(RampDetuneDC, 0, RampPitchMixer, 0);
AudioConnection          patchCord16(SquareDetuneDC, 0, SquarePitchMixer, 0);
AudioConnection          patchCord17(TremeloLFO, TremeloEnv);
AudioConnection          patchCord18(RectShapeMixer, 0, RectWave, 1);
AudioConnection          patchCord19(RectPitchMixer, 0, RectWave, 0);
AudioConnection          patchCord20(RampPitchMixer, 0, RampWave, 0);
AudioConnection          patchCord21(SquarePitchMixer, 0, SquareWave, 0);
AudioConnection          patchCord22(TrianglePitchMixer, 0, TriangleWave, 0);
AudioConnection          patchCord23(TremeloExpDC, 0, TremeloAmp, 1);
AudioConnection          patchCord24(BreathExpDC, BreathEnv);
AudioConnection          patchCord25(TremeloEnv, 0, TremeloAmp, 0);
AudioConnection          patchCord26(RectWave, 0, MainMixer, 0);
AudioConnection          patchCord27(SquareWave, 0, MainMixer, 2);
AudioConnection          patchCord28(TriangleWave, 0, MainMixer, 3);
AudioConnection          patchCord29(RampWave, 0, MainMixer, 1);
AudioConnection          patchCord30(BreathEnv, 0, VolumeMixer, 2);
AudioConnection          patchCord31(BreathEnv, 0, BreathFilter, 1);
AudioConnection          patchCord32(TremeloAmp, 0, VolumeMixer, 1);
AudioConnection          patchCord33(VolumeMixer, 0, VolumeExpAmp, 1);
AudioConnection          patchCord34(MainMixer, 0, VolumeExpAmp, 0);
AudioConnection          patchCord35(VolumeExpAmp, 0, BreathFilter, 0);
AudioConnection          patchCord36(ResonanceDC, 0, BreathFilter, 2);
AudioConnection          patchCord37(BreathFilter, 0, VolumeAmp, 0);
AudioConnection          patchCord38(VolumeDC, 0, VolumeAmp, 1);
AudioConnection          patchCord39(VolumeAmp, Chorus);
AudioConnection          patchCord40(Chorus, Delay);
AudioConnection          patchCord41(Delay, 0, DelayMixer, 0);
AudioConnection          patchCord42(Delay, 1, DelayMixer, 1);
AudioConnection          patchCord43(Delay, 2, DelayMixer, 2);
AudioConnection          patchCord44(Delay, 3, DelayMixer, 3);
AudioConnection          patchCord45(DelayMixer, Reverb);
AudioConnection          patchCord46(Reverb, 0, AudioOut, 0);
AudioConnection          patchCord47(Reverb, 1, AudioOut, 1);
// GUItool: end automatically generated code


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
