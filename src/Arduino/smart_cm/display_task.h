#ifndef __DISPLAYTASK__
#define __DISPLAYTASK__
#include "Task.h"
#include "display.h"
#include "display_impl.h"

class DisplayTask: public Task {
 Display* machineDisplay;
 //enum { ON, OFF} state;
 
public:

 DisplayTask(); 
 void init(int period); 
 void tick();
 
};
#endif
