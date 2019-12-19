#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_FRAM_I2C.h"

/**********************************************************************************************************************************************/

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

/**********************************************************************************************************************************************/

#define SELECT_BUTTON_PIN 3
#define BACK_BUTTON_PIN 2

#define JOYSTICK_X_PORT A0
#define JOYSTICK_Y_PORT A1
#define JOYSTICK_LOWER_THR 370
#define JOYSTICK_UPPER_THR 653

/**********************************************************************************************************************************************/

#define XPOS 0 
#define YPOS 1 
#define XMAX 2
#define YMAX 3
#define XSCROLL 4
#define YSCROLL 5
#define XSIZE 6
#define YSIZE 7
#define ABSVAL 8

/**********************************************************************************************************************************************/

#define MAIN_MENU 0
#define SENSOR_ADJUST_MENU 1
#define MP_MODE 2
#define MP_ADJUSTER 3
#define MP_CHORD_SELECT 6
#define MP_PRESET_SELECT 8
#define CHORD_PITCH 9
#define SENSOR_ADJUST 10
#define BREATH_CURVE 11

/**********************************************************************************************************************************************/

#define SENSOR_UPDATE_DELAY 40

#define SENSOR_ADJUST_RANGE_1 0
#define SENSOR_ADJUST_RANGE_2 1
#define SENSOR_ADJUST_LOWER_THR_1 2
#define SENSOR_ADJUST_LOWER_THR_2 3
#define SENSOR_ADJUST_UPPER_THR_1 4
#define SENSOR_ADJUST_UPPER_THR_2 5
#define SENSOR_ADJUST_MAX_1 6
#define SENSOR_ADJUST_MAX_2 7

/**********************************************************************************************************************************************/

#define HARMONIZER 0 
#define ROTATOR 1
#define PRESET 2 

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

                           // xpos ypos xmax ymax xscroll yscroll xsize ysize absval
int8_t menuCursor[12][9] = { {   1,   1,   1,   6,      1,      1,    1,    4,     1},    //main menu select
                             {   1,   1,   1,   5,      1,      1,    1,    4,     1},    //sensor adjust select
                             {   1,   1,   1,   3,      1,      1,    1,    3,     1},    //multiphonics mode select
                             {   1,   1,   1,   4,      1,      1,    1,    3,     1},    //multiphonics adjust selector (harmonizer)
                             {   1,   1,   1,   4,      1,      1,    1,    3,     1},    //multiphonics adjust selector (rotator)
                             {   1,   1,   2,   4,      1,      1,    2,    3,     1},    //multiphonics adjust selector (presets)
                             {   1,   1,   2,   5,      1,      1,    2,    3,     1},    //multiphonics adjust chord selector
                             {   1,   1,   2,   4,      1,      1,    2,    3,     1},    //multiphonics adjust chord selector w/o presets
                             {   1,   1,   2,   4,      1,      1,    2,    3,     1},    //multiphonics adjust preset select
                             {   1,   1,   2,   2,      1,      1,    2,    2,     1},    //chord pitch selection
                             {   1,   2,   1,   3,      1,      1,    1,    3,     1},    //sensor adjuster select
                             {   1,   1,   1,   5,      1,      1,    1,    3,     1} } ; //breath curve select


/**********************************************************************************************************************************************/

boolean menuUpdate = true ;
int8_t menuCase = 0 ;

/**********************************************************************************************************************************************/

int8_t sensorAdjustMenuCase = 0 ;
int8_t sensorAdjustCase = 0 ;
boolean sensorAdjustBlinker = 1 ;
unsigned long sensorAdjustLastTime = 0 ;
unsigned long calibrationTimer = 0 ;
static uint8_t calibrationSampleSize = 50 ;
uint8_t calibrationSampler = 0 ;
uint8_t calibrationTimings = 500/calibrationSampleSize ;
uint16_t calibrationData[50] ;
float calibrationMean = 0 ;
float calibrationSD = 0 ;
uint16_t sensorAdjustAddress[8] = {0x20, 0x28, 0x30, 0x38, 0x40, 0x48, 0x50, 0x58} ;
int16_t sensorAdjustRange = 1023 ;
int16_t sensorAdjustLowerTHR = 250 ;
int16_t sensorAdjustUpperTHR = 300 ;
int16_t sensorAdjustMAX = 650 ;
int16_t sensorRealPosition = 0 ;
uint8_t sensorAdjustTHRState = 0 ;

/**********************************************************************************************************************************************/

int8_t transpositionPosition = 0 ;
int8_t transpositionMAX = 12 ;
int8_t transpositionMIN = -12 ;
int8_t transpositionMenuCase = 0 ;
unsigned long blinkerLastTime = 0 ;
int transpositionAddress = 0x60 ;

/**********************************************************************************************************************************************/

uint16_t breathCurveAddress = 0x61 ;
uint8_t breathCurveSelectType = 0 ;
int8_t breathCurveRate[] = {0, 0, 0} ; //log, exp, sin
unsigned long breathCurveTimer = 0 ;
boolean breathCurveBlinker = true ;
uint8_t breathCurveBlinkerState = 0 ; //which controller to change 0=menu, 1=const, 2=linear, 3=log, 4=exp


/**********************************************************************************************************************************************/

int8_t mpSelectMenuCase = 0 ;

/**********************************************************************************************************************************************/

int8_t mpAdjusterMenuCase = 0 ;
int8_t mpAdjustChordSelector = 0 ;
int8_t mpAdjustChordSelectCase = 0 ;
int8_t mpAdjustChordMenuCase = 0 ;
int8_t mpAdjustChordPresetCase = 0 ;
int8_t mpAdjustPitchNum[2] = {0, 0} ;
boolean mpAdjustPitchSelect = 0 ;
int8_t mpAdjustPitchLast = 0 ;
boolean mpAdjustPitchBlinker[4] = {1, 1, 1, 1} ;
int8_t mpAdjustValues[8][4] ;
uint16_t static mpAdjustAddress[3] = {256, 384, 512} ;
String mpAdjustType = "Harmonizer" ;
char mpAdjustTypeShort = 'H' ;

/**********************************************************************************************************************************************/

boolean selectFunction = false ;
boolean selectFunctionToggle = false ;
boolean selectButton = false ;
boolean selectButtonToggle = false ;
boolean backFunction = false ;
boolean backFunctionToggle = false ;
boolean backButton = false ;
boolean backButtonToggle = false ;

/**********************************************************************************************************************************************/

boolean cursorUp = false ;
boolean cursorUpToggle = false ;
boolean cursorDown = false ;
boolean cursorDownToggle = false ;
uint16_t joystickY = 512 ;
boolean joystickYToggle = false ;
boolean cursorLeft = false ;
boolean cursorLeftToggle = false ;
boolean cursorRight = false ;
boolean cursorRightToggle = false ;
uint16_t joystickX = 512 ;
boolean joystickXToggle = false ;
int16_t joystickXAbs = 0 ;
int16_t joystickYAbs = 0 ;

