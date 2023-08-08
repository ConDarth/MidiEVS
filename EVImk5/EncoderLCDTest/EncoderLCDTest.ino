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
#include <seesaw_neopixel.h>

#define SS_SWITCH        24
#define SS_NEOPIX        6

#define SS0_ADDR          0x36
#define SS1_ADDR          0x38
#define SS2_ADDR          0x39
#define SS3_ADDR          0x3A

//                RS  EN  D0  D1  D2  D3  D4  D5  D6  D7
LiquidCrystal lcd( 2,  3, 11, 10,  9,  8,  7,  6,  5,  4);

int t0 = 0 ;
int tDel = 0 ;

Adafruit_seesaw ss[4] ;
seesaw_NeoPixel ssPixel[4] = {seesaw_NeoPixel(1, SS_NEOPIX, NEO_GRB + NEO_KHZ800), seesaw_NeoPixel(1, SS_NEOPIX, NEO_GRB + NEO_KHZ800), seesaw_NeoPixel(1, SS_NEOPIX, NEO_GRB + NEO_KHZ800), seesaw_NeoPixel(1, SS_NEOPIX, NEO_GRB + NEO_KHZ800)} ;
uint8_t ssPixelColor[4][3] = { {0, 255, 0}, {255, 255, 0}, {0, 0, 255}, {255, 0, 0}} ;


const uint8_t menuRowNum  = 4 ;
int8_t        menuRowCurr = 0 ;
int8_t        menuRowLast = 0 ;
int8_t        menuCurr    = 0 ;
int8_t        menuLast    = -1 ;
char   *menuTitle[menuRowNum] = {" Sin Pwr Vol Tun ###",
                                 " Sqr Pwr Vol Tun ###", 
                                 " Tri Pwr Vol Tun ###", 
                                 " Pul Pwr Vol Tun ###" } ;
                                    
int8_t  menuVal[menuRowNum][4][3] = {{ {   1,   1,   0}, { 100, 100,   0}, {   0, 111,-111}, {   0,  0,   0} }, 
                                     { {   1,   1,   0}, { 100, 100,   0}, {   0, 111,-111}, {   0,  0,   0} },
                                     { {   1,   1,   0}, { 100, 100,   0}, {   0, 111,-111}, {   0,  0,   0} }, 
                                     { {   1,   1,   0}, { 100, 100,   0}, {   0, 111,-111}, {   0,  0,   0} }} ;
bool menuUpdateFlag[5] = {0, 0, 0, 0, 1} ;

int8_t ssDel[4] = {0, 0, 0, 0} ;
bool ssPush[4] = {0, 0, 0, 0} ;
bool ssPushFlag[4] = {0, 0, 0, 0} ;




void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  lcd.begin(20, 4);

  ss[0].begin(SS0_ADDR) ;
  ss[1].begin(SS1_ADDR) ;
  ss[2].begin(SS2_ADDR) ;
  ss[3].begin(SS3_ADDR) ;

  ssPixel[0].begin(SS0_ADDR) ;
  ssPixel[1].begin(SS1_ADDR) ;
  ssPixel[2].begin(SS2_ADDR) ;
  ssPixel[3].begin(SS3_ADDR) ;
  
  for (int i=0;i<4;i++) {

    ssPixel[i].setBrightness(2);
    ssPixel[i].setPixelColor(0, ssPixelColor[i][0], ssPixelColor[i][1], ssPixelColor[i][2]) ;
    ssPixel[i].show();
    
    ss[i].pinMode(SS_SWITCH, INPUT_PULLUP);     // use a pin for the built in encoder switch

    ss[i].setGPIOInterrupts((uint32_t)1 << SS_SWITCH, 1);   //Enabling the interrupts 
    ss[i].enableEncoderInterrupt();
  }

  //Initialize the Menu
  updateMenuTitle() ;
}

void loop() {
  t0 = micros() ;
  updateEncoder() ;
  tDel = micros() - t0 ;
  Serial.print(tDel) ; Serial.print("  \t") ;
  t0 = micros() ;
  updateMenuTitle() ;
  tDel = micros() - t0 ;
  Serial.print(tDel) ; Serial.print("  \t") ;
  t0 = micros() ;
  updateMenuData(menuRowCurr) ;
  tDel = micros() - t0 ;
  Serial.println(tDel) ;
  // don't overwhelm serial port
  delay(20);
}

