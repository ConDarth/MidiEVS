#include "AudioStream.h"

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Audio.h>


// GUItool: begin automatically generated code
AudioMixer4              VibratoLink;        //xy=202.78559112548828,558.8426055908203
AudioSynthWaveformDc     Expression;           //xy=279.24852752685547,1014.0554962158203
AudioSynthWaveformDc     Breath;            //xy=282.8040237426758,867.3888702392578
AudioSynthWaveformDc     Mod;           //xy=308.35962677001953,1129.8336639404297
AudioAmplifier           VibratoLinkFrq;           //xy=376.3966751098633,496.2036590576172
AudioSynthWaveformDc     VibratoLinkAmtDC;            //xy=397.6929702758789,581.6667022705078
AudioEffectWaveshaper    waveshape2;     //xy=419.8040237426758,868.3888397216797
AudioEffectWaveshaper    waveshape4;     //xy=439.35962677001953,1130.8335418701172
AudioEffectWaveshaper    waveshape3;     //xy=440.35962677001953,1012.8332672119141
AudioSynthWaveformModulated VibratoLFO;   //xy=545.0263481140137,504.0117130279541
AudioFilterStateVariable BreathFilter;        //xy=574.8040237426758,875.3888397216797
AudioMixer4              VibratoLinkAmtMix;        //xy=600.8411331176758,575.6481170654297
AudioEffectEnvelope      VibratoEnv;      //xy=693.7839012145996,505.3888187408447
AudioEffectMultiply      VibratoLinkAmt;      //xy=866.9521713256836,512.3147249221802
AudioSynthWaveformDc     Note;            //xy=903.7838668823242,616.8333282470703
AudioSynthWaveformDc     Pitchbend;           //xy=909.7838668823242,578.8332977294922
AudioMixer4              TuneMix;         //xy=1056.3596267700195,584.8332824707031
AudioSynthWaveformDc     TriTune; //xy=1173.0262069702148,679.1665802001953
AudioSynthWaveformDc     SqrTune; //xy=1184.0262069702148,604.8332672119141
AudioSynthWaveformDc     SawTune; //xy=1185.0262069702148,532.4999542236328
AudioSynthWaveformDc     PulTune;            //xy=1186.0262069702148,458.4999237060547
AudioSynthWaveformModulated PulLFO;   //xy=1210.1742630004883,303.92588806152344
AudioSynthWaveformDc     PulRNG;            //xy=1212.3596267700195,377.8333282470703
AudioSynthWaveformDc     PulDC;            //xy=1212.942756652832,341.1665496826172
AudioMixer4              TriTuneMix; //xy=1354.0261917114258,698.1665802001953
AudioMixer4              PulTuneMix;         //xy=1358.0261917114258,476.4999237060547
AudioMixer4              SawTuneMix; //xy=1360.0261917114258,551.1666107177734
AudioMixer4              SqrTuneMix; //xy=1362.0261917114258,623.1666107177734
AudioMixer4              PulModMix;         //xy=1366.4428176879883,347.91658782958984
AudioSynthWaveformModulated SawWave;        //xy=1560.0261764526367,560.4999542236328
AudioSynthWaveformModulated SqrWave;        //xy=1561.0261764526367,621.4999542236328
AudioSynthWaveformModulated PulWave;       //xy=1566.0261764526367,477.4999542236328
AudioSynthWaveformModulated TriWave;       //xy=1570.0261764526367,693.4999542236328
AudioSynthNoisePink      PinkWave;          //xy=1737.3596267700195,651.8332977294922
AudioMixer4              WaveMix;        //xy=1743.0261764526367,600.4999542236328
AudioSynthWaveformDc     FilterFrqRNG;            //xy=1796.103172302246,739.1153907775879
AudioSynthWaveformDc     FilterFrqNote;           //xy=1796.6300964355469,771.4651412963867
AudioSynthWaveformDc     FilterFrqAmt;           //xy=1798.717872619629,804.1025667190552
AudioSynthWaveformDc     FilterResRNG; //xy=1816.8467712402344,865.5256643295288
AudioMixer4              TremeloLink;        //xy=1887.554214477539,1189.3056411743164
AudioMixer4              WaveMixFX;         //xy=1896.396583557129,618.9813709259033
AudioMixer4              FilterFrqMix;         //xy=1968.0262832641602,741.5000038146973
AudioMixer4              FilterResMix;         //xy=1973.5649185180664,862.9615383148193
AudioAmplifier           Amp;           //xy=1989.3331298828125,2284.3328857421875
AudioEffectEnvelope      MainEnv;       //xy=2059.740524291992,613.4642372131348
AudioAmplifier           TremeloLinkFrq;           //xy=2093.804153442383,1125.5556411743164
AudioSynthWaveformDc     TremeloLinkAmtDC;           //xy=2114.3595962524414,1220.2777080535889
AudioFilterStateVariable FormantF3;        //xy=2192.0472412109375,2428.333251953125
AudioFilterStateVariable FormantF1;        //xy=2192.618797302246,2328.476007461548
AudioFilterStateVariable FormantF2;        //xy=2192.4757080078125,2379.475830078125
AudioFilterLadder        MainFilter;        //xy=2229.1691665649414,619.7499351501465
AudioSynthWaveformModulated TremeloLFO;   //xy=2260.2212677001953,1131.2221450805664
AudioSynthWaveformDc     VolumePreAmpDC;            //xy=2330.4700317382812,883.277717590332
AudioMixer4              TremeloLinkAmtMix;        //xy=2336.304153442383,1211.8055801391602
AudioAmplifier           FormantL2;  //xy=2337,2381.66650390625
AudioAmplifier           FormantL1;           //xy=2338.3330078125,2329.3328857421875
AudioAmplifier           FormantL3; //xy=2341,2431.66650390625
AudioSynthWaveformDc     VolumeRNG;            //xy=2348.9700927734375,925.527717590332
AudioEffectWaveshaper    waveshape1;     //xy=2378.2485847473145,593.0554795265198
AudioEffectEnvelope      TremeloEnv;      //xy=2412.221145629883,1131.2221450805664
AudioMixer4              VolumePreAmpMix;         //xy=2543.4699096679688,931.2777786254883
AudioMixer4              FormantMix;        //xy=2549.047508239746,2299.0478172302246
AudioMixer4              WaveshapeMix;         //xy=2557.0261001586914,624.7499465942383
AudioEffectMultiply      TremeloLinkAmt;      //xy=2581.304397583008,1138.055519104004
AudioSynthWaveformDc     TremeloDC;           //xy=2593.2484397888184,1093.0554494857788
AudioEffectDelay         MainDelay;         //xy=2734.952579498291,2470.6667098999023
AudioMixer4              TremeloMix;        //xy=2751.5819206237793,1143.0554733276367
AudioEffectMultiply      VolumePreAmpMult;      //xy=2789.359931945801,630.8332977294922
AudioMixer4              DelayFeedbackMix;        //xy=2827.61873626709,2310.4764499664307
AudioFilterLadder        DelayFilter;        //xy=2903.3332901000977,2437.6194591522217
AudioEffectMultiply      TremeloMult;      //xy=2988.2486724853516,636.3888339996338
AudioEffectFreeverbStereo Freeverb;     //xy=3076.9069213867188,2310.833282470703
AudioMixer4              FreeverbMixLeft;         //xy=3264.9069213867188,2286.833251953125
AudioMixer4              FreeverbMixRight; //xy=3266.240234375,2355.1666259765625
AudioAmplifier           LineLeftAmp;      //xy=3504.90673828125,2140.8333129882812
AudioMixer4              SpeakerMix;        //xy=3508.739990234375,2493.1666870117188
AudioAmplifier           LineRightAmp;           //xy=3511.906982421875,2181.8333129882812
AudioOutputPT8211        LineOut;       //xy=3671.332763671875,2156.4259643554688
AudioFilterStateVariable Speaker80HzFilter;        //xy=3773.7400665283203,2386.1666412353516
AudioFilterStateVariable Speaker320HzFilter;        //xy=3774.739990234375,2481.1666259765625
AudioFilterStateVariable Speaker640HzFilter;        //xy=3774.739990234375,2529.1666259765625
AudioFilterStateVariable Speaker40HzFilter;        //xy=3775.739990234375,2340.1666259765625
AudioFilterStateVariable Speaker160HzFilter;        //xy=3775.739990234375,2434.1666259765625
AudioFilterBiquad        Speaker1280HzFilter;        //xy=3777.739990234375,2567.1666259765625
AudioFilterBiquad        Speaker2560HzFilter;        //xy=3778.739990234375,2600.1666259765625
AudioFilterBiquad        Speaker5120HzFilter;        //xy=3778.739990234375,2633.1666259765625
AudioFilterBiquad        Speaker10240HzFilter;        //xy=3782.739990234375,2666.1666259765625
AudioFilterBiquad        Speaker20480HzFilter;        //xy=3784.739990234375,2698.1666259765625
AudioAmplifier           Speaker40HzAmp;           //xy=3979.739990234375,2327.1666564941406
AudioAmplifier           Speaker80HzAmp; //xy=3982.40673828125,2386.8333435058594
AudioAmplifier           Speaker160HzAmp; //xy=3989.40673828125,2435.8333435058594
AudioAmplifier           Speaker320HzAmp; //xy=3989.40673828125,2482.8333435058594
AudioAmplifier           Speaker640HzAmp; //xy=3991.40673828125,2530.8333435058594
AudioAmplifier           Speaker1280HzAmp; //xy=3994.40673828125,2566.8333435058594
AudioAmplifier           Speaker2560HzAmp; //xy=3999.40673828125,2601.8333435058594
AudioAmplifier           Speaker20480HzAmp; //xy=4000.40673828125,2699.8333129882812
AudioAmplifier           Speaker5120HzAmp; //xy=4001.40673828125,2633.8333129882812
AudioAmplifier           Speaker10240HzAmp; //xy=4002.40673828125,2666.8333129882812
AudioMixer4              SpeakerLowMix;        //xy=4211.740234375,2415.1666564941406
AudioMixer4              SpeakerMidMix;        //xy=4218.740234375,2546.166717529297
AudioMixer4              SpeakerHighMix;        //xy=4228.740478515625,2651.166717529297
AudioMixer4              SpeakerEQMix;        //xy=4408.740234375,2552.1666564941406
AudioAmplifier           SpeakerAmp;           //xy=4575.740234375,2553.1666564941406
AudioOutputPT8211_2      SpeakerOut;     //xy=4737.311859130859,2555.166851043701
AudioConnection          patchCord1(VibratoLink, VibratoLinkFrq);
AudioConnection          patchCord2(VibratoLink, 0, VibratoLinkAmtMix, 0);
AudioConnection          patchCord3(Expression, waveshape3);
AudioConnection          patchCord4(Breath, waveshape2);
AudioConnection          patchCord5(Mod, waveshape4);
AudioConnection          patchCord6(VibratoLinkFrq, 0, VibratoLFO, 0);
AudioConnection          patchCord7(VibratoLinkAmtDC, 0, VibratoLinkAmtMix, 1);
AudioConnection          patchCord8(waveshape2, 0, BreathFilter, 0);
AudioConnection          patchCord9(waveshape4, 0, VibratoLink, 2);
AudioConnection          patchCord10(waveshape4, 0, TremeloLink, 2);
AudioConnection          patchCord11(waveshape3, 0, VibratoLink, 1);
AudioConnection          patchCord12(waveshape3, 0, TremeloLink, 1);
AudioConnection          patchCord13(VibratoLFO, VibratoEnv);
AudioConnection          patchCord14(BreathFilter, 0, VibratoLink, 0);
AudioConnection          patchCord15(BreathFilter, 0, TremeloLink, 0);
AudioConnection          patchCord16(BreathFilter, 0, FilterFrqMix, 0);
AudioConnection          patchCord17(BreathFilter, 0, FilterResMix, 0);
AudioConnection          patchCord18(BreathFilter, 0, VolumePreAmpMix, 2);
AudioConnection          patchCord19(VibratoLinkAmtMix, 0, VibratoLinkAmt, 1);
AudioConnection          patchCord20(VibratoEnv, 0, VibratoLinkAmt, 0);
AudioConnection          patchCord21(VibratoLinkAmt, 0, TuneMix, 0);
AudioConnection          patchCord22(Note, 0, TuneMix, 2);
AudioConnection          patchCord23(Pitchbend, 0, TuneMix, 1);
AudioConnection          patchCord24(TuneMix, 0, PulTuneMix, 1);
AudioConnection          patchCord25(TuneMix, 0, SawTuneMix, 1);
AudioConnection          patchCord26(TuneMix, 0, SqrTuneMix, 1);
AudioConnection          patchCord27(TuneMix, 0, TriTuneMix, 1);
AudioConnection          patchCord28(TriTune, 0, TriTuneMix, 0);
AudioConnection          patchCord29(SqrTune, 0, SqrTuneMix, 0);
AudioConnection          patchCord30(SawTune, 0, SawTuneMix, 0);
AudioConnection          patchCord31(PulTune, 0, PulTuneMix, 0);
AudioConnection          patchCord32(PulLFO, 0, PulModMix, 0);
AudioConnection          patchCord33(PulRNG, 0, PulModMix, 2);
AudioConnection          patchCord34(PulDC, 0, PulModMix, 1);
AudioConnection          patchCord35(TriTuneMix, 0, TriWave, 0);
AudioConnection          patchCord36(PulTuneMix, 0, PulWave, 0);
AudioConnection          patchCord37(SawTuneMix, 0, SawWave, 0);
AudioConnection          patchCord38(SqrTuneMix, 0, SqrWave, 0);
AudioConnection          patchCord39(PulModMix, 0, PulWave, 1);
AudioConnection          patchCord40(SawWave, 0, WaveMix, 1);
AudioConnection          patchCord41(SqrWave, 0, WaveMix, 2);
AudioConnection          patchCord42(PulWave, 0, WaveMix, 0);
AudioConnection          patchCord43(TriWave, 0, WaveMix, 3);
AudioConnection          patchCord44(PinkWave, 0, WaveMixFX, 1);
AudioConnection          patchCord45(WaveMix, 0, WaveMixFX, 0);
AudioConnection          patchCord46(FilterFrqRNG, 0, FilterFrqMix, 1);
AudioConnection          patchCord47(FilterFrqNote, 0, FilterFrqMix, 2);
AudioConnection          patchCord48(FilterFrqAmt, 0, FilterFrqMix, 3);
AudioConnection          patchCord49(FilterResRNG, 0, FilterResMix, 1);
AudioConnection          patchCord50(TremeloLink, TremeloLinkFrq);
AudioConnection          patchCord51(TremeloLink, 0, TremeloLinkAmtMix, 0);
AudioConnection          patchCord52(WaveMixFX, MainEnv);
AudioConnection          patchCord53(FilterFrqMix, 0, MainFilter, 1);
AudioConnection          patchCord54(FilterResMix, 0, MainFilter, 2);
AudioConnection          patchCord55(Amp, 0, FormantF1, 0);
AudioConnection          patchCord56(Amp, 0, FormantF2, 0);
AudioConnection          patchCord57(Amp, 0, FormantF3, 0);
AudioConnection          patchCord58(Amp, 0, FormantMix, 0);
AudioConnection          patchCord59(MainEnv, 0, MainFilter, 0);
AudioConnection          patchCord60(TremeloLinkFrq, 0, TremeloLFO, 0);
AudioConnection          patchCord61(TremeloLinkAmtDC, 0, TremeloLinkAmtMix, 1);
AudioConnection          patchCord62(FormantF3, 1, FormantL3, 0);
AudioConnection          patchCord63(FormantF1, 1, FormantL1, 0);
AudioConnection          patchCord64(FormantF2, 1, FormantL2, 0);
AudioConnection          patchCord65(MainFilter, 0, WaveshapeMix, 1);
AudioConnection          patchCord66(MainFilter, waveshape1);
AudioConnection          patchCord67(TremeloLFO, TremeloEnv);
AudioConnection          patchCord68(VolumePreAmpDC, 0, VolumePreAmpMix, 0);
AudioConnection          patchCord69(TremeloLinkAmtMix, 0, TremeloLinkAmt, 1);
AudioConnection          patchCord70(FormantL2, 0, FormantMix, 2);
AudioConnection          patchCord71(FormantL1, 0, FormantMix, 1);
AudioConnection          patchCord72(FormantL3, 0, FormantMix, 3);
AudioConnection          patchCord73(VolumeRNG, 0, VolumePreAmpMix, 1);
AudioConnection          patchCord74(waveshape1, 0, WaveshapeMix, 0);
AudioConnection          patchCord75(TremeloEnv, 0, TremeloLinkAmt, 0);
AudioConnection          patchCord76(VolumePreAmpMix, 0, VolumePreAmpMult, 1);
AudioConnection          patchCord77(FormantMix, 0, DelayFeedbackMix, 0);
AudioConnection          patchCord78(WaveshapeMix, 0, VolumePreAmpMult, 0);
AudioConnection          patchCord79(TremeloLinkAmt, 0, TremeloMix, 1);
AudioConnection          patchCord80(TremeloDC, 0, TremeloMix, 0);
AudioConnection          patchCord81(MainDelay, 0, DelayFilter, 0);
AudioConnection          patchCord82(TremeloMix, 0, TremeloMult, 1);
AudioConnection          patchCord83(VolumePreAmpMult, 0, TremeloMult, 0);
AudioConnection          patchCord84(DelayFeedbackMix, MainDelay);
AudioConnection          patchCord85(DelayFeedbackMix, Freeverb);
AudioConnection          patchCord86(DelayFeedbackMix, 0, FreeverbMixLeft, 1);
AudioConnection          patchCord87(DelayFeedbackMix, 0, FreeverbMixRight, 1);
AudioConnection          patchCord88(DelayFilter, 0, DelayFeedbackMix, 1);
AudioConnection          patchCord89(TremeloMult, Amp);
AudioConnection          patchCord90(Freeverb, 0, FreeverbMixLeft, 0);
AudioConnection          patchCord91(Freeverb, 1, FreeverbMixRight, 0);
AudioConnection          patchCord92(FreeverbMixLeft, LineLeftAmp);
AudioConnection          patchCord93(FreeverbMixLeft, 0, SpeakerMix, 0);
AudioConnection          patchCord94(FreeverbMixRight, LineRightAmp);
AudioConnection          patchCord95(FreeverbMixRight, 0, SpeakerMix, 1);
AudioConnection          patchCord96(LineLeftAmp, 0, LineOut, 0);
AudioConnection          patchCord97(SpeakerMix, 0, Speaker80HzFilter, 0);
AudioConnection          patchCord98(SpeakerMix, 0, Speaker160HzFilter, 0);
AudioConnection          patchCord99(SpeakerMix, 0, Speaker320HzFilter, 0);
AudioConnection          patchCord100(SpeakerMix, 0, Speaker640HzFilter, 0);
AudioConnection          patchCord101(SpeakerMix, Speaker1280HzFilter);
AudioConnection          patchCord102(SpeakerMix, Speaker2560HzFilter);
AudioConnection          patchCord103(SpeakerMix, Speaker5120HzFilter);
AudioConnection          patchCord104(SpeakerMix, Speaker10240HzFilter);
AudioConnection          patchCord105(SpeakerMix, Speaker20480HzFilter);
AudioConnection          patchCord106(SpeakerMix, 0, Speaker40HzFilter, 0);
AudioConnection          patchCord107(LineRightAmp, 0, LineOut, 1);
AudioConnection          patchCord108(Speaker80HzFilter, 1, Speaker80HzAmp, 0);
AudioConnection          patchCord109(Speaker320HzFilter, 1, Speaker320HzAmp, 0);
AudioConnection          patchCord110(Speaker640HzFilter, 1, Speaker640HzAmp, 0);
AudioConnection          patchCord111(Speaker40HzFilter, 0, Speaker40HzAmp, 0);
AudioConnection          patchCord112(Speaker160HzFilter, 1, Speaker160HzAmp, 0);
AudioConnection          patchCord113(Speaker1280HzFilter, Speaker1280HzAmp);
AudioConnection          patchCord114(Speaker2560HzFilter, Speaker2560HzAmp);
AudioConnection          patchCord115(Speaker5120HzFilter, Speaker5120HzAmp);
AudioConnection          patchCord116(Speaker10240HzFilter, Speaker10240HzAmp);
AudioConnection          patchCord117(Speaker20480HzFilter, Speaker20480HzAmp);
AudioConnection          patchCord118(Speaker40HzAmp, 0, SpeakerLowMix, 0);
AudioConnection          patchCord119(Speaker80HzAmp, 0, SpeakerLowMix, 1);
AudioConnection          patchCord120(Speaker160HzAmp, 0, SpeakerLowMix, 2);
AudioConnection          patchCord121(Speaker320HzAmp, 0, SpeakerMidMix, 0);
AudioConnection          patchCord122(Speaker640HzAmp, 0, SpeakerMidMix, 1);
AudioConnection          patchCord123(Speaker1280HzAmp, 0, SpeakerMidMix, 2);
AudioConnection          patchCord124(Speaker2560HzAmp, 0, SpeakerMidMix, 3);
AudioConnection          patchCord125(Speaker20480HzAmp, 0, SpeakerHighMix, 3);
AudioConnection          patchCord126(Speaker5120HzAmp, 0, SpeakerHighMix, 1);
AudioConnection          patchCord127(Speaker10240HzAmp, 0, SpeakerHighMix, 2);
AudioConnection          patchCord128(SpeakerLowMix, 0, SpeakerEQMix, 0);
AudioConnection          patchCord129(SpeakerMidMix, 0, SpeakerEQMix, 1);
AudioConnection          patchCord130(SpeakerHighMix, 0, SpeakerEQMix, 2);
AudioConnection          patchCord131(SpeakerEQMix, SpeakerAmp);
AudioConnection          patchCord132(SpeakerAmp, 0, SpeakerOut, 0);
AudioConnection          patchCord133(SpeakerAmp, 0, SpeakerOut, 1);
// GUItool: end automatically generated code


