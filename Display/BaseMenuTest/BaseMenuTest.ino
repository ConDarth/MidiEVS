#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define JOYSTICK_X_PORT A0
#define JOYSTICK_Y_PORT A1
#define SELECT_BUTTON_PIN 5
#define BACK_BUTTON_PIN 2

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

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
unsigned long transpositionMenuLastTime = 0 ;

int8_t threeCursorPosition = 0 ;
int8_t threeCursorMAX = 2 ;
int8_t threeMenuPosition = 0 ;
int8_t threeMenuCase = 0 ;

int8_t harmonizerCursor = 1 ;
int8_t harmonizerCursorMAX = 3 ;
int8_t harmonizerMenuPos = 1 ;
int8_t harmonizerMenuCase = 0 ;

int8_t harmonizer1Cursor[2] = {1, 1} ;
int8_t harmonizer1CursorMAX[2] = {2, 4}  ;
int8_t harmonizer1MenuPos = 1 ;
int8_t harmonizer1MenuCase = 0 ;

int8_t harmonizer2Cursor[2] = {1, 1} ;
int8_t harmonizer2CursorMAX[2] = {2, 4} ;


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

  display.display();
  delay(1000); // Pause for 2 seconds

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
  if (joystickYToggle && (joystickY > 260) && (joystickY < 760)) {
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
  if (joystickXToggle && (joystickX > 260) && (joystickX < 760)) {
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
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Sensor Adjust") ;    
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
          display.print("Multi-Phonics Mode") ;  
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
          display.print("Test Title 5") ;  
        break;
        case 6:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Test Title 6") ;  
        break;
        case 7:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Test Title 7") ;  
        break;
        case 8:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Test Title 8") ;  
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
          display.print("Pitch Bend Up") ;  
        break;
        case 4:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Pitch Bend Down") ;  
        break;
        case 5:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Test SubTitle 5") ;  
        break;
        case 6:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Test SubTitle 6") ;  
        break;
        case 7:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Test SubTitle 7") ;  
        break;
        case 8:
          display.setCursor(4,(4+16*i)) ;
          display.setTextColor(WHITE) ;
          display.setTextSize(1) ;   
          display.print("Test SubTitle 8") ;  
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
    break;
    case 3:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Pitch Bend Up") ;
      
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
    break;
    case 4:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Pitch Bend Down") ;
      
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
    break;
    case 5:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Test SubTitle 5") ;
      
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
    break;
    case 6:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;   
      display.print("Test SubTitle 6") ;
      
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
    break;
  }
    
}

void transpositionMenuControl() {
  
  if ((millis() - transpositionMenuLastTime > 400) && (transpositionMenuCase == 0)) {
    transpositionMenuCase = 1;
    menuUpdate = true ;
    transpositionMenuLastTime = millis() ;
  }
  if ((millis() - transpositionMenuLastTime > 150) && (transpositionMenuCase == 1)) {
    transpositionMenuCase = 0 ;
    menuUpdate = true ;
    transpositionMenuLastTime = true ;
    transpositionMenuLastTime = millis() ;
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
  display.print("Multi-Phonics Mode") ;  

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
        display.setCursor(4,(20+16*i)) ;
        display.setTextColor(WHITE) ;
        display.setTextSize(1) ;
        display.print("Rotator") ;
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
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        harmonizerMenuCase = 0 ;
      }
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        harmonizer1Cursor[0] -- ;
      }
      if (cursorRight && cursorRightToggle) {
        cursorRightToggle = false ;
        harmonizer1Cursor[0] ++ ;
      }
      if (cursorUp && cursorUpToggle) {
        harmonizer1Cursor[1] -- ;
        cursorUpToggle = false ;
      }
      if (cursorDown && cursorDownToggle) {
        harmonizer1Cursor[1] ++ ;
        cursorDownToggle = false ;
      }
      
      if (harmonizer1Cursor[0] > harmonizer1CursorMAX[0]) {
        harmonizer1Cursor[0] = 1 ;
      }
      if (harmonizer1Cursor[0] < 1) {
        harmonizer1Cursor[0] = harmonizer1CursorMAX[0] ;
      }
      if (harmonizer1Cursor[1] > harmonizer1CursorMAX[1]) {
        harmonizer1Cursor[1] = 1 ;
      }
      if (harmonizer1Cursor[1] < 1) {
        harmonizer1Cursor[1] = harmonizer1CursorMAX[1] ;
      } 
      while(harmonizer1Cursor[1] > (harmonizer1MenuPos+2)) {
        harmonizer1MenuPos ++ ;
      }
      while(harmonizer1Cursor[1] < harmonizer1MenuPos) {
        harmonizer1MenuPos -- ;
      }
    break;
    case 2:
      if (backFunction && backFunctionToggle) {
        backFunctionToggle = false ;
        harmonizerMenuCase = 0 ;
      }
      if (cursorLeft && cursorLeftToggle) {
        cursorLeftToggle = false ;
        
      }
      
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
            display.print("Harmonizer 1") ;
          break;
          case 2:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Harmonizer 2") ;
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
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;
      display.print("Harmonizer 1") ;

      for (int i=0; i<3; i++) {
        switch(harmonizer1MenuPos+i) {
          case 1:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Chord 1") ;

            display.setCursor(68,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Chord 2") ;
          break;
          case 2:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Chord 3") ;

            display.setCursor(68,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Chord 4") ;
          break;
          case 3:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Chord 5") ;

            display.setCursor(68,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Chord 6") ;
          break;
          case 4:
            display.setCursor(4,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Chord 7") ;

            display.setCursor(68,(20+16*i)) ;
            display.setTextColor(WHITE) ;
            display.setTextSize(1) ;
            display.print("Chord 8") ;
          break;
        }
      }
      display.drawRect(1+(harmonizer1Cursor[0]-1)*64, 17+(harmonizer1Cursor[1]-harmonizer1MenuPos)*16, 62, 13, WHITE) ;
    break;
    case 2:
      display.setCursor(4,4) ;
      display.setTextColor(WHITE) ;
      display.setTextSize(1) ;
      display.print("Harmonizer 2") ;
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
  display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Test Title 5") ;  
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
  display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Test Title 6") ;  
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
  display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Test Title 7") ;  
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
  display.setCursor(4,4) ;
  display.setTextColor(WHITE) ;
  display.setTextSize(1) ;   
  display.print("Test Title 8") ;  
}
