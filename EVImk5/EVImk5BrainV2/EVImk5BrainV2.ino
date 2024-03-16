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
#include <Adafruit_MCP4725.h>
#include "Adafruit_FRAM_I2C.h"


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
#define SS_MENU_SWITCH   24

#define SEESAW_ADDR           0x49
#define SEESAW_MENU_ADDR      0x39


//----------------------------------------Object Definitions----------------------------
Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_seesaw ss = Adafruit_seesaw(&Wire);
Adafruit_seesaw ssMenu ;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_MCP4725 dacLow;
Adafruit_MCP4725 dacHigh;
Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();

IntervalTimer dataReadTimer ;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI) ;


//-------------------------------------------Data Read Variables-------------------------
char buff[5] ;

bool updateNoteFlag      = 0 ;
bool touchReadFlag       = 1 ;
bool dataReadFlag        = 1 ;
bool encoderReadFlag     = 1 ;
bool encoderMenuReadFlag = 1 ;

//All times in milliseconds
uint32_t dataReadTime = 1 ;  //milliseconds
uint32_t dataReadTimeStart = 0 ; 
uint32_t encoderReadTime = 50 ; 
uint32_t encoderReadTimeStart = 0 ; 
uint32_t touchReadTime = 10 ;
uint32_t touchReadTimeStart = 0 ;
uint32_t encoderMenuReadTime = 50 ;
uint32_t encoderMenuReadTimeStart = 0 ; 

//-----------------------------------------Touch Sensor Variables-------------------------------------

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

//----------------------------------------Encoder Variables-------------------------------------------

int8_t encoderDelta[5]     = {0, 0, 0, 0, 0} ;
int8_t encoderSwitch[5]    = {0, 0, 0, 0, 0} ;
bool   encoderSwitchTog[5] = {1, 1, 1, 1, 1} ;

//------------------------------------Breath Sensor Variables-----------------------------------------

//Values for fast breath reading (in Volts)
float schmittLow  = 0.87 ;
float schmittHigh = 0.90 ;
float breathRead  = 0 ; 
int16_t breathVal = 0 ;

//--------------------------------------------MIDI Note Variables-------------------------------------

int noteMaskTouch[12] = { 1,  2,  4,  8, 16, 32, 64, 128, 256, 512, 1024, 2048} ;
int noteMaskVal[12]   = {25, 32, 39, 46, 53, 60, 67, 74,  81,  88, 95,  102 } ;

int currNote = 64 ;
int lastNote = 0 ;
bool noteFlag = false ;

/******************************************************************************************************
Menu Variables
******************************************************************************************************/

bool displayUpdateFlag = 0 ;

//                        Col1 Col2 Col3 Col4 Row
bool menuUpdateFlag[5]       = {0,   0,   0,   0,   0} ;
bool menuUpdateFlagSwitch[5] = {0,   0,   0,   0,   0} ;
int8_t menuDataDel[5]        = {0,   0,   0,   0,   0} ;
int8_t menuDataLast[5]       = {0,   0,   0,   0,   0} ;

//What state should the menu be in 
// 0 - Off
// 1 - Main Menu
// 2 - Synth
// 3 - Audio Settings
// 4 - Sensor Settings
// 5 - MIDI Settings
int8_t menuCase = 0 ;
uint32_t menuSleepTime = 60000 ;
uint32_t menuSleepTimeStart = 0 ;
uint32_t menuTimeStart = 0 ;

int8_t menuTextPos[6][2]   = { { 2,  2}, { 2, 12}, { 2, 22}, { 66,  2}, { 66, 12}, { 66, 22} } ;
int8_t menuBoxPos[6][2]    = { { 0,  0}, { 0, 10}, { 0, 20}, { 64,  0}, { 64, 10}, { 64, 20} } ;
int8_t menuBoxSize[2]      =   {63, 11} ;
int8_t menuCirclePos[6][2] = { {57,  5}, {57, 15}, {57, 25}, {121,  5}, {121, 15}, {121, 25} } ;

//-----------------------------------------Main Menu Variables----------------------------------

int8_t mainMenuCursor = 0 ;
int8_t mainMenuCursorLast = 0 ;

//-----------------------------------------Synth Menu Variables----------------------------------

int8_t synthCurrRow = 0 ;
int8_t synthLastRow = 1 ;
int8_t synthNumRow  = 17 ;

int8_t synthTopRow  = 0 ;
int8_t synthBotRow  = 1 ;
int8_t synthCurrRowPos = 0 ;

int16_t presetLength = 128 ;

int8_t synthDataMin[][4] = { {0,    0,    0,    0   },           //MAIN
                             {-40,  0,    0,    -50 },           //VOL
                             {0,    0,    0,    0   },           //AMP
                             {-111, -111, -111, -111},           //TUN
                             {0,    0,    0,    0   },           //PUL
                             {-100, 0,    0,    0   },           //FIL
                             {0,    0,    0,    0   },           //ENV
                             {0,    0,    0,    0   },           //PRT
                             {0,    0,    0,    0   },           //VIB
                             {0,    0,    0,    0   },           //VIB
                             {0,    0,    0,    0   },           //TRM
                             {0,    0,    0,    0   },           //TRM
                             {-50,  0,    0,    0   },           //RNG
                             {0,    0,    0,    0   },           //WAV
                             {0,    1,    0,    0   },           //DLY
                             {0,    0,    0,    0   },           //RVB
                             {0,    0,    0,    0   }   } ;      //FMT

int8_t synthDataMax[][4] = { {0,    0,    0,    0   },           //MAIN
                             {20,   100,  100,  50  },           //VOL
                             {100,  100,  100,  100 },           //AMP
                             {111,  111,  111,  111 },           //TUN
                             {100,  4,    100,  100 },           //PUL
                             {100,  100,  100,  100 },           //FIL
                             {100,  100,  100,  100 },           //ENV
                             {100,  100,  3,    100 },           //PRT
                             {4,    100,  111,  3   },           //VIB
                             {100,  100,  100,  100 },           //VIB
                             {4,    100,  100,  3   },           //TRM
                             {100,  100,  100,  100 },           //TRM
                             {50,   100,  100,  100 },           //RNG
                             {2,    100,  3,    100 },           //WAV
                             {100,  100,  100,  100 },           //DLY
                             {100,  100,  100,  0   },           //RVB
                             {2,    9,    100,  0   }   } ;      //FMT