//Extra Libraries 
#include <MIDI.h>
#include <Entropy.h>


//---------------------------------------------------Waveshape Arrays-----------------------------------------------------
//Note: Function must integrate to 0 from [-1,1] otherwise large click and pops
int waveshapeLen = 257 ;

float waveshapeLIN[257] = { 
	-1,	
	-0.9921875,	-0.984375,	-0.9765625,	-0.96875,	-0.9609375,	-0.953125,	-0.9453125,	-0.9375,	
	-0.9296875,	-0.921875,	-0.9140625,	-0.90625,	-0.8984375,	-0.890625,	-0.8828125,	-0.875,	
	-0.8671875,	-0.859375,	-0.8515625,	-0.84375,	-0.8359375,	-0.828125,	-0.8203125,	-0.8125,	
	-0.8046875,	-0.796875,	-0.7890625,	-0.78125,	-0.7734375,	-0.765625,	-0.7578125,	-0.75,	
	-0.7421875,	-0.734375,	-0.7265625,	-0.71875,	-0.7109375,	-0.703125,	-0.6953125,	-0.6875,	
	-0.6796875,	-0.671875,	-0.6640625,	-0.65625,	-0.6484375,	-0.640625,	-0.6328125,	-0.625,	
	-0.6171875,	-0.609375,	-0.6015625,	-0.59375,	-0.5859375,	-0.578125,	-0.5703125,	-0.5625,	
	-0.5546875,	-0.546875,	-0.5390625,	-0.53125,	-0.5234375,	-0.515625,	-0.5078125,	-0.5,	
	-0.4921875,	-0.484375,	-0.4765625,	-0.46875,	-0.4609375,	-0.453125,	-0.4453125,	-0.4375,	
	-0.4296875,	-0.421875,	-0.4140625,	-0.40625,	-0.3984375,	-0.390625,	-0.3828125,	-0.375,	
	-0.3671875,	-0.359375,	-0.3515625,	-0.34375,	-0.3359375,	-0.328125,	-0.3203125,	-0.3125,	
	-0.3046875,	-0.296875,	-0.2890625,	-0.28125,	-0.2734375,	-0.265625,	-0.2578125,	-0.25,	
	-0.2421875,	-0.234375,	-0.2265625,	-0.21875,	-0.2109375,	-0.203125,	-0.1953125,	-0.1875,	
	-0.1796875,	-0.171875,	-0.1640625,	-0.15625,	-0.1484375,	-0.140625,	-0.1328125,	-0.125,	
	-0.1171875,	-0.109375,	-0.1015625,	-0.09375,	-0.0859375,	-0.078125,	-0.0703125,	-0.0625,	
	-0.0546875,	-0.046875,	-0.0390625,	-0.03125,	-0.0234375,	-0.015625,	-0.0078125,	0,	
	0.0078125,	0.015625,	0.0234375,	0.03125,	0.0390625,	0.046875,	0.0546875,	0.0625,	
	0.0703125,	0.078125,	0.0859375,	0.09375,	0.1015625,	0.109375,	0.1171875,	0.125,	
	0.1328125,	0.140625,	0.1484375,	0.15625,	0.1640625,	0.171875,	0.1796875,	0.1875,	
	0.1953125,	0.203125,	0.2109375,	0.21875,	0.2265625,	0.234375,	0.2421875,	0.25,	
	0.2578125,	0.265625,	0.2734375,	0.28125,	0.2890625,	0.296875,	0.3046875,	0.3125,	
	0.3203125,	0.328125,	0.3359375,	0.34375,	0.3515625,	0.359375,	0.3671875,	0.375,	
	0.3828125,	0.390625,	0.3984375,	0.40625,	0.4140625,	0.421875,	0.4296875,	0.4375,	
	0.4453125,	0.453125,	0.4609375,	0.46875,	0.4765625,	0.484375,	0.4921875,	0.5,	
	0.5078125,	0.515625,	0.5234375,	0.53125,	0.5390625,	0.546875,	0.5546875,	0.5625,	
	0.5703125,	0.578125,	0.5859375,	0.59375,	0.6015625,	0.609375,	0.6171875,	0.625,	
	0.6328125,	0.640625,	0.6484375,	0.65625,	0.6640625,	0.671875,	0.6796875,	0.6875,	
	0.6953125,	0.703125,	0.7109375,	0.71875,	0.7265625,	0.734375,	0.7421875,	0.75,	
	0.7578125,	0.765625,	0.7734375,	0.78125,	0.7890625,	0.796875,	0.8046875,	0.8125,	
	0.8203125,	0.828125,	0.8359375,	0.84375,	0.8515625,	0.859375,	0.8671875,	0.875,	
	0.8828125,	0.890625,	0.8984375,	0.90625,	0.9140625,	0.921875,	0.9296875,	0.9375,	
	0.9453125,	0.953125,	0.9609375,	0.96875,	0.9765625,	0.984375,	0.9921875,	1,	
	
} ;

