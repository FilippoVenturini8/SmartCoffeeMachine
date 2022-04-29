#ifndef __CHECKTASK__
#define __CHECKTASK__
#include "shared_variables.h"
#include "Task.h"
#include <Arduino.h>
#include "temp_sensor.h"

class CheckTask: public Task {

 enum { WAITING_CHECK, SELF_TEST, TEMP_CHECK } state;
 TempSensor* tempSensor;
 int pinTempSensor;
 
public:

 CheckTask(int pinTempSensor); 
 void init(int period); 
 void tick();
 
};
#endif