int8_t synthDataVal[][4] = { {0,    0,    0,    0   },           //MAIN
                             {0,    10,   100,  0   },           //VOL
                             {0,    100,  0,    0   },           //AMP
                             {0,    0,    0,    0   },           //TUN
                             {50,   0,    0,    0   },           //PUL
                             {0,    100,  0,    20  },           //FIL
                             {0,    0,    100,  0   },           //ENV
                             {10,   0,    0,    0   },           //PRT
                             {0,    0,    0,    0   },           //VIB
                             {0,    0,    0,    0   },           //VIB
                             {0,    0,    0,    0   },           //TRM
                             {0,    0,    0,    0   },           //TRM
                             {0,    0,    10,   0   },           //RNG
                             {0,    0,    0,    0   },           //WAV
                             {0,    1,    100,  0   },           //DLY
                             {5,    0,    20,   0   },           //RVB
                             {0,    0,    0,    0   }   } ;      //FMT

char synthHeaders[][21]  = { " BACK               ",             //MAIN
                             " VOL  MN PRE  BR BAL",             //VOL
                             " AMP PUL SAW SQR TRI",             //AMP
                             " TUN PUL SAW SQR TRI",             //TUN
                             " PUL DTY SHP FRQ AMT",             //PUL
                             " FIL FRQ  BR RES  BR",             //FIL
                             " ENV ATK DLY SUS RLS",             //ENV
                             " PRT SNS CRV LNK AMT",             //PRT
                             " VIB SHP FRQ AMT LNK",             //VIB
                             " VIB ATK RLS FRQ AMT",             //VIB
                             " TRM SHP FRQ AMT LNK",             //TRM
                             " TRM ATK RLS FRQ AMT",             //TRM
                             " RNG POL STP MAX NSE",             //RNG
                             " WAV SHP AMT LNK AMT",             //WAV
                             " DLY FDB TME FRQ RES",             //DLY
                             " RVB  RM DMP AMP    ",             //RVB
                             " FMT SEX VOW AMT    "     } ;      //FMT

//MIDI CC Channels to send to and exceptions to standard sending procedure
int8_t synthDataCC[][4]  = { {-1,   -1,   -1,   -1  },           //MAIN
                             {7,    9,    10,   8   },           //VOL
                             {16,   17,   18,   19  },           //AMP
                             {20,   21,   22,   23  },           //TUN
                             {106,  107,  108,  109 },           //PUL
                             {14,   12,   15,   13  },           //FIL
                             {73,   74,   75,   72  },           //ENV
                             {6,    5,    89,   90  },           //PRT
                             {110,  111,  112,  113 },           //VIB
                             {114,  115,  116,  116 },           //VIB
                             {56,   57,   58,   59  },           //TRM
                             {60,   61,   62,   63  },           //TRM
                             {98,   99,   100,  101 },           //RNG
                             {85,   86,   87,   88  },           //WAV
                             {76,   77,   78,   79  },           //DLY
                             {102,  103,  104,  -1  },           //RVB
                             {91,   92,   93,   -1  }   } ;      //FMT

// Types of data to send
// 0: Standard (7bit unsigned int)
// 1: Toggle Type (0-Off 64-On)
// 2: LSB Negative (7bit positive data and 7bit negative data sent on CC+32)
// 3: Centered negative (Data from -64 to 63 has 64 added to be sent over 7 bits)
int8_t synthDataCCType[][4] = { {-1,   -1,   -1,   -1  },        //MAIN
                                {3,    0,    0,    3   },        //VOL
                                {0,    0,    0,    0   },        //AMP
                                {2,    2,    2,    2   },        //TUN
                                {0,    0,    0,    0   },        //PUL
                                {2,    0,    0,    0   },        //FIL
                                {0,    0,    0,    0   },        //ENV
                                {0,    0,    0,    0   },        //PRT
                                {0,    0,    0,    0   },        //VIB
                                {0,    0,    0,    0   },        //VIB
                                {0,    0,    0,    0   },        //TRM
                                {0,    0,    0,    0   },        //TRM
                                {3,    0,    0,    0   },        //RNG
                                {0,    0,    0,    0   },        //WAV
                                {0,    0,    0,    0   },        //DLY
                                {0,    0,    0,    -1  },        //RVB
                                {0,    0,    0,    -1  }   } ;   //FMT

//Types of Exceptions to Print
//Used for Data without Exceptions
int8_t      nullExc[1]        = {     0} ; 
char const* nullExcChar[1]    = {"    "} ;
//Print Toggle Type Data
int8_t      powExc[2]         = {     0,     1} ;
char const* powExcChar[2]     = {" OFF","  ON"} ;
//Print Frequency Type Data
int8_t      tuningExc[24]     = {   100,   101,   102,   103,   104,   105,   106,   107,   108,   109,   110,   111,  -100,  -101,  -102,  -103,  -104,  -105,  -106,  -107,  -108,  -109,  -110,  -111} ;
char const* tuningExcChar[24] = {" +1s"," +2s"," +3s"," +4s"," +5s"," +6s"," +7s"," +8s"," +9s","+10s","+11s","+12s"," -1s"," -2s"," -3s"," -4s"," -5s"," -6s"," -7s"," -8s"," -9s","-10s","-11s","-12s"} ;
//Print Empty Column
int8_t emptyExc[1]            = {     0} ; 
char const* emptyExcChar[1]   = {"    "} ;
//Waveshape Ecxeptions
int8_t wavshpExc[3]           = {     0,     1,     2} ;
char const* wavshpExcChar[3]  = {" ABS"," SIN","ATAN"} ;
//Expression Linking Exceptions
int8_t linkExc[4]             = {     0,     1,     2,     3} ;
char const* linkExcChar[4]    = {" OFF","  BR"," EXP"," MOD"} ;
//Expression for waveform shape exceptions
int8_t waveExc[5]             = {     0,     1,     2,     3,     4} ;
char const* waveExcChar[5]    = {" SIN"," SAW"," SQR"," TRI"," S&H"} ;
//Exceptions for vowel formant type
int8_t sexExc[3]              = {     0,     1,     2} ;
char const* sexExcChar[3]     = {"   M","   W","  Ch"} ;
//Vowels
int8_t vowelExc[10]           = {     0,     1,     2,     3,     4,     5,     6,     7,     8,     9} ;
char const*vowelExcChar[10]   = {"   i","   I","   e","  ae","   a","  uh","   u","  oo","  ow","  er"} ;
//Preset Names
int8_t presetExc[10]          = {     0,     1,     2,     3,     4,     5,     6,     7,     8,     9} ;
char const* presetExcChar[10] = {"USR1","USR2","USR3","USR4","USR5","USR6","USR7","USR8"," EVI","TRPT"} ;
//Audio Out
int8_t audioExc[4]            = {     0,     1,     2,     3} ;
char const* audioExcChar[4]   = {" OFF"," SPK"," LNE"," BTH"} ;
//Set the current values to usr preset
int8_t setExc[1]              = {     0} ;
char const* setExcChar[1]     = {" SET"} ;
int8_t backExc[1]             = {     0} ;
char const* backExcChar[1]    = {" BCK"} ;


