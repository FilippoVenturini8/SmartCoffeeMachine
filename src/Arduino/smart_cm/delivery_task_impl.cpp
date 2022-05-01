#include "delivery_task.h"
#include <Arduino.h>
#include "sonar_impl.h"

DeliveryTask::DeliveryTask(int pinTrig, int pinEcho){
  this->pinTrig = pinTrig;
  this->pinEcho = pinEcho;
}
 
void DeliveryTask::init(int period){
  Task::init(period);
  this->sonar = new SonarImpl(pinTrig, pinEcho);
  this->state = WAIT_MAKING;
}
 
void DeliveryTask::tick(){
  switch(state){
    case WAIT_MAKING:
      if(productDone){
        productDoneTime = millis();
        state = DELIVERING;
        productDone = false;
      }
      break;
    case DELIVERING:
      distance = sonar->getDistance();
      if(distance >= 0.40 or millis()-productDoneTime >= T_TIMEOUT){
        state = DELIVERED;
      }
      delay(50); 
      break;
    case DELIVERED:
      servoMotor->on();
      servoMotor->setPosition(0);
      delay(100);
      servoMotor->off();
      state = WAIT_MAKING;
      delivered = true;
      canCheck = true;
      break;
  }
}