void updateEncoder() {

  for (int i=0; i<4; i++) {
    ssPush[i] = !ss[i].digitalRead(SS_SWITCH) ;
    ssDel[i] = ss[i].getEncoderDelta() ;
    
    if (ssPush[i] && !ssPushFlag[i]) {
      ssPushFlag[i] = 1 ;
      menuRowLast = menuRowCurr ;
      switch(i){
        case 1:
          menuRowCurr-- ;
        break;
        case 2:
          menuRowCurr++ ;
        break;
      }
      menuRowCurr = menuRowCurr%menuRowNum ;
      if (menuRowCurr < 0) {menuRowCurr += menuRowNum;}  

      menuCurr = menuRowCurr/2 ;
      menuLast = menuRowLast/2 ;
      menuUpdateFlag[4] = 1 ;
      
    } else if (ssPushFlag[i] && !ssPush[i]) {
      ssPushFlag[i] = 0 ;
    }

    if (ssDel[i] != 0) {
      menuVal[menuRowCurr][i][0] += ssDel[i] ;
      menuUpdateFlag[i] = 1 ;

      menuVal[menuRowCurr][i][0] = max(menuVal[menuRowCurr][i][2], menuVal[menuRowCurr][i][0]) ;
      menuVal[menuRowCurr][i][0] = min(menuVal[menuRowCurr][i][0], menuVal[menuRowCurr][i][1]) ;
    }
    
    
  }  
}



void updateMenuTitle(){
  
  if (menuUpdateFlag[4]) {
    menuUpdateFlag[4] = 0 ;
    
    if (menuCurr != menuLast) {
      //Reset the titles if we move to a new page of the menu
      lcd.setCursor(0,0) ;
      lcd.print(menuTitle[menuCurr*2  ]) ;
      lcd.setCursor(0,2) ;
      lcd.print(menuTitle[menuCurr*2+1]) ;

      menuUpdateFlag[0]=1;menuUpdateFlag[1]=1;menuUpdateFlag[2]=1;menuUpdateFlag[3]=1;
      updateMenuData(menuCurr*2) ;
      menuUpdateFlag[0]=1;menuUpdateFlag[1]=1;menuUpdateFlag[2]=1;menuUpdateFlag[3]=1;
      updateMenuData(menuCurr*2+1) ;
    }
    
    lcd.setCursor(1,2*(menuRowLast%2)+1) ;
    lcd.print("  ") ;
    lcd.setCursor(1,2*(menuRowCurr%2)+1) ;
    lcd.print("->") ;
  }
}

void updateMenuData(int8_t row) {
  switch(row) {
    case 0:
      if (menuUpdateFlag[0]) {
        if (menuVal[0][0][0]) {
          printWord4(4, 1, "ON") ;
        } else {
          printWord4(4, 1, "OFF") ;
        }
      }
      if (menuUpdateFlag[1]) {
        printInt4(8, 1, 100) ;
      }
      
      for(int i=1; i<4; i++) { 
        if (menuUpdateFlag[i]) {
          printInt4(4+4*i,1,menuVal[0][i][0]) ;   // display new position
          menuUpdateFlag[i] = 0 ;
        } 
      }
    break;
    case 1:
      if (menuUpdateFlag[0]) {
        if (menuVal[1][0][0]) {
          printWord4(4, 3, "ON") ;
        } else {
          printWord4(4, 3, "OFF") ;
        }
      }
      for(int i=1; i<4; i++) { 
        if (menuUpdateFlag[i]) {
          printInt4(4+4*i,3,menuVal[1][i][0]) ;   // display new position
          menuUpdateFlag[i] = 0 ;
        } 
      }
    break;
    case 2:
      if (menuUpdateFlag[0]) {
        if (menuVal[2][0][0]) {
          printWord4(4, 1, "ON") ;
        } else {
          printWord4(4, 1, "OFF") ;
        }
      }
      for(int i=1; i<4; i++) { 
        if (menuUpdateFlag[i]) {
          printInt4(4+4*i,1,menuVal[2][i][0]) ;   // display new position
          menuUpdateFlag[i] = 0 ;
        } 
      }
    break;
    case 3:
      if (menuUpdateFlag[0]) {
        if (menuVal[3][0][0]) {
          printWord4(4, 3, "ON") ;
        } else {
          printWord4(4, 3, "OFF") ;
        }
      }
      for(int i=1; i<4; i++) { 
        if (menuUpdateFlag[i]) {
          printInt4(4+4*i,3,menuVal[3][i][0]) ;   // display new position
          menuUpdateFlag[i] = 0 ;
        } 
      }
    break;
  }
}

void printInt4(int row, int col, int num) {
  lcd.setCursor(row, col) ;
  String val = String(num) ;
  
  switch( val.length() ) {
    case 1:
      lcd.print("   " + val) ;
    break;
    case 2:
      lcd.print("  " + val) ;
    break;
    case 3:
      lcd.print(" " + val) ;
    break;
    case 4:
      lcd.print(val) ;
    break;
  }
  
}

void printWord4(int row, int col, String val) {
  lcd.setCursor(row, col) ;
  
  switch( val.length() ) {
    case 1:
      lcd.print("   " + val) ;
    break;
    case 2:
      lcd.print("  " + val) ;
    break;
    case 3:
      lcd.print(" " + val) ;
    break;
    case 4:
      lcd.print(val) ;
    break;
  }
  
}
