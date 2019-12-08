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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();

                           // xpos ypos xmax ymax xscroll yscroll xsize ysize absval
int8_t menuCursor[7][9] =  { {   1,   1,   1,   4,      1,      1,    1,    4,     1},    //main menu select
                             {   1,   1,   1,   4,      1,      1,    1,    4,     1},    //sensor adjust select
                             {   1,   1,   1,   3,      1,      1,    1,    3,     1},    //multiphonics mode select
                             {   1,   1,   1,   3,      1,      1,    1,    3,     1} } ; //multiphonics adjust selector

int8_t oneMenuPosition = 1 ;
int8_t oneCursorPosition = 1 ;
int8_t oneCursorPositionMAX = 4 ;

int8_t transpositionPosition = 0 ;
int8_t transpositionMAX = 12 ;
int8_t transpositionMIN = -12 ;
int8_t transpositionMenuCase = 0 ;
unsigned long blinkerLastTime = 0 ;

int8_t threeMenuPosition = 0 ;
int8_t threeMenuCase = 0 ;

int8_t harmonizerMenuPos = 1 ;
int8_t harmonizerMenuCase = 0 ;

int8_t harmonizerSelectMenuCase[8] = {0, 0, 0, 0, 0, 0, 0, 0} ;
int8_t harmonizerChordMenuCase = 0 ;
int8_t harmonizerChordPresetCase = 0 ;
int8_t harmonizerChordNum = 1 ;
int8_t harmonizerPitchNum[2] = {0, 0} ;
boolean harmonizerPitchSelect = 0 ;
int8_t harmonizerPitchLast = 0 ;
boolean harmonizerPitchBlinker[4] = {1, 1, 1, 1} ;

int hpresetMenuCase = 0 ;

int8_t harmonizerValues[8][4] ;
uint16_t static harmonizerAddress = 256 ;

int8_t mpAdjusterMenuCase = 0 ;



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
          
        break;
        case 6:
          
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
          break; 
        case 2:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;           
          display.print("Portamento") ;   
        break;
        case 3:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Pitch") ; 
          display.print(" ") ;
          display.print("Bend") ;
          display.print(" ") ;
          display.print("Up") ; 
        break;
        case 4:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Pitch") ; 
          display.print(" ") ;
          display.print("Bend") ;
          display.print(" ") ;
          display.print("Down") ;  
        break;
        case 5:
          
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
      
      display.setCursor(4,22) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("THR") ;    

      display.setCursor(4,36) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("SEN") ;  

      display.setCursor(4,52) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("MAX") ;

      display.drawRect(26, 19, 96, 12, WHITE) ;
      display.drawFastVLine(26, 35, 10, WHITE) ;
      display.drawFastVLine(121, 35, 10, WHITE) ;
      display.drawRect(26, 49, 96, 12, WHITE) ;
    break;
    case 2:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Portamento") ;
      
    break;
    case 3:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Pitch") ; 
      display.print(" ") ;
      display.print("Bend") ;
      display.print(" ") ;
      display.print("Up") ;
      
    break;
    case 4:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Pitch") ; 
      display.print(" ") ;
      display.print("Bend") ;
      display.print(" ") ;
      display.print("Down") ;
      
    break;
    case 5:
      
    break;
    case 6:
      
    break;
  }
    
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
  }
  if (cursorLeft && cursorLeftToggle) {
    cursorLeftToggle = false ;
    menuCase = 0 ;
  }
  
  if (selectFunction && selectFunctionToggle) {
    selectFunctionToggle = false ;
    menuCase = 0 ;
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

  display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Transposition") ;  
     
  switch(transpositionMenuCase) {
    case 0:  
      if (transpositionPosition > 9) {
        display.setCursor(40, 22) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(4) ;
        display.print(transpositionPosition) ;
      } else if (transpositionPosition > -1) {
        display.setCursor(52, 22) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(4) ;
        display.print(transpositionPosition) ;
      } else if (transpositionPosition > -10) {
        display.setCursor(40, 22) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(4) ;
        display.print(transpositionPosition) ;
      } else {
        display.setCursor(28, 22) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(4) ;
        display.print(transpositionPosition) ;
      }
      
    break;
    case 1:
    
    break;
  }
  
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
  switch(harmonizerMenuCase) {
    case 0:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        menuCase = 0 ;
      }
      menuControl(HARMONIZER) ;
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        harmonizerMenuCase = menuCursor[HARMONIZER][YPOS] ;
        //set the harmonizer to correct value here from fram
        if(menuCursor[HARMONIZER][YPOS] < 3) {
          for (int i=0; i<8; i++) {
            for (int j=0; j<4; j++) {
              int address = harmonizerAddress + 32*(menuCursor[HARMONIZER][YPOS]-1) + 4*i + j ;
              harmonizerValues[i][j] = fram.read8(address) ;
            }
          }
        }   
      }
    break;
    case 1:
      harmonizerChordSelectControl(0) ;
    break;
    case 2:
      harmonizerChordSelectControl(1) ;
    break;
    case 3:
      harmonizerPresetSelectControl() ;
    break;
  }
  
}
void fourMenuPrint() {
  switch(harmonizerMenuCase) {
    case 0:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Harmonizer") ;  

      for (int i=0; i<3; i++) {
        switch(menuCursor[HARMONIZER][YSCROLL]+i) {
          case 1:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Harmonizer") ;
            display.print(" ") ;
            display.print("1") ;
          break;
          case 2:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Harmonizer") ;
            display.print(" ") ;
            display.print("2") ;
          break;
          case 3:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Presets") ;
          break;
          case 4:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Reset") ;
          break;
        }
      }
      display.drawRect(1, 17+(menuCursor[HARMONIZER][YPOS]-menuCursor[HARMONIZER][YSCROLL])*16, 85, 13, WHITE) ;
  
    break;
    case 1:
      harmonizerChordSelectPrint(0) ;
    break;
    case 2:
      harmonizerChordSelectPrint(1) ;
    break;
    case 3:
      harmonizerPresetSelectPrint() ;
    break;
  }
}

