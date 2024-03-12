#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <MIDI.h>

// GUItool: begin automatically generated code
AudioSynthWaveformModulated VibratoLFO;   //xy=86.57575225830078,438.956205368042
AudioSynthWaveformDc     TriTune; //xy=236.99998474121094,551.666633605957
AudioSynthWaveformDc     SqrTune; //xy=247.99998474121094,477.3333206176758
AudioSynthWaveformDc     SawTune; //xy=248.99998474121094,405.00000762939453
AudioSynthWaveformDc     PulTune;            //xy=249.99998474121094,330.9999771118164
AudioMixer4              TriTuneMix; //xy=417.9999694824219,570.666633605957
AudioMixer4              PulTuneMix;         //xy=421.9999694824219,348.9999771118164
AudioMixer4              SawTuneMix; //xy=423.9999694824219,423.66666412353516
AudioMixer4              SqrTuneMix; //xy=425.9999694824219,495.66666412353516
AudioSynthWaveformModulated PulLFO;   //xy=428.1481475830078,275.9259567260742
AudioSynthWaveformModulated SawWave;        //xy=623.9999542236328,433.00000762939453
AudioSynthWaveformModulated SqrWave;        //xy=624.9999542236328,494.00000762939453
AudioSynthWaveformModulated PulWave;       //xy=629.9999542236328,350.00000762939453
AudioSynthWaveformModulated TriWave;       //xy=633.9999542236328,566.0000076293945
AudioSynthNoisePink      PinkWave;          //xy=800.972225189209,534.7223472595215
AudioMixer4              WaveMix;        //xy=806.9999542236328,473.00000762939453
AudioMixer4              WaveMixFX;         //xy=960.370361328125,491.48142433166504
AudioEffectEnvelope      ClickPop;       //xy=1280.5000305175781,489.00003814697266
AudioFilterLadder        MainFilter;        //xy=1448.5001068115234,491.00000762939453
AudioEffectWaveshaper    Waveshape;     //xy=1615.5001068115234,453.00000762939453
AudioMixer4              WaveshapeMix;         //xy=1793.4999237060547,496.00000762939453
AudioAmplifier           VolumePreAmp;           //xy=1977.5001068115234,496.00000762939453
AudioEffectFreeverbStereo Freeverb;     //xy=2156.500228881836,497.00003814697266
AudioMixer4              FreeverbMixLeft;         //xy=2344.500228881836,473.00000762939453
AudioMixer4              FreeverbMixRight; //xy=2345.833541870117,541.333381652832
AudioAmplifier           VolumeAmpLeft;      //xy=2532.5001068115234,479.00003814697266
AudioAmplifier           VolumeAmpRight;           //xy=2538.500228881836,519.0000381469727
AudioOutputI2S           AudioOut;       //xy=2720.499984741211,497.00003814697266
AudioConnection          patchCord1(VibratoLFO, 0, PulTuneMix, 1);
AudioConnection          patchCord2(VibratoLFO, 0, SawTuneMix, 1);
AudioConnection          patchCord3(VibratoLFO, 0, SqrTuneMix, 1);
AudioConnection          patchCord4(VibratoLFO, 0, TriTuneMix, 1);
AudioConnection          patchCord5(TriTune, 0, TriTuneMix, 0);
AudioConnection          patchCord6(SqrTune, 0, SqrTuneMix, 0);
AudioConnection          patchCord7(SawTune, 0, SawTuneMix, 0);
AudioConnection          patchCord8(PulTune, 0, PulTuneMix, 0);
AudioConnection          patchCord9(TriTuneMix, 0, TriWave, 0);
AudioConnection          patchCord10(PulTuneMix, 0, PulWave, 0);
AudioConnection          patchCord11(SawTuneMix, 0, SawWave, 0);
AudioConnection          patchCord12(SqrTuneMix, 0, SqrWave, 0);
AudioConnection          patchCord13(PulLFO, 0, PulWave, 1);
AudioConnection          patchCord14(SawWave, 0, WaveMix, 1);
AudioConnection          patchCord15(SqrWave, 0, WaveMix, 2);
AudioConnection          patchCord16(PulWave, 0, WaveMix, 0);
AudioConnection          patchCord17(TriWave, 0, WaveMix, 3);
AudioConnection          patchCord18(PinkWave, 0, WaveMixFX, 1);
AudioConnection          patchCord19(WaveMix, 0, WaveMixFX, 0);
AudioConnection          patchCord20(WaveMixFX, ClickPop);
AudioConnection          patchCord21(ClickPop, 0, MainFilter, 0);
AudioConnection          patchCord22(MainFilter, 0, WaveshapeMix, 1);
AudioConnection          patchCord23(MainFilter, Waveshape);
AudioConnection          patchCord24(Waveshape, 0, WaveshapeMix, 0);
AudioConnection          patchCord25(WaveshapeMix, VolumePreAmp);
AudioConnection          patchCord26(VolumePreAmp, Freeverb);
AudioConnection          patchCord27(VolumePreAmp, 0, FreeverbMixLeft, 1);
AudioConnection          patchCord28(VolumePreAmp, 0, FreeverbMixRight, 1);
AudioConnection          patchCord29(Freeverb, 0, FreeverbMixLeft, 0);
AudioConnection          patchCord30(Freeverb, 1, FreeverbMixRight, 0);
AudioConnection          patchCord31(FreeverbMixLeft, VolumeAmpLeft);
AudioConnection          patchCord32(FreeverbMixRight, VolumeAmpRight);
AudioConnection          patchCord33(VolumeAmpLeft, 0, AudioOut, 0);
AudioConnection          patchCord34(VolumeAmpRight, 0, AudioOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2726.499984741211,553.0000076293945
// GUItool: end automatically generated code







//---------------------------------------------------Waveshape Arrays-----------------------------------------------------
//Note: Function must integrate to 0 from [-1,1] otherwise large click and pops
int waveshapeLen = 257 ;

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


const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI) ;

