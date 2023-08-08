#include "Arduino.h"
#include "MenuRow.h"
#include <LiquidCrystal.h>

//Empty constructor since it will be used in an array 
MenuRow::MenuRow() {
}

//Initialization of all the necessary data
void MenuRow::init(LiquidCrystal* _lcd, char* _title, int8_t _min0, int8_t _min1, int8_t _min2, int8_t _min3, int8_t _max0, int8_t _max1, int8_t _max2, int8_t _max3){
  lcd = _lcd;
  title = _title ;
  minVal[0] = _min0 ;
  minVal[1] = _min1 ;
  minVal[2] = _min2 ;
  minVal[3] = _min3 ;
  maxVal[0] = _max0 ;
  maxVal[1] = _max1 ;
  maxVal[2] = _max2 ;
  maxVal[3] = _max3 ;

  for (int8_t i=0; i<4; i++){
    currVal[i] = constrain(currVal[i], minVal[i], maxVal[i]) ;
  }
}

//-------------------------------------------------------------------------------------------------
//Alteration functions for the data stored in this row
//Ensures the proper constraints and sets off a flag if data changes

int8_t MenuRow::getVal(int8_t _col){
  return currVal[_col] ;
}

void MenuRow::setVal(int8_t _col, int8_t _newVal){
  lastVal[_col] = currVal[_col] ;
  currVal[_col] = constrain(_newVal, minVal[_col], maxVal[_col]) ;

  if (lastVal[_col] != currVal[_col]){
    updateFlag |= 1<<_col ;
  }
}

void MenuRow::setRow(int8_t* _newVals){
  currVal[0] = _newVals[0] ;
  currVal[1] = _newVals[1] ;
  currVal[2] = _newVals[2] ;
  currVal[3] = _newVals[3] ;

  updateFlag |= B00001111 ;
}

void MenuRow::addVal(int8_t _col, int8_t _delVal){
  lastVal[_col] = currVal[_col] ;
  currVal[_col] = constrain(currVal[_col]+_delVal, minVal[_col], maxVal[_col]) ;

  if (lastVal[_col] != currVal[_col]){
    updateFlag |= 1<<_col ;
  }
}

void MenuRow::addRow(int8_t* _delVals){
  for (int8_t i=0; i<4; i++){
    lastVal[i] = currVal[i] ;
    currVal[i] = constrain(currVal[i]+_delVals[i], minVal[i], maxVal[i]) ;

    if (lastVal[i] != currVal[i]){
      updateFlag |= 1<<i ;
    }
  }
}

//-------------------------------------------------------------------------------------------------
//This adds in exceptions for data values in certain colums

void MenuRow::setExceptions(int8_t _col, int8_t _exceptionVal[], char** _exceptionChar, int8_t _exceptionNum){
  exceptionVal[_col] = _exceptionVal  ;
  exceptionChar[_col] = _exceptionChar ;
  exceptionNum[_col] = _exceptionNum ;
}

//-------------------------------------------------------------------------------------------------
//Set function for the layer 
//This determines where on the screen the row is printed

void MenuRow::setLayer(int8_t _layer){
  //Layer 0 is the top row on screen and layer 1 is the bottom row on screen
  layer = _layer ;
  updateFlag = B00011111  ;  //Tells the class to reprint the title heading
}

//-------------------------------------------------------------------------------------------------
//Updating the display to print out the necessary data if any had been updated

void MenuRow::update(){
  //Update the title if necessay
  if ( updateFlag&B00010000 ){
    lcd->setCursor(0, 2*layer) ;
    lcd->print(title) ;
    updateFlag ^= B00010000  ;
  }

  //Update each of the data in the 4 columns if necessary 
  for (int8_t i=0; i<4; i++){
    if ( updateFlag&(1<<i) ){
      sprintf(buff, "% 4i", currVal[i]) ;
      lcd->setCursor(4+4*i, 2*layer+1) ;
      
      for (int j=0; j<exceptionNum[i];j++){
        if (currVal[i] == exceptionVal[i][j]){
          buff[0] = exceptionChar[i][j][0] ;
          buff[1] = exceptionChar[i][j][1] ;
          buff[2] = exceptionChar[i][j][2] ;
          buff[3] = exceptionChar[i][j][3] ;
        }
      }
      
      lcd->print(buff) ;
      updateFlag ^= 1<<i ;
    }
  }
}