float waveshapeABS[257] = { 
	-1,	
	-0.98828125,	-0.9765625,	-0.96484375,	-0.953125,	-0.94140625,	-0.9296875,	-0.91796875,	-0.90625,	
	-0.89453125,	-0.8828125,	-0.87109375,	-0.859375,	-0.84765625,	-0.8359375,	-0.82421875,	-0.8125,	
	-0.80078125,	-0.7890625,	-0.77734375,	-0.765625,	-0.75390625,	-0.7421875,	-0.73046875,	-0.71875,	
	-0.70703125,	-0.6953125,	-0.68359375,	-0.671875,	-0.66015625,	-0.6484375,	-0.63671875,	-0.625,	
	-0.62109375,	-0.6171875,	-0.61328125,	-0.609375,	-0.60546875,	-0.6015625,	-0.59765625,	-0.59375,	
	-0.58984375,	-0.5859375,	-0.58203125,	-0.578125,	-0.57421875,	-0.5703125,	-0.56640625,	-0.5625,	
	-0.55859375,	-0.5546875,	-0.55078125,	-0.546875,	-0.54296875,	-0.5390625,	-0.53515625,	-0.53125,	
	-0.52734375,	-0.5234375,	-0.51953125,	-0.515625,	-0.51171875,	-0.5078125,	-0.50390625,	-0.5,	
	-0.49609375,	-0.4921875,	-0.48828125,	-0.484375,	-0.48046875,	-0.4765625,	-0.47265625,	-0.46875,	
	-0.46484375,	-0.4609375,	-0.45703125,	-0.453125,	-0.44921875,	-0.4453125,	-0.44140625,	-0.4375,	
	-0.43359375,	-0.4296875,	-0.42578125,	-0.421875,	-0.41796875,	-0.4140625,	-0.41015625,	-0.40625,	
	-0.40234375,	-0.3984375,	-0.39453125,	-0.390625,	-0.38671875,	-0.3828125,	-0.37890625,	-0.375,	
	-0.36328125,	-0.3515625,	-0.33984375,	-0.328125,	-0.31640625,	-0.3046875,	-0.29296875,	-0.28125,	
	-0.26953125,	-0.2578125,	-0.24609375,	-0.234375,	-0.22265625,	-0.2109375,	-0.19921875,	-0.1875,	
	-0.17578125,	-0.1640625,	-0.15234375,	-0.140625,	-0.12890625,	-0.1171875,	-0.10546875,	-0.09375,	
	-0.08203125,	-0.0703125,	-0.05859375,	-0.046875,	-0.03515625,	-0.0234375,	-0.01171875,	0,	
	0.01171875,	0.0234375,	0.03515625,	0.046875,	0.05859375,	0.0703125,	0.08203125,	0.09375,	
	0.10546875,	0.1171875,	0.12890625,	0.140625,	0.15234375,	0.1640625,	0.17578125,	0.1875,	
	0.19921875,	0.2109375,	0.22265625,	0.234375,	0.24609375,	0.2578125,	0.26953125,	0.28125,	
	0.29296875,	0.3046875,	0.31640625,	0.328125,	0.33984375,	0.3515625,	0.36328125,	0.375,	
	0.37890625,	0.3828125,	0.38671875,	0.390625,	0.39453125,	0.3984375,	0.40234375,	0.40625,	
	0.41015625,	0.4140625,	0.41796875,	0.421875,	0.42578125,	0.4296875,	0.43359375,	0.4375,	
	0.44140625,	0.4453125,	0.44921875,	0.453125,	0.45703125,	0.4609375,	0.46484375,	0.46875,	
	0.47265625,	0.4765625,	0.48046875,	0.484375,	0.48828125,	0.4921875,	0.49609375,	0.5,	
	0.50390625,	0.5078125,	0.51171875,	0.515625,	0.51953125,	0.5234375,	0.52734375,	0.53125,	
	0.53515625,	0.5390625,	0.54296875,	0.546875,	0.55078125,	0.5546875,	0.55859375,	0.5625,	
	0.56640625,	0.5703125,	0.57421875,	0.578125,	0.58203125,	0.5859375,	0.58984375,	0.59375,	
	0.59765625,	0.6015625,	0.60546875,	0.609375,	0.61328125,	0.6171875,	0.62109375,	0.625,	
	0.63671875,	0.6484375,	0.66015625,	0.671875,	0.68359375,	0.6953125,	0.70703125,	0.71875,	
	0.73046875,	0.7421875,	0.75390625,	0.765625,	0.77734375,	0.7890625,	0.80078125,	0.8125,	
	0.82421875,	0.8359375,	0.84765625,	0.859375,	0.87109375,	0.8828125,	0.89453125,	0.90625,	
	0.91796875,	0.9296875,	0.94140625,	0.953125,	0.96484375,	0.9765625,	0.98828125,	1
} ;

