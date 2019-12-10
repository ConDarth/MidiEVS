#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_FRAM_I2C.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define JOYSTICK_X_PORT A0
#define JOYSTICK_Y_PORT A1
#define SELECT_BUTTON_PIN 3
#define BACK_BUTTON_PIN 2

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

#define XPOS 0 
#define YPOS 1 
#define XMAX 2
#define YMAX 3
#define XSCROLL 4
#define YSCROLL 5
#define XSIZE 6
#define YSIZE 7
#define ABSVAL 8

#define MAIN_MENU 0
#define SENSOR_ADJUST 1
#define MP_MODE 2
#define MP_ADJUSTER 3
#define MP_CHORD_SELECT 6
#define MP_PRESET_SELECT 8
#define CHORD_PITCH 9

#define HARMONIZER 0 
#define ROTATOR 1
#define PRESET 2 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();

                           // xpos ypos xmax ymax xscroll yscroll xsize ysize absval
int8_t menuCursor[10][9] = { {   1,   1,   1,   6,      1,      1,    1,    4,     1},    //main menu select
                             {   1,   1,   1,   5,      1,      1,    1,    4,     1},    //sensor adjust select
                             {   1,   1,   1,   3,      1,      1,    1,    3,     1},    //multiphonics mode select
                             {   1,   1,   1,   4,      1,      1,    1,    3,     1},    //multiphonics adjust selector (harmonizer)
                             {   1,   1,   1,   4,      1,      1,    1,    3,     1},    //multiphonics adjust selector (rotator)
                             {   1,   1,   2,   4,      1,      1,    2,    3,     1},    //multiphonics adjust selector (presets)
                             {   1,   1,   2,   5,      1,      1,    2,    3,     1},    //multiphonics adjust chord selector
                             {   1,   1,   2,   4,      1,      1,    2,    3,     1},    //multiphonics adjust chord selector w/o presets
                             {   1,   1,   2,   4,      1,      1,    2,    3,     1},    //multiphonics adjust preset select
                             {   1,   1,   2,   2,      1,      1,    2,    2,     1} } ; //chord pitch selection
                             


int8_t transpositionPosition = 0 ;
int8_t transpositionMAX = 12 ;
int8_t transpositionMIN = -12 ;
int8_t transpositionMenuCase = 0 ;
unsigned long blinkerLastTime = 0 ;
int transpositionAddress = 0x40 ;

int8_t threeMenuPosition = 0 ;
int8_t threeMenuCase = 0 ;

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




boolean selectFunction = false ;
boolean selectFunctionToggle = false ;
boolean selectButton = false ;
boolean selectButtonToggle = false ;
boolean backFunction = false ;
boolean backFunctionToggle = false ;
boolean backButton = false ;
boolean backButtonToggle = false ;

boolean cursorUp = false ;
boolean cursorUpToggle = false ;
boolean cursorDown = false ;
boolean cursorDownToggle = false ;
int joystickY = 512 ;
boolean joystickYToggle = false ;
boolean cursorLeft = false ;
boolean cursorLeftToggle = false ;
boolean cursorRight = false ;
boolean cursorRightToggle = false ;
int joystickX = 512 ;
boolean joystickXToggle = false ;

boolean menuUpdate = true ;
int8_t menuCase = 0 ;
int8_t oneMenuCase = 0 ;

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
}

