#ifndef __CHECKTASK__
#define __CHECKTASK__
#include "shared_variables.h"
#include "Task.h"
#include <Arduino.h>
#include "temp_sensor.h"

class CheckTask: public Task {

 const long T_CHECK = 180000; 
 const float T_MIN = 17.0;
 const float T_MAX = 24.0;
 float temperature;
 enum { WAITING_CHECK, TEMP_CHECK, SELF_TEST } state;
 TempSensor* tempSensor;
 int pinTempSensor;
 unsigned long lastCheckTime;
 
 
public:

 CheckTask(int pinTempSensor); 
 void init(int period); 
 void tick();
 
};
#endif
