#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define EQUALIZER_PIN A0

Adafruit_24bargraph bar = Adafruit_24bargraph();

int equalizerSize = 24 ;
int equalizerYellow = (float) (equalizerSize*0.65) - 1;
int equalizerRed = (float) (equalizerSize*0.85) - 1;
int equalizerPos = 0 ;
int analogRaw = 0 ;


void setup() {
  Serial.begin(9600);
  Serial.println("HT16K33 Bi-Color Bargraph test");
  
  bar.begin(0x70);  // pass in the address

  equalizerYellow = constrain(equalizerYellow, 0, (equalizerSize-1)) ;
  equalizerRed = constrain(equalizerRed, 0, (equalizerSize-1)) ;

  bar.writeDisplay() ;
}

void loop() {
  analogRaw = analogRead(EQUALIZER_PIN) ;
  analogRaw = map(analogRaw, 0, 1023, 0, equalizerSize) ;

  if (analogRaw > equalizerPos) {
    while(analogRaw > equalizerPos) {
      equalizerPos ++ ;
      setEqualizer(equalizerPos) ;
      Serial.println(equalizerPos) ;
    }
  }
  
  if (analogRaw < equalizerPos) {
    equalizerPos -- ;
    bar.setBar(equalizerPos, LED_OFF) ;
    bar.writeDisplay() ;
    Serial.println(equalizerPos) ;
  }
  
  delay(10) ;
}

void setEqualizer(int pos) {
  pos -- ;
  pos = constrain(pos, 0, 23) ;
  if (pos > equalizerRed) {
    bar.setBar(pos, LED_RED) ;
    Serial.print("red") ;
    Serial.print("\t") ;
  } else if (pos > equalizerYellow) {
    bar.setBar(pos, LED_YELLOW) ;
    Serial.print("yellow") ;
    Serial.print("\t") ;
  } else {
    bar.setBar(pos, LED_GREEN) ;
    Serial.print("green") ;
    Serial.print("\t") ;
  }

  bar.writeDisplay() ;
}
