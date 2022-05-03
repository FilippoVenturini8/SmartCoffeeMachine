#ifndef __SELECTIONTASK__
#define __SELECTIONTASK__
#include "shared_variables.h"
#include "Task.h"
#include "button.h"
#include "button_impl.h"
#include "potentiometer.h"
#include "potentiometer_impl.h"
#include <Arduino.h>

class SelectionTask: public Task {

 const int T_READY = 5000;
 unsigned long lastIteration;
 int pin[4];
 int delta;
 int sugarLevel;
 Button* buttonUp;
 Button* buttonDown;
 Button* buttonMake;
 Pot* potentiometer;
 enum { SELECTING, WAIT_DELIVERY } state;
 
public:

 SelectionTask(int pinUp, int pinDown, int pinMake, int pinPot); 
 void init(int period); 
 void tick();
 void checkButtonPressed();
 void nextProduct();
 void checkSugarLevel();
 
};

#endif
