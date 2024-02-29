/*********************************************************
Connor Lindsay

MIDI Wind Synth Transmit Controller
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <MIDI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_seesaw.h"


//------------------------------Constant Addresses-----------------------------
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

#define SS_NEO_PIN       18
#define SS_ENC0_SWITCH   12
#define SS_ENC1_SWITCH   14
#define SS_ENC2_SWITCH   17
#define SS_ENC3_SWITCH   9

#define SEESAW_ADDR      0x49


//----------------------------------------Object Definitions-------------------
Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_seesaw ss = Adafruit_seesaw(&Wire);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

IntervalTimer dataReadTimer ;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI) ;


//-------------------------------------------Note Data-------------------------
char buff[5] ;

bool updateNoteFlag = 0 ;
bool touchReadFlag = 1 ;
bool dataReadFlag = 1 ;
bool encoderReadFlag = 1;

uint16_t lasttouched = 0;
uint16_t currtouched = 0;


int noteMaskTouch[12] = { 1,  2,  4,  8, 16, 32, 64, 128, 256, 512, 1024, 2048} ;
int noteMaskVal[12]   = {64, 65, 66, 67, 68, 69, 70,  71,  72,  73,   74,   75} ;

int currNote = 64 ;
int lastNote = 0 ;

//--------------------------------------------------Menu Data--------------------------------------   
bool displayUpdateFlag = 0 ;

//                        Col1 Col2 Col3 Col4 Row
bool menuUpdateFlag[5] = {0,   0,   0,   0,   0} ;
int8_t menuDataDel[5]  = {0,   0,   0,   0,   0} ;
int8_t menuDataLast[4] = {0,   0,   0,   0  } ;

//                        Up Dn
bool menuRowDelTog[2]  = {0, 0} ;
int8_t menuCurrRow = 0 ;
int8_t menuLastRow = 1 ;
int8_t menuNumRow  = 3 ;

int8_t menuTopRow  = 0 ;
int8_t menuBotRow  = 1 ;
int8_t menuCurrRowPos = 0 ;
 

int8_t menuDataMin[][4] = { {0,    0,    0,    0   },
                            {-111, -111, -111, -111},
                            {0,    0,    0,    0   }   } ;

int8_t menuDataMax[][4] = { {100,  100,  100,  100 },
                            {111,  111,  111,  111 },
                            {1,  1,  1,  1 }   } ;

int8_t menuDataVal[][4] = { {100,  0,    0,    0  },
                            {0,    0,    0,    0  },
                            {1,    1,    1,    1  }   } ;

char menuHeaders[][21]  = { " VOL SIN SQR TRI PUL", 
                            " TUN SIN SQR TRI PUL",
                            " POW SIN SQR TRI PUL"    } ;


//Types of Exceptions to Print
//Print Toggle Type Data
int8_t      powExc[2]         = {     0,     1} ;
char const* powExcChar[2]     = {" OFF","  ON"} ;
//Print Frequency Type Data
int8_t      tuningExc[24]     = {   100,   101,  102,   103,   104,   105,   106,   107,   108,   109,   110,   111,  -100,  -101, -102,  -103,  -104,  -105,  -106,  -107,  -108,  -109,  -110,  -111} ;
char const* tuningExcChar[24] = {" +1s"," +2s"," +3s"," +4s"," +5s"," +6s"," +7s"," +8s"," +9s","+10s","+11s","+12s"," -1s"," -2s"," -3s"," -4s"," -5s"," -6s"," -7s"," -8s"," -9s","-10s","-11s","-12s"} ;
//Print Empty Column
int8_t emptyExc[1]            = {     0} ; 
char const* emptyExcChar[1]   = {"    "} ;
//Used for Data without Exceptions
int8_t      nullExc[1]        = {     0} ; 
char const* nullExcChar[1]    = {"    "} ;


//Storing all the exceptions to printing raw numbers
int8_t menuExcSize[][4]       = { {0,             0,             0,             0             }, 
                                  {24,            24,            24,            24            }, 
                                  {2,             2,             2,             2             } } ;

int8_t* menuExcVal[][4]       = { {nullExc,       nullExc,       nullExc,       nullExc       },
                                  {tuningExc,     tuningExc,     tuningExc,     tuningExc     },
                                  {powExc,        powExc,        powExc,        powExc        } } ; 

const char** menuExcChar[][4] = { {nullExcChar,   nullExcChar,   nullExcChar,   nullExcChar   },  
                                  {tuningExcChar, tuningExcChar, tuningExcChar, tuningExcChar },
                                  {powExcChar,    powExcChar,    powExcChar,    powExcChar    } } ;




//The hardware locations to print data to 
static int8_t menuHeaderPos[2][2]  = { {8, 0 }, 
                                       {8, 16} } ;

static int8_t menuDataPos[2][4][2] = {  { {32, 8 }, {56, 8 }, {80, 8 }, {104, 8 } }, 
                                        { {32, 24}, {56, 24}, {80, 24}, {104, 24} }  } ;

static int8_t menuArrowPos[2][2] = { {8, 8 }, 
                                     {8, 24} } ;

int        menuScrollPos[2]  = {0, SCREEN_HEIGHT*menuTopRow/menuNumRow} ;
static int menuScrollSize[2] = {4, max(2*SCREEN_HEIGHT/menuNumRow, 2) };

/******************************************************************************
Setup
******************************************************************************/
void setup() {

//------------------------------Serial Setup-----------------------------------
  Serial.begin(115200);
  MIDI.begin() ;
  Serial1.begin(1000000) ;


//------------------------------OLED DISPLAY Setup-----------------------------
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Initialize Display Style
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);  