float waveshapeSIN[257] = { 
	-1,	
	-0.9999247018,	-0.9996988187,	-0.9993223846,	-0.9987954562,	-0.9981181129,	-0.9972904567,	-0.9963126122,	-0.9951847267,	
	-0.99390697,	-0.9924795346,	-0.9909026354,	-0.98917651,	-0.9873014182,	-0.9852776424,	-0.9831054874,	-0.9807852804,	
	-0.9783173707,	-0.97570213,	-0.9729399522,	-0.9700312532,	-0.966976471,	-0.9637760658,	-0.9604305194,	-0.9569403357,	
	-0.9533060404,	-0.9495281806,	-0.9456073254,	-0.9415440652,	-0.9373390119,	-0.9329927988,	-0.9285060805,	-0.9238795325,	
	-0.9191138517,	-0.9142097557,	-0.9091679831,	-0.9039892931,	-0.8986744657,	-0.8932243012,	-0.8876396204,	-0.8819212643,	
	-0.8760700942,	-0.8700869911,	-0.8639728561,	-0.85772861,	-0.8513551931,	-0.8448535652,	-0.8382247056,	-0.8314696123,	
	-0.8245893028,	-0.8175848132,	-0.8104571983,	-0.8032075315,	-0.7958369046,	-0.7883464276,	-0.7807372286,	-0.7730104534,	
	-0.7651672656,	-0.7572088465,	-0.7491363945,	-0.7409511254,	-0.7326542717,	-0.724247083,	-0.7157308253,	-0.7071067812,	
	-0.6983762494,	-0.6895405447,	-0.6806009978,	-0.6715589548,	-0.6624157776,	-0.653172843,	-0.6438315429,	-0.6343932842,	
	-0.6248594881,	-0.6152315906,	-0.6055110414,	-0.5956993045,	-0.5857978575,	-0.5758081914,	-0.5657318108,	-0.555570233,	
	-0.5453249884,	-0.5349976199,	-0.5245896827,	-0.5141027442,	-0.5035383837,	-0.4928981922,	-0.4821837721,	-0.4713967368,	
	-0.460538711,	-0.4496113297,	-0.4386162385,	-0.4275550934,	-0.4164295601,	-0.405241314,	-0.3939920401,	-0.3826834324,	
	-0.371317194,	-0.3598950365,	-0.3484186802,	-0.3368898534,	-0.3253102922,	-0.3136817404,	-0.3020059493,	-0.2902846773,	
	-0.2785196894,	-0.2667127575,	-0.2548656596,	-0.2429801799,	-0.2310581083,	-0.2191012402,	-0.2071113762,	-0.195090322,	
	-0.183039888,	-0.1709618888,	-0.1588581433,	-0.1467304745,	-0.1345807085,	-0.1224106752,	-0.1102222073,	-0.09801714033,	
	-0.08579731234,	-0.0735645636,	-0.0613207363,	-0.04906767433,	-0.03680722294,	-0.02454122852,	-0.01227153829,	0,	
	0.01227153829,	0.02454122852,	0.03680722294,	0.04906767433,	0.0613207363,	0.0735645636,	0.08579731234,	0.09801714033,	
	0.1102222073,	0.1224106752,	0.1345807085,	0.1467304745,	0.1588581433,	0.1709618888,	0.183039888,	0.195090322,	
	0.2071113762,	0.2191012402,	0.2310581083,	0.2429801799,	0.2548656596,	0.2667127575,	0.2785196894,	0.2902846773,	
	0.3020059493,	0.3136817404,	0.3253102922,	0.3368898534,	0.3484186802,	0.3598950365,	0.371317194,	0.3826834324,	
	0.3939920401,	0.405241314,	0.4164295601,	0.4275550934,	0.4386162385,	0.4496113297,	0.460538711,	0.4713967368,	
	0.4821837721,	0.4928981922,	0.5035383837,	0.5141027442,	0.5245896827,	0.5349976199,	0.5453249884,	0.555570233,	
	0.5657318108,	0.5758081914,	0.5857978575,	0.5956993045,	0.6055110414,	0.6152315906,	0.6248594881,	0.6343932842,	
	0.6438315429,	0.653172843,	0.6624157776,	0.6715589548,	0.6806009978,	0.6895405447,	0.6983762494,	0.7071067812,	
	0.7157308253,	0.724247083,	0.7326542717,	0.7409511254,	0.7491363945,	0.7572088465,	0.7651672656,	0.7730104534,	
	0.7807372286,	0.7883464276,	0.7958369046,	0.8032075315,	0.8104571983,	0.8175848132,	0.8245893028,	0.8314696123,	
	0.8382247056,	0.8448535652,	0.8513551931,	0.85772861,	0.8639728561,	0.8700869911,	0.8760700942,	0.8819212643,	
	0.8876396204,	0.8932243012,	0.8986744657,	0.9039892931,	0.9091679831,	0.9142097557,	0.9191138517,	0.9238795325,	
	0.9285060805,	0.9329927988,	0.9373390119,	0.9415440652,	0.9456073254,	0.9495281806,	0.9533060404,	0.9569403357,	
	0.9604305194,	0.9637760658,	0.966976471,	0.9700312532,	0.9729399522,	0.97570213,	0.9783173707,	0.9807852804,	
	0.9831054874,	0.9852776424,	0.9873014182,	0.98917651,	0.9909026354,	0.9924795346,	0.99390697,	0.9951847267,	
	0.9963126122,	0.9972904567,	0.9981181129,	0.9987954562,	0.9993223846,	0.9996988187,	0.9999247018,	1
} ;

