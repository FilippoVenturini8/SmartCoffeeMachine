#ifndef __DISPLAY_IMPL__
#define __DISPLAY_IMPL__

#include "display.h"
#include <LiquidCrystal_I2C.h>

/* Wiring: SDA => A4, SCL => A5 */

class DisplayImpl: public Display {

public:
  DisplayImpl();

  void displayMessage(char* msg);
    
private:
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2);
};

#endif
