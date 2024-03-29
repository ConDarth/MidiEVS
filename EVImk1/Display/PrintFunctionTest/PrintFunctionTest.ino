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
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();

int8_t menuPosition = 1 ;
int8_t cursorPosition = 1 ;
int8_t cursorPositionMAX = 4 ;

int8_t oneMenuPosition = 1 ;
int8_t oneCursorPosition = 1 ;
int8_t oneCursorPositionMAX = 4 ;

int8_t transpositionPosition = 0 ;
int8_t transpositionMAX = 12 ;
int8_t transpositionMIN = -12 ;
int8_t transpositionMenuCase = 0 ;
unsigned long blinkerLastTime = 0 ;

int8_t threeCursorPosition = 0 ;
int8_t threeCursorMAX = 2 ;
int8_t threeMenuPosition = 0 ;
int8_t threeMenuCase = 0 ;

int8_t harmonizerCursor = 1 ;
int8_t harmonizerCursorMAX = 3 ;
int8_t harmonizerMenuPos = 1 ;
int8_t harmonizerMenuCase = 0 ;

int8_t harmonizerSelectCursor[2][2] = { {1, 1},
                                        {1, 1} } ;
int8_t harmonizerSelectCursorMAX[2] = {2, 5} ;
int8_t harmonizerSelectMenuPos[2] = {1, 1} ;
int8_t harmonizerSelectMenuCase[2] = {0, 0} ;
int8_t harmonizerChordMenuCase = 0 ;
int8_t harmonizerChordNum = 1 ;
int8_t harmonizerPitchNum[2] = {0, 0} ;
boolean harmonizerPitchSelect = 0 ;
int8_t harmonizerPitchLast = 0 ;
boolean harmonizerPitchBlinker[4] = {1, 1, 1, 1} ;


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

