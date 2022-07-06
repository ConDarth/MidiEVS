/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t currTouched = 0 ;
uint16_t lastTouched = 0 ;

unsigned long t0 = 0 ;
unsigned long t = 0 ;

#define touchTimeInterval 10000 //Interval before sampling in microseconds
IntervalTimer touchTimer ; 
volatile bool touchFlag = false ;       //Flag for the interrupt

#define P_HIGH_OFFSET 40
#define P_LOW_OFFSET 10
int pTHRBase = 0 ;
volatile int pTHRHigh = 0 ;
volatile int pTHRLow = 0 ;
volatile bool pressureFlag = false ;
volatile bool pressureToggle = true ;
volatile bool pressureState = false ;


void setup() {
  Serial.begin(9600);
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  pinMode(16, INPUT) ;
  pinMode(17, INPUT) ;
  pinMode(13, OUTPUT) ;

  attachInterrupt(digitalPinToInterrupt(17), touchInterrupt, FALLING) ;
  attachInterrupt(digitalPinToInterrupt(16), pressureInterrupt, CHANGE) ;

  pTHRBase = analogRead(14) ;
  pTHRLow = pTHRBase + P_LOW_OFFSET ;
  pTHRHigh = pTHRBase + P_HIGH_OFFSET ;
  analogWriteResolution(10) ;
  analogWrite(A14, pTHRHigh) ;
}

void loop() {
  //t0 = micros() ;

  if (touchFlag) {
    touchFlag = false ;

    lastTouched = currTouched ;
    currTouched = cap.touched();
    if (lastTouched != currTouched) {
      Serial.println(currTouched, BIN) ;
    }
  } 

  if (pressureFlag) {
    if (pressureState) {
      Serial.println("Pressure On") ;
    } else {
      Serial.println("Pressure Off") ;
    }
    
    digitalWrite(13, pressureState) ;
    pressureFlag = false ;
  }
  
  /*
  t = micros() - t0 ;
  Serial.print("     ") ;
  Serial.println(t) ;
  */
  //delay(20) ;
}

void touchInterrupt() {
  touchTimer.begin(touchTimerInterrupt, touchTimeInterval) ;
}

void touchTimerInterrupt() {
  touchTimer.end() ;
  touchFlag = true ;
}

void pressureInterrupt() {
  pressureFlag = true ;
  pressureState = digitalRead(16) ;
  if (pressureState) {
    analogWrite(A14, pTHRLow) ;
  } else {
    analogWrite(A14, pTHRHigh) ;
  }
}