void fiveMenuControl() {
  if (backFunction && backFunctionToggle) {
    backFunctionToggle = false ;
    menuCase = 0 ;
  }
  if (cursorLeft && cursorLeftToggle) {
    cursorLeftToggle = false ;
    menuCase = 0 ;
  }
}
void fiveMenuPrint() {
  /*display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Test Title 5") ;  
  */
}

void sixMenuControl() {
  if (backFunction && backFunctionToggle) {
    backFunctionToggle = false ;
    menuCase = 0 ;
  }
  if (cursorLeft && cursorLeftToggle) {
    cursorLeftToggle = false ;
    menuCase = 0 ;
  }
}
void sixMenuPrint() {
  /*display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Test Title 6") ;  
  */
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
      }
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        mpAdjusterMenuCase = 1 ;
        //set the harmonizer to correct value here from fram
        if(menuCursor[HARMONIZER][YPOS] < 3) {
          for (int i=0; i<8; i++) {
            for (int j=0; j<4; j++) {
              int address = harmonizerAddress + 32*(menuCursor[HARMONIZER][YPOS]-1) + 4*i + j ;
              harmonizerValues[i][j] = fram.read8(address) ;
            }
          }
        }   
      }
      menuControl(MP_ADJUSTER) ; 
    break;
    case 1: 
    break;
  }
}
void mpChordAdjusterPrint(int8_t mpType) {
  switch(mpAdjusterMenuCase) {
    case 0:
    break;
    case 1: 
    break;
  }
}