static int8_t harmonizerPresets[2][8][4] = { { {0, 4, 7, 0}, //major triad
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
      
      switch(menuPosition+i) {
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
    
    display.drawRect(1, (1+(cursorPosition-menuPosition)*16), 126, 13, WHITE) ;
}

void initialMenuControl() {
  if (cursorUp && cursorUpToggle) {
    cursorPosition -- ;
    cursorUpToggle = false ;
  }
  if (cursorDown && cursorDownToggle) {
    cursorPosition ++ ;
    cursorDownToggle = false ;
  }
  if (cursorPosition > cursorPositionMAX) {
    cursorPosition = 1 ;
  }
  if (cursorPosition < 1) {
    cursorPosition = cursorPositionMAX ;
  }
  while(cursorPosition > (menuPosition+3)) {
    menuPosition ++ ;
  }
  while(cursorPosition < menuPosition) {
    menuPosition -- ;
  }
  if (selectFunction && selectFunctionToggle) {
    selectFunctionToggle = false ;
    menuCase = cursorPosition ;
  }
  if (cursorRight && cursorRightToggle) {
    cursorRightToggle = false ;
    menuCase = cursorPosition ;
  }

}

void oneMenuControl() {
  switch(oneMenuCase) {
    case 0: 
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        menuCase = 0 ;
      }
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        menuCase = 0 ;
      }

      if (cursorUp && cursorUpToggle) {
        oneCursorPosition -- ;
        cursorUpToggle = false ;
      }
      if (cursorDown && cursorDownToggle) {
        oneCursorPosition ++ ;
        cursorDownToggle = false ;
      }
      if (oneCursorPosition > oneCursorPositionMAX) {
        oneCursorPosition = 1 ;
      }
      if (oneCursorPosition < 1) {
        oneCursorPosition = oneCursorPositionMAX ;
      }
      while(oneCursorPosition > (oneMenuPosition+3)) {
        oneMenuPosition ++ ;
      }
      while(oneCursorPosition < oneMenuPosition) {
        oneMenuPosition -- ;
      }
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        oneMenuCase = oneCursorPosition ;
      }
      if (cursorRight && cursorRightToggle) {
        cursorRightToggle = false ;
        oneMenuCase = oneCursorPosition ;
      }

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
      
      switch(oneMenuPosition+i) {
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
    
    display.drawRect(1, (1+(oneCursorPosition-oneMenuPosition)*16), 126, 13, WHITE) ;
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
  if (cursorLeft && cursorLeftToggle) {
    cursorLeftToggle = false ;
    menuCase = 0 ;
  }
  if (cursorUp && cursorUpToggle) {
    cursorUpToggle = false ;
    threeCursorPosition -- ;
  }
  if (cursorDown && cursorDownToggle) {
    cursorDownToggle = false ;
    threeCursorPosition ++ ;
  }
  if (threeCursorPosition > threeCursorMAX) {
    threeCursorPosition = 0 ;
  }
  if (threeCursorPosition < 0) {
    threeCursorPosition = threeCursorMAX ;
  }
  while (threeCursorPosition > (threeMenuPosition + 2)) {
    threeMenuPosition ++ ;
  }
  while (threeCursorPosition < threeMenuPosition) {
    threeMenuPosition -- ;
  }
  if (selectFunction && selectFunctionToggle) {
    selectFunctionToggle = false ;
    threeMenuCase = threeCursorPosition ;  
  }
  if (cursorRight && cursorRightToggle) {
    cursorRightToggle = false ;
    threeMenuCase = threeCursorPosition ;  
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
    switch(threeMenuPosition+i) {
      case 0:
        display.setCursor(4,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print("Sustainer") ;
      break;
      case 1:
        display.setCursor(4,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print("Harmonizer") ;
      break;
      case 2:
        display.setCursor(4,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print("Rotator") ;
      break;
      case 3:
        
      break;
    }
  }
  display.drawRect(1, 17+(threeCursorPosition-threeMenuPosition)*16, 116, 13, WHITE) ;
  int selectPosition = 20+(threeMenuCase-threeMenuPosition)*16 ;
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
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        menuCase = 0 ;
      }
      if (cursorUp && cursorUpToggle) {
        harmonizerCursor -- ;
        cursorUpToggle = false ;
      }
      if (cursorDown && cursorDownToggle) {
        harmonizerCursor ++ ;
        cursorDownToggle = false ;
      }
      if (harmonizerCursor > harmonizerCursorMAX) {
        harmonizerCursor = 1 ;
      }
      if (harmonizerCursor < 1) {
        harmonizerCursor = harmonizerCursorMAX ;
      }
      while(harmonizerCursor > (harmonizerMenuPos+2)) {
        harmonizerMenuPos ++ ;
      }
      while(harmonizerCursor < harmonizerMenuPos) {
        harmonizerMenuPos -- ;
      }
      if (selectFunction && selectFunctionToggle) {
        selectFunctionToggle = false ;
        harmonizerMenuCase = harmonizerCursor ;
      }
      if (cursorRight && cursorRightToggle) {
        cursorRightToggle = false ;
        harmonizerMenuCase = harmonizerCursor ;
      }
    break;
    case 1:
      harmonizerChordSelectControl(0) ;
    break;
    case 2:
      harmonizerChordSelectControl(1) ;
    break;
    case 3:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        harmonizerMenuCase = 0 ;
      }
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        
      }
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
        switch(harmonizerMenuPos+i) {
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
      display.drawRect(1, 17+(harmonizerCursor-harmonizerMenuPos)*16, 116, 13, WHITE) ;
  
    break;
    case 1:
      harmonizerChordSelectPrint(0) ;
    break;
    case 2:
      harmonizerChordSelectPrint(1) ;
    break;
    case 3:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;
      display.print("Presets") ;
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

void harmonizerChordSelectControl(int8_t harmonizerNum) {
  switch(harmonizerSelectMenuCase[harmonizerNum]) {
    case 0:
    if (backFunction && backFunctionToggle) {
      backFunctionToggle = false ;
      harmonizerMenuCase = 0 ;
    }
    if (cursorLeft && cursorLeftToggle) {
      cursorLeftToggle = false ;
      harmonizerSelectCursor[harmonizerNum][0] -- ;
    }
    if (cursorRight && cursorRightToggle) {
      cursorRightToggle = false ;
      harmonizerSelectCursor[harmonizerNum][0] ++ ;
    }
    if (cursorUp && cursorUpToggle) {
      harmonizerSelectCursor[harmonizerNum][1] -- ;
      cursorUpToggle = false ;
    }
    if (cursorDown && cursorDownToggle) {
      harmonizerSelectCursor[harmonizerNum][1] ++ ;
      cursorDownToggle = false ;
    }
    if (selectFunction && selectFunctionToggle) {
      selectFunctionToggle = false ;
      harmonizerSelectMenuCase[harmonizerNum] = 1 ;

      harmonizerChordNum = (2*(harmonizerSelectCursor[harmonizerNum][1]-1)) + harmonizerSelectCursor[harmonizerNum][0] ;
      harmonizerPitchNum[0] = 0 ;
      harmonizerPitchNum[1] = 0 ;

      if (harmonizerSelectCursor[harmonizerNum][1] < 5) {
        harmonizerChordMenuCase = 0 ;
      } else if (harmonizerSelectCursor[harmonizerNum][0] == 1) {
        harmonizerChordMenuCase = 1 ;
      } else {
        harmonizerChordMenuCase = 2 ;
      }
        
    }
      
    if (harmonizerSelectCursor[harmonizerNum][0] > harmonizerSelectCursorMAX[0]) {
      harmonizerSelectCursor[harmonizerNum][0] = 1 ;
    }
    if (harmonizerSelectCursor[harmonizerNum][0] < 1) {
      harmonizerSelectCursor[harmonizerNum][0] = harmonizerSelectCursorMAX[0] ;
    }
    if (harmonizerSelectCursor[harmonizerNum][1] > harmonizerSelectCursorMAX[1]) {
      harmonizerSelectCursor[harmonizerNum][1] = 1 ;
    }
    if (harmonizerSelectCursor[harmonizerNum][1] < 1) {
      harmonizerSelectCursor[harmonizerNum][1] = harmonizerSelectCursorMAX[1] ;
    } 
    while(harmonizerSelectCursor[harmonizerNum][1] > (harmonizerSelectMenuPos[harmonizerNum]+2)) {
      harmonizerSelectMenuPos[harmonizerNum] ++ ;
    }
    while(harmonizerSelectCursor[harmonizerNum][1] < harmonizerSelectMenuPos[harmonizerNum]) {
      harmonizerSelectMenuPos[harmonizerNum] -- ;
    }
    break;
    case 1:
      switch(harmonizerChordMenuCase) {
        case 0:
          harmonizerPitchSelectControl(harmonizerNum, harmonizerChordNum, harmonizerPitchNum[0], harmonizerPitchNum[1], harmonizerPitchSelect ) ; 
        break; 
        case 1:
          if (backFunction && backFunctionToggle) {
            backFunctionToggle = false ;
            harmonizerSelectMenuCase[harmonizerNum] = 0 ;
          }
        break;
        case 2:
          if (backFunction && backFunctionToggle) {
            backFunctionToggle = false ;
            harmonizerSelectMenuCase[harmonizerNum] = 0 ;
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
    display.print("Harmonizer") ;
    display.print(" ") ;
    display.print(harmonizerNum+1) ;

    for (int i=0; i<3; i++) {
      switch(harmonizerSelectMenuPos[harmonizerNum]+i) {
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
    display.drawRect(1+(harmonizerSelectCursor[harmonizerNum][0]-1)*64, 17+(harmonizerSelectCursor[harmonizerNum][1]-harmonizerSelectMenuPos[harmonizerNum])*16, 62, 13, WHITE) ;
    
    break;
    case 1:
      switch(harmonizerChordMenuCase) {
        case 0:
          harmonizerPitchSelectPrint(harmonizerNum, harmonizerChordNum, harmonizerPitchNum[0], harmonizerPitchNum[1], harmonizerPitchSelect ) ;
        break;
        case 1:
          display.setCursor(4,4) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Presets") ;
        break;
        case 2:
          display.setCursor(4,4) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;
          display.print("Reset") ;
          display.print("?") ;
        break;
      }
      
    break;
  }
}


void harmonizerPitchSelectControl(int8_t harmonizerNum, int8_t chordNum, int8_t pitchNumX, int8_t pitchNumY, boolean pitchSelector) {
  int8_t pitchNum = 2*harmonizerPitchNum[1] + harmonizerPitchNum[0] ;
  
  if (harmonizerPitchSelect == false) {
    if (backFunction && backFunctionToggle) {
      backFunctionToggle = false ;
      harmonizerSelectMenuCase[harmonizerNum] = 0 ;
    }
    if (cursorLeft && cursorLeftToggle) {
      cursorLeftToggle = false ;
      harmonizerPitchNum[0] -- ;
    }
    if (cursorRight && cursorRightToggle) {
      cursorRightToggle = false ;
      harmonizerPitchNum[0] ++ ;
    }
    if (cursorUp && cursorUpToggle) {
      harmonizerPitchNum[1] -- ;
      cursorUpToggle = false ;
    }
    if (cursorDown && cursorDownToggle) {
      harmonizerPitchNum[1] ++ ;
      cursorDownToggle = false ;
    }
    if (harmonizerPitchNum[0] > 1) {
      harmonizerPitchNum[0] = 0 ;
    }
    if (harmonizerPitchNum[0] < 0) {
      harmonizerPitchNum[0] = 1 ;
    }
    if (harmonizerPitchNum[1] > 1) {
      harmonizerPitchNum[1] = 0 ;
    }
    if (harmonizerPitchNum[1] < 0) {
      harmonizerPitchNum[1] = 1 ;
    } 
    if (selectFunction && selectFunctionToggle) {
      selectFunctionToggle = false ;
      harmonizerPitchSelect = true ;
      harmonizerPitchLast = harmonizerValues[harmonizerNum][chordNum-1][pitchNum] ;
    }
  } else if (harmonizerPitchSelect == true) {
    
    if (selectFunction && selectFunctionToggle) {
      selectFunctionToggle = false ;
      harmonizerPitchSelect = false ;
      harmonizerPitchBlinker[pitchNum] = 1 ;
    }
    if (backFunction && backFunctionToggle) {
      backFunctionToggle = false ;
      harmonizerPitchSelect = false ;
      harmonizerPitchBlinker[pitchNum] = 1 ;
      harmonizerValues[harmonizerNum][chordNum-1][pitchNum] = harmonizerPitchLast ;
    }
    if (cursorUp && cursorUpToggle) {
      harmonizerValues[harmonizerNum][chordNum-1][pitchNum] ++ ;
      harmonizerValues[harmonizerNum][chordNum-1][pitchNum] = constrain(harmonizerValues[harmonizerNum][chordNum-1][pitchNum], -12, 12) ;
      cursorUpToggle = false ;
    }
    if (cursorDown && cursorDownToggle) {
      harmonizerValues[harmonizerNum][chordNum-1][pitchNum] -- ;
      harmonizerValues[harmonizerNum][chordNum-1][pitchNum] = constrain(harmonizerValues[harmonizerNum][chordNum-1][pitchNum], -12, 12) ;
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
  display.print("Chord") ;
  display.print(" ") ;
  display.print(chordNum) ;

  display.setCursor(4,26) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (harmonizerPitchBlinker[0] == 1) {
    display.print(" ") ;
    if (harmonizerValues[harmonizerNum][chordNum-1][0] >= 0) {
     display.print("+") ;
   } 
   display.print(harmonizerValues[harmonizerNum][chordNum-1][0]) ;
  }
  

  display.setCursor(68,26) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (harmonizerPitchBlinker[1] == 1) {
    display.print(" ") ;
    if (harmonizerValues[harmonizerNum][chordNum-1][1] >= 0) {
     display.print("+") ;
   } 
   display.print(harmonizerValues[harmonizerNum][chordNum-1][1]) ;
  }

  display.setCursor(4,50) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (harmonizerPitchBlinker[2] == 1) {
    display.print(" ") ;
    if (harmonizerValues[harmonizerNum][chordNum-1][2] >= 0) {
     display.print("+") ;
   } 
   display.print(harmonizerValues[harmonizerNum][chordNum-1][2]) ;
  }

  display.setCursor(68,50) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;
  display.print("Pitch") ;
  if (harmonizerPitchBlinker[3] == 1) {
    display.print(" ") ;
    if (harmonizerValues[harmonizerNum][chordNum-1][3] >= 0) {
     display.print("+") ;
   } 
   display.print(harmonizerValues[harmonizerNum][chordNum-1][3]) ;
  }

  display.drawRect(pitchNumX*64, 22+(pitchNumY*24), 64, 15, WHITE) ;
}   