//----------------------------Quad Encoder Setup-------------------------------
  if (! ss.begin(SEESAW_ADDR)) {
    Serial.println("Couldn't find seesaw on default address");
    while(1) delay(10);
  }
  Serial.println("seesaw started");
  uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
  if (version  != 5752){
    Serial.print("Wrong firmware loaded? ");
    Serial.println(version);
    while(1) delay(10);
  }
  Serial.println("Found Product 5752");

  ss.pinMode(SS_ENC0_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC1_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC2_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC3_SWITCH, INPUT_PULLUP);
  ss.setGPIOInterrupts(1UL << SS_ENC0_SWITCH | 1UL << SS_ENC1_SWITCH | 
                       1UL << SS_ENC2_SWITCH | 1UL << SS_ENC3_SWITCH, 1);

  // get starting positions
  for (int e=0; e<4; e++) {
    ss.enableEncoderInterrupt(e);
  }
  Serial.println("Turning on interrupts");


//-------------------------------Cap Sense Setup-------------------------------
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");


//-----------------------------------Interrupt Setup---------------------------
  dataReadTimer.begin(dataReadInt, 10000) ;
  attachInterrupt(2, touchReadInt, FALLING) ;
  attachInterrupt(3, encoderReadInt, FALLING) ;
  

//-------------------------------------User Code-------------------------------
  printMenuAll() ;
}

/******************************************************************************
Loop
******************************************************************************/

void loop() {
  updateData() ;
  updateNote() ;
  updateMenu() ;

}

/******************************************************************************
Functions
******************************************************************************/

//---------------------------Update Functions----------------------------------

void updateNote(){
  if (updateNoteFlag){
    updateNoteFlag = 0 ;
    
    if (currtouched == 0){
      MIDI.sendNoteOff(currNote, 100, 1) ;
      Serial.print(currNote) ;
      Serial.println(" Off") ;
      lastNote = 0 ;
    } else {
      for (int i=0; i<12; i++){
        if (currtouched >= noteMaskTouch[i]){
          currNote = noteMaskVal[i] ;
        }
      }

      if (currNote != lastNote){
        MIDI.sendNoteOn(currNote, 100, 1) ;
        MIDI.sendNoteOff(lastNote, 100, 1) ;
        Serial.print(currNote) ;
        Serial.println(" On") ;

        lastNote = currNote ;
      }
    }
    

  }
}

void updateData(){
  if (dataReadFlag){
    dataReadFlag = 0 ;
    
    //Read data only at set times to clear up processing power
    if (touchReadFlag){
      touchReadFlag = 0 ;

      currtouched = cap.touched();

      if (currtouched != lasttouched){
        updateNoteFlag = 1 ;
        // reset our state
        lasttouched = currtouched;
      }
    }
  }

  if (encoderReadFlag) {
    encoderReadFlag = 0 ;

    for (int8_t i=0; i<4; i++) {
      //Get the change in encoder position to be used in menuUpdate
      menuDataDel[i] = ss.getEncoderDelta(i) ;
      if (menuDataDel[i] != 0){
        menuUpdateFlag[i] = 1 ;
      }
    }

    //Get any change in menuRow from switches
    //Check if we have moved up a menu row
    if (!ss.digitalRead(SS_ENC1_SWITCH) && !menuRowDelTog[0]){
      menuUpdateFlag[4] = 1;
      menuDataDel[4] = -1 ;
      menuRowDelTog[0] = 1 ;
    } else if (ss.digitalRead(SS_ENC1_SWITCH) && menuRowDelTog[0]) {
      menuRowDelTog[0] = 0 ;
    }
    //Check if we have moved down a menu row
    if (!ss.digitalRead(SS_ENC2_SWITCH) && !menuRowDelTog[1]){
      menuUpdateFlag[4] = 1;
      menuDataDel[4] = 1 ;
      menuRowDelTog[1] = 1 ;
    } else if (ss.digitalRead(SS_ENC2_SWITCH) && menuRowDelTog[1]) {
      menuRowDelTog[1] = 0 ;
    }

  }

}

