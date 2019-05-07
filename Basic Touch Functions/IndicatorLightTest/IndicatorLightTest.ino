/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define PRESSURE_SENSOR_PIN A0
#define SELECTOR_DIAL_PIN A1
#define SELECT_BUTTON 6 

int pressureRaw = 0 ;
int equalizer = 0 ; 
int lastEqualizer = 1 ;
boolean equalizerToggle = true ;
int modeSelectRaw = 0 ;
int modeSelector = 0 ;
int lastModeSelector = 1 ;
boolean selectButton[4] = {1, 0, 0, 0} ;
boolean selectButtonToggle = false ;
boolean indicatorDisplayToggle = true ;

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

  pinMode(SELECT_BUTTON, INPUT_PULLUP) ;
  
  matrix.begin(0x70);  // pass in the address
  matrix.setRotation(1) ;
  matrix.setBrightness(0) ;
}

void loop() {
  modeSelectRaw = analogRead(SELECTOR_DIAL_PIN) ;
  modeSelector = map(modeSelectRaw, 0, 950, 0, 3) ;
  if (modeSelector != lastModeSelector) {
    indicatorDisplayToggle = true ;
  }

  pressureRaw = analogRead(PRESSURE_SENSOR_PIN) ;
  equalizer = map(pressureRaw, 0, 950, 0, 8) ;
  if (equalizer != lastEqualizer) {
    if (equalizerToggle) {
      indicatorDisplayToggle = true ;
    } else if (!equalizerToggle) {
      if ((equalizer == 0) || (lastEqualizer == 0)) {
        indicatorDisplayToggle = true ;
      }
    }
  }

  if ((digitalRead(SELECT_BUTTON) == LOW) && (!selectButtonToggle)) {
    selectButtonToggle = true ;
    if (!selectButton[modeSelector]) {
      selectButton[modeSelector] = true ;
      switch(modeSelector) {
        case 0:
        equalizerToggle = true ;
        break;
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
      }
    } else if (selectButton[modeSelector]) {
      selectButton[modeSelector] = false ;
      switch(modeSelector) {
        case 0:
        equalizerToggle = false ;
        break;
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
      }
    }
    indicatorDisplayToggle = true ;
  } else if ((digitalRead(SELECT_BUTTON) == HIGH) && (selectButtonToggle)) {
    selectButtonToggle = false ;
  }

  if (indicatorDisplayToggle) {
    matrix.clear() ;
    
    if (equalizerToggle) {
      if (equalizer>7) {
        matrix.fillRect(5, 0, 2, 5, LED_GREEN) ;
        matrix.fillRect(5, 5, 2, 2, LED_YELLOW) ;
        matrix.fillRect(5, 7, 2, (equalizer-7), LED_RED) ;
      } else if (equalizer>5) {
        matrix.fillRect(5, 0, 2, 5, LED_GREEN) ;
        matrix.fillRect(5, 5, 2, (equalizer-5), LED_YELLOW) ;
      } else if (equalizer>0) {
        matrix.fillRect(5, 0, 2, equalizer, LED_GREEN) ;
      } else {
      }
    } else if (!equalizerToggle) {
      if (equalizer > 0) {
        matrix.fillRect(5, 0, 2, 2, LED_GREEN) ;
      } else {
      }
    }
    
    matrix.fillRect(2, 0, 2, 8, LED_RED) ;
    
    matrix.fillRect(0, (2*modeSelector), 2, 2, LED_RED) ;

    for (int i=0; i<4; i++) {
      if (selectButton[i]) {
        matrix.fillRect(2, (2*i), 2, 2, LED_GREEN) ;
      }
    }
    
    matrix.writeDisplay() ;

    indicatorDisplayToggle = false ;
  }

  lastModeSelector = modeSelector ;
  lastEqualizer = equalizer ;
}