//Storing all the exceptions to printing raw numbers
int8_t synthExcSize[][4]       = { {1,             1,             1,             1             },          //MAIN
                                   {0,             0,             0,             0             },          //VOL
                                   {0,             0,             0,             0             },          //AMP
                                   {24,            24,            24,            24            },          //TUN
                                   {0,             5,             0,             0             },          //PUL
                                   {0,             0,             0,             0             },          //FIL
                                   {0,             0,             0,             0             },          //ENV
                                   {0,             0,             4,             0             },          //PRT
                                   {5,             0,             24,            4             },          //VIB
                                   {0,             0,             0,             0             },          //VIB
                                   {5,             0,             0,             4             },          //TRM
                                   {0,             0,             0,             0             },          //TRM
                                   {0,             0,             0,             0             },          //RNG
                                   {3,             0,             4,             0             },          //WAV
                                   {0,             0,             0,             0             },          //DLY
                                   {0,             0,             0,             1             },          //RVB
                                   {3,             10,            0,             1             } } ;       //FMT

int8_t* synthExcVal[][4]       = { {emptyExc,      emptyExc,      emptyExc,      emptyExc      },          //MAIN
                                   {nullExc,       nullExc,       nullExc,       nullExc       },          //VOL
                                   {nullExc,       nullExc,       nullExc,       nullExc       },          //AMP
                                   {tuningExc,     tuningExc,     tuningExc,     tuningExc     },          //TUN
                                   {nullExc,       waveExc,       nullExc,       nullExc       },          //PUL
                                   {nullExc,       nullExc,       nullExc,       nullExc       },          //FIL
                                   {nullExc,       nullExc,       nullExc,       nullExc       },          //ENV
                                   {nullExc,       nullExc,       linkExc,       nullExc       },          //PRT
                                   {waveExc,       nullExc,       tuningExc,     linkExc       },          //VIB
                                   {nullExc,       nullExc,       nullExc,       nullExc       },          //VIB
                                   {waveExc,       nullExc,       nullExc,       linkExc       },          //TRM
                                   {nullExc,       nullExc,       nullExc,       nullExc       },          //TRM
                                   {nullExc,       nullExc,       nullExc,       nullExc       },          //RNG
                                   {wavshpExc,     nullExc,       linkExc,       nullExc       },          //WAV
                                   {nullExc,       nullExc,       nullExc,       nullExc       },          //DLY
                                   {nullExc,       nullExc,       nullExc,       emptyExc      },          //RVB
                                   {sexExc,        vowelExc,      nullExc,       emptyExc      } } ;       //FMT


const char** synthExcChar[][4] = { {emptyExcChar,  emptyExcChar,  emptyExcChar,  emptyExcChar  },          //MAIN
                                   {nullExcChar,   nullExcChar,   nullExcChar,   nullExcChar   },          //VOL
                                   {nullExcChar,   nullExcChar,   nullExcChar,   nullExcChar   },          //AMP
                                   {tuningExcChar, tuningExcChar, tuningExcChar, tuningExcChar },          //TUN
                                   {nullExcChar,   waveExcChar,   nullExcChar,   nullExcChar   },          //PUL
                                   {nullExcChar,   nullExcChar,   nullExcChar,   nullExcChar   },          //FIL
                                   {nullExcChar,   nullExcChar,   nullExcChar,   nullExcChar   },          //ENV
                                   {nullExcChar,   nullExcChar,   linkExcChar,   nullExcChar   },          //PRT
                                   {waveExcChar,   nullExcChar,   tuningExcChar, linkExcChar   },          //VIB
                                   {nullExcChar,   nullExcChar,   nullExcChar,   nullExcChar   },          //VIB
                                   {waveExcChar,   nullExcChar,   nullExcChar,   linkExcChar   },          //TRM
                                   {nullExcChar,   nullExcChar,   nullExcChar,   nullExcChar   },          //TRM
                                   {nullExcChar,   nullExcChar,   nullExcChar,   nullExcChar   },          //RNG
                                   {wavshpExcChar, nullExcChar,   linkExcChar,   nullExcChar   },          //WAV
                                   {nullExcChar,   nullExcChar,   nullExcChar,   nullExcChar   },          //DLY
                                   {nullExcChar,   nullExcChar,   nullExcChar,   emptyExcChar  },          //RVB
                                   {sexExcChar,    vowelExcChar,  nullExcChar,   emptyExcChar  } } ;       //FMT


//The hardware locations to print data to 
static int8_t synthHeaderPos[2][2]  = { {8, 0 }, 
                                       {8, 16} } ;

static int8_t synthDataPos[2][4][2] = {  { {32, 8 }, {56, 8 }, {80, 8 }, {104, 8 } }, 
                                        { {32, 24}, {56, 24}, {80, 24}, {104, 24} }  } ;

static int8_t synthArrowPos[2][2] = { {8, 8 }, 
                                     {8, 24} } ;

int        synthScrollPos[2]  = {0, SCREEN_HEIGHT*synthTopRow/synthNumRow} ;
static int synthScrollSize[2] = {4, max(2*SCREEN_HEIGHT/synthNumRow, 2) };


//--------------------------------------Audio Menu Variables-----------------------------------

int8_t audioMenuCursor = 0 ;
int8_t audioMenuCursorLast = 0 ;
int8_t audioMenuCase = 0 ;

