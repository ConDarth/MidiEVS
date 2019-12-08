#include <Wire.h>
#include "Adafruit_FRAM_I2C.h"

/* Example code for the Adafruit I2C FRAM breakout */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 5.0V DC
   Connect GROUND to common ground */
   
Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();
uint16_t          framAddr = 0;


uint16_t address ;
int8_t harmonizerValues[2][8][4] = { { {0, 4, 7, 0}, //major triad
                                       {0, 3, 7, 0}, //minor triad
                                       {0, 4, 7,10}, //dominent chord
                                       {0, 3, 6, 0}, //diminished triad
                                       {0, 7,14, 0}, //open chord
                                       {0, 4, 8, 0}, //augmented triad
                                       {4, 7,12, 0}, //first inversion major
                                       {3, 7,12, 0} //first inversion minor
                                      },
                                     { {0, 2, 0, 0}, //major second
                                       {0, 3, 0, 0}, //minor third
                                       {0, 4, 0, 0}, //major third
                                       {0, 5, 0, 0}, //perfect fourth
                                       {0, 7, 0, 0}, //perfect fifth
                                       {0, 9, 0, 0}, //major sixth
                                       {0, 11, 0, 0}, //major seventh
                                       {0, 12, 0, 0} //octave
                                      }
                                    } ;

void setup(void) {
  Serial.begin(9600);
  
  if (fram.begin()) {  // you can stick the new i2c addr in here, e.g. begin(0x51);
    Serial.println("Found I2C FRAM");
  } else {
    Serial.println("I2C FRAM not identified ... check your connections?\r\n");
    Serial.println("Will continue in case this processor doesn't support repeated start\r\n");
  }
  
  // Read the first byte
  uint8_t test = fram.read8(0x0);
  Serial.print("Restarted "); Serial.print(test); Serial.println(" times");
  // Test write ++
  fram.write8(0x0, test+1);

  for(int i=0; i<2; i++) {
    for(int j=0; j<8; j++) {
      for(int k=0; k<4; k++) {
        address = 192 + 32*i + 4*j + k ;
        fram.write8(address, harmonizerValues[i][j][k]) ;
        Serial.print(address) ;
        Serial.print("\t") ;
        Serial.println(harmonizerValues[i][j][k]) ;
      }
    }
  }
  
}

void loop(void) {

}