void harmonizerChordSelectControl(int8_t harmonizerNum) {
  switch(harmonizerSelectMenuCase[harmonizerNum]) {
    case 0:
    if (backFunction && backFunctionToggle) {
      backFunctionToggle = false ;
      if (harmonizerNum < 2) {
        harmonizerMenuCase = 0 ;
      } else {
        hpresetMenuCase = 0 ;
      }
      
    }
    if (selectFunction && selectFunctionToggle) {
      selectFunctionToggle = false ;
      harmonizerSelectMenuCase[harmonizerNum] = 1 ;

      harmonizerPitchNum[0] = 0 ;
      harmonizerPitchNum[1] = 0 ;

      if (menuCursor[H_CHANGE+harmonizerNum][YPOS] < 5) {
        harmonizerChordMenuCase = 0 ;
      } else if (menuCursor[H_CHANGE+harmonizerNum][XPOS] == 1) {
        harmonizerChordMenuCase = 1 ;
      } else {
        harmonizerChordMenuCase = 2 ;
      }
        
    }
    menuControl(H_CHANGE + harmonizerNum) ;
    break;
    case 1:
      switch(harmonizerChordMenuCase) {
        case 0:
          harmonizerPitchSelectControl(harmonizerNum, menuCursor[H_CHANGE+harmonizerNum][ABSVAL], (menuCursor[CHORD_PITCH][XPOS]-1), (menuCursor[CHORD_PITCH][YPOS]-1), harmonizerPitchSelect ) ; 
        break; 
        case 1:
          if (harmonizerChordPresetCase == 0) {
            if (backFunction && backFunctionToggle) {
              backFunctionToggle = false ;
              harmonizerSelectMenuCase[harmonizerNum] = 0 ;
            }   
            
            menuControl(H_PRESET_SELECT+harmonizerNum) ;
            
            if (selectFunction && selectFunctionToggle) {
              selectFunctionToggle = false ;
              harmonizerChordPresetCase = 1 ;  
            }
            
          } else if (harmonizerChordPresetCase == 1) {
            if (cursorLeft && cursorLeftToggle) {
              cursorLeftToggle = false ;
              harmonizerPitchNum[0] -- ;
            }
            if (cursorRight && cursorRightToggle) {
              cursorRightToggle = false ;
              harmonizerPitchNum[0] ++ ;
            }
            harmonizerPitchNum[0] = constrain(harmonizerPitchNum[0], 0, 1) ;
            
            if (selectFunction && selectFunctionToggle) {
              selectFunctionToggle = false ;
              
              if (harmonizerPitchNum[0] == 0) {
                harmonizerSelectMenuCase[harmonizerNum] = 0 ;
                
                for(int j=0; j<8; j++) {
                 for(int k=0; k<4; k++) {
                    int address1 = 320 + 32*harmonizerPitchNum[1] + 4*j + k ;
                    harmonizerValues[j][k] = fram.read8(address1) ;
                  
                    int address2 = 256 + 32*harmonizerNum + 4*j + k ;
                    fram.write8(address2, harmonizerValues[j][k]) ;
                  }
                }
              } else {
                harmonizerChordPresetCase = 0 ;
              }

              
            }
          }
                  
        break;
        case 2:

          if (cursorLeft && cursorLeftToggle) {
           cursorLeftToggle = false ;
           harmonizerPitchNum[0] -- ;
          }
          if (cursorRight && cursorRightToggle) {
            cursorRightToggle = false ;
            harmonizerPitchNum[0] ++ ;
          }
          harmonizerPitchNum[0] = constrain(harmonizerPitchNum[0], 0, 1) ;

          if (selectFunction && selectFunctionToggle) {
            selectFunctionToggle = false ;
            harmonizerSelectMenuCase[harmonizerNum] = 0 ;

            if (harmonizerPitchNum[0] == 0) {
              
              for(int j=0; j<8; j++) {
               for(int k=0; k<4; k++) {
                  int address1 = 192 + 32*harmonizerNum + 4*j + k ;
                  harmonizerValues[j][k] = fram.read8(address1) ;
                  
                  int address2 = 256 + 32*harmonizerNum + 4*j + k ;
                  fram.write8(address2, harmonizerValues[j][k]) ;
                }
              }
            }
          }
          
        break; 
      }
    break;
  }
}