int8_t audioOutCursor = 0 ;
int8_t audioOutCursorLast = 0 ;
int8_t audioOutData = 0b00000001 ;

int8_t audioEQCursor = 0 ;
int8_t audioEQCursorLast = 0 ;
int8_t 

int8_t audioPresetCursor = 0 ;
int8_t audioPresetCursorLast = 0 ;

//------------------------------------------Testing Variables-----------------------------------

//Measure how long functions take
uint32_t t0 = 0 ;
uint32_t t = 0 ;


/******************************************************************************
Setup
******************************************************************************/
void setup() {

//------------------------------Serial Setup-----------------------------------
  Serial.begin(115200);
  MIDI.begin() ;
  Serial1.begin(1000000) ;

//FRAM Setup for preset storage
if (fram.begin()) {  // you can stick the new i2c addr in here, e.g. begin(0x51);
  Serial.println("Found I2C FRAM");
} else {
  Serial.println("I2C FRAM not identified ... check your connections?\r\n");
  Serial.println("Will continue in case this processor doesn't support repeated start\r\n");
  while (1);
}


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


//----------------------------Menu Encoder Setup-------------------------------

if (! ssMenu.begin(SEESAW_MENU_ADDR) ) {
    Serial.println("Couldn't find seesaw on default address");
    while(1) delay(10);
  }
  Serial.println("seesaw started");

  uint32_t versionMenu = ((ssMenu.getVersion() >> 16) & 0xFFFF);
  if (versionMenu  != 4991){
    Serial.print("Wrong firmware loaded? ");
    Serial.println(versionMenu);
    while(1) delay(10);
  }
  Serial.println("Found Product 4991");

  // use a pin for the built in encoder switch
  ssMenu.pinMode(SS_MENU_SWITCH, INPUT_PULLUP);
  ssMenu.setGPIOInterrupts((uint32_t)1 << SS_MENU_SWITCH, 1);
  ssMenu.enableEncoderInterrupt();



//-------------------------------Cap Sense Setup-------------------------------
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

//Custom Schmitt Trigger Setup
dacLow.begin(0x62) ;
dacHigh.begin(0x63) ;
dacLow.setVoltage(voltageToDAC(schmittLow), false) ;
dacHigh.setVoltage(voltageToDAC(schmittHigh), false) ;

//-----------------------------------Interrupt Setup---------------------------
  dataReadTimer.begin(dataReadInt, dataReadTime*1000) ;
  attachInterrupt(9, touchReadInt, FALLING) ;
  attachInterrupt(4, encoderReadInt, FALLING) ;
  attachInterrupt(3, breathReadInt, CHANGE) ;
  attachInterrupt(5, encoderMenuReadInt, FALLING) ;
  

//-------------------------------------User Code-------------------------------
  display.clearDisplay() ;
  display.display() ;
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
  
    for (int i=0; i<12; i++){
      if (currtouched >= noteMaskTouch[i]){
        currNote = noteMaskVal[i] ;
      }
    }

    if (noteFlag){
      if (currNote != lastNote){
        MIDI.sendNoteOn(currNote, 100, 1) ;
        MIDI.sendNoteOff(lastNote, 100, 1) ;

        usbMIDI.sendNoteOn(currNote, 100, 1) ;
        usbMIDI.sendNoteOff(lastNote, 100, 1) ;

        lastNote = currNote ;
      }
    }
  }
}

void updateData(){
  if (dataReadFlag){
    dataReadFlag = 0 ;
    dataReadTimeStart = millis() ;

    if (noteFlag){
      breathRead = ADCToVoltage( analogRead(22) ) ;
      breathVal = breathAmount(breathRead) ;
      MIDI.sendControlChange(34, 0x7f & breathVal, 1) ;
      MIDI.sendControlChange(2, 0x7f & (breathVal >> 7), 1) ;

      usbMIDI.sendControlChange(34, 0x7f & breathVal, 1) ;
      usbMIDI.sendControlChange(2, 0x7f & (breathVal >> 7), 1) ;
    }

    
    //Read data only at set times to clear up processing power
    if (touchReadFlag){
      if (dataReadTimeStart - touchReadTimeStart >= touchReadTime){
        touchReadFlag = 0 ;

        currtouched = cap.touched();

        if (currtouched != lasttouched){
          updateNoteFlag = 1 ;
          // reset our state
          lasttouched = currtouched;
        }
      }
    }

    if (encoderReadFlag){
      if (dataReadTimeStart - encoderReadTimeStart >= encoderReadTime){
        encoderReadFlag = 0 ;

        encoderSwitch[0] = ss.digitalRead(SS_ENC0_SWITCH) ;
        encoderSwitch[1] = ss.digitalRead(SS_ENC1_SWITCH) ;
        encoderSwitch[2] = ss.digitalRead(SS_ENC2_SWITCH) ;
        encoderSwitch[3] = ss.digitalRead(SS_ENC3_SWITCH) ;

        for (int8_t i=0; i<4; i++) {
          //Get the change in encoder position to be used in menuUpdate
          encoderDelta[i] = ss.getEncoderDelta(i) ;
          menuDataDel[i] = encoderDelta[i] ;

          if (menuDataDel[i] != 0){
            menuUpdateFlag[i] = 1 ;
          }

          if (encoderSwitch[i] && !encoderSwitchTog[i]){
            menuUpdateFlagSwitch[i] = 1 ;
            menuUpdateFlag[i] = 1 ;
            encoderSwitchTog[i] = 1 ;
          } else if (!encoderSwitch[i] && encoderSwitchTog[i]){
            encoderSwitchTog[i] = 0 ;
          }
        }

      }
    }

    if (encoderMenuReadFlag){
      if (dataReadTimeStart - encoderMenuReadTimeStart >= encoderMenuReadTime){
        encoderMenuReadFlag = 0 ;
        encoderDelta[4] = ssMenu.getEncoderDelta() ;
        menuDataDel[4] = encoderDelta[4] ;

        encoderSwitch[4] = ssMenu.digitalRead(SS_MENU_SWITCH) ;

        if (menuDataDel[4] != 0){
          menuUpdateFlag[4] = 1 ;
        }

        if (encoderSwitch[4] && !encoderSwitchTog[4]){
          menuUpdateFlagSwitch[4] = 1 ;
          menuUpdateFlag[4] = 1 ;
          encoderSwitchTog[4] = 1 ;
        } else if (!encoderSwitch[4] && encoderSwitchTog[4]){
          encoderSwitchTog[4] = 0 ;
        }
      }
    }

  }
}

