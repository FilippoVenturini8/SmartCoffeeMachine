#ifndef __BUTTONSTASK__
#define __BUTTONSTASK__
#include "Task.h"
#include "button.h"
#include "button_impl.h"
#include <Arduino.h>

class ButtonsTask: public Task {

 int pin[3];
 Button* buttonUp;
 Button* buttonDown;
 Button* buttonMake;
 enum { UP, DOWN, MAKE } state;
 
public:

 ButtonsTask(int pinUp, int pinDown, int pinMake); 
 void init(int period); 
 void tick();
 void checkState();
 
};
#endif
