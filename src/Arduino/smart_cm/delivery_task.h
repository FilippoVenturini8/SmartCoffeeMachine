#ifndef __DELIVERYTASK__
#define __DELIVERYTASK__
#include "shared_variables.h"
#include "Task.h"
#include <Arduino.h>
#include "sonar.h"
#include "servo_motor.h"

class DeliveryTask: public Task {

 const int T_TIMEOUT = 5000;
 unsigned long productDoneTime;
 enum { WAIT_MAKING, DELIVERING, DELIVERED } state;
 Sonar* sonar;
 int pinEcho;
 int pinTrig;
 int pinServo;
 float distance;
 
public:

 DeliveryTask(int pinTrig, int pinEcho); 
 void init(int period); 
 void tick();
 
};
#endif