void updateMenu(){

  menuTimeStart = millis() ;

  if (menuCase != 0){
    if (menuTimeStart - menuSleepTimeStart >= menuSleepTime){
      menuCase = 0 ;

      display.clearDisplay() ;
      displayUpdateFlag = 1;
    } else if(menuUpdateFlag[0] || menuUpdateFlag[1] || menuUpdateFlag[2] || menuUpdateFlag[3] || menuUpdateFlag[4]){
      menuSleepTimeStart = menuTimeStart ;   
    }
  }

  switch(menuCase){
    case 0:  //Off
      offMenuUpdate() ;
    break;
    case 1:  //Main menu
      mainMenuUpdate() ;
    break;
    case 2:  //Synth Menu
      synthMenuUpdate() ;
    break;
    case 3:  //Audio Settings
      audioMenuUpdate() ;
    break;
    case 4:  //Sensor Settings
    break;
    case 5:  //MIDI Settings
    break;
  }

  //Clear all menu update data is not taken care of by other updates
  for (int8_t i=0; i<5; i++){
    menuUpdateFlag[i] = 0 ;
    menuUpdateFlagSwitch[i] = 0 ;
  }
  

  if (displayUpdateFlag){
    displayUpdateFlag = 0 ;
    display.display() ;
  }

}

void updateCC(int8_t _row, int8_t _col) {
  //Send Data differently depending on the entry type
  switch(synthDataCCType[_row][_col]){
    case 0:
      //Standard 
      MIDI.sendControlChange(synthDataCC[_row][_col], synthDataVal[_row][_col], 1) ;
      usbMIDI.sendControlChange(synthDataCC[_row][_col], synthDataVal[_row][_col], 1) ;
    break;
    case 1:
      //On/Off type data defaults to (0-63=Off, 64-127=On)
      if (synthDataVal[_row][_col]){
        MIDI.sendControlChange(synthDataCC[_row][_col], 64, 1) ;
        usbMIDI.sendControlChange(synthDataCC[_row][_col], 64, 1) ;
      } else {
        MIDI.sendControlChange(synthDataCC[_row][_col], 0, 1) ;
        usbMIDI.sendControlChange(synthDataCC[_row][_col], 0, 1) ;
      }
    break;
    case 2:
      //Send Negative values over the LSB channel
      if (synthDataVal[_row][_col] >= 0){
        MIDI.sendControlChange(synthDataCC[_row][_col], synthDataVal[_row][_col], 1) ;
        usbMIDI.sendControlChange(synthDataCC[_row][_col], synthDataVal[_row][_col], 1) ;
      } else {
        MIDI.sendControlChange(synthDataCC[_row][_col]+32, abs(synthDataVal[_row][_col]), 1) ;
        usbMIDI.sendControlChange(synthDataCC[_row][_col]+32, abs(synthDataVal[_row][_col]), 1) ;
      }
    break;
    case 3:
      //Send +/- Signals with -63/+64 range
      MIDI.sendControlChange(synthDataCC[_row][_col], synthDataVal[_row][_col]+64, 1) ;
      usbMIDI.sendControlChange(synthDataCC[_row][_col], synthDataVal[_row][_col]+64, 1) ;
    break;
    case -1:
      //dont send anything in this case
    break;
  }

  /* Print What CC is sent
  Serial.print("CC Channel: ") ;
  Serial.print(synthDataCC[_row][_col]) ;
  Serial.print("\t Value: ") ;
  Serial.println(synthDataVal[_row][_col]) ;
  */

}

/******************************************************************************************************
Menu Update Functions
******************************************************************************************************/

void offMenuUpdate(){
  for (int8_t i=0; i<5; i++){
    if (menuUpdateFlag[i]){
      menuUpdateFlag[i] = 0 ;
      menuCase = 1 ; //Wake up menu if any knobs or buttons pressed
      menuSleepTimeStart = millis() ; //Start the sleep timer
      display.clearDisplay() ;
      printMainAll() ;
    }
  }
}

void mainMenuUpdate(){
  if (menuUpdateFlag[4]){
    menuUpdateFlag[4] = 0 ;

    mainMenuCursorLast = mainMenuCursor ;
    mainMenuCursor = constrain(mainMenuCursor+menuDataDel[4], 0, 4) ;

    printMenuSelect(mainMenuCursor, mainMenuCursorLast) ;
  }

  if (menuUpdateFlagSwitch[4]){
    //Switch case to whatever menu we were on
    displayUpdateFlag = 1 ;
    display.clearDisplay() ;
    switch(mainMenuCursor){
      case 0:
        //Start Synth menu
        menuCase = 2 ; 
        printSynthAll() ;
      break;
      case 1:
        //Start Audio Settings menu
        menuCase = 3 ;
        printAudioMenu() ;
      break;
      case 2:
        //Start Sensor Settings menu
        menuCase = 4 ;
        printSensorAll() ;
      break;
      case 3:
        //Start MIDI Settings menu
        menuCase = 5 ;
        printMIDIAll() ;
      break;
      case 4:
        //Turn the menu off
        menuCase = 0 ;
      break;
    }
  }

}

void synthMenuUpdate(){
  if (menuUpdateFlag[4]){
    menuUpdateFlag[4] = 0 ;

    synthLastRow = synthCurrRow ;
    synthCurrRow = constrain(synthCurrRow + menuDataDel[4], 0, synthNumRow-1) ;
    menuDataDel[4] = 0 ;

    if (synthCurrRow != synthLastRow){
      displayUpdateFlag = 1 ;
      //Update the screen with all new headers and data
      if (synthCurrRow > synthLastRow){
        synthTopRow = synthCurrRow - 1 ;
        synthBotRow = synthCurrRow ;
        synthCurrRowPos = 1 ;
      } else {
        synthTopRow = synthCurrRow ;
        synthBotRow = synthCurrRow + 1 ;
        synthCurrRowPos = 0 ;
      }

      printSynthAll() ;
    }
  }

  for (int8_t i=0; i<4; i++){
    if (menuUpdateFlag[i]){
      menuUpdateFlag[i] = 0 ;

      menuDataLast[i] = synthDataVal[synthCurrRow][i] ;
      synthDataVal[synthCurrRow][i] = constrain(synthDataVal[synthCurrRow][i] + menuDataDel[i], synthDataMin[synthCurrRow][i], synthDataMax[synthCurrRow][i]) ;
      menuDataDel[i] = 0 ;

      if (synthDataVal[synthCurrRow][i] != menuDataLast[i]){
        //Update the value that changed only
        printSynthData(synthCurrRow, i) ;

        //Send MIDI Data of updated value
        updateCC(synthCurrRow, i) ;
      }
    }
  }

  if (menuUpdateFlagSwitch[4] && synthCurrRow == 0){
    menuCase = 1 ;

    displayUpdateFlag = 1 ;
    display.clearDisplay() ;
    printMainAll() ;

  }
}

