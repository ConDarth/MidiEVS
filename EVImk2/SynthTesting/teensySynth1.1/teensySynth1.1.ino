#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dcTuner1;            //xy=60,386
AudioSynthWaveformDc     dcTuner2; //xy=61,427
AudioSynthWaveform       pitchLFO;      //xy=64.5,480
AudioMixer4              mixerPitch1;         //xy=251,398
AudioMixer4              mixerPitch2;         //xy=251,464
AudioSynthWaveformModulated Osc1Voice1;   //xy=424.3333333333333,395.99999999999994
AudioSynthNoiseWhite     NoiseVoice1;         //xy=425,479
AudioSynthWaveformModulated Osc2Voice1; //xy=429,437
AudioMixer4              MixerVoice1;         //xy=616,444
AudioOutputI2S           i2s1;           //xy=770.0000305175781,440.8888244628906
AudioConnection          patchCord1(dcTuner1, 0, mixerPitch1, 0);
AudioConnection          patchCord2(dcTuner2, 0, mixerPitch2, 0);
AudioConnection          patchCord3(pitchLFO, 0, mixerPitch1, 1);
AudioConnection          patchCord4(pitchLFO, 0, mixerPitch2, 1);
AudioConnection          patchCord5(mixerPitch1, 0, Osc1Voice1, 0);
AudioConnection          patchCord6(mixerPitch2, 0, Osc2Voice1, 0);
AudioConnection          patchCord7(Osc1Voice1, 0, MixerVoice1, 0);
AudioConnection          patchCord8(NoiseVoice1, 0, MixerVoice1, 2);
AudioConnection          patchCord9(Osc2Voice1, 0, MixerVoice1, 1);
AudioConnection          patchCord10(MixerVoice1, 0, i2s1, 0);
AudioConnection          patchCord11(MixerVoice1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=526.8888854980469,288.6666564941406
// GUItool: end automatically generated code


#define BUFFER 8

const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
uint8_t noteState[1] = {0};
uint8_t velocity[1] = {100} ;
float noteAmplitude[1] = {0} ;

float DIV127 = 1.0 / 127.0 ;
float DIV100 = 1.0 / 100.0 ;
float DIV12 = 1.0 / 12.0 ;

void setup() {
  // put your setup code here, to run once:
  AudioMemory(50) ;
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);
  sgtl5000_1.enable() ;
  sgtl5000_1.volume(0.3) ;
    
  Osc1Voice1.begin(WAVEFORM_SINE) ; 
  Osc1Voice1.frequencyModulation(1) ;  
  Osc2Voice1.begin(WAVEFORM_SINE) ; 
  Osc2Voice1.frequencyModulation(1) ;  
  
  NoiseVoice1.amplitude(1.0) ;

  pitchLFO.begin(WAVEFORM_SINE) ;
  
  dcTuner1.amplitude(0.0) ;
  mixerPitch1.gain(0, 1.0);
  mixerPitch1.gain(1, 1.0);
  
  dcTuner2.amplitude(0.0) ;
  mixerPitch2.gain(0, 1.0);
  mixerPitch2.gain(1, 1.0);

  MixerVoice1.gain(0, 1.0);
  MixerVoice1.gain(1, 1.0);
  MixerVoice1.gain(2, 0.0);
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
  float deTune;
  switch (control) {
    case 12:
      MixerVoice1.gain(0, (value * DIV127));
    break;
    case 13:
      MixerVoice1.gain(1, (value * DIV127));
    break;
    case 14:
      MixerVoice1.gain(2, (value * DIV127));
    break;
    case 15:
      switch(value) {
        case 0: 
         Osc1Voice1.begin(WAVEFORM_SINE) ;
        break;
        case 1: 
          Osc1Voice1.begin(WAVEFORM_SAWTOOTH) ;
        break;
        case 2: 
          Osc1Voice1.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
        break;
        case 3:
          Osc1Voice1.begin(WAVEFORM_SQUARE) ;
        break;
        case 4: 
          Osc1Voice1.begin(WAVEFORM_TRIANGLE) ;
        break;
      }
    break;
    case 16:
      switch(value) {
        case 0: 
         Osc2Voice1.begin(WAVEFORM_SINE) ;
        break;
        case 1: 
          Osc2Voice1.begin(WAVEFORM_SAWTOOTH) ;
        break;
        case 2: 
          Osc2Voice1.begin(WAVEFORM_SAWTOOTH_REVERSE) ;
        break;
        case 3:
          Osc2Voice1.begin(WAVEFORM_SQUARE) ;
        break;
        case 4: 
          Osc2Voice1.begin(WAVEFORM_TRIANGLE) ;
        break;
      }
    break;
    case 17:
      if (value <= 100) {
        deTune= value * DIV100 ;
        deTune= DIV12 * deTune;
      } else if (value <= 112) {
        deTune= value - 100 ;
        deTune= deTune* DIV12 ;
      } else {
        deTune= 1.0 ;
      }
      dcTuner1.amplitude(deTune) ;
    break;
    case 18:
      if (value <= 100) {
        deTune= value * DIV100 ;
        deTune= DIV12 * deTune;
      } else if (value <= 112) {
        deTune= value - 100 ;
        deTune= deTune* DIV12 ;
      } else {
        deTune= 1.0 ;
      }
      dcTuner2.amplitude(deTune) ;
    break;
    case 28:
      if (value <= 100) {
        deTune= value * DIV100 ;
        deTune= -DIV12 * deTune;
      } else if (value <= 112) {
        deTune= value - 100 ;
        deTune= -1 * deTune* DIV12 ;
      } else {
        deTune= -1.0 ;
      }
      dcTuner1.amplitude(deTune) ;
    break;
    case 29:
      if (value <= 100) {
        deTune= value * DIV100 ;
        deTune= -DIV12 * deTune;
      } else if (value <= 112) {
        deTune= value - 100 ;
        deTune= -1 * deTune* DIV12 ;
      } else {
        deTune= -1.0 ;
      }
      dcTuner2.amplitude(deTune) ;
    break;
  }
}