float pulVolume = 0 ;
float sawVolume = 1 ;
float sqrVolume = 0 ;
float triVolume = 0 ;

float preampVolume = 0.9 ;
float balanceVolume = 0 ;
float leftVolume = 0.5 ;
float rightVolume = 0.5 ;


int currNote = 0 ;
bool currNoteFlag = 0 ;

//Octaves Frequency Modulation
int freqOctaveNum = 10 ;

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
  VolumePreAmp.gain(preampVolume) ;
  VolumeAmpLeft.gain(leftVolume + balanceVolume) ;
  VolumeAmpRight.gain(rightVolume + balanceVolume) ;

  //An envelope for suppressing click and pop noise
  ClickPop.delay(0) ;
  ClickPop.attack(0) ;
  ClickPop.hold(0) ;
  ClickPop.decay(0) ;
  ClickPop.sustain(1) ;
  ClickPop.release(0) ;
  ClickPop.releaseNoteOn(0) ;

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

  //Set The Frequency Modulation to 10 Octave Range
  PulWave.frequencyModulation(freqOctaveNum) ;
  SawWave.frequencyModulation(freqOctaveNum) ;
  SqrWave.frequencyModulation(freqOctaveNum) ;
  TriWave.frequencyModulation(freqOctaveNum) ;

  //Main Filter Settings
  MainFilter.frequency(20000) ;
  MainFilter.resonance(0) ;

  Waveshape.shape(waveshapeSIN, waveshapeLen) ;
  WaveshapeMix.gain(0, 0) ;
  WaveshapeMix.gain(1, 1) ;
  WaveshapeMix.gain(2, 0) ;
  WaveshapeMix.gain(3, 0) ;

  Freeverb.roomsize(0) ;
  Freeverb.damping(0) ;
  FreeverbMixLeft.gain(0, 0) ;
  FreeverbMixLeft.gain(1, 1) ;
  FreeverbMixLeft.gain(2, 0) ;
  FreeverbMixLeft.gain(3, 0) ;
  FreeverbMixRight.gain(0, 0) ;
  FreeverbMixRight.gain(1, 1) ;
  FreeverbMixRight.gain(2, 0) ;
  FreeverbMixRight.gain(3, 0) ;


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
    case 7:
      //Control Main Volume
      leftVolume = amt/100 ;
      rightVolume = amt/100 ;
      VolumeAmpLeft.gain(leftVolume + balanceVolume) ;
      VolumeAmpRight.gain(rightVolume + balanceVolume) ;
    break;
    case 8:
      //Control Left Right Balance
      balanceVolume = (amt-64)/64 ;
      VolumeAmpLeft.gain(leftVolume + balanceVolume) ;
      VolumeAmpRight.gain(rightVolume + balanceVolume) ;
    break;
    case 9:
      //Control Preamp Volume (CLOSE TO 1 CAN CAUSE CLIPPING)
      preampVolume = amt/100 ;
      VolumePreAmp.gain(preampVolume) ;
    break;
    case 10:
      PinkWave.amplitude(amt/100) ;
    break;
    case 14:
      //Cutoff Frequency for main filter
      amt = 200 * pow(10, 2*amt/100) ;
      MainFilter.frequency( amt ) ;
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
    case 85:
      //Assign different waveshapes to different values
      switch(value){
        case 0:
          Waveshape.shape(waveshapeABS, waveshapeLen) ;
        break;
        case 1:
          Waveshape.shape(waveshapeSIN, waveshapeLen) ;
        break;
        case 2:
          Waveshape.shape(waveshapeATAN, waveshapeLen) ;
        break;
      }
    break;
    case 86:
      //Amount of reshaped wave in the mix
      WaveshapeMix.gain(0, amt/100) ;
      WaveshapeMix.gain(1, 1 - amt/100) ;
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
  }

  AudioInterrupts() ;
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
    PulWave.frequency(noteFreqs[note]) ;
    SawWave.frequency(noteFreqs[note]) ;
    SqrWave.frequency(noteFreqs[note]) ;
    TriWave.frequency(noteFreqs[note]) ;
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

//-------------------------------------------------Value Setting Functions-----------------------

float detuneAmount(int8_t val){
  float amt = val ;
  if (val <= 100){
    amt = ( amt/1200 ) / freqOctaveNum ;
  } else {
    amt = ( (amt-99)/12 ) / freqOctaveNum ;
  }
  Serial.print(val) ;
  Serial.print("\t") ;
  Serial.println(amt) ;
  return amt ;
}