void audioMenuUpdate(){
  //Change between the different sub menus for the audio menu
  switch(audioMenuCase){
    case 0:
      //Main Audio Menu
      audioMenuMainUpdate() ;
    break;
    case 1:
      //Audio Output Select Menu
      audioMenuOutUpdate() ;
    break;
    case 2:
      //Audio Equalizer Menu
      audioMenuEQUpdate() ;
    break;
    case 3:
      //Synth Presets Menu
      audioMenuPresetUpdate() ;
    break;
  }
  

}

void audioMenuMainUpdate(){
  if (menuUpdateFlag[4]){
    menuUpdateFlag[4] = 0 ;

    audioMenuCursorLast = audioMenuCursor ;
    audioMenuCursor = constrain(audioMenuCursor+menuDataDel[4], 0, 3) ;
    
    printMenuSelect(audioMenuCursor, audioMenuCursorLast) ;
  }

  if (menuUpdateFlagSwitch[4]){
    //Switch case to whatever menu we were on
    displayUpdateFlag = 1 ;
    display.clearDisplay() ;
    switch(audioMenuCursor){
      case 0:
        //Start Synth menu
        menuCase = 1 ; 
        printMainAll() ;
      break;
      case 1:
        //Start Audio Output Select
        audioMenuCase = 1 ;
        printAudioOutMenu() ;
      break;
      case 2:
        //Start Equalizer Menu
        audioMenuCase = 2 ;
        printAudioEQMenu() ;
      break;
      case 3:
        //Start Synth Presets Menu
        audioMenuCase = 3 ;
        printAudioPresetMenu() ;
      break;
    }
  }
}

void audioMenuOutUpdate(){
  if (menuUpdateFlag[4]){
    menuUpdateFlag[4] = 0 ;

    audioOutCursorLast = audioOutCursor ;
    audioOutCursor = constrain(audioOutCursor+menuDataDel[4], 0, 3) ;
    
    printMenuSelect(audioOutCursor, audioOutCursorLast) ;
  }

  if (menuUpdateFlagSwitch[4]){
    //Switch case to whatever menu we were on
    displayUpdateFlag = 1 ;

    switch(audioOutCursor){
      case 0:
        //Return to Audio Menu
        audioMenuCase = 0 ;
        display.clearDisplay() ; 
        printAudioMenu() ;
      break;
      case 1:
        //Toggle Line Out
        audioOutData = audioOutData^0b00000001 ;
        printAudioOutMarkers() ;
      break;
      case 2:
        //Toggle Speakers
        audioOutData = audioOutData^0b00000010 ;
        printAudioOutMarkers() ;
      break;
      case 3:
        //Toggle USB Audio
        audioOutData = audioOutData^0b00000100 ;
        printAudioOutMarkers() ;
      break;
    }
    MIDI.sendControlChange(0, audioOutData, 1) ;
    usbMIDI.sendControlChange(0, audioOutData, 1) ;
  }
}

void audioMenuEQUpdate(){

}

void audioMenuPresetUpdate(){

}
/******************************************************************************************************
Menu Print Functions
******************************************************************************************************/

void printMenuBox(int8_t pos, uint16_t color){
  display.drawRect(menuBoxPos[pos][0], menuBoxPos[pos][1], menuBoxSize[0], menuBoxSize[1], color) ;
}

void printMenuText(int8_t pos, const char* text){
  display.setCursor(menuTextPos[pos][0], menuTextPos[pos][1]) ;
  display.print(text) ;
}

void printMenuSelect(int8_t pos, int8_t posLast){
  displayUpdateFlag = 1 ;

  printMenuBox(posLast, SSD1306_BLACK) ;
  printMenuBox(pos, SSD1306_WHITE) ;
}

void printMenuCircle(int8_t pos, uint16_t color){
  display.fillCircle(menuCirclePos[pos][0], menuCirclePos[pos][1], 2, color) ;
}

//-------------------------------Main Menu Printing---------------------------

void printMainAll(){
  displayUpdateFlag = 1 ;

  printMainText() ;
  printMenuSelect(mainMenuCursor, mainMenuCursorLast) ;
}

void printMainText(){
  displayUpdateFlag = 1 ;

  printMenuText(0, "Synth") ;
  printMenuText(1, "Audio") ;
  printMenuText(2, "Sensor") ;
  printMenuText(3, "MIDI") ;
  printMenuText(4, "Off") ;
}

//-----------------------------Synth Menu Printing-----------------------------------

void printSynthAll() {
  displayUpdateFlag = 1 ;

  printSynthHeaders() ; 
  printSynthArrows() ;
  printSynthScroll() ;
  for (int8_t i=0; i<4; i++) {
    printSynthData(synthTopRow, i) ;
    printSynthData(synthBotRow, i) ;
  }
}

void printSynthScroll() {
  displayUpdateFlag = 1 ;

  display.fillRect(synthScrollPos[0], synthScrollPos[1], synthScrollSize[0], synthScrollSize[1], SSD1306_BLACK) ;
  synthScrollPos[1] = SCREEN_HEIGHT*synthTopRow/synthNumRow ;
  display.fillRect(synthScrollPos[0], synthScrollPos[1], synthScrollSize[0], synthScrollSize[1], SSD1306_WHITE) ;
}

void printSynthHeaders() {
  displayUpdateFlag = 1 ;

  display.setCursor(synthHeaderPos[0][0], synthHeaderPos[0][1]) ;
  display.print(synthHeaders[synthTopRow]) ;
  display.setCursor(synthHeaderPos[1][0], synthHeaderPos[1][1]) ;
  display.print(synthHeaders[synthBotRow]) ;    
}

