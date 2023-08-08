#include "Arduino.h"
#include "MenuRow.h"
#include <LiquidCrystal.h>
#include "Menu.h"

//Constructor to assign all the needed references
Menu::Menu(MenuRow _menu[], int8_t _menuSize, int8_t _menuData[][4], LiquidCrystal* _menuLCD){
  menuLCD = _menuLCD ;
  menu = _menu ;
  menuSize = _menuSize ;
  menuData = _menuData ;

  menuLCD->begin(20, 4);
}

//Initializer for the rows of the menu
void Menu::initRow(int8_t _row, char* _title, int8_t _min0, int8_t _min1, int8_t _min2, int8_t _min3, int8_t _max0, int8_t _max1, int8_t _max2, int8_t _max3){
  menu[_row].init(menuLCD, _title, _min0, _min1, _min2, _min3, _max0, _max1, _max2, _max3) ; 
  menu[_row].setRow(menuData[_row]) ; 
}

//Function to set any exceptions a row may have 
void Menu::setExceptions(int8_t _row, int8_t _col, int8_t* _exceptionVal, char** _exceptionChar, int8_t _exceptionNum) {
  menu[_row].setExceptions(_col, _exceptionVal, _exceptionChar, _exceptionNum) ;
}

int8_t Menu::getRow(){
  return currRow ;
}


//Update function for the menu
//Takes in a pointer to the 5 things that can change
//deltas for: col0 col1 col2 col3 row
void Menu::update(int8_t* _delta){
  //The last column changes which rows shown
  currRow = (currRow +_delta[4])%menuSize ;

  //This updates the top and bottom row depending on where we were
  if (currRow != lastRow) {
    if (lastRow = topRow) {
      topRow = currRow ;
      botRow = (currRow+1)%menuSize ;
    } else {
      topRow = (currRow-1)%menuSize ;
      botRow = currRow ;
    }

    //Resetting the menu to the new displayed rows
    menu[topRow].setLayer(0) ;
    menu[botRow].setLayer(1) ;
    menu[topRow].update() ;
    menu[botRow].update() ;
  }

  //Updates the values of the columns in all the rows
  
  menu[currRow].addRow(_delta) ;
  menu[currRow].update() ;
}