float waveshapeATAN[257] = { 
	-0.999999999,	
	-0.9986032385,	-0.9971856407,	-0.995746746,	-0.9942860816,	-0.9928031608,	-0.9912974829,	-0.9897685322,	-0.9882157778,	
	-0.9866386729,	-0.9850366543,	-0.9834091417,	-0.9817555373,	-0.9800752247,	-0.9783675689,	-0.9766319148,	-0.9748675869,	
	-0.9730738887,	-0.9712501013,	-0.9693954832,	-0.9675092689,	-0.9655906682,	-0.9636388653,	-0.9616530175,	-0.9596322547,	
	-0.9575756776,	-0.955482357,	-0.9533513324,	-0.9511816108,	-0.9489721656,	-0.9467219346,	-0.9444298193,	-0.9420946827,	
	-0.9397153482,	-0.9372905978,	-0.9348191701,	-0.9322997589,	-0.929731011,	-0.9271115242,	-0.9244398452,	-0.9217144676,	
	-0.9189338294,	-0.9160963106,	-0.9132002306,	-0.9102438458,	-0.9072253466,	-0.9041428543,	-0.9009944185,	-0.8977780136,	
	-0.8944915354,	-0.8911327976,	-0.8876995285,	-0.8841893664,	-0.8805998561,	-0.8769284448,	-0.8731724769,	-0.8693291903,	
	-0.8653957108,	-0.8613690476,	-0.8572460875,	-0.8530235898,	-0.8486981804,	-0.8442663458,	-0.8397244269,	-0.8350686124,	
	-0.8302949323,	-0.8253992507,	-0.820377259,	-0.8152244679,	-0.8099362003,	-0.8045075831,	-0.7989335393,	-0.79320878,	
	-0.7873277956,	-0.7812848481,	-0.775073962,	-0.7686889164,	-0.7621232365,	-0.7553701856,	-0.7484227572,	-0.7412736677,	
	-0.7339153497,	-0.7263399456,	-0.718539303,	-0.7105049701,	-0.7022281936,	-0.6936999179,	-0.6849107859,	-0.6758511432,	
	-0.6665110445,	-0.6568802635,	-0.6469483071,	-0.6367044341,	-0.6261376785,	-0.6152368797,	-0.6039907193,	-0.592387765,	
	-0.5804165239,	-0.5680655047,	-0.555323291,	-0.5421786258,	-0.5286205082,	-0.5146383043,	-0.5002218708,	-0.4853616947,	
	-0.470049047,	-0.4542761513,	-0.4380363672,	-0.4213243873,	-0.4041364451,	-0.3864705335,	-0.3683266289,	-0.3497069177,	
	-0.3306160202,	-0.3110612058,	-0.2910525931,	-0.2706033263,	-0.2497297218,	-0.2284513749,	-0.206791219,	-0.1847755311,	
	-0.1624338741,	-0.1397989745,	-0.1169065295,	-0.09379494468,	-0.07050500504,	-0.04707948283,	-0.02356269211,	0,	
	0.02356269211,	0.04707948283,	0.07050500504,	0.09379494468,	0.1169065295,	0.1397989745,	0.1624338741,	0.1847755311,	
	0.206791219,	0.2284513749,	0.2497297218,	0.2706033263,	0.2910525931,	0.3110612058,	0.3306160202,	0.3497069177,	
	0.3683266289,	0.3864705335,	0.4041364451,	0.4213243873,	0.4380363672,	0.4542761513,	0.470049047,	0.4853616947,	
	0.5002218708,	0.5146383043,	0.5286205082,	0.5421786258,	0.555323291,	0.5680655047,	0.5804165239,	0.592387765,	
	0.6039907193,	0.6152368797,	0.6261376785,	0.6367044341,	0.6469483071,	0.6568802635,	0.6665110445,	0.6758511432,	
	0.6849107859,	0.6936999179,	0.7022281936,	0.7105049701,	0.718539303,	0.7263399456,	0.7339153497,	0.7412736677,	
	0.7484227572,	0.7553701856,	0.7621232365,	0.7686889164,	0.775073962,	0.7812848481,	0.7873277956,	0.79320878,	
	0.7989335393,	0.8045075831,	0.8099362003,	0.8152244679,	0.820377259,	0.8253992507,	0.8302949323,	0.8350686124,	
	0.8397244269,	0.8442663458,	0.8486981804,	0.8530235898,	0.8572460875,	0.8613690476,	0.8653957108,	0.8693291903,	
	0.8731724769,	0.8769284448,	0.8805998561,	0.8841893664,	0.8876995285,	0.8911327976,	0.8944915354,	0.8977780136,	
	0.9009944185,	0.9041428543,	0.9072253466,	0.9102438458,	0.9132002306,	0.9160963106,	0.9189338294,	0.9217144676,	
	0.9244398452,	0.9271115242,	0.929731011,	0.9322997589,	0.9348191701,	0.9372905978,	0.9397153482,	0.9420946827,	
	0.9444298193,	0.9467219346,	0.9489721656,	0.9511816108,	0.9533513324,	0.955482357,	0.9575756776,	0.9596322547,	
	0.9616530175,	0.9636388653,	0.9655906682,	0.9675092689,	0.9693954832,	0.9712501013,	0.9730738887,	0.9748675869,	
	0.9766319148,	0.9783675689,	0.9800752247,	0.9817555373,	0.9834091417,	0.9850366543,	0.9866386729,	0.9882157778,	
	0.9897685322,	0.9912974829,	0.9928031608,	0.9942860816,	0.995746746,	0.9971856407,	0.9986032385,	0.999999999
} ;


//                              |          i         |          I         |          e         |          ae        |          a         |         uh         |          u         |          oo        |          ow        |          er       |
float formantFrq[3][10][3] = { { {  270, 2290, 3010}, {  390, 1990, 2550}, {  530, 1840, 2480}, {  660, 1720, 2410}, {  730, 1090, 2440}, {  570,  840, 2410}, {  440, 1020, 2240}, {  300,  870, 2240}, {  640, 1190, 2390}, {  490, 1350, 1690} },     //M
                               { {  310, 2790, 2210}, {  430, 2480, 3070}, {  610, 2330, 2990}, {  860, 1220, 2810}, {  850, 1220, 2810}, {  590,  920, 2710}, {  470, 1160, 2680}, {  370,  950, 2670}, {  760, 1400, 2780}, {  500, 1640, 1960} },     //W
                               { {  370, 3200, 3730}, {  530, 2730, 3600}, {  690, 2610, 3570}, { 1010, 2320, 3320}, { 1030, 1370, 3170}, {  680, 1060, 3180}, {  560, 1410, 3310}, {  430, 1170, 3260}, {  850, 1590, 3360}, {  560, 1820, 2160} } } ;  //Ch
//                              |                    |                    |                    |                    |                    |                    |                    |                    |                    |                   |
float formantDB[10][3]     =   { {   -4,  -24,  -28}, {    -3, -23,  -27}, {   -2,  -17,  -24}, {   -1,  -12,  -22}, {   -1,   -5,  -28}, {    0,   -7,  -34}, {   -1,  -12,  -34}, {   -3,  -19,  -43}, {   -1,  -10,  -27}, {   -5,  -15,  -20} } ;
float formantAmt[10][3] ; 
float formantVolume = 0 ;  //dB Shift 

int8_t formantType  = 0 ;  //M, W, Ch
int8_t formantVowel = 0 ;  //Vowel to form

const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI) ;

//10 Band EQ levels (in dB)
float EQLevel[] = {12, 6, 0, 0, -3, -6, -9, -12, -18, -24} ;

//Storing Volume data
float pulVolume = 0 ;
float sawVolume = 1 ;
float sqrVolume = 0 ;
float triVolume = 0 ;

float preampVolume = 0.1 ;
float balanceVolume = 0 ; //in dB
float volume = 0 ;      //in dB