void printSynthData(int8_t _row, int8_t _col){
  displayUpdateFlag = 1 ;
  sprintf(buff, "% 4i", synthDataVal[_row][_col]) ;

  if (synthExcSize[_row][_col] != 0) {
    for (int8_t i=0; i<synthExcSize[_row][_col]; i++){
      if (synthDataVal[_row][_col] == synthExcVal[_row][_col][i]){
        buff[0] = synthExcChar[_row][_col][i][0] ;
        buff[1] = synthExcChar[_row][_col][i][1] ;
        buff[2] = synthExcChar[_row][_col][i][2] ;
        buff[3] = synthExcChar[_row][_col][i][3] ;
      }
    }
  }

  if (_row == synthTopRow) {
    display.setCursor(synthDataPos[0][_col][0], synthDataPos[0][_col][1]) ;
    display.print(buff) ;
  } else if (_row == synthBotRow) {
    display.setCursor(synthDataPos[1][_col][0], synthDataPos[1][_col][1]) ;
    display.print(buff) ;
  }
}

void printSynthArrows() {
  if (synthCurrRow == synthTopRow) {
    display.setCursor(synthArrowPos[0][0], synthArrowPos[0][1]) ;
    display.print(" -> ") ;
    display.setCursor(synthArrowPos[1][0], synthArrowPos[1][1]) ;
    display.print("    ") ;
  } else {
    display.setCursor(synthArrowPos[0][0], synthArrowPos[0][1]) ;
    display.print("    ") ;
    display.setCursor(synthArrowPos[1][0], synthArrowPos[1][1]) ;
    display.print(" -> ") ;
  }
}

//------------------------------Audio Menu Printing----------------------------------

void printAudioMenu(){
  displayUpdateFlag = 1;
  printMenuBox(audioMenuCursor, SSD1306_WHITE) ;

  printMenuText(0, "Back") ;
  printMenuText(1, "Output") ;
  printMenuText(2, "Equalizer") ;
  printMenuText(3, "Presets") ;
}

void printAudioOutMenu(){
  displayUpdateFlag = 1 ;

  printMenuText(0, "Back") ;
  printMenuText(1, "Speaker") ;
  printMenuText(2, "Line Out") ;
  printMenuText(3, "USB") ;

  printAudioOutMarkers() ;

  printMenuBox(audioOutCursor, SSD1306_WHITE) ;
}

void printAudioOutMarkers(){
  displayUpdateFlag = 1 ;
  
  if (audioOutData & 0b00000001){
    printMenuCircle(1, SSD1306_WHITE) ;
  } else {
    printMenuCircle(1, SSD1306_BLACK) ;
  }
  if (audioOutData & 0b00000010){
    printMenuCircle(2, SSD1306_WHITE) ;
  } else {
    printMenuCircle(2, SSD1306_BLACK) ;
  }
  if (audioOutData & 0b00000100){
    printMenuCircle(3, SSD1306_WHITE) ;
  } else {
    printMenuCircle(3, SSD1306_BLACK) ;
  }
}

void printAudioEQMenu(){
  displayUpdateFlag = 1 ;

  printMenuText(1, "Back") ;
  printMenuBox(1, SSD1306_WHITE) ;
}

void printAudioPresetMenu(){
  displayUpdateFlag = 1 ;

  printMenuText(0, "Back") ;
  printMenuText(1, "Presets") ;
  printMenuText(2, "Save") ;
  printMenuBox(audioPresetCursor, SSD1306_WHITE) ;
}


//--------------------------------Sensor Menu Printing-------------------------------

void printSensorAll(){

}

//-----------------------------------MIDI Menu Printing-------------------------------

void printMIDIAll(){

}

/******************************************************************************************************
Formatting Functions
******************************************************************************************************/

int8_t mod(int8_t val, int8_t modulus){
  int8_t out = val % modulus ;

  if (val<0){
    out += modulus ;
  }

  return out ;
}

int16_t voltageToDAC(float volt){
  return (volt/3.3) * 4095 ;
}

float ADCToVoltage(int16_t val){
  return (float)val/1023 * 3.3 ;
}

int16_t breathAmount(float breath){
  return constrain(map(breath, schmittLow, 3.3, 0, 16383), 0, 16383);
}

/******************************************************************************************************
Interrupts
******************************************************************************************************/

void touchReadInt() {
  touchReadFlag = 1 ;
  touchReadTimeStart = millis() ;
}

void dataReadInt() {
  dataReadFlag = 1 ;
}

void encoderReadInt() {
  encoderReadFlag = 1 ;
  encoderReadTimeStart = millis() ;
}

void encoderMenuReadInt() {
  encoderMenuReadFlag = 1 ;
  encoderMenuReadTimeStart = millis() ;
}

void breathReadInt(){
  noteFlag = digitalReadFast(3) ;
  if (noteFlag){
    breathRead = ADCToVoltage(analogRead(22)) ;
    breathVal = breathAmount(breathRead) ;
    MIDI.sendControlChange(34, 0x7f & breathVal, 1) ;
    MIDI.sendControlChange(2, 0x7f & (breathVal >> 7), 1) ;
    MIDI.sendNoteOn(currNote, 100, 1) ;

    usbMIDI.sendControlChange(34, 0x7f & breathVal, 1) ;
    usbMIDI.sendControlChange(2, 0x7f & (breathVal >> 7), 1) ;
    usbMIDI.sendNoteOn(currNote, 100, 1) ;
  } else {
    MIDI.sendControlChange(34, 0, 1) ;
    MIDI.sendControlChange(2, 0, 1) ;
    MIDI.sendNoteOff(currNote, 100, 1) ;

    usbMIDI.sendControlChange(34, 0, 1) ;
    usbMIDI.sendControlChange(2, 0, 1) ;
    usbMIDI.sendNoteOff(currNote, 100, 1) ;
  }
}


/******************************************************************************
MIDI CC Table
******************************************************************************/