void updateMenu(){

  if (menuUpdateFlag[4]){
    menuUpdateFlag[4] = 0 ;

    menuLastRow = menuCurrRow ;
    menuCurrRow = constrain(menuCurrRow + menuDataDel[4], 0, menuNumRow-1) ;
    menuDataDel[4] = 0 ;

    if (menuCurrRow != menuLastRow){
      displayUpdateFlag = 1 ;
      //Update the screen with all new headers and data
      if (menuCurrRow > menuLastRow){
        menuTopRow = menuCurrRow - 1 ;
        menuBotRow = menuCurrRow ;
        menuCurrRowPos = 1 ;
      } else {
        menuTopRow = menuCurrRow ;
        menuBotRow = menuCurrRow + 1 ;
        menuCurrRowPos = 0 ;
      }

      printMenuAll() ;
    }
  }

  for (int8_t i=0; i<4; i++){
    if (menuUpdateFlag[i]){
      menuUpdateFlag[i] = 0 ;

      menuDataLast[i] = menuDataVal[menuCurrRow][i] ;
      menuDataVal[menuCurrRow][i] = constrain(menuDataVal[menuCurrRow][i] + menuDataDel[i], menuDataMin[menuCurrRow][i], menuDataMax[menuCurrRow][i]) ;
      menuDataDel[i] = 0 ;

      if (menuDataVal[menuCurrRow][i] != menuDataLast[i]){
        //Update the value that changed only
        printMenuData(menuCurrRow, i) ;
      }
    }
  }

  if (displayUpdateFlag){
    displayUpdateFlag = 0 ;
    display.display() ;
  }

}

//--------------------------Formatting-----------------------------------------

int8_t mod(int8_t val, int8_t modulus){
  int8_t out = val % modulus ;

  if (val<0){
    out += modulus ;
  }

  return out ;
}

//-----------------------------Menu Printing-----------------------------------

void printMenuAll() {
  displayUpdateFlag = 1 ;

  printMenuHeaders() ; 
  printMenuArrows() ;
  printMenuScroll() ;
  for (int8_t i=0; i<4; i++) {
    printMenuData(menuTopRow, i) ;
    printMenuData(menuBotRow, i) ;
  }
}

void printMenuScroll() {
  displayUpdateFlag = 1 ;

  display.fillRect(menuScrollPos[0], menuScrollPos[1], menuScrollSize[0], menuScrollSize[1], SSD1306_BLACK) ;
  menuScrollPos[1] = SCREEN_HEIGHT*menuTopRow/menuNumRow ;
  display.fillRect(menuScrollPos[0], menuScrollPos[1], menuScrollSize[0], menuScrollSize[1], SSD1306_WHITE) ;
}

void printMenuHeaders() {
  displayUpdateFlag = 1 ;

  display.setCursor(menuHeaderPos[0][0], menuHeaderPos[0][1]) ;
  display.print(menuHeaders[menuTopRow]) ;
  display.setCursor(menuHeaderPos[1][0], menuHeaderPos[1][1]) ;
  display.print(menuHeaders[menuBotRow]) ;    
}

void printMenuData(int8_t _row, int8_t _col){
  displayUpdateFlag = 1 ;
  sprintf(buff, "% 4i", menuDataVal[_row][_col]) ;

  if (menuExcSize[_row][_col] != 0) {
    for (int8_t i=0; i<menuExcSize[_row][_col]; i++){
      if (menuDataVal[_row][_col] == menuExcVal[_row][_col][i]){
        buff[0] = menuExcChar[_row][_col][i][0] ;
        buff[1] = menuExcChar[_row][_col][i][1] ;
        buff[2] = menuExcChar[_row][_col][i][2] ;
        buff[3] = menuExcChar[_row][_col][i][3] ;
      }
    }
  }

  if (_row == menuTopRow) {
    display.setCursor(menuDataPos[0][_col][0], menuDataPos[0][_col][1]) ;
    display.print(buff) ;
  } else if (_row == menuBotRow) {
    display.setCursor(menuDataPos[1][_col][0], menuDataPos[1][_col][1]) ;
    display.print(buff) ;
  }
}

void printMenuArrows() {
  if (menuCurrRow == menuTopRow) {
    display.setCursor(menuArrowPos[0][0], menuArrowPos[0][1]) ;
    display.print(" -> ") ;
    display.setCursor(menuArrowPos[1][0], menuArrowPos[1][1]) ;
    display.print("    ") ;
  } else {
    display.setCursor(menuArrowPos[0][0], menuArrowPos[0][1]) ;
    display.print("    ") ;
    display.setCursor(menuArrowPos[1][0], menuArrowPos[1][1]) ;
    display.print(" -> ") ;
  }
}

//--------------------------Interrupts-----------------------------------------

void touchReadInt() {
  touchReadFlag = 1 ;
}

void dataReadInt() {
  dataReadFlag = 1 ;
}

void encoderReadInt() {
  encoderReadFlag = 1 ;
}
