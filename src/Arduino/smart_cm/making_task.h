#ifndef __MAKINGTASK__
#define __MAKINGTASK__
#include "shared_variables.h"
#include "Task.h"
#include <Arduino.h>

class MakingTask: public Task {

 enum { WAIT_SELECTION, MAKING } state;
 int servoPosition;
 
public:

 MakingTask(); 
 void init(int period); 
 void tick();
 
};
#endif