/*
Num   | Standard                              | Personal
------------------------------------------------------------------------------
0	    | Bank Select	                          | OUT
1	    | Modulation Wheel	                    | MOD 
2	    | Breath Controller	                    | BR
3	    | Undefined	                            | RTP
4	    | Foot Controller	                      | 
5	    | Portamento Time	                      | PRT TME (TIME)
6	    | Data Entry MSB	                      | PRT SNS (Sensitivity)
7	    | Main Volume	                          | VOL MN (MAIN)
8	    | Balance	                              | VOL BAL (BALANCE)
9	    | Undefined	                            | VOL PRE (PREAMP)
10	  | Pan	                                  | VOL BR (BREATH AMT)
11	  | Expression	                          | EXP
12	  | Effect Control 1	                    | FIL FRQ BR  (Filter Frequency Breath)
13	  | Effect Control 2	                    | FIL RES BR  (Filter Resonance Breath)
14    | Undefined                             | FIL FRQ + (Filter Frequency)
15    | Undefined	                            | FIL RES (Filter Resonance)
16    | General Purpose 1                     | SIN VOL
17    | General Purpose 2                     | SQR VOL
18    | General Purpose 3                     | TRI VOL
19    | General Purpose 4                     | PUL VOL
20    | Undefined	                            | SIN TUN +
21    | Undefined	                            | SQR TUN + 
22    | Undefined	                            | TRI TUN +
23    | Undefined	                            | PUL TUN +
24    | Undefined	                            | 
25    | Undefined	                            | 
26    | Undefined	                            | 
27    | Undefined	                            | 
28    | Undefined	                            | 
29    | Undefined	                            | 
30    | Undefined	                            | 
31    | Undefined	                            | 
32    | LSB 0                                 | 
33    | LSB 1                                 | MOD LSB
34    | LSB 2                                 | BR  LSB
35    | LSB 3                                 | RTP LSB
36    | LSB 4                                 | 
37    | LSB 5                                 | 
38    | LSB 6                                 | 
39    | LSB 7                                 | 
40    | LSB 8                                 | 
41    | LSB 9                                 | 
42    | LSB 10                                | 
43    | LSB 11                                | EXP LSB
44    | LSB 12                                | 
45    | LSB 13                                | 
46    | LSB 14                                | FIL FRQ -
47    | LSB 15                                | 
48    | LSB 16                                | 
49    | LSB 17                                | 
50    | LSB 18                                | 
51    | LSB 19                                | 
52    | LSB 20                                | SIN TUN -
53    | LSB 21                                | SQR TUN -
54    | LSB 22                                | TRI TUN -
55    | LSB 23                                | PUL TUN -
56    | LSB 24                                | TRM SHP
57    | LSB 25                                | TRM FRQ
58    | LSB 26                                | TRM AMT
59    | LSB 27                                | TRM LNK
60    | LSB 28                                | TRM ATK
61    | LSB 29                                | TRM RLS
62    | LSB 30                                | TRM FRQ
63    | LSB 31                                | TRM AMT
64	  | Damper Pedal On/Off                   | 
65	  | Portamento	On/Off                    | 
66	  | Sostenuto	On/Off                      | 
67	  | Soft Pedal	On/Off                    | 
68	  | Legato Footswitch	On/Off              | 
69	  | Hold 2                                | 
70	  | Sound Controller 1 (Variation)	      | 
71	  | Sound Controller 2 (Resonance)        | 
72	  | Sound Controller 3 (Release)          | ENV RELEASE
73	  | Sound Controller 4 (Attack)           | ENV ATTACK
74	  | Sound Controller 5 (Brightness)       | ENV DECAY
75    | Sound Controller 6                    | ENV SUSTAIN
76    | Sound Controller 7                    | DLY FEEDBACK
77    | Sound Controller 8                    | DLY TIME
78    | Sound Controller 9                    | DLY AMOUNT
79    | Sound Controller 10                   | DLY FREQUENCY
80    | General Purpose 5 On/Off              | SIN POW
81    | General Purpose 6 On/Off              | SQR POW
82    | General Purpose 7 On/Off              | TRI POW
83    | General Purpose 8 On/Off              | PUL POW
84	  | Portamento                            | 
85    | Undefined	                            | WAV SHP
86    | Undefined	                            | WAV SHP AMT
87    | Undefined	                            | WAV LNK
88    | Undefined	                            | WAV LNK AMT
89    | Undefined	                            | PRT LNK
90    | Undefined	                            | PRT LNK AMT
91	  | Effects 1 Depth	(reverb)              | FMT SEX           (VOWEL FORMAT)
92	  | Effects 2 Depth	(tremelo)             | FMT VOW
93	  | Effects 3 Depth	(chorus)              | FMT AMT
94	  | Effects 4 Depth	(detune)              | FMT UNDEFINED
95	  | Effects 5 Depth	(phaser)              | 
96	  | Data Increment                        | 
97	  | Data Decrement                        | 
98	  | Non-Registered Parameter              | RNG POL (POLARITY)
99	  | Non-Registered Parameter              | RNG STP
100	  | Registered Parameter                  | RNG MAX
101	  | Registered Parameter                  | RNG NSE
102   | Undefined	                            | RVB RM  ROOMSIZE
103   | Undefined	                            | RVB DMP DAMPING
104   | Undefined	                            | RVB AMT AMOUNT
105   | Undefined	                            | RVB UNDEFINED
106   | Undefined	                            | PUL DTY
107   | Undefined	                            | PUL SHP
108   | Undefined	                            | PUL FRQ
109   | Undefined	                            | PUL AMT
110   | Undefined	                            | VIB SHP
111   | Undefined	                            | VIB FRQ
112   | Undefined	                            | VIB AMT
113   | Undefined	                            | VIB LNK
114   | Undefined	                            | VIB FRQ
115   | Undefined	                            | VIB AMT
116   | Undefined	                            | VIB ATK
117   | Undefined	                            | VIB RLS
118   | Undefined	                            | EQ 40Hz
119   | Undefined	                            | EQ 80Hz
120	  | All Sounds Off                        | EQ 160Hz
121	  | Reset All Controllers	                | EQ 320Hz
122	  | Local Control                         | EQ 640Hz
123	  | All Notes Off                         | EQ 1280Hz
124	  | Omni Off	                            | EQ 2560Hz
125	  | Omni On	                              | EQ 5120Hz
126	  | Mono On	                              | EQ 10240Hz
127	  | Poly On	                              | EQ 20480Hz
*/