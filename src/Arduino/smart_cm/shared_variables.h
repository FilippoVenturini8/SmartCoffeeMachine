#ifndef __SHARED_VARIABLES__
#define __SHARED_VARIABLES__
#include "display.h"
#include "servo_motor.h"

extern bool isReady;

extern bool selected;

extern bool productDone;

extern bool delivered;

extern bool isWorking;

extern bool assistanceRequired;

extern char* productList[3];

extern int quantityList[3];

extern int selectedIndex;

extern int nSelfTest;

extern const int N_MAX;

extern Display* machineDisplay;

extern ServoMotor* servoMotor;

#endif
