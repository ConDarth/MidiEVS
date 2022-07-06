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

volatile bool touchFlag = false ;       //Flag for the interrupt
volatile unsigned long touchTime = 0 ;  //Time storage for debounce
unsigned long touchInterval = 10 ;      //Wait time before reading sensor for debounce (millis)


void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  attachInterrupt(digitalPinToInterrupt(17), touchInterrupt, FALLING) ;
}

void loop() {
  //t0 = micros() ;

  if (touchFlag && (millis() - touchTime > touchInterval)) {
    touchFlag = false ;

    lastTouched = currTouched ;
    currTouched = cap.touched();
    if (lastTouched != currTouched) {
      Serial.println(currTouched, BIN) ;
    }
  } 

  /*
  t = micros() - t0 ;
  Serial.print("     ") ;
  Serial.println(t) ;
  */
}

void touchInterrupt() {
  touchFlag = true ;
  touchTime = millis() ;
}
