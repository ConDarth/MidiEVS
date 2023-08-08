#ifndef Menu_h
#define Menu_h

#include <Arduino.h>
#include "MenuRow.h"
#include <LiquidCrystal.h>

class Menu {
public:
  Menu(MenuRow _menu[], int8_t _menuSize,int8_t _menuData[][4], LiquidCrystal* _menuLCD);
  void initRow(int8_t _row, char* _title, int8_t _min0, int8_t _min1, int8_t _min2, int8_t _min3, int8_t _max0, int8_t _max1, int8_t _max2, int8_t _max3) ;
  void update(int8_t* _delta) ;
  void setExceptions(int8_t _row, int8_t _col, int8_t* _exceptionVal, char** _exceptionChar, int8_t _exceptionNum) ;
  int8_t getRow() ;
  
private:
  LiquidCrystal* menuLCD ;
  MenuRow* menu ;
  int8_t menuSize ;
  int8_t (*menuData)[4] ; 
  int8_t currRow = 0 ;
  int8_t lastRow = 0 ;
  int8_t topRow = 0 ;
  int8_t botRow = 1 ;
  
} ;

#endif