void loop() {
  // put your main code here, to run repeatedly
  joystickY = analogRead(JOYSTICK_Y_PORT) ;
  joystickX = analogRead(JOYSTICK_X_PORT) ;
  selectButton = digitalRead(SELECT_BUTTON_PIN) ;
  backButton = digitalRead(BACK_BUTTON_PIN) ;
  
  if ((joystickY > 768) && !joystickYToggle) {
    cursorDown = true ;
    cursorDownToggle = true ;
    joystickYToggle = true ;
    menuUpdate = true ;
  } 
  if ((joystickY < 256) && !joystickYToggle) {
    cursorUp = true ;
    cursorUpToggle = true ;
    joystickYToggle = true ;
    menuUpdate = true ;
  } 
  if (joystickYToggle && (joystickY > 270) && (joystickY < 750)) {
    joystickYToggle = false ;
    cursorUp = false ;
    cursorDown = false ;
  }

  if ((joystickX < 256) && !joystickXToggle) {
    menuUpdate = true ;
    cursorRight = true ;
    cursorRightToggle = true ;
    joystickXToggle = true ;
  }
  if ((joystickX > 768) && !joystickXToggle) {
    menuUpdate = true ;
    cursorLeft = true ;
    cursorLeftToggle = true ;
    joystickXToggle = true ;
  }
  if (joystickXToggle && (joystickX > 270) && (joystickX < 750)) {
    joystickXToggle = false ;
    cursorLeft = false ;
    cursorRight = false ;
  }

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
  

  switch(menuCase) {
    case 0:
      initialMenuControl() ;
    break;
    case 1:
      oneMenuControl() ;
    break;
    case 2:
      transpositionMenuControl() ;
    break;
    case 3:
      threeMenuControl() ;
    break;
    case 4:
      fourMenuControl() ;
    break;
    case 5:
      fiveMenuControl() ;
    break;
    case 6:
      sixMenuControl() ;
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
  
  
  if (menuUpdate) {
    display.clearDisplay() ;

    switch(menuCase) {
      case 0:
        initialMenuPrint() ;
      break;
      case 1:
        oneMenuPrint() ;
      break;
      case 2:
        transpositionMenuPrint() ;
      break;
      case 3:
        threeMenuPrint() ;
      break;
      case 4:
        fourMenuPrint() ;
      break;
      case 5:
        fiveMenuPrint() ;
      break;
      case 6:
        sixMenuPrint() ;
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

          if (transpositionPosition > 9) {
            display.setCursor(102, (4+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print(transpositionPosition) ;
          } else if (transpositionPosition > -1) {
            display.setCursor(104, (4+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print(transpositionPosition) ;
          } else if (transpositionPosition > -10) {
            display.setCursor(102, (4+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print(transpositionPosition) ;
          } else {
            display.setCursor(100, (4+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print(transpositionPosition) ;
          }
        break;
        case 3:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Multi-Phonics") ;
          display.print(" ") ;
          display.print("Mode") ;    
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

void initialMenuControl() {
  menuControl(MAIN_MENU) ;
  
  if (selectFunction && selectFunctionToggle) {
    selectFunctionToggle = false ;
    menuCase = menuCursor[MAIN_MENU][YPOS] ;
  }
  if (cursorRight && cursorRightToggle) {
    cursorRightToggle = false ;
    menuCase = menuCursor[MAIN_MENU][YPOS] ;
  }

}

void oneMenuControl() {
  switch(oneMenuCase) {
    case 0: 
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        menuCase = 0 ;
      }
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        oneMenuCase = menuCursor[SENSOR_ADJUST][YPOS] ;
      }

      if (cursorLeft && cursorLeftToggle) {
        menuCase = 0 ;
      }
      if (cursorRight && cursorRightToggle) {
        oneMenuCase = menuCursor[SENSOR_ADJUST][YPOS] ;
      }
      
      menuControl(SENSOR_ADJUST) ;
      
    break;
    case 1:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        oneMenuCase = 0 ;
      }
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        oneMenuCase = 0 ;
      }
    break;
    case 2:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        oneMenuCase = 0 ;
      }
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        oneMenuCase = 0 ;
      }
    break;
    case 3:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        oneMenuCase = 0 ;
      }
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        oneMenuCase = 0 ;
      }
    break;
    case 4:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        oneMenuCase = 0 ;
      }
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        oneMenuCase = 0 ;
      }
    break;
    case 5:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        oneMenuCase = 0 ;
      }
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        oneMenuCase = 0 ;
      }
    break;
    case 6:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        oneMenuCase = 0 ;
      }
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        oneMenuCase = 0 ;
      }
    break;
  }
  
}
void oneMenuPrint() {

  switch(oneMenuCase) {
    case 0:
      for (int i=0; i<4; i++) {
      
      switch(menuCursor[SENSOR_ADJUST][YSCROLL]+i) {
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
    
    display.drawRect(1, (1+(menuCursor[SENSOR_ADJUST][YPOS]-menuCursor[SENSOR_ADJUST][YSCROLL])*16), 126, 13, WHITE) ;
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

void sensorAdjustControl() {
  
}

void sensorAdjustPrint() {
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

  display.drawRect(26, 18, 96, 13, WHITE) ;
  display.drawFastVLine(26, 22, 5, BLACK) ;
  display.drawFastVLine(121, 22, 5, BLACK) ;
  
  display.drawFastVLine(46, 21, 7, WHITE) ; //variable for the THR setting
  
  display.drawFastVLine(26, 36, 7, WHITE) ;
  display.drawFastVLine(121, 36, 7, WHITE) ;

  display.drawFastVLine(36, 38, 3, WHITE) ; //variable for realtime sensor output  


  display.drawRect(26, 48, 96, 13, WHITE) ;
  display.drawFastVLine(26, 52, 5, BLACK) ;
  display.drawFastVLine(121, 52, 5, BLACK) ;
  
  display.drawFastVLine(106, 51, 7, WHITE) ; // variable for 
}

void transpositionMenuControl() {
  
  if ((millis() - blinkerLastTime > 400) && (transpositionMenuCase == 0)) {
    transpositionMenuCase = 1;
    menuUpdate = true ;
    blinkerLastTime = millis() ;
  }
  if ((millis() - blinkerLastTime > 150) && (transpositionMenuCase == 1)) {
    transpositionMenuCase = 0 ;
    menuUpdate = true ;
    blinkerLastTime = true ;
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
        display.print("Multi-Phonics") ;
        display.print(" ") ;
        display.print("Mode") ;    
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
      if (transpositionPosition > 9) {
        display.setCursor(102, (36-menuCursor[MAIN_MENU][YSCROLL]*16)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(transpositionPosition) ;
      } else if (transpositionPosition > -1) {
        display.setCursor(104, (36-menuCursor[MAIN_MENU][YSCROLL]*16)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(transpositionPosition) ;
      } else if (transpositionPosition > -10) {
        display.setCursor(102, (36-menuCursor[MAIN_MENU][YSCROLL]*16)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(transpositionPosition) ;
      } else {
        display.setCursor(100, (36-menuCursor[MAIN_MENU][YSCROLL]*16)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print(transpositionPosition) ;
      }      
    break;
    case 1:
    
    break;
  }

  display.drawRect(1, (1+(menuCursor[MAIN_MENU][YPOS]-menuCursor[MAIN_MENU][YSCROLL])*16), 126, 13, WHITE) ;
  
}

void threeMenuControl() {
  if (backFunction && backFunctionToggle) {
    backFunctionToggle = false ;
    menuCase = 0 ;
  }
  menuControl(MP_MODE) ;
  if (selectFunction && selectFunctionToggle) {
    selectFunctionToggle = false ;
    threeMenuCase = menuCursor[MP_MODE][YPOS] ;  
  }
  if (cursorRight && cursorRightToggle) {
    cursorRightToggle = false ;
    threeMenuCase = menuCursor[MP_MODE][YPOS] ;  
  }
}
void threeMenuPrint() {
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
  int selectPosition = 20+(threeMenuCase-menuCursor[MP_MODE][YSCROLL])*16 ;
  if ((selectPosition < 20) || (selectPosition > 64)) {
    
  } else {
    display.fillRoundRect(120, selectPosition, 8, 8, 4, WHITE) ;
  }
  
}

void fourMenuControl() {
  mpChordAdjusterControl(HARMONIZER) ;
}
void fourMenuPrint() {
  mpChordAdjusterPrint(HARMONIZER) ;
}

void fiveMenuControl() {
  mpChordAdjusterControl(ROTATOR) ;
}
void fiveMenuPrint() {
  mpChordAdjusterPrint(ROTATOR) ;
}

void sixMenuControl() {
  mpChordAdjusterControl(PRESET) ;
}
void sixMenuPrint() {
  mpChordAdjusterPrint(PRESET) ;
}

void sevenMenuControl() {
  if (backFunction && backFunctionToggle) {
    backFunctionToggle = false ;
    menuCase = 0 ;
  }
  if (cursorLeft && cursorLeftToggle) {
    cursorLeftToggle = false ;
    menuCase = 0 ;
  }
}
void sevenMenuPrint() {
  /*display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Test Title 7") ;
  */  
}

void eightMenuControl() {
  if (backFunction && backFunctionToggle) {
    backFunctionToggle = false ;
    menuCase = 0 ;
  }
  if (cursorLeft && cursorLeftToggle) {
    cursorLeftToggle = false ;
    menuCase = 0 ;
  }
}
void eightMenuPrint() {
  /*display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Test Title 8") ;  
  */
}

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
