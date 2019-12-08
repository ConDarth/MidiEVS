#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define JOYSTICK_X_PORT A0
#define JOYSTICK_Y_PORT A1

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


double cursorXRaw = 64 ;
int cursorX = 64 ;
int cursorXLast = 0 ;
double cursorYRaw = 32 ;
int cursorY = 32 ;
int cursorYLast = 0 ;

boolean menuUpdate = true ;

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

  // Clear the buffer
  display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  getCursor() ;
  
  if (menuUpdate) {
    display.clearDisplay() ;

    display.setCursor(3, 3) ;
    display.setTextColor(WHITE) ;
    display.setTextSize(1) ;
    display.println("Test Title 1") ;
    
    display.setCursor(3, 19) ;
    display.setTextColor(WHITE) ;
    display.setTextSize(1) ;
    display.print("Test Title 2") ;
    
    display.setCursor(3, 35) ;
    display.setTextColor(WHITE) ;
    display.setTextSize(1) ;
    display.print("Test Title 3") ;
    
    display.setCursor(3, 51) ;
    display.setTextColor(WHITE) ;
    display.setTextSize(1) ;
    display.print("Test Title 4") ; 
    
    for (int i=0; i<64; i+=16) {
      if ((cursorX >= 0) && (cursorX <= 96) && (cursorY >= i) && (cursorY <= 14+i)) {
        display.drawRect(0, i, 96, 13, WHITE) ;
      }
    }
    
    
    display.fillTriangle(cursorX, cursorY, (cursorX+3), (cursorY+3), (cursorX), (cursorY+4), WHITE) ;
    
    display.display() ;
    menuUpdate = false ;
  }

}

void getCursor() {
  cursorXRaw = cursorXRaw + (515 - analogRead(JOYSTICK_X_PORT))*0.01 ;
  cursorYRaw = cursorYRaw + (analogRead(JOYSTICK_Y_PORT) - 495)*0.01 ;
  cursorXRaw = constrain(cursorXRaw, -2, 127) ;
  cursorYRaw = constrain(cursorYRaw, -2, 62) ;
  cursorX = (int) cursorXRaw ;
  cursorY = (int) cursorYRaw ;
  if ((cursorXLast != cursorX) || (cursorYLast != cursorY)) {
    menuUpdate = true ;
  }
  cursorXLast = cursorX ;
  cursorYLast - cursorY ;   
}