void keyBuff(byte note, byte velocity, bool state) {
  static byte noteBuff[BUFFER];
  static byte velBuff[BUFFER];
  static byte buffSize = 0;

  // Add Note
  if (state == true && (buffSize < BUFFER) ) {
    oscPlay(note);
    noteBuff[buffSize] = note;
    velBuff[buffSize] = velocity ;
    buffSize++;
    return;
    //need to add ability to play exactly 4 notes
  }

  // Remove Note
  else if (state == false && buffSize != 0) {
    for (byte found = 0; found < buffSize; found++) {
      if (noteBuff[found] == note) {
        for (byte gap = found; gap < (buffSize - 1); gap++) {
          noteBuff[gap] = noteBuff[gap + 1];
          velBuff[gap] = velBuff[gap + 1];
        }
        buffSize--;
        noteBuff[buffSize] = 255;
        velBuff[buffSize] = 255;
        //here 
        if (buffSize != 0) {
          oscPlay(noteBuff[buffSize - 1]);
          return;
        }
        else {
          oscStop();
          return;
        }
        //to here defines what to do with notes, need to figure this part out 
      }
    }
  }

  return ;
}

void oscPlay(byte note) {
  Osc1Voice1.frequency(noteFreqs[note]) ;
  Osc2Voice1.frequency(noteFreqs[note]) ;
  noteAmplitude[0] = (float) velocity[0] * DIV127 ;
  Osc1Voice1.amplitude(noteAmplitude[0]) ;
  Osc2Voice1.amplitude(noteAmplitude[0]) ;
  NoiseVoice1.amplitude(noteAmplitude[0]) ;
}

void oscStop() {
  Osc1Voice1.amplitude(0.0);
  Osc2Voice1.amplitude(0.0);
  NoiseVoice1.amplitude(0.0) ;
}
