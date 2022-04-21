#ifndef __DISPLAY_IMPL__
#define __DISPLAY_IMPL__

#include "display.h"
#include <LiquidCrystal_I2C.h>

class DisplayImpl: public Display {

public:
  DisplayImpl();

  void displayMessage(char* msg);
    
private:
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);
};

#endif
