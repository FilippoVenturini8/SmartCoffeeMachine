#ifndef __USERDETECTIONTASK__
#define __USERDETECTIONTASK__
#include "shared_variables.h"
#include "Task.h"
#include <Arduino.h>
#include "pir.h"

class UserDetectionTask: public Task {

 enum { DETECTED, NOT_DETECTED } state;
 const int T_IDLE = 3000;
 unsigned long lastDetectionTime;
 int pinPir;
 Pir* pir;
 
public:

 UserDetectionTask(int pinPir); 
 void init(int period); 
 void tick();
 
};
#endif
