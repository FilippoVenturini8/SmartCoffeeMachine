#include "check_task.h"
#include <Arduino.h>
#include "temp_sensor_impl.h"

CheckTask::CheckTask(int pinTempSensor){
  this->pinTempSensor = pinTempSensor;
}
 
void CheckTask::init(int period){
  Task::init(period);
  this->tempSensor = new TempSensorImpl(pinTempSensor);
  this->state = TEMP_CHECK;
}
 
void CheckTask::tick(){
  switch(state){
    case WAITING_CHECK:
      break;
    case SELF_TEST:
      break;
    case TEMP_CHECK:
      Serial.println(tempSensor->getTemperature());
      break;
  }
}
