/*
 * This example shows how to read from a seesaw encoder module.
 * The available encoder API is:
 *      int32_t getEncoderPosition();
        int32_t getEncoderDelta();
        void enableEncoderInterrupt();
        void disableEncoderInterrupt();
        void setEncoderPosition(int32_t pos);
 */
#include <LiquidCrystal.h>
#include "Adafruit_seesaw.h"
#include "MenuRow.h"
#include "Menu.h"

#define MENU_SIZE         4

#define SS_SWITCH         24

#define SS0_ADDR          0x36
#define SS1_ADDR          0x38
#define SS2_ADDR          0x39
#define SS3_ADDR          0x3A

//                RS  EN  D0  D1  D2  D3  D4  D5  D6  D7
LiquidCrystal lcd( 2,  3, 11, 10,  9,  8,  7,  6,  5,  4);

int t0 = 0 ;
int tDel = 0 ;

Adafruit_seesaw ss[4] ;

//Encoder values
int8_t ssDel[5] = {0, 0, 0, 0, 0} ;
bool ssPush[4] = {0, 0, 0, 0} ;
bool ssPushLast[4] = {0, 0, 0, 0} ;


MenuRow synthRows[MENU_SIZE] ;
int8_t synthData[MENU_SIZE][4] = {{1, 100, 0, 0}, 
                                  {0, 100, 0, 0}, 
                                  {0, 100, 0, 0}, 
                                  {0, 100, 0, 0} };
Menu synthMenu(synthRows, MENU_SIZE, synthData, &lcd)  ;                              


int8_t powException[2]     = {     0,     1} ;
char*  powExceptionChar[2] = {" OFF","  ON"} ;
int8_t tuningException[24]     = {   100,   101,  102,   103,   104,   105,   106,   107,   108,   109,   110,   111,  -100,  -101, -102,  -103,  -104,  -105,  -106,  -107,  -108,  -109,  -110,  -111} ;
char*  tuningExceptionChar[24] = {" +1s"," +2s"," +3s"," +4s"," +5s"," +6s"," +7s"," +8s"," +9s","+10s","+11s","+12s"," -1s"," -2s"," -3s"," -4s"," -5s"," -6s"," -7s"," -8s"," -9s","-10s","-11s","-12s"} ;
int8_t emptyException[1]     = {     0} ; 
char*  emptyExceptionChar[1] = {"    "} ;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  lcd.begin(20, 4);

  synthMenu.initRow(0, " SIN POW VOL TUN    ",   0,   0,-111,   0,   1, 100, 111,   0) ;
  synthMenu.initRow(1, " SQR POW VOL TUN    ",   0,   0,-111,   0,   1, 100, 111,   0) ;
  synthMenu.initRow(2, " TRI POW VOL TUN    ",   0,   0,-111,   0,   1, 100, 111,   0) ;
  synthMenu.initRow(3, " PUL POW VOL TUN    ",   0,   0,-111,   0,   1, 100, 111,   0) ;


  for (int8_t i=0; i<4; i++){
    synthMenu.setExceptions(i, 0, powException, powExceptionChar, 2) ;
    synthMenu.setExceptions(i, 2, tuningException, tuningExceptionChar, 24) ;
    synthMenu.setExceptions(i, 3, emptyException, emptyExceptionChar, 1) ;
  }

  ss[0].begin(SS0_ADDR) ;
  ss[1].begin(SS1_ADDR) ;
  ss[2].begin(SS2_ADDR) ;
  ss[3].begin(SS3_ADDR) ;
  
  for (int i=0;i<4;i++) {   
    ss[i].pinMode(SS_SWITCH, INPUT_PULLUP);     // use a pin for the built in encoder switch

    ss[i].setGPIOInterrupts((uint32_t)1 << SS_SWITCH, 1);   //Enabling the interrupts 
    ss[i].enableEncoderInterrupt();
  }

}

void loop() {
  updateEncoder() ;
  synthMenu.update(ssDel) ;
  Serial.println(synthMenu.getRow()) ;
}

void updateEncoder() {
  ssDel[4] = 0 ;
  for (int i=0; i<4; i++) {
    ssPushLast[i] = ssPush[i] ;
    ssPush[i] = !ss[i].digitalRead(SS_SWITCH) ;
    ssDel[i] = ss[i].getEncoderDelta() ;
    switch (i){
      case 1:
        if (ssPush[i] != ssPushLast[i]){
          ssDel[4] = -1 ;
        }
      break;
      case 2:
        if (ssPush[i] != ssPushLast[i]){
          ssDel[4] = 1 ;
        }
      break;
    }    
  }  
}
