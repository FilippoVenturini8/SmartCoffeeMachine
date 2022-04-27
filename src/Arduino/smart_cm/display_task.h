#ifndef __DISPLAYTASK__
#define __DISPLAYTASK__
#include "Task.h"
#include "display.h"
#include "display_impl.h"
#include "shared_variables.h"

class DisplayTask: public Task {
 Display* machineDisplay;
 char* lastPrint;
 
public:

 DisplayTask(); 
 void init(int period); 
 void tick();
 
};
#endif
