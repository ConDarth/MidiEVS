#ifndef MenuRow_h
#define MenuRow_h

#include <Arduino.h>
#include <LiquidCrystal.h>

class MenuRow {
public:
  //Constructor
  MenuRow();

  //Initialization of the class with its data
  void init(LiquidCrystal* _lcd, char* _title, int8_t _min0, int8_t _min1, int8_t _min2, int8_t _min3, int8_t _max0, int8_t _max1, int8_t _max2, int8_t _max3) ;

  //get and set functions for the columns 
  int8_t getVal(int8_t _col) ;
  void setVal(int8_t _col, int8_t _newVal) ;
  void setRow(int8_t* _newVals) ;
  void addVal(int8_t _col, int8_t _delVal) ;
  void addRow(int8_t* _delVals) ;

  //This adds in exceptions for the writing of the data
  void setExceptions(int8_t _col, int8_t* _exceptionVal, char** _exceptionChar, int8_t _exceptionNum);

  //Setting which layer to write to
  void setLayer(int8_t _layer);

  //Update function to draw the row at the current layer 
  void update() ;
private:
  char* title;
  LiquidCrystal* lcd;     //Note: I use a pointer to the LCD screen here
  int8_t currVal[4] = {0, 0, 0, 0} ;
  int8_t lastVal[4] = {0, 0, 0, 0} ;
  int8_t minVal[4];
  int8_t maxVal[4];
  byte updateFlag = B00011111 ;
  int8_t layer = 0;

  int8_t* exceptionVal[4] ;
  char** exceptionChar[4] ;
  int8_t exceptionNum[4] = {0, 0, 0, 0} ;

  char buff[4] ;
} ;



#endif