void harmonizerChordSelectPrint(int8_t harmonizerNum) {
  switch(harmonizerSelectMenuCase[harmonizerNum]) {
    case 0:
    
    display.setCursor(4,4) ;
    display.setTextColor(WHITE) ;
    display.setTextSize(1) ;
    if (harmonizerNum < 2) {
      display.print("Harmonizer") ;
      display.print(" ") ;
      display.print(harmonizerNum+1) ;
    } else {
      display.print("Preset") ;
      display.print(" ") ;
      display.print(harmonizerNum-1) ;
    }

    for (int i=0; i<3; i++) {
      switch(menuCursor[H_CHANGE+harmonizerNum][YSCROLL]+i) {
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
    display.drawRect(1+(menuCursor[H_CHANGE+harmonizerNum][XPOS]-1)*64, 17+(menuCursor[H_CHANGE+harmonizerNum][YPOS]-menuCursor[H_CHANGE+harmonizerNum][YSCROLL])*16, 62, 13, WHITE) ;
    
    break;
    case 1:
      switch(harmonizerChordMenuCase) {
        case 0:
          harmonizerPitchSelectPrint(harmonizerNum, menuCursor[H_CHANGE+harmonizerNum][ABSVAL], (menuCursor[CHORD_PITCH][XPOS]-1), (menuCursor[CHORD_PITCH][YPOS]-1), harmonizerPitchSelect ) ;
        break;
        case 1:
          if (harmonizerChordPresetCase == 0) {
          display.setCursor(4,4) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("H") ;
          display.print(harmonizerNum+1) ;
          display.print(" ") ;
          display.print("Preset") ;
          display.print("s") ;

          for (int8_t i=0; i<3; i++) {
            switch(menuCursor[H_PRESET_SELECT+harmonizerNum][YSCROLL] + i) {
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
          display.drawRect(1+(menuCursor[H_PRESET_SELECT+harmonizerNum][XPOS]-1)*64, 17+(menuCursor[H_PRESET_SELECT+harmonizerNum][YPOS]-menuCursor[H_PRESET_SELECT+harmonizerNum][YSCROLL])*16, 61, 13, WHITE) ;
          } else if (harmonizerChordPresetCase == 1) {
            
            display.setCursor(25,19) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Set") ;
            display.print(" ") ;
            display.print("Preset") ;
            display.print(" ") ;
            display.print(menuCursor[H_PRESET_SELECT][ABSVAL]) ;
            display.print("?") ;

            display.setCursor(37, 37) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("YES") ;

            display.setCursor(76, 37) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("NO") ;

            display.drawRect(28+harmonizerPitchNum[0]*36, 34, 36, 13, WHITE) ; 
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

          display.drawRect(28+harmonizerPitchNum[0]*36, 34, 36, 13, WHITE) ; 
          
        break;
      }
      
    break;
  }
}


void harmonizerPitchSelectControl(int8_t harmonizerNum, int8_t chordNum, int8_t pitchNumX, int8_t pitchNumY, boolean pitchSelector) {
  int8_t pitchNum = 2*pitchNumY + pitchNumX ;
  
  if (harmonizerPitchSelect == false) {
    if (backFunction && backFunctionToggle) {
      backFunctionToggle = false ;
      harmonizerSelectMenuCase[harmonizerNum] = 0 ;
    }
    menuControl(CHORD_PITCH) ; 
    if (selectFunction && selectFunctionToggle) {
      selectFunctionToggle = false ;
      harmonizerPitchSelect = true ;
      harmonizerPitchLast = harmonizerValues[chordNum-1][pitchNum] ;
    }
  } else if (harmonizerPitchSelect == true) {
    
    if (selectFunction && selectFunctionToggle) {
      selectFunctionToggle = false ;
      harmonizerPitchSelect = false ;
      harmonizerPitchBlinker[pitchNum] = 1 ;
      int address = harmonizerAddress + 32*harmonizerNum + 4*(chordNum-1) + pitchNum ;
      fram.write8(address, harmonizerValues[chordNum-1][pitchNum]) ;
    }
    if (backFunction && backFunctionToggle) {
      backFunctionToggle = false ;
      harmonizerPitchSelect = false ;
      harmonizerPitchBlinker[pitchNum] = 1 ;
      harmonizerValues[chordNum-1][pitchNum] = harmonizerPitchLast ;
    }
    if (cursorUp && cursorUpToggle) {
      harmonizerValues[chordNum-1][pitchNum] ++ ;
      harmonizerValues[chordNum-1][pitchNum] = constrain(harmonizerValues[chordNum-1][pitchNum], -12, 12) ;
      cursorUpToggle = false ;
    }
    if (cursorDown && cursorDownToggle) {
      harmonizerValues[chordNum-1][pitchNum] -- ;
      harmonizerValues[chordNum-1][pitchNum] = constrain(harmonizerValues[chordNum-1][pitchNum], -12, 12) ;
      cursorDownToggle = false ;
    }
    
    if ((millis() - blinkerLastTime > 150) && (harmonizerPitchBlinker[pitchNum] == 0)) {
      harmonizerPitchBlinker[pitchNum] = 1 ;
      menuUpdate = true ;
      blinkerLastTime = millis() ;
    }
    if ((millis() - blinkerLastTime > 400) && (harmonizerPitchBlinker[pitchNum] == 1)) {
      harmonizerPitchBlinker[pitchNum] = 0 ;
      menuUpdate = true ;
      blinkerLastTime = millis() ;
    }
  }
  
  
}

void harmonizerPitchSelectPrint(int8_t harmonizerNum, int8_t chordNum, int8_t pitchNumX, int8_t pitchNumY, boolean pitchSelector) {
  display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  if (harmonizerNum < 2) {
    display.print("H") ;
    display.print(harmonizerNum+1) ;
  } else {
    display.print("P") ;
    display.print(harmonizerNum-1) ;
  }
  display.print(" ") ;
  display.print("Chord") ;
  display.print(" ") ;
  display.print(chordNum) ;

  display.setCursor(4,26) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (harmonizerPitchBlinker[0] == 1) {
    display.print(" ") ;
    if (harmonizerValues[chordNum-1][0] >= 0) {
     display.print("+") ;
   } 
   display.print(harmonizerValues[chordNum-1][0]) ;
  }
  

  display.setCursor(68,26) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (harmonizerPitchBlinker[1] == 1) {
    display.print(" ") ;
    if (harmonizerValues[chordNum-1][1] >= 0) {
     display.print("+") ;
   } 
   display.print(harmonizerValues[chordNum-1][1]) ;
  }

  display.setCursor(4,50) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (harmonizerPitchBlinker[2] == 1) {
    display.print(" ") ;
    if (harmonizerValues[chordNum-1][2] >= 0) {
     display.print("+") ;
   } 
   display.print(harmonizerValues[chordNum-1][2]) ;
  }

  display.setCursor(68,50) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (harmonizerPitchBlinker[3] == 1) {
    display.print(" ") ;
    if (harmonizerValues[chordNum-1][3] >= 0) {
     display.print("+") ;
   } 
   display.print(harmonizerValues[chordNum-1][3]) ;
  }

  display.drawRect((pitchNumX)*64, 22+((pitchNumY)*24), 64, 15, WHITE) ;
}   

void harmonizerPresetSelectControl() {
  switch(hpresetMenuCase) {
    case 0:
      menuControl(H_PRESET) ;
      
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        harmonizerMenuCase = 0 ;
      }
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        hpresetMenuCase = 1 ;
        
        for (int i=0; i<8; i++) {
          for (int j=0; j<4; j++) {
            int address = harmonizerAddress + 32*(menuCursor[HARMONIZER][YPOS]-1) + 4*i + j ;
            harmonizerValues[i][j] = fram.read8(address) ;
          }
        }  
      }
    break;
    case 1:
      harmonizerChordSelectControl(menuCursor[H_PRESET][ABSVAL]+1) ;
    break;       
  }
}

void harmonizerPresetSelectPrint() {
  switch(hpresetMenuCase) {
    case 0:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;
      display.print("Presets") ;

      for (int i=0; i<3; i++) {
        switch(menuCursor[H_PRESET][YSCROLL]+i) {
          case 1:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Preset") ;
            display.print(" ") ;
            display.print("1") ;

            display.setCursor(68,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Preset") ;
            display.print(" ") ;
            display.print("2") ;
          break;
          case 2:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Preset") ;
            display.print(" ") ;
            display.print("3") ;
            
            display.setCursor(68,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Preset") ;
            display.print(" ") ;
            display.print("4") ;
          break;
          case 3:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Preset") ;
            display.print(" ") ;
            display.print("5") ;

            display.setCursor(68,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Preset") ;
            display.print(" ") ;
            display.print("6") ;
          break;
          case 4:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Preset") ;
            display.print(" ") ;
            display.print("7") ;

            display.setCursor(68,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Preset") ;
            display.print(" ") ;
            display.print("8") ;
          break;
        }
      }
      display.drawRect(1+(menuCursor[H_PRESET][XPOS]-1)*64, 17+(menuCursor[H_PRESET][YPOS]-menuCursor[H_PRESET][YSCROLL])*16, 61, 13, WHITE) ;

    break;
    case 1:
      harmonizerChordSelectPrint(menuCursor[H_PRESET][ABSVAL]+1) ;
    break;
  }
  
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
  menuCursor[menuChannel][ABSVAL] = 2*(menuCursor[menuChannel][YPOS]-1) + menuCursor[menuChannel][XPOS] ;
}

void menuControlReset(int8_t menuChannel) {
  menuCursor[menuChannel][XPOS] = 1 ;
  menuCursor[menuChannel][YPOS] = 1 ;
  menuCursor[menuChannel][XSCROLL] = 1 ;
  menuCursor[menuChannel][YSCROLL] = 1 ;
}