unsigned long timer = 0 ;

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  if (fram.begin()) {  // you can stick the new i2c addr in here, e.g. begin(0x51);
    Serial.println("Found I2C FRAM");
  } else {
    Serial.println("I2C FRAM not identified ... check your connections?\r\n");
    Serial.println("Will continue in case this processor doesn't support repeated start\r\n");
  }

  display.display();
  delay(1000); // Pause for 1 seconds

  pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP) ;
  pinMode(BACK_BUTTON_PIN, INPUT_PULLUP) ;

  transpositionPosition = fram.read8(transpositionAddress) ; //reads transposition from fram to initialize
  
  breathCurveSelectType = fram.read8(breathCurveAddress) ; //initializes values for the breath curves
  breathCurveRate[0] = fram.read8(breathCurveAddress+1) ;
  breathCurveRate[1] = fram.read8(breathCurveAddress+2) ;
  breathCurveRate[2] = fram.read8(breathCurveAddress+3) ;
  //run the quantization for the breath curves here based on retreived numbers
}

/**********************************************************************************************************************************************/

void loop() {  
  // put your main code here, to run repeatedly
  joystickUpdate() ;  
  buttonUpdate() ;
  
  mainMenuControl() ;  
  mainMenuPrint() ;  
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void joystickUpdate() {
  joystickY = analogRead(JOYSTICK_Y_PORT) ;
  joystickX = analogRead(JOYSTICK_X_PORT) ;
  
  if (joystickY > JOYSTICK_UPPER_THR) {
    if (!joystickYToggle) {
      cursorDown = true ;
      cursorDownToggle = true ;
      joystickYToggle = true ;
      menuUpdate = true ;
    }  
    joystickYAbs = JOYSTICK_UPPER_THR - joystickY ;
  } 
  if (joystickY < JOYSTICK_LOWER_THR) {
    if (!joystickYToggle) {
      cursorUp = true ;
      cursorUpToggle = true ;
      joystickYToggle = true ;
      menuUpdate = true ;
    }  
    joystickYAbs = JOYSTICK_LOWER_THR - joystickY ;
  } 
  if (joystickYToggle && (joystickY > JOYSTICK_LOWER_THR+20) && (joystickY < JOYSTICK_UPPER_THR-20)) {
    joystickYToggle = false ;
    cursorUp = false ;
    cursorDown = false ;

    joystickYAbs = 0 ;
  }

  if (joystickX < JOYSTICK_LOWER_THR) {
    if (!joystickXToggle) {
      menuUpdate = true ;
      cursorRight = true ;
      cursorRightToggle = true ;
      joystickXToggle = true ;
    }
    joystickXAbs = JOYSTICK_LOWER_THR - joystickX ;
  }
  if (joystickX > JOYSTICK_UPPER_THR) {
    if (!joystickXToggle) {
      menuUpdate = true ;
      cursorLeft = true ;
      cursorLeftToggle = true ;
      joystickXToggle = true ;
    }
    joystickXAbs = JOYSTICK_UPPER_THR - joystickX ;
  }
  if (joystickXToggle && (joystickX > JOYSTICK_LOWER_THR+20) && (joystickX < JOYSTICK_UPPER_THR-20)) {
    joystickXToggle = false ;
    cursorLeft = false ;
    cursorRight = false ;

    joystickXAbs = 0 ;
  }
}

/**********************************************************************************************************************************************/

void buttonUpdate() {
  selectButton = digitalRead(SELECT_BUTTON_PIN) ;
  backButton = digitalRead(BACK_BUTTON_PIN) ;

  if (!selectButton && !selectButtonToggle) {
    selectButtonToggle = true ;
    selectFunction = true ;
    selectFunctionToggle = true ;
    menuUpdate = true ;
  } 
  if (selectButton && selectButtonToggle) {
    selectButtonToggle = false ;
    selectFunction = false ;
  }
  if (!backButton && !backButtonToggle) {
    backButtonToggle = true ;
    backFunction = true ;
    backFunctionToggle = true ;
    menuUpdate = true ;
  } 
  
  if (backButton && backButtonToggle) {
    backButtonToggle = false ;
    backFunction = false ;
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void mainMenuControl() {
  switch(menuCase) {
    case 0:
      initialMenuControl() ;
    break;
    case 1:
      sensorAdjustMenuControl() ;
    break;
    case 2:
      transpositionMenuControl() ;
    break;
    case 3:
      breathCurveMenuControl() ;
    break;
    case 4:
      harmonizerMenuControl() ;
    break;
    case 5:
      rotatorMenuControl() ;
    break;
    case 6:
      presetMenuControl() ;
    break;
    case 7:
      sevenMenuControl() ;
    break;
    case 8:
      eightMenuControl() ;
    break;
    default: 

    break;
  }
}

/**********************************************************************************************************************************************/

void mainMenuPrint() {
  if (menuUpdate) {
    display.clearDisplay() ;

    switch(menuCase) {
      case 0:
        initialMenuPrint() ;
      break;
      case 1:
        sensorAdjustMenuPrint() ;
      break;
      case 2:
        transpositionMenuPrint() ;
      break;
      case 3:
        breathCurveMenuPrint() ;
      break;
      case 4:
        harmonizerMenuPrint() ;
      break;
      case 5:
        rotatorMenuPrint() ;
      break;
      case 6:
        presetMenuPrint() ;
      break;
      case 7:
        sevenMenuPrint() ;
      break;
      case 8:
        eightMenuPrint() ;
      break;
      default: 

      break;
    }

    
    display.display() ;
    menuUpdate = false ;
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void initialMenuControl() {
  if (selectFunction && selectFunctionToggle) {
    selectFunctionToggle = false ;
    menuCase = menuCursor[MAIN_MENU][YPOS] ;
  }
  
  menuControl(MAIN_MENU) ;
}

/**********************************************************************************************************************************************/

void initialMenuPrint() {
    for (int i=0; i<4; i++) {
      
      switch(menuCursor[MAIN_MENU][YSCROLL]+i) {
        case 1:
          display.setCursor(4, (4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Sensor") ;
          display.print(" ") ;
          display.print("Adjust") ;      
          break; 
        case 2:
          display.setCursor(4, (4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Transposition") ;

          display.setCursor((100-2*sizeOfInt(transpositionPosition)), (4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print(transpositionPosition) ;
          
        break;
        case 3:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ; 
          display.print("Breath") ;
          display.print(" ") ;
          display.print("Curve") ;
          /*  
          display.print("Multi-Phonics") ;
          display.print(" ") ;
          display.print("Mode") ; 
          */   
        break;
        case 4:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Harmonizer") ;  
        break;
        case 5:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Rotator") ;  
        break;
        case 6:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Chord Presets") ;  
        break;
        case 7:
          
        break;
        case 8:
          
        break;
        
      }
    }
    
    display.drawRect(1, (1+(menuCursor[MAIN_MENU][YPOS]-menuCursor[MAIN_MENU][YSCROLL])*16), 126, 13, WHITE) ;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void sensorAdjustMenuControl() {
  switch(sensorAdjustMenuCase) {
    case 0: 
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        menuCase = 0 ;
      }
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        sensorAdjustMenuCase = menuCursor[SENSOR_ADJUST_MENU][YPOS] ;
        
        sensorAdjustRange = fram.read8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_RANGE_1) ;
        sensorAdjustRange += fram.read8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_RANGE_2) << 8 ;
        
        sensorAdjustFRAMRead() ;
      }
      
      menuControl(SENSOR_ADJUST_MENU) ;
      
    break;
    case 1:
      sensorAdjustControl() ;
    break;
    case 2:
      sensorAdjustControl() ;
    break;
    case 3:
      sensorAdjustControl() ;
    break;
    case 4:
      sensorAdjustControl() ;
    break;
    case 5:
      sensorAdjustControl() ;
    break;
    case 6:
      sensorAdjustControl() ;
    break;
  }
  
}

/**********************************************************************************************************************************************/

void sensorAdjustMenuPrint() {

  switch(sensorAdjustMenuCase) {
    case 0:
      for (int i=0; i<4; i++) {
      
      switch(menuCursor[SENSOR_ADJUST_MENU][YSCROLL]+i) {
        case 1:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Pressure") ;
          display.print(" ") ; 
          display.print("Sensor") ;      
          break; 
        case 2:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Pitch") ; 
          display.print(" ") ;
          display.print("Bend") ;
          display.print(" ") ;
          display.print("Up") ; 
        break;
        case 3:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Pitch") ; 
          display.print(" ") ;
          display.print("Bend") ;
          display.print(" ") ;
          display.print("Down") ; 
        break;
        case 4:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;           
          display.print("Bite") ; 
          display.print(" ") ; 
          display.print("Sensor") ;    
        break;
        case 5:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Extra") ; 
          display.print(" ") ;
          display.print("Mod") ;
        break;
        case 6:
          
        break;
        case 7:
          
        break;
        case 8:
          
        break;
        
      }
    }
    
    display.drawRect(1, (1+(menuCursor[SENSOR_ADJUST_MENU][YPOS]-menuCursor[SENSOR_ADJUST_MENU][YSCROLL])*16), 126, 13, WHITE) ;
    break;
    case 1:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Pressure") ;
      
      sensorAdjustPrint() ;
    break;
    case 2:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Pitch") ; 
      display.print(" ") ;
      display.print("Bend") ;
      display.print(" ") ;
      display.print("Up") ;  

      sensorAdjustPrint() ;
    break;
    case 3:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Pitch") ; 
      display.print(" ") ;
      display.print("Bend") ;
      display.print(" ") ;
      display.print("Down") ;

      sensorAdjustPrint() ;      
    break;
    case 4:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Bite") ; 
      display.print(" ") ;
      display.print("Sensor") ;  

      sensorAdjustPrint() ;
    break;
    case 5:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Extra") ; 
      display.print(" ") ;
      display.print("Mod") ; 

      sensorAdjustPrint() ;
    break;
    case 6:
      
    break;
  }
    
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void sensorAdjustControl() {

  switch(sensorAdjustMenuCase) {
    case 1:
      sensorRealPosition = 1023 - analogRead(A0) ;
    break;
    case 2:
      sensorRealPosition = 200 ;
    break;
    case 3:
      sensorRealPosition = 200 ;
    break;
    case 4:
      sensorRealPosition = 200 ;
    break;
    case 5:
      sensorRealPosition = 200 ;
    break;
  }
  sensorRealPosition = constrain(sensorRealPosition, 0, sensorAdjustRange) ;
  
  switch(sensorAdjustCase) {
    case 0:
      menuControl(SENSOR_ADJUST) ;
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        sensorAdjustMenuCase = 0 ;
        menuCursor[SENSOR_ADJUST][YPOS] = 2 ;
      }
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        sensorAdjustCase = menuCursor[SENSOR_ADJUST][YPOS] ;
        calibrationTimer = millis() ;
      }
    break;
    case 1:
      if (calibrationSampler <= calibrationSampleSize) {
        if ((millis() - calibrationTimer) >= calibrationTimings*calibrationSampler) {
          calibrationData[calibrationSampler] = sensorRealPosition ;
          calibrationSampler ++ ;
        }

        if (calibrationSampler == calibrationSampleSize) {
          calibrationMean = 0 ;
          calibrationSD = 0 ;
          
          for (int i=0; i<calibrationSampleSize; i++) {
            calibrationMean += calibrationData[i] ;
          }
          calibrationMean = calibrationMean/calibrationSampleSize ;
          
          for (int i=0; i<calibrationSampleSize; i++) {
            calibrationSD += sq(calibrationData[i]-calibrationMean) ;
          }
          calibrationSD = calibrationSD/(calibrationSampleSize-1) ;
          calibrationSD = sqrt(calibrationSD) ;

          calibrationSampler ++ ;
        }
      }
      
      if ((millis() - calibrationTimer) >= 1000 && (calibrationSampler > calibrationSampleSize)) {
        sensorAdjustCase = 0 ;

        uint16_t diff = sensorAdjustMAX - calibrationMean ;
        
        sensorAdjustLowerTHR = calibrationMean + 2*calibrationSD + 0.05*diff ;
        sensorAdjustUpperTHR = calibrationMean + 5*calibrationSD  + 0.1*diff;

        sensorAdjustLowerTHR = constrain(sensorAdjustLowerTHR, 0, sensorAdjustRange) ;
        sensorAdjustUpperTHR = constrain(sensorAdjustUpperTHR, 0, sensorAdjustRange) ;

        sensorAdjustFRAMWrite() ;

        calibrationSampler = 0 ;
      }
      
    break; 
    case 2:
      switch(sensorAdjustTHRState) {
        case 0:
          if (backFunction && backFunctionToggle) {
            backFunctionToggle = false ;
            sensorAdjustCase = 0 ;
            sensorAdjustTHRState = 0 ;

            sensorAdjustFRAMRead() ;
          }
          if (selectFunction && selectFunctionToggle) {
            selectFunctionToggle = false ;
            sensorAdjustTHRState = 1 ;
            
          }
 
          if ((millis() - sensorAdjustLastTime) > SENSOR_UPDATE_DELAY) {
            float adjuster = (float) (joystickXAbs * SENSOR_UPDATE_DELAY) / (JOYSTICK_LOWER_THR) ;
            adjuster = (adjuster * sensorAdjustRange) / 2000 ;
          
            sensorAdjustUpperTHR += adjuster ;
            sensorAdjustUpperTHR = constrain(sensorAdjustUpperTHR, 0, sensorAdjustRange) ;
            if (sensorAdjustUpperTHR < sensorAdjustLowerTHR) {
              sensorAdjustLowerTHR = sensorAdjustUpperTHR ;
            }
            if (sensorAdjustUpperTHR > sensorAdjustMAX) {
              sensorAdjustMAX = sensorAdjustUpperTHR ;
            }
          }
        break;
        case 1:
          if (backFunction && backFunctionToggle) {
            backFunctionToggle = false ;
            sensorAdjustCase = 0 ;
            sensorAdjustTHRState = 0 ;

            sensorAdjustFRAMRead() ;
          }
          if (selectFunction && selectFunctionToggle) {
            selectFunctionToggle = false ;
            sensorAdjustCase = 0 ;
            sensorAdjustTHRState = 0 ;

            sensorAdjustFRAMWrite() ;
          }
          
          if ((millis() - sensorAdjustLastTime) > SENSOR_UPDATE_DELAY) {
            float adjuster = (float) (joystickXAbs * SENSOR_UPDATE_DELAY) / (JOYSTICK_LOWER_THR) ;
            adjuster = (adjuster * sensorAdjustRange) / 2000 ;
          
            sensorAdjustLowerTHR += adjuster ;
            sensorAdjustLowerTHR = constrain(sensorAdjustLowerTHR, 0, sensorAdjustRange) ;
            if (sensorAdjustLowerTHR > sensorAdjustUpperTHR) {
              sensorAdjustUpperTHR = sensorAdjustLowerTHR ;
            }
            if (sensorAdjustLowerTHR > sensorAdjustMAX) {
              sensorAdjustMAX = sensorAdjustLowerTHR ;
            }
          }
        break;
      }
    break;
    case 3:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        sensorAdjustCase = 0 ;

        sensorAdjustFRAMRead() ;
      }
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        sensorAdjustCase = 0 ;

        sensorAdjustFRAMWrite() ;
      }
      if ((millis() - sensorAdjustLastTime) > SENSOR_UPDATE_DELAY) {
        float adjuster = (float) (joystickXAbs * SENSOR_UPDATE_DELAY) / (JOYSTICK_LOWER_THR) ;
        adjuster = (adjuster * sensorAdjustRange) / 2000 ;
        
        sensorAdjustMAX += adjuster ;
        sensorAdjustMAX = constrain(sensorAdjustMAX, 0, sensorAdjustRange) ;
        if (sensorAdjustMAX < sensorAdjustUpperTHR) {
          sensorAdjustUpperTHR = sensorAdjustMAX ;
        }
        if (sensorAdjustMAX < sensorAdjustLowerTHR) {
          sensorAdjustLowerTHR = sensorAdjustMAX ;
        }
      }
    break;
  }

  if ((millis() - sensorAdjustLastTime) > SENSOR_UPDATE_DELAY) {
    menuUpdate = true ;
    sensorAdjustLastTime = millis() ;
  }
}

/**********************************************************************************************************************************************/

void sensorAdjustFRAMRead() {
  sensorAdjustLowerTHR = fram.read8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_LOWER_THR_1) ;
  sensorAdjustLowerTHR += fram.read8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_LOWER_THR_2) << 8 ;
      
  sensorAdjustUpperTHR = fram.read8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_UPPER_THR_1) ;
  sensorAdjustUpperTHR += fram.read8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_UPPER_THR_2) << 8 ;
        
  sensorAdjustMAX = fram.read8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_MAX_1) ;
  sensorAdjustMAX += fram.read8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_MAX_2) << 8 ;
}

