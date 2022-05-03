#ifndef __SENDINFOTASK__
#define __SENDINFOTASK__
#include "shared_variables.h"
#include "Task.h"
#include <Arduino.h>
#include "pir.h"

class SendInfoTask: public Task {

 char* modalityNames [3];
 int indexModality;
  
public:

 SendInfoTask(); 
 void init(int period); 
 void tick();
 void verifyMachineModality();
 void sendMsg();
 void readMsg();
 
};

extern SendInfoTask sendInfoTask;
#endif