//Audio Crossover Data
float bassFrq = 200 ;
float bassDB = 6 ;  //in dB
float bassMultVol = pow(10, -bassDB/20) ;
float bassMultFrq = pow(2, bassDB/12) ;


//Flags for keeping track of a note
int currNote = 0 ;
bool currNoteFlag = 0 ;

//Octaves Frequency Modulation
int freqOctaveNum = 10 ;

//Store Randomness altering factors
int8_t polarityRNG = 0 ;
int8_t maxRNG = 1 ;
int8_t stepRNG = 0 ;

//Portamento Data
int16_t portamentoTime = 0 ;    //in milliseconds
int16_t portamentoSens = 10 ;

//Breath Data
int8_t breathLSB = 0 ;
int8_t breathMSB = 0 ;
float breathLevel = 0 ;

//Audio Out 
bool speakerFlag = 1 ;
bool lineOutFlag = 0 ;

void setup() {
  Serial.begin(115200) ;

  AudioMemory(800) ;

  MIDI.begin() ;
  Serial1.begin(1000000) ;

  MIDI.setHandleControlChange(myControlChange);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandlePitchBend(myPitchBend);


  //Overall Volume Control
  VolumePreAmpMix.gain(0, 1) ;
  VolumePreAmpMix.gain(1, 1) ;
  VolumePreAmpMix.gain(2, 1) ;
  VolumePreAmpMix.gain(3, 1) ;
  VolumePreAmpDC.amplitude(preampVolume) ;

  //Volume Settings
  LineLeftAmp.gain( 0 ) ;
  LineRightAmp.gain( 0 ) ;
  SpeakerAmp.gain( volumeAmount(volume) ) ;
  Amp.gain(1) ;

  //10 Band EQ for speakers
  Speaker40HzFilter.frequency(40) ;
  Speaker80HzFilter.frequency(80) ;
  Speaker160HzFilter.frequency(160) ;
  Speaker320HzFilter.frequency(320) ;
  Speaker640HzFilter.frequency(640) ;
  Speaker1280HzFilter.setBandpass(0, 1280, 0.707) ;
  Speaker2560HzFilter.setBandpass(0, 2560, 0.707) ;
  Speaker5120HzFilter.setBandpass(0, 5120, 0.707) ;
  Speaker10240HzFilter.setBandpass(0, 10240, 0.707) ;
  Speaker20480HzFilter.setLowpass(0, 20480, 0.707) ;

  Speaker40HzAmp.gain(    volumeAmount(EQLevel[0]) ) ;
  Speaker80HzAmp.gain(    volumeAmount(EQLevel[1]) ) ;
  Speaker160HzAmp.gain(   volumeAmount(EQLevel[2]) ) ;
  Speaker320HzAmp.gain(   volumeAmount(EQLevel[3]) ) ;
  Speaker640HzAmp.gain(   volumeAmount(EQLevel[4]) ) ;
  Speaker1280HzAmp.gain(  volumeAmount(EQLevel[5]) ) ;
  Speaker2560HzAmp.gain(  volumeAmount(EQLevel[6]) ) ;
  Speaker5120HzAmp.gain(  volumeAmount(EQLevel[7]) ) ;
  Speaker10240HzAmp.gain( volumeAmount(EQLevel[8]) ) ;
  Speaker20480HzAmp.gain( volumeAmount(EQLevel[9]) ) ;

  
  
  //An envelope for suppressing click and pop noise
  MainEnv.delay(0) ;
  MainEnv.attack(0) ;
  MainEnv.hold(0) ;
  MainEnv.decay(0) ;
  MainEnv.sustain(1) ;
  MainEnv.release(0) ;
  MainEnv.releaseNoteOn(0) ;

  //Mix all 4 oscillators together with Noise
  WaveMix.gain(0, pulVolume) ;
  WaveMix.gain(1, sawVolume) ;
  WaveMix.gain(2, sqrVolume) ;
  WaveMix.gain(3, triVolume) ;
  WaveMixFX.gain(0, 1) ;
  WaveMixFX.gain(1, 1) ;
  WaveMixFX.gain(2, 0) ;
  WaveMixFX.gain(3, 0) ;


  //Main waveforms used
  PulWave.begin(1, noteFreqs[64], WAVEFORM_BANDLIMIT_PULSE) ;
  SawWave.begin(1, noteFreqs[64], WAVEFORM_BANDLIMIT_SAWTOOTH) ;
  SqrWave.begin(1, noteFreqs[64], WAVEFORM_BANDLIMIT_SQUARE) ;
  TriWave.begin(1, noteFreqs[64], WAVEFORM_TRIANGLE) ;

  //Setting up Main Filter
  FilterFrqMix.gain(0, 1) ;
  FilterFrqMix.gain(1, 1) ;
  FilterFrqMix.gain(2, 1) ;
  FilterFrqMix.gain(3, 1) ;
  FilterResMix.gain(0, 0.2) ;
  FilterResMix.gain(1, 1) ;
  FilterResMix.gain(2, 1) ;
  FilterResMix.gain(3, 1) ;
  MainFilter.frequency(noteFreqs[64]) ;
  MainFilter.octaveControl(7) ;

  //Set The Frequency Modulation to 10 Octave Range
  PulWave.frequencyModulation(freqOctaveNum) ;
  SawWave.frequencyModulation(freqOctaveNum) ;
  SqrWave.frequencyModulation(freqOctaveNum) ;
  TriWave.frequencyModulation(freqOctaveNum) ;

  //Pulse Width Modulation Settings
  PulLFO.begin(0, 0.1, WAVEFORM_SINE) ;
  PulDC.amplitude(0.5) ;
  PulModMix.gain(0, 1) ;
  PulModMix.gain(1, 1) ;
  PulModMix.gain(2, 0) ;
  PulModMix.gain(3, 0) ;

  //Vibrato Initialization
  VibratoEnv.delay(0) ;
  VibratoEnv.attack(0) ;
  VibratoEnv.hold(0) ;
  VibratoEnv.decay(0) ;
  VibratoEnv.sustain(1) ;
  VibratoEnv.release(0) ;
  VibratoEnv.releaseNoteOn(0) ;
  VibratoLFO.begin(0, 0.1, WAVEFORM_SINE) ;
  VibratoLinkAmtDC.amplitude(1) ;

  //Tremelo Initialization
  TremeloEnv.delay(0) ;
  TremeloEnv.attack(0) ;
  TremeloEnv.hold(0) ;
  TremeloEnv.decay(0) ;
  TremeloEnv.sustain(1) ;
  TremeloEnv.release(0) ;
  TremeloEnv.releaseNoteOn(0) ;
  TremeloLFO.begin(0, 0.1, WAVEFORM_SINE) ;
  TremeloLinkAmtDC.amplitude(1) ;
  TremeloMix.gain(0, 1) ;
  TremeloMix.gain(1, 1) ;
  TremeloMix.gain(2, 0) ;
  TremeloMix.gain(3, 0) ;
  TremeloDC.amplitude(1) ;

  //Random Number Setup (Crucial for dynamic sound)
  Entropy.Initialize() ;
  randomSeed(Entropy.random()) ;
  PulRNG.amplitude(0) ;
  FilterFrqRNG.amplitude(0) ;
  FilterResRNG.amplitude(0) ;
  VolumeRNG.amplitude(0) ;

  //Setting Up the main waveshaper
  waveshape1.shape(waveshapeSIN, waveshapeLen) ;
  WaveshapeMix.gain(0, 0) ;
  WaveshapeMix.gain(1, 1) ;
  WaveshapeMix.gain(2, 0) ;
  WaveshapeMix.gain(3, 0) ;

  //Setup for delay
  DelayFeedbackMix.gain(0, 1) ;
  DelayFeedbackMix.gain(1, 0) ;
  DelayFeedbackMix.gain(2, 0) ;
  DelayFeedbackMix.gain(3, 0) ;
  MainDelay.delay(0, 10) ;
  DelayFilter.frequency(5000) ;

  //Setup for Freeverb
  Freeverb.roomsize(0.05) ;
  Freeverb.damping(0) ;
  FreeverbMixLeft.gain(0, 0.2) ;
  FreeverbMixLeft.gain(1, 0.8) ;
  FreeverbMixLeft.gain(2, 0) ;
  FreeverbMixLeft.gain(3, 0) ;
  FreeverbMixRight.gain(0, 0.2) ;
  FreeverbMixRight.gain(1, 0.8) ;
  FreeverbMixRight.gain(2, 0) ;
  FreeverbMixRight.gain(3, 0) ;

  //Set Up breath Control
  Breath.amplitude(0) ;
  waveshape2.shape(waveshapeLIN, waveshapeLen) ;
  BreathFilter.frequency(1000) ;

  //Set Up Modulation Links
  VibratoLink.gain(0, 0) ;
  VibratoLink.gain(1, 0) ;
  VibratoLink.gain(2, 0) ;
  VibratoLink.gain(3, 0) ;

  TremeloLink.gain(0, 0) ;
  TremeloLink.gain(1, 0) ;
  TremeloLink.gain(2, 0) ;
  TremeloLink.gain(3, 0) ;


  //Formant Setup
  for (int8_t i=0; i<10; i++){
    formantAmt[i][0] = pow(10, (formantDB[i][0]+formantVolume)/20) ;
    formantAmt[i][1] = pow(10, (formantDB[i][1]+formantVolume)/20) ;
    formantAmt[i][2] = pow(10, (formantDB[i][2]+formantVolume)/20) ;
  }
  FormantF1.resonance(5) ;
  FormantF2.resonance(5) ;
  FormantF3.resonance(5) ;

  FormantF1.frequency(formantFrq[formantType][formantVowel][0]) ;
  FormantF2.frequency(formantFrq[formantType][formantVowel][1]) ;
  FormantF3.frequency(formantFrq[formantType][formantVowel][2]) ;
  FormantL1.gain(formantAmt[formantVowel][0]) ;
  FormantL2.gain(formantAmt[formantVowel][1]) ;
  FormantL3.gain(formantAmt[formantVowel][2]) ;

  FormantMix.gain(0, 1) ;
  FormantMix.gain(1, 0) ;
  FormantMix.gain(2, 0) ;
  FormantMix.gain(3, 0) ;

}