/**********************************************************************************************************************************************/

void sensorAdjustFRAMWrite() {
  int8_t data1 = sensorAdjustLowerTHR & B11111111 ;
  int8_t data2 = sensorAdjustLowerTHR >> 8 ;
  fram.write8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_LOWER_THR_1, data1) ;
  fram.write8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_LOWER_THR_2, data2) ;
 
  data1 = sensorAdjustUpperTHR & B11111111 ;
  data2 = sensorAdjustUpperTHR >> 8 ;
  fram.write8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_UPPER_THR_1, data1) ;
  fram.write8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_UPPER_THR_2, data2) ;

  data1 = sensorAdjustMAX & B11111111 ;
  data2 = sensorAdjustMAX >> 8 ;
  fram.write8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_MAX_1, data1) ;
  fram.write8(sensorAdjustAddress[menuCursor[SENSOR_ADJUST_MENU][YPOS]-1]+SENSOR_ADJUST_MAX_2, data2) ;
}

/**********************************************************************************************************************************************/

void sensorAdjustPrint() {
  display.setCursor(108,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("CAL") ;  

  display.setCursor(4,21) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("THR") ; 

  display.setCursor(4,36) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("SEN") ;  
  
  display.setCursor(4,51) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("MAX") ;  
    
  if (menuCursor[SENSOR_ADJUST][YPOS] == 1) {
    display.drawRect(105, 1, 23, 13, WHITE) ;
  } else if (menuCursor[SENSOR_ADJUST][YPOS] == 2) {
    display.drawRect(1, 18, 23, 13, WHITE) ;
  } else if (menuCursor[SENSOR_ADJUST][YPOS] == 3) {
    display.drawRect(1, 48, 23, 13, WHITE) ;
  }
  
  display.drawRect(26, 18, 102, 13, WHITE) ;
  display.drawFastVLine(26, 22, 5, BLACK) ;
  display.drawFastVLine(127, 22, 5, BLACK) ;

  uint16_t a = (float) sensorAdjustLowerTHR*100/sensorAdjustRange ;
  uint16_t b = (float) sensorAdjustUpperTHR*100/sensorAdjustRange ;
  display.drawFastVLine(27+a, 22, 5, WHITE) ; //variable for the Lower THR setting
  display.drawFastVLine(27+b, 21, 7, WHITE) ; //variable for the Upper THR setting
  
  display.drawFastVLine(26, 36, 7, WHITE) ;
  display.drawFastVLine(127, 36, 7, WHITE) ;

  uint16_t c = (float) sensorRealPosition*100/sensorAdjustRange ;
  display.drawFastVLine(27+c, 38, 3, WHITE) ; //variable for realtime sensor output  


  display.drawRect(26, 48, 102, 13, WHITE) ;
  display.drawFastVLine(26, 52, 5, BLACK) ;
  display.drawFastVLine(127, 52, 5, BLACK) ;

  uint16_t d = (float) sensorAdjustMAX*100/sensorAdjustRange ;
  display.drawFastVLine(27+d, 51, 7, WHITE) ; // variable for MAX setting

  switch(sensorAdjustCase) {
    case 0:
    break;
    case 1:
      display.fillRect(0, 0, 128, 36, BLACK) ;
      display.fillRect(0, 44, 128, 20, BLACK) ;
      display.setCursor(19, 17) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Calibrating") ;
      display.print(" ") ;
      display.print("...") ;
    break;
    case 2:
    break;
    case 3:
    break;
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void transpositionMenuControl() {
  
  if ((millis() - blinkerLastTime > 400) && (transpositionMenuCase == 0)) {
    transpositionMenuCase = 1;
    menuUpdate = true ;
    blinkerLastTime = millis() ;
  }
  if ((millis() - blinkerLastTime > 200) && (transpositionMenuCase == 1)) {
    transpositionMenuCase = 0 ;
    menuUpdate = true ;
    blinkerLastTime = millis() ;
  }
  
  if (backFunction && backFunctionToggle) {
    backFunctionToggle = false ;
    menuCase = 0 ;
    transpositionPosition = fram.read8(transpositionAddress) ;
  }
  if (cursorLeft && cursorLeftToggle) {
    cursorLeftToggle = false ;
    menuCase = 0 ;
  }
  
  if (selectFunction && selectFunctionToggle) {
    selectFunctionToggle = false ;
    menuCase = 0 ;
    fram.write8(transpositionAddress, transpositionPosition) ;
  }
  if (cursorRight && cursorRightToggle) {
    cursorRightToggle = false ;
    menuCase = 0 ;
  }

  if (cursorUpToggle && cursorUp) {
    transpositionPosition ++ ;
    cursorUpToggle = false ;
  }
  if (cursorDownToggle && cursorDown) {
    transpositionPosition -- ;
    cursorDownToggle = false ;
  }
  transpositionPosition = constrain(transpositionPosition, transpositionMIN, transpositionMAX) ;

  
}

/**********************************************************************************************************************************************/

void transpositionMenuPrint() {
  for (int i=0; i<4; i++) {
    switch(menuCursor[MAIN_MENU][YSCROLL]+i) {
      case 1:
        display.setCursor(4,(4+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print("Sensor") ;
        display.print(" ") ;
        display.print("Adjust") ;   
      break;
      case 2:
        display.setCursor(4,(4+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print("Transposition") ;
      break;
      case 3:
        display.setCursor(4,(4+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print("Breath") ;
        display.print(" ") ;
        display.print("Curve") ;    
      break;
      case 4:
        display.setCursor(4,(4+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print("Harmonizer") ;  
      break;
      case 5:
        display.setCursor(4,(4+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print("Rotator") ;  
      break;
    }
  }

  switch(transpositionMenuCase) {
    case 0: 
      int s = sizeOfInt(transpositionPosition) ;
          
      display.setCursor((100-2*s), (36-menuCursor[MAIN_MENU][YSCROLL]*16)) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;
      display.print(transpositionPosition) ;      
    break;
    case 1:
    
    break;
  }

  display.drawRect(1, (1+(menuCursor[MAIN_MENU][YPOS]-menuCursor[MAIN_MENU][YSCROLL])*16), 126, 13, WHITE) ;
  
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void breathCurveMenuControl() {
  switch(breathCurveBlinkerState) {
    case 0:
      menuControl(BREATH_CURVE) ;
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        menuCase = 0 ;
      }
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        breathCurveBlinkerState = menuCursor[BREATH_CURVE][YPOS] ;
    
        breathCurveSelectType = menuCursor[BREATH_CURVE][YPOS]-1 ;
        fram.write8(breathCurveAddress, breathCurveSelectType) ;
      }
      
    break;
    case 1:
      breathCurveBlinkerState = 0 ;
    break;
    case 2:
      breathCurveBlinkerState = 0 ;
    break;
    case 3:
      breathCurveRateControl(0) ;
    break;
    case 4:
      breathCurveRateControl(1) ;
    break;
    case 5:
      breathCurveRateControl(2) ;
    break; 
  } 
}

/**********************************************************************************************************************************************/

void breathCurveMenuPrint() {
  display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Breath") ;
  display.print(" ") ;
  display.print("Curve") ;
  
  for (int i=0; i<4; i++) {
    switch(menuCursor[BREATH_CURVE][YSCROLL]+i) {
      case 1:
        display.setCursor(16,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print("Constant") ;
      break;
      case 2:
        display.setCursor(16,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print("Linear") ;
      break;
      case 3:
        display.setCursor(16,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print("Logarithmic") ;
        
        display.setCursor((100-2*sizeOfInt(breathCurveRate[0]+1)), (20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print(breathCurveRate[0]+1) ;

        if ((breathCurveBlinker == 0) && (breathCurveBlinkerState == 3)) {
          display.fillRect(90, (20+16*i), 20, 9, BLACK) ;
        }
      break;
      case 4:
        display.setCursor(16,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print("Exponential") ; 

        display.setCursor((100-2*sizeOfInt(breathCurveRate[1]+1)), (20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print(breathCurveRate[1]+1) ;

        if ((breathCurveBlinker == 0) && (breathCurveBlinkerState == 4)) {
          display.fillRect(90, (20+16*i), 20, 9, BLACK) ;
        }
      break;
      case 5:
        display.setCursor(16,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print("Sinusoidal") ;

        display.setCursor((100-2*sizeOfInt(breathCurveRate[2]+1)), (20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;   
        display.print(breathCurveRate[2]+1) ;

        if ((breathCurveBlinker == 0) && (breathCurveBlinkerState == 5)) {
          display.fillRect(90, (20+16*i), 20, 9, BLACK) ;
        }
      break;
    }
  }

  display.drawRect(13, (17+(menuCursor[BREATH_CURVE][YPOS]-menuCursor[BREATH_CURVE][YSCROLL])*16), 113, 13, WHITE) ;
  
  int selectPosition = 21+(breathCurveSelectType+1-menuCursor[BREATH_CURVE][YSCROLL])*16 ;
  if ((selectPosition < 20) || (selectPosition > 64)) {
    
  } else { 
    display.fillRoundRect(5, selectPosition, 5, 5, 2, WHITE) ;
  }
}

/**********************************************************************************************************************************************/

void breathCurveRateControl(uint8_t type) {
  if ( ((millis() - breathCurveTimer) >= 400) && (breathCurveBlinker == 1) ) {
    breathCurveBlinker = 0 ;
    breathCurveTimer = millis() ;
    menuUpdate = true ;
  } else if ( ((millis() - breathCurveTimer) >= 200) && (breathCurveBlinker == 0) ) {
    breathCurveBlinker = 1 ;
    breathCurveTimer = millis() ;
    menuUpdate = true ;
  }

  if (backFunction && backFunctionToggle) {
    backFunctionToggle = false ;
    breathCurveBlinkerState = 0 ;
    breathCurveRate[type] = fram.read8(breathCurveAddress+type+1) ;
    breathCurveBlinker = 0 ;
  }  
  if (selectFunction && selectFunctionToggle) {
    selectFunctionToggle = false ;
    breathCurveBlinkerState = 0 ;
    fram.write8(breathCurveAddress+type+1, breathCurveRate[type]) ;
    breathCurveBlinker = 0 ;
  }
  if (cursorUpToggle && cursorUp) {
    breathCurveRate[type] ++ ;
    cursorUpToggle = false ;
  }
  if (cursorDownToggle && cursorDown) {
    breathCurveRate[type] -- ;
    cursorDownToggle = false ;
  }
  breathCurveRate[type] = constrain(breathCurveRate[type], 0, 9) ;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void mpSelectMenuControl() {
  if (backFunction && backFunctionToggle) {
    backFunctionToggle = false ;
    menuCase = 0 ;
  }
  menuControl(MP_MODE) ;
  if (selectFunction && selectFunctionToggle) {
    selectFunctionToggle = false ;
    mpSelectMenuCase = menuCursor[MP_MODE][YPOS] ;  
  }
}

/**********************************************************************************************************************************************/

void mpSelectMenuPrint() {
  display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Multi-Phonics") ;
  display.print(" ") ;
  display.print("Mode") ;  

  for (int i=0; i<3; i++) {
    switch(menuCursor[MP_MODE][YSCROLL]+i) {
      case 1:
        display.setCursor(4,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print("Sustainer") ;
      break;
      case 2:
        display.setCursor(4,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print("Harmonizer") ;
      break;
      case 3:
        display.setCursor(4,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print("Rotator") ;
      break;
      case 4:
        
      break;
    }
  }
  display.drawRect(1, 17+(menuCursor[MP_MODE][YPOS]-menuCursor[MP_MODE][YSCROLL])*16, 116, 13, WHITE) ;
  int selectPosition = 20+(mpSelectMenuCase-menuCursor[MP_MODE][YSCROLL])*16 ;
  if ((selectPosition < 20) || (selectPosition > 64)) {
    
  } else {
    display.fillRoundRect(120, selectPosition, 8, 8, 4, WHITE) ;
  }
  
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void harmonizerMenuControl() {
  mpChordAdjusterControl(HARMONIZER) ;
}

/**********************************************************************************************************************************************/

void harmonizerMenuPrint() {
  mpChordAdjusterPrint(HARMONIZER) ;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void rotatorMenuControl() {
  mpChordAdjusterControl(ROTATOR) ;
}

/**********************************************************************************************************************************************/

void rotatorMenuPrint() {
  mpChordAdjusterPrint(ROTATOR) ;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void presetMenuControl() {
  mpChordAdjusterControl(PRESET) ;
}

/**********************************************************************************************************************************************/

void presetMenuPrint() {
  mpChordAdjusterPrint(PRESET) ;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void sevenMenuControl() {
  if (backFunction && backFunctionToggle) {
    backFunctionToggle = false ;
    menuCase = 0 ;
  }
}

/**********************************************************************************************************************************************/

void sevenMenuPrint() {
  /*display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Test Title 7") ;
  */  
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void eightMenuControl() {
  if (backFunction && backFunctionToggle) {
    backFunctionToggle = false ;
    menuCase = 0 ;
  }
}

/**********************************************************************************************************************************************/

void eightMenuPrint() {
  /*display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Test Title 8") ;  
  */
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void mpChordAdjusterControl(int8_t mpType) {
  switch(mpAdjusterMenuCase) {
    case 0:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        menuCase = 0 ;
        mpAdjusterMenuCase = 0 ; 
        menuControlReset(MP_ADJUSTER + mpType) ;    
      }
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        mpAdjusterMenuCase = 1 ;
        if (mpType == 2) {
          mpAdjustChordSelector = MP_CHORD_SELECT + 1 ;
        } else {
          mpAdjustChordSelector = MP_CHORD_SELECT ;
        }
        
        //set the intermediate chord values to correct value here from fram
        for (int i=0; i<8; i++) {
          for (int j=0; j<4; j++) {
            int address = mpAdjustAddress[mpType] + 32*(menuCursor[MP_ADJUSTER+mpType][ABSVAL]-1) + 4*i + j ;
            mpAdjustValues[i][j] = fram.read8(address) ;
          }
        }
      }   
      menuControl(MP_ADJUSTER+mpType) ; 
    break;
    case 1: 
      mpAdjustChordSelectControl(mpType, menuCursor[MP_ADJUSTER+mpType][ABSVAL]) ;
    break;
  }
}

/**********************************************************************************************************************************************/

void mpChordAdjusterPrint(int8_t mpType) {
  switch(mpAdjusterMenuCase) {
    case 0:
      switch(mpType) {
        case 0:
          mpAdjustType = "Harmonizer" ;
          mpAdjustTypeShort = 'H' ;
        break;
        case 1:
          mpAdjustType = "Rotator" ;
          mpAdjustTypeShort = 'R' ;
        break;
        case 2:
          mpAdjustType = "Preset" ;
          mpAdjustTypeShort = 'P' ;
        break;
      }
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print(mpAdjustType) ;
      display.print("s") ;
      
      if (mpType == 2) {
        display.setCursor(4,20) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(mpAdjustType) ;
        display.print(" ") ;
        display.print(1+2*(menuCursor[MP_ADJUSTER+mpType][YSCROLL]-1)) ;

        display.setCursor(68,20) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(mpAdjustType) ;
        display.print(" ") ;
        display.print(2+2*(menuCursor[MP_ADJUSTER+mpType][YSCROLL]-1)) ;

        display.setCursor(4,36) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(mpAdjustType) ;
        display.print(" ") ;
        display.print(3+2*(menuCursor[MP_ADJUSTER+mpType][YSCROLL]-1)) ;

        display.setCursor(68,36) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(mpAdjustType) ;
        display.print(" ") ;
        display.print(4+2*(menuCursor[MP_ADJUSTER+mpType][YSCROLL]-1)) ;

        display.setCursor(4,52) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(mpAdjustType) ;
        display.print(" ") ;
        display.print(5+2*(menuCursor[MP_ADJUSTER+mpType][YSCROLL]-1)) ;

        display.setCursor(68,52) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(mpAdjustType) ;
        display.print(" ") ;
        display.print(6+2*(menuCursor[MP_ADJUSTER+mpType][YSCROLL]-1)) ;

        display.drawRect(1+(menuCursor[MP_ADJUSTER+mpType][XPOS]-1)*64, 17+(menuCursor[MP_ADJUSTER+mpType][YPOS]-menuCursor[MP_ADJUSTER+mpType][YSCROLL])*16, 61, 13, WHITE) ;
      } else {
        display.setCursor(4,20) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(mpAdjustType) ;
        display.print(" ") ;
        display.print(0+menuCursor[MP_ADJUSTER+mpType][YSCROLL]) ;

        display.setCursor(4,36) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(mpAdjustType) ;
        display.print(" ") ;
        display.print(1+menuCursor[MP_ADJUSTER+mpType][YSCROLL]) ;

        display.setCursor(4,52) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(mpAdjustType) ;
        display.print(" ") ;
        display.print(2+menuCursor[MP_ADJUSTER+mpType][YSCROLL]) ;
        
        display.drawRect(1, 17+(menuCursor[MP_ADJUSTER+mpType][YPOS]-menuCursor[MP_ADJUSTER+mpType][YSCROLL])*16, 80, 13, WHITE) ;
      } 
    break;
    case 1: 
      mpAdjustChordSelectPrint(mpType, menuCursor[MP_ADJUSTER+mpType][ABSVAL]) ;
    break;
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void mpAdjustChordSelectControl(int8_t mpType, int8_t mpAdjustNum) {
  switch(mpAdjustChordSelectCase) {
    case 0:
    if (backFunction && backFunctionToggle) {
      backFunctionToggle = false ;
      mpAdjusterMenuCase = 0 ;
      menuControlReset(mpAdjustChordSelector) ;
    }
    if (selectFunction && selectFunctionToggle) {
      selectFunctionToggle = false ;
      mpAdjustChordSelectCase = 1 ;

      mpAdjustPitchNum[0] = 0 ;
      mpAdjustPitchNum[1] = 0 ;

      if (menuCursor[MP_CHORD_SELECT][YPOS] < 5) {
        mpAdjustChordMenuCase = 0 ;
      } else if (menuCursor[mpAdjustChordSelector][XPOS] == 1) {
        mpAdjustChordMenuCase = 1 ;
      } else {
        mpAdjustChordMenuCase = 2 ;
      }
        
    }
    menuControl(mpAdjustChordSelector) ;
    break;
    case 1:
      switch(mpAdjustChordMenuCase) {
        case 0:
          mpAdjustPitchSelectControl(mpType, mpAdjustNum, menuCursor[mpAdjustChordSelector][ABSVAL]) ; 
        break; 
        case 1:
          if (mpAdjustChordPresetCase == 0) {
            if (backFunction && backFunctionToggle) {
              backFunctionToggle = false ;
              mpAdjustChordSelectCase = 0 ;
              menuControlReset(MP_PRESET_SELECT) ;
            }   
            
            menuControl(MP_PRESET_SELECT) ;
            
            if (selectFunction && selectFunctionToggle) {
              selectFunctionToggle = false ;
              mpAdjustChordPresetCase = 1 ;  
            }
            
          } else if (mpAdjustChordPresetCase == 1) {
            if (cursorLeft && cursorLeftToggle) {
              cursorLeftToggle = false ;
              mpAdjustPitchNum[0] -- ;
            }
            if (cursorRight && cursorRightToggle) {
              cursorRightToggle = false ;
              mpAdjustPitchNum[0] ++ ;
            }
            mpAdjustPitchNum[0] = constrain(mpAdjustPitchNum[0], 0, 1) ;
            
            if (selectFunction && selectFunctionToggle) {
              selectFunctionToggle = false ;
              
              if (mpAdjustPitchNum[0] == 0) {
                mpAdjustChordSelectCase = 0 ;
                
                for(int j=0; j<8; j++) {
                 for(int k=0; k<4; k++) {
                    int address1 = mpAdjustAddress[PRESET] + 32*(menuCursor[MP_PRESET_SELECT][ABSVAL]-1) + 4*j + k ;
                    mpAdjustValues[j][k] = fram.read8(address1) ;
                  
                    int address2 = mpAdjustAddress[mpType] + 32*(mpAdjustNum-1) + 4*j + k ;
                    fram.write8(address2, mpAdjustValues[j][k]) ;
                  }
                }
              } else {
                mpAdjustChordPresetCase = 0 ;
              }

              
            }
          }
                  
        break;
        case 2:

          if (cursorLeft && cursorLeftToggle) {
           cursorLeftToggle = false ;
           mpAdjustPitchNum[0] -- ;
          }
          if (cursorRight && cursorRightToggle) {
            cursorRightToggle = false ;
            mpAdjustPitchNum[0] ++ ;
          }
          mpAdjustPitchNum[0] = constrain(mpAdjustPitchNum[0], 0, 1) ;

          if (selectFunction && selectFunctionToggle) {
            selectFunctionToggle = false ;
            mpAdjustChordSelectCase = 0 ;

            if (mpAdjustPitchNum[0] == 0) {
              
              for(int j=0; j<8; j++) {
               for(int k=0; k<4; k++) {
                  int address1 = 192 + 4*j + k ;
                  mpAdjustValues[j][k] = fram.read8(address1) ;
                  
                  int address2 = mpAdjustAddress[mpType] + 32*(mpAdjustNum-1) + 4*j + k ;
                  fram.write8(address2, mpAdjustValues[j][k]) ;
                }
              }
            }
          }
          
        break; 
      }
    break;
  }
}

/**********************************************************************************************************************************************/

void mpAdjustChordSelectPrint(int8_t mpType, int8_t mpAdjustNum) {
  switch(mpAdjustChordSelectCase) {
    case 0:
    
    display.setCursor(4,4) ;
    display.setTextColor(WHITE) ;
    display.setTextSize(1) ;
    display.print(mpAdjustType) ;
    display.print(" ") ;
    display.print(mpAdjustNum) ;
    
    for (int i=0; i<3; i++) {
      switch(menuCursor[mpAdjustChordSelector][YSCROLL]+i) {
        case 1:
          display.setCursor(4,(20+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Chord") ;
          display.print(" ") ;
          display.print("1") ;

          display.setCursor(68,(20+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Chord") ;
          display.print(" ") ;
          display.print("2") ;
        break;
        case 2:
          display.setCursor(4,(20+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Chord") ;
          display.print(" ") ;
          display.print("3") ;
            
          display.setCursor(68,(20+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Chord") ;
          display.print(" ") ;
          display.print("4") ;
        break;
        case 3:
          display.setCursor(4,(20+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Chord") ;
          display.print(" ") ;
          display.print("5") ;

          display.setCursor(68,(20+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Chord") ;
          display.print(" ") ;
          display.print("6") ;
        break;
        case 4:
          display.setCursor(4,(20+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Chord") ;
          display.print(" ") ;
          display.print("7") ;

          display.setCursor(68,(20+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Chord") ;
          display.print(" ") ;
          display.print("8") ;
        break;
        case 5:
          display.setCursor(4,(20+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Presets") ;

          display.setCursor(68,(20+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Reset") ;
        break;
      }
    }
    display.drawRect(1+(menuCursor[mpAdjustChordSelector][XPOS]-1)*64, 17+(menuCursor[mpAdjustChordSelector][YPOS]-menuCursor[mpAdjustChordSelector][YSCROLL])*16, 62, 13, WHITE) ;
    
    break;
    case 1:
      switch(mpAdjustChordMenuCase) {
        case 0:
          mpAdjustPitchSelectPrint(mpType, mpAdjustNum, menuCursor[mpAdjustChordSelector][ABSVAL]) ;
        break;
        case 1:
          if (mpAdjustChordPresetCase == 0) {
          display.setCursor(4,4) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print(mpAdjustTypeShort) ;
          display.print(mpAdjustNum) ;
          display.print(" ") ;
          display.print("Preset") ;
          display.print("s") ;

          for (int8_t i=0; i<3; i++) {
            switch(menuCursor[MP_PRESET_SELECT][YSCROLL] + i) {
              case 1:
                display.setCursor(4, (20+16*i)) ;
                display.setTextColor(WHITE) ;
                display.setTextSize(1) ;
                display.print("Preset") ;
                display.print(" ") ;
                display.print("1") ;

                display.setCursor(68, (20+16*i)) ;
                display.setTextColor(WHITE) ;
                display.setTextSize(1) ;
                display.print("Preset") ;
                display.print(" ") ;
                display.print("2") ;
              break;
              case 2:
                display.setCursor(4, (20+16*i)) ;
                display.setTextColor(WHITE) ;
                display.setTextSize(1) ;
                display.print("Preset") ;
                display.print(" ") ;
                display.print("3") ;

                display.setCursor(68, (20+16*i)) ;
                display.setTextColor(WHITE) ;
                display.setTextSize(1) ;
                display.print("Preset") ;
                display.print(" ") ;
                display.print("4") ;
              break;
              case 3:
                display.setCursor(4, (20+16*i)) ;
                display.setTextColor(WHITE) ;
                display.setTextSize(1) ;
                display.print("Preset") ;
                display.print(" ") ;
                display.print("5") ;

                display.setCursor(68, (20+16*i)) ;
                display.setTextColor(WHITE) ;
                display.setTextSize(1) ;
                display.print("Preset") ;
                display.print(" ") ;
                display.print("6") ;           
              break;
              case 4:
                display.setCursor(4, (20+16*i)) ;
                display.setTextColor(WHITE) ;
                display.setTextSize(1) ;
                display.print("Preset") ;
                display.print(" ") ;
                display.print("7") ;

                display.setCursor(68, (20+16*i)) ;
                display.setTextColor(WHITE) ;
                display.setTextSize(1) ;
                display.print("Preset") ;
                display.print(" ") ;
                display.print("8") ;           
              break;
            }
          }
          display.drawRect(1+(menuCursor[MP_PRESET_SELECT][XPOS]-1)*64, 17+(menuCursor[MP_PRESET_SELECT][YPOS]-menuCursor[MP_PRESET_SELECT][YSCROLL])*16, 61, 13, WHITE) ;
          } else if (mpAdjustChordPresetCase == 1) {
            
            display.setCursor(25,19) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Set") ;
            display.print(" ") ;
            display.print("Preset") ;
            display.print(" ") ;
            display.print(menuCursor[MP_PRESET_SELECT][ABSVAL]) ;
            display.print("?") ;

            display.setCursor(37, 37) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("YES") ;

            display.setCursor(76, 37) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("NO") ;

            display.drawRect(28+mpAdjustPitchNum[0]*36, 34, 36, 13, WHITE) ; 
          }
        break;
        case 2:
          display.setCursor(46,19) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Reset") ;
          display.print("?") ;

          display.setCursor(37, 37) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("YES") ;

          display.setCursor(76, 37) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("NO") ;

          display.drawRect(28+mpAdjustPitchNum[0]*36, 34, 36, 13, WHITE) ; 
          
        break;
      }
      
    break;
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void mpAdjustPitchSelectControl(int8_t mpType, int8_t mpAdjustNum, int8_t chordNum) {
  int8_t pitchNum = menuCursor[CHORD_PITCH][ABSVAL]-1 ;  
  if (mpAdjustPitchSelect == false) {
    if (backFunction && backFunctionToggle) {
      backFunctionToggle = false ;
      mpAdjustChordSelectCase = 0 ;
      menuControlReset(CHORD_PITCH) ;
    }
    menuControl(CHORD_PITCH) ; 
    if (selectFunction && selectFunctionToggle) {
      selectFunctionToggle = false ;
      mpAdjustPitchSelect = true ;
      mpAdjustPitchLast = mpAdjustValues[chordNum-1][pitchNum] ;
    }
  } else if (mpAdjustPitchSelect == true) {
    
    if (selectFunction && selectFunctionToggle) {
      selectFunctionToggle = false ;
      mpAdjustPitchSelect = false ;
      mpAdjustPitchBlinker[pitchNum] = 1 ;
      int address = mpAdjustAddress[mpType] + 32*(mpAdjustNum-1) + 4*(chordNum-1) + pitchNum ;
      fram.write8(address, mpAdjustValues[chordNum-1][pitchNum]) ;
    }
    if (backFunction && backFunctionToggle) {
      backFunctionToggle = false ;
      mpAdjustPitchSelect = false ;
      mpAdjustPitchBlinker[pitchNum] = 1 ;
      mpAdjustValues[chordNum-1][pitchNum] = mpAdjustPitchLast ;
    }
    if (cursorUp && cursorUpToggle) {
      mpAdjustValues[chordNum-1][pitchNum] ++ ;
      mpAdjustValues[chordNum-1][pitchNum] = constrain(mpAdjustValues[chordNum-1][pitchNum], -12, 12) ;
      cursorUpToggle = false ;
    }
    if (cursorDown && cursorDownToggle) {
      mpAdjustValues[chordNum-1][pitchNum] -- ;
      mpAdjustValues[chordNum-1][pitchNum] = constrain(mpAdjustValues[chordNum-1][pitchNum], -12, 12) ;
      cursorDownToggle = false ;
    }
    
    if ((millis() - blinkerLastTime > 150) && (mpAdjustPitchBlinker[pitchNum] == 0)) {
      mpAdjustPitchBlinker[pitchNum] = 1 ;
      menuUpdate = true ;
      blinkerLastTime = millis() ;
    }
    if ((millis() - blinkerLastTime > 400) && (mpAdjustPitchBlinker[pitchNum] == 1)) {
      mpAdjustPitchBlinker[pitchNum] = 0 ;
      menuUpdate = true ;
      blinkerLastTime = millis() ;
    }
  }
  
  
}

/**********************************************************************************************************************************************/

void mpAdjustPitchSelectPrint(int8_t mpType, int8_t mpAdjustNum, int8_t chordNum) {
  display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print(mpAdjustTypeShort) ;
  display.print(mpAdjustNum) ;
  display.print(" ") ;
  display.print("Chord") ;
  display.print(" ") ;
  display.print(chordNum) ;

  display.setCursor(4,26) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (mpAdjustPitchBlinker[0] == 1) {
    display.print(" ") ;
    if (mpAdjustValues[chordNum-1][0] >= 0) {
     display.print("+") ;
   } 
   display.print(mpAdjustValues[chordNum-1][0]) ;
  }
  

  display.setCursor(68,26) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (mpAdjustPitchBlinker[1] == 1) {
    display.print(" ") ;
    if (mpAdjustValues[chordNum-1][1] >= 0) {
     display.print("+") ;
   } 
   display.print(mpAdjustValues[chordNum-1][1]) ;
  }

  display.setCursor(4,50) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (mpAdjustPitchBlinker[2] == 1) {
    display.print(" ") ;
    if (mpAdjustValues[chordNum-1][2] >= 0) {
     display.print("+") ;
   } 
   display.print(mpAdjustValues[chordNum-1][2]) ;
  }

  display.setCursor(68,50) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (mpAdjustPitchBlinker[3] == 1) {
    display.print(" ") ;
    if (mpAdjustValues[chordNum-1][3] >= 0) {
     display.print("+") ;
   } 
   display.print(mpAdjustValues[chordNum-1][3]) ;
  }

  display.drawRect((menuCursor[CHORD_PITCH][XPOS]-1)*64, 22+((menuCursor[CHORD_PITCH][YPOS]-1)*24), 64, 15, WHITE) ;
}   

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int sizeOfInt(int number) {
  int a = abs(number) ;
  int s = 0 ;
  
  if (a >= 10000) {
    s = 5 ;
  } else if (a >= 1000) {
    s = 4 ;
  } else if (a >= 100) {
    s = 3 ;
  } else if (a >= 10) {
    s = 2 ;
  } else {
    s = 1 ;
  }

  if (number < 0) {
    s ++ ;
  }

  return s ;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
****************************************************************************************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void menuControl(int8_t menuChannel) {
  if (cursorLeft && cursorLeftToggle) {
    cursorLeftToggle = false ;
    menuCursor[menuChannel][XPOS] -- ;
  }
  if (cursorRight && cursorRightToggle) {
    cursorRightToggle = false ;
    menuCursor[menuChannel][XPOS] ++ ;
  }
  if (cursorUp && cursorUpToggle) {
    cursorUpToggle = false ;
    menuCursor[menuChannel][YPOS] -- ;
  }
  if (cursorDown && cursorDownToggle) {
    cursorDownToggle = false ;
    menuCursor[menuChannel][YPOS] ++ ;
  }
  if (menuCursor[menuChannel][XPOS] > menuCursor[menuChannel][XMAX] ) {
    menuCursor[menuChannel][XPOS] = 1 ;
  }
  if (menuCursor[menuChannel][XPOS] < 1) {
    menuCursor[menuChannel][XPOS] = menuCursor[menuChannel][XMAX] ;
  }
  if (menuCursor[menuChannel][YPOS] > menuCursor[menuChannel][YMAX] ) {
    menuCursor[menuChannel][YPOS] = 1 ;
  }
  if (menuCursor[menuChannel][YPOS] < 1) {
    menuCursor[menuChannel][YPOS] = menuCursor[menuChannel][YMAX] ;
  }
  while (menuCursor[menuChannel][XPOS] < menuCursor[menuChannel][XSCROLL]) {
    menuCursor[menuChannel][XSCROLL] -- ;
  }
  while (menuCursor[menuChannel][XPOS] > (menuCursor[menuChannel][XSCROLL] + menuCursor[menuChannel][XSIZE] - 1) ) {
    menuCursor[menuChannel][XSCROLL] ++ ;
  }
  while (menuCursor[menuChannel][YPOS] < menuCursor[menuChannel][YSCROLL]) {
    menuCursor[menuChannel][YSCROLL] -- ;
  }
  while (menuCursor[menuChannel][YPOS] > (menuCursor[menuChannel][YSCROLL] + menuCursor[menuChannel][YSIZE] - 1) ) {
    menuCursor[menuChannel][YSCROLL] ++ ;
  }
  menuCursor[menuChannel][ABSVAL] = menuCursor[menuChannel][XSIZE]*(menuCursor[menuChannel][YPOS]-1) + menuCursor[menuChannel][XPOS] ;
}

void menuControlReset(int8_t menuChannel) {
  menuCursor[menuChannel][XPOS] = 1 ;
  menuCursor[menuChannel][YPOS] = 1 ;
  menuCursor[menuChannel][XSCROLL] = 1 ;
  menuCursor[menuChannel][YSCROLL] = 1 ;
}
