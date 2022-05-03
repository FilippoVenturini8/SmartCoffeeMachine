#include "user_detection_task.h"
#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include <Arduino.h>
#include "pir_impl.h"

UserDetectionTask::UserDetectionTask(int pinPir){
  this->pinPir = pinPir;
}
 
void UserDetectionTask::init(int period){
  Task::init(period);
  this->pir = new PirImpl(pinPir);
  this->state = NOT_DETECTED;
}
 
void UserDetectionTask::tick(){
  if(!pir->isReady()){
    return;
  }
  switch(state){
    case DETECTED:
      if(!pir->isDetected()){
        state = NOT_DETECTED;
        lastDetectionTime = millis();
      }
      break;
    case NOT_DETECTED:
      if(pir->isDetected()){
        state = DETECTED;
        
      }else if(!pir->isDetected() and millis()-lastDetectionTime >= T_IDLE){
        delay(100);    
        enableInterrupt(pinPir, wakeUp, RISING);
        set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
        sleep_enable();
        sleep_mode();
         
        disableInterrupt(pinPir);
        sleep_disable();
      }
      break;
  }
}

void UserDetectionTask::wakeUp(){
}