void loop() {
  // put your main code here, to run repeatedly:
  MIDI.read() ;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void myControlChange(byte channel, byte control, byte value){
  AudioNoInterrupts() ;
  float amt = value ;
  float rescale = 1 ;
  switch(control){
    case 0:
    //Change the audio output type
    speakerFlag = value & 1 ;
    lineOutFlag = (value >> 1) & 1 ;

    if (lineOutFlag){
      LineLeftAmp.gain( volumeAmount(volume - balanceVolume) ) ;
      LineRightAmp.gain( volumeAmount(volume + balanceVolume) ) ;
    } else {
      LineLeftAmp.gain( 0 ) ;
      LineRightAmp.gain( 0 ) ;
    }
      
    if (speakerFlag){
      SpeakerAmp.gain( volumeAmount(volume) ) ;
    } else {
      SpeakerAmp.gain( 0 ) ;
    }

    break;
    case 2:
      //Breath Control
      breathMSB = value ;
      breathLevel = breathAmount(breathMSB, breathLSB) ;
      Breath.amplitude( breathLevel ) ;
    break;
    case 5:
      portamentoTime = value ;
      Note.amplitude( noteAmount(currNote), portamentoTime*portamentoSens) ;
      FilterFrqNote.amplitude( noteFrqAmount(currNote), portamentoTime*portamentoSens) ;
    break;
    case 6:
      portamentoSens = value ;
    break;
    case 7:
      //Control Main Volume
      volume = amt - 64 ;

      if (lineOutFlag){
        LineLeftAmp.gain( volumeAmount(volume - balanceVolume) ) ;
        LineRightAmp.gain( volumeAmount(volume + balanceVolume) ) ;
      }
      
      if (speakerFlag){
        SpeakerAmp.gain( volumeAmount(volume) ) ;
      }
      
      
    break;
    case 8:
      //Control Left Right Balance
      balanceVolume = (amt-64)/64 ;
      if (lineOutFlag){
        LineLeftAmp.gain( volumeAmount(volume - balanceVolume) ) ;
        LineRightAmp.gain( volumeAmount(volume + balanceVolume) ) ;
      }
    break;
    case 9:
      //Control Preamp Volume (CLOSE TO 1 CAN CAUSE CLIPPING)
      preampVolume = amt/100 ;
      VolumePreAmpDC.amplitude(preampVolume) ;
    break;
    case 10:
      VolumePreAmpMix.gain(2, amt/100) ;
    break;
    case 12:
      FilterFrqMix.gain(0, amt/100) ;
    break;
    case 13:
      FilterResMix.gain(0, amt/100) ;
    break;
    case 14:
      //Cutoff Frequency Offset for main filter
      FilterFrqAmt.amplitude(amt/700) ;
    break;
    case 15:
      //Resonance amount for main filter
      MainFilter.resonance( amt / 101) ; //Resonance must be less than 1
    break;
    case 16:
      //Relative Volume of Pulse Wave
      pulVolume = amt/100 ;
      rescale = max(pulVolume+sawVolume+sqrVolume+triVolume, 1) ;

      WaveMix.gain(0, pulVolume/rescale) ;
      WaveMix.gain(1, sawVolume/rescale) ;
      WaveMix.gain(2, sqrVolume/rescale) ;
      WaveMix.gain(3, triVolume/rescale) ;
    break;
    case 17:
      //Relative Volume of Saw Wave
      sawVolume = amt/100 ;
      rescale = max(pulVolume+sawVolume+sqrVolume+triVolume, 1) ;

      WaveMix.gain(0, pulVolume/rescale) ;
      WaveMix.gain(1, sawVolume/rescale) ;
      WaveMix.gain(2, sqrVolume/rescale) ;
      WaveMix.gain(3, triVolume/rescale) ;
    break;
    case 18:
      //Relative Volume of Square Wave
      sqrVolume = amt/100 ;
      rescale = max(pulVolume+sawVolume+sqrVolume+triVolume, 1) ;

      WaveMix.gain(0, pulVolume/rescale) ;
      WaveMix.gain(1, sawVolume/rescale) ;
      WaveMix.gain(2, sqrVolume/rescale) ;
      WaveMix.gain(3, triVolume/rescale) ;
    break;
    case 19:
      //Relative Volume of Triangle Wave
      triVolume = amt/100 ;
      rescale = max(pulVolume+sawVolume+sqrVolume+triVolume, 1) ;

      WaveMix.gain(0, pulVolume/rescale) ;
      WaveMix.gain(1, sawVolume/rescale) ;
      WaveMix.gain(2, sqrVolume/rescale) ;
      WaveMix.gain(3, triVolume/rescale) ;
    break;
    case 20:
      //Detune amount for Pulse wave (positive)
      PulTune.amplitude( detuneAmount(value) ) ;
    break;
    case 21:
      //Detune amount for Saw wave (positive)
      SawTune.amplitude( detuneAmount(value) ) ;
    break;
    case 22:
      //Detune amount for Square wave (positive)
      SqrTune.amplitude( detuneAmount(value) ) ;
    break;
    case 23:
      //Detune amount for Triangle wave (positive)
      TriTune.amplitude( detuneAmount(value) ) ;
    break;
    case 34:
      breathLSB = value ;
    break;
    case 46:
      //Cutoff Frequency Offset for main filter
      FilterFrqAmt.amplitude(-amt/700) ;
    break;
    case 52:
      //Detune amount for Pulse wave (negative)
      PulTune.amplitude( -detuneAmount(value) ) ;
    break;
    case 53:
      //Detune amount for Saw wave (negative)
      SawTune.amplitude( -detuneAmount(value) ) ;
    break;
    case 54:
      //Detune amount for Square wave (negative)
      SqrTune.amplitude( -detuneAmount(value) ) ;
    break;
    case 55:
      //Detune amount for Triangle wave (negative)
      TriTune.amplitude( -detuneAmount(value) ) ;
    break;
        case 56:
      //Change waveform of the Vibrato
      switch(value){
        case 0:
        TremeloLFO.begin(WAVEFORM_SINE) ;
        break;
        case 1:
        TremeloLFO.begin(WAVEFORM_BANDLIMIT_SAWTOOTH) ;
        break;
        case 2:
        TremeloLFO.begin(WAVEFORM_BANDLIMIT_SQUARE) ;
        break;
        case 3:
        TremeloLFO.begin(WAVEFORM_TRIANGLE) ;
        break;
        case 4:
        TremeloLFO.begin(WAVEFORM_SAMPLE_HOLD) ;
        break;
      }
    break;
    case 57:
      amt = 0.1 * pow(10, 2*amt/100) ;
      TremeloLFO.frequency(amt) ;
    break;
    case 58:
      TremeloLFO.amplitude( amt/100 ) ;
    break;
    case 60:
      TremeloEnv.attack(10*amt) ;
    break;
    case 61:
      TremeloEnv.release(10*amt) ;
    break;
    case 72:
      MainEnv.release(amt*10) ;
    break;
    case 73:
      MainEnv.attack(amt*10) ;
    break;
    case 74:
      MainEnv.decay(amt*10) ;
    break;
    case 75:
      MainEnv.sustain(amt/100) ;
    break;
    case 76:
      DelayFeedbackMix.gain(1, amt/100) ;
    break;
    case 77:
      MainDelay.delay(0, amt*10) ;
    break;
    case 78:
      amt = 500*pow(10, amt/100) ; 
      DelayFilter.frequency(amt) ;
    break;
    case 79:
      DelayFilter.resonance(amt/100) ;
    break;
    case 85:
      //Assign different waveshapes to different values
      switch(value){
        case 0:
          waveshape1.shape(waveshapeABS, waveshapeLen) ;
        break;
        case 1:
          waveshape1.shape(waveshapeSIN, waveshapeLen) ;
        break;
        case 2:
          waveshape1.shape(waveshapeATAN, waveshapeLen) ;
        break;
      }
    break;
    case 86:
      //Amount of reshaped wave in the mix
      WaveshapeMix.gain(0, amt/100) ;
      WaveshapeMix.gain(1, 1 - amt/100) ;
    break;
    case 91:
      formantType = value ;

      FormantF1.frequency(formantFrq[formantType][formantVowel][0]) ;
      FormantF2.frequency(formantFrq[formantType][formantVowel][1]) ;
      FormantF3.frequency(formantFrq[formantType][formantVowel][2]) ;
    break;
    case 92:
      formantVowel = value ;

      FormantF1.frequency(formantFrq[formantType][formantVowel][0]) ;
      FormantF2.frequency(formantFrq[formantType][formantVowel][1]) ;
      FormantF3.frequency(formantFrq[formantType][formantVowel][2]) ;
      FormantL1.gain(formantAmt[formantVowel][0]) ;
      FormantL2.gain(formantAmt[formantVowel][1]) ;
      FormantL3.gain(formantAmt[formantVowel][2]) ;      
    break;
    case 93:
      FormantMix.gain(0, 1 - amt/100) ;
      FormantMix.gain(1, amt/100) ;
      FormantMix.gain(2, amt/100) ;
      FormantMix.gain(3, amt/100) ;
    break;
    case 98:
      polarityRNG = value-64 ;
    break;
    case 99:
      stepRNG = value ;
    break;
    case 100:
      maxRNG = value ;
    break;
    case 101:
      PinkWave.amplitude(amt/100) ;
    break;
    case 102:
      //Roomsize (echoiness) of reverb
      Freeverb.roomsize(amt/100) ;
    break;
    case 103:
      //Damping (dullness) of reverb
      Freeverb.damping(amt/100) ;
    break;
    case 104:
      //Amount of reverb in the left and right channel mix
      FreeverbMixLeft.gain(0, amt/100) ;
      FreeverbMixLeft.gain(1, 1 - amt/100) ;
      FreeverbMixRight.gain(0, amt/100) ;
      FreeverbMixRight.gain(1, 1 - amt/100) ;
    break;
    case 106:
      //Change the standard duty cycle of the pulse wave
      PulDC.amplitude(amt/100) ;
    break;
    case 107:
      //Change waveform of the duty cycle modulation
      switch(value){
        case 0:
        PulLFO.begin(WAVEFORM_SINE) ;
        break;
        case 1:
        PulLFO.begin(WAVEFORM_BANDLIMIT_SAWTOOTH) ;
        break;
        case 2:
        PulLFO.begin(WAVEFORM_BANDLIMIT_SQUARE) ;
        break;
        case 3:
        PulLFO.begin(WAVEFORM_TRIANGLE) ;
        break;
        case 4:
        PulLFO.begin(WAVEFORM_SAMPLE_HOLD) ;
        break;
      }
    break;
    case 108:
      amt = 0.1 * pow(10, 2*amt/100) ;
      PulLFO.frequency(amt) ;
    break;
    case 109:
      PulLFO.amplitude(amt/100) ;
    break;
    case 110:
      //Change waveform of the Vibrato
      switch(value){
        case 0:
        VibratoLFO.begin(WAVEFORM_SINE) ;
        break;
        case 1:
        VibratoLFO.begin(WAVEFORM_BANDLIMIT_SAWTOOTH) ;
        break;
        case 2:
        VibratoLFO.begin(WAVEFORM_BANDLIMIT_SQUARE) ;
        break;
        case 3:
        VibratoLFO.begin(WAVEFORM_TRIANGLE) ;
        break;
        case 4:
        VibratoLFO.begin(WAVEFORM_SAMPLE_HOLD) ;
        break;
      }
    break;
    case 111:
      amt = 0.1 * pow(10, 2*amt/100) ;
      VibratoLFO.frequency(amt) ;
    break;
    case 112:
      VibratoLFO.amplitude( detuneAmount(value) ) ;
    break;
    case 114:
      VibratoEnv.attack(10*amt) ;
    break;
    case 115:
      VibratoEnv.release(10*amt) ;
    break;
    case 118:
      EQLevel[0] = amt-64 ;
      Speaker40HzAmp.gain( volumeAmount(EQLevel[0]) ) ;
    break;
    case 119:
      EQLevel[1] = amt-64 ;
      Speaker80HzAmp.gain( volumeAmount(EQLevel[1]) ) ;
    break;
    case 120:
      EQLevel[2] = amt-64 ;
      Speaker160HzAmp.gain( volumeAmount(EQLevel[2]) ) ;
    break;
    case 121:
      EQLevel[3] = amt-64 ;
      Speaker320HzAmp.gain( volumeAmount(EQLevel[3]) ) ;
    break;
    case 122:
      EQLevel[4] = amt-64 ;
      Speaker640HzAmp.gain( volumeAmount(EQLevel[4]) ) ;
    break;
    case 123:
      EQLevel[5] = amt-64 ;
      Speaker1280HzAmp.gain( volumeAmount(EQLevel[5]) ) ;
    break;
    case 124:
      EQLevel[6] = amt-64 ;
      Speaker2560HzAmp.gain( volumeAmount(EQLevel[6]) ) ;
    break;
    case 125:
      EQLevel[7] = amt-64 ;
      Speaker5120HzAmp.gain( volumeAmount(EQLevel[7]) ) ;
    break;
    case 126:
      EQLevel[8] = amt-64 ;
      Speaker10240HzAmp.gain( volumeAmount(EQLevel[8]) ) ;
    break;
    case 127:
      EQLevel[9] = amt-64 ;
      Speaker20480HzAmp.gain( volumeAmount(EQLevel[9]) ) ;
    break;
  }

  AudioInterrupts() ;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void myNoteOff(byte channel, byte note, byte velocity){
  //Serial.print(note) ;
  //Serial.println(" Off") ;

  AudioNoInterrupts() ;

  if (note == currNote){
    if (currNoteFlag){
      currNoteFlag = 0 ;
      MainEnv.noteOff() ;
      VibratoEnv.noteOff() ;
      TremeloEnv.noteOff() ;
    }
  }

  AudioInterrupts() ;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void myNoteOn(byte channel, byte note, byte velocity){
  //Serial.print(note) ;
  //Serial.println(" On") ;

  //Stop Audio Interrupts So all effects take place at once
  AudioNoInterrupts() ;

  if (!currNoteFlag){
    currNoteFlag = 1 ;
    currNote = note ;

    Note.amplitude( noteAmount(note) ) ;
    FilterFrqNote.amplitude( noteFrqAmount(note) ) ;

    PulRNG.amplitude( randomAmount() ) ;
    FilterFrqRNG.amplitude( randomAmount() ) ;
    FilterResRNG.amplitude( randomAmount() ) ;
    VolumeRNG.amplitude( randomAmount() ) ;

    MainEnv.noteOn() ;
    VibratoEnv.noteOn() ;
    TremeloEnv.noteOn() ;
  } else if (note != currNote){
    currNote = note ;
    Note.amplitude( noteAmount(note), portamentoTime*portamentoSens ) ;
    FilterFrqNote.amplitude( noteFrqAmount(note) , portamentoTime*portamentoSens ) ;

    PulRNG.amplitude( randomAmount() ) ;
    FilterFrqRNG.amplitude( randomAmount() ) ;
    FilterResRNG.amplitude( randomAmount() ) ;
    VolumeRNG.amplitude( randomAmount() ) ;

    MainEnv.noteOn() ;
    VibratoEnv.noteOn() ;
    TremeloEnv.noteOn() ;

  }

  AudioInterrupts() ;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void myPitchBend(byte channel, int bend){

}

//-------------------------------------------------Value Setting Functions-----------------------

float detuneAmount(int8_t val){
  float amt = val ;
  if (val <= 100){
    amt = ( amt/1200 ) / freqOctaveNum ;
  } else {
    amt = ( (amt-99)/12 ) / freqOctaveNum ;
  }
  
  return amt ;
}

float volumeAmount(float dB){
  return pow(10, dB/20) ;
}

float randomAmount(){
  float amt = 0 ;
  int8_t val = random(-maxRNG, maxRNG) ;

  if (maxRNG != 0){
    //Discretize the value according to step
    if (stepRNG > 0){
      val = (val/stepRNG) * stepRNG ;
    }

    //Rescale as a float with absolute max value of 1
    amt = (float)val/100 ;

    //Alter probability of how negative number is
    amt = amt + (float)polarityRNG/(maxRNG*1000) ;

  } else {
    amt = 0;
  }

  return amt ;
}

float noteAmount(int8_t val){
  float amt = val ;

  //All Oscillators set to MIDI note 64
  //VCO is then shifted to make correct note
  //10 Octaves, 12 Half steps per octave
  amt = (amt-64)/120 ;

  return amt ;
}

float noteFrqAmount(int8_t val){
  float amt = val ;

  //Frequency set to MIDI note 64
  //VCF Shifted to alwayd be offset equally
  //7 octave control, 12 steps per octave
  //Fc = 2^(amt * 7)
  amt = (amt-64)/84 ;

  return amt ;
}

float breathAmount(int8_t msb, int8_t lsb){
  float amt = (msb << 7) + lsb ;
  return amt/16838 ;
}


