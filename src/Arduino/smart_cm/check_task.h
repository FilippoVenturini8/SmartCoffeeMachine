#ifndef __CHECKTASK__
#define __CHECKTASK__
#include "shared_variables.h"
#include "Task.h"
#include <Arduino.h>
#include "temp_sensor.h"

class CheckTask: public Task {

 const int T_CHECK = 10000; //DA MODIFICARE
 const float T_MIN = 17.0;
 const float T_MAX = 24.0;
 enum { WAITING_CHECK, TEMP_CHECK, SELF_TEST } state;
 TempSensor* tempSensor;
 int pinTempSensor;
 unsigned long startCheckTime;
 
 
public:

 CheckTask(int pinTempSensor); 
 void init(int period); 
 void tick();
 
};
#endif
