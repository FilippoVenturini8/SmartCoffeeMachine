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
  this->servoDelay = (T_CHECK / 2) / 180;
}
 
void CheckTask::tick(){
  switch(state){
    case WAITING_CHECK:
      if(millis() - lastCheckTime >= CHECK_PERIOD and canCheck){
        state = TEMP_CHECK;
      }
      break;
    case TEMP_CHECK:
      machineDisplay->displayMessage((char*)"SELF TEST...");
      temperature = tempSensor->getTemperature();
      Serial.println(temperature);

      if(temperature < T_MIN or temperature > T_MAX){
        machineDisplay->displayMessage((char*)"Assistance Required");
      }else{
        state = SELF_TEST;
      }
      break;
    case SELF_TEST:
      servoMotor->on();
      for(int i = 0; i < 180; i++){
        servoMotor->setPosition(i);
        delay(servoDelay);
      }
      for(int i = 178; i >= 0; i--){
        servoMotor->setPosition(i);
        delay(servoDelay);
      }
      servoMotor->off();

      state = WAITING_CHECK;
      lastCheckTime = millis();
      break;
  }
}
