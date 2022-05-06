#include "check_task.h"
#include <Arduino.h>
#include "temp_sensor_impl.h"

CheckTask::CheckTask(int pinTempSensor){
  this->pinTempSensor = pinTempSensor;
}
 
void CheckTask::init(int period){
  Task::init(period);
  this->tempSensor = new TempSensorImpl(pinTempSensor);
  this->state = WAITING_CHECK;
  this->lastCheckTime = millis();
}
 
void CheckTask::tick(){
  if(assistanceRequired){
    return;
  }
  switch(state){
    case WAITING_CHECK:
      if(millis() - lastCheckTime >= T_CHECK and !isWorking){
        state = TEMP_CHECK;
      }
      break;
    case TEMP_CHECK:
      machineDisplay->displayMessage((char*)"SELF TEST...");
      nSelfTest++;
      isWorking = true;
      temperature = tempSensor->getTemperature();

      if(temperature < T_MIN or temperature > T_MAX){
        machineDisplay->displayMessage((char*)"Assistance Required");
        assistanceRequired = true; 
        lastCheckTime = millis();
        state = WAITING_CHECK;
        isWorking = false;
      }else{
        state = SELF_TEST;
      }
      break;
    case SELF_TEST:
      servoMotor->on();
      servoMotor->setPosition(180);
      delay(500);
      servoMotor->setPosition(0);
      delay(500);
      servoMotor->off();

      state = WAITING_CHECK;
      lastCheckTime = millis();
      isWorking = false;
      break;
  }
}
