#include "user_detection_task.h"
#include <avr/sleep.h>
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
      if(pir->isDetected()){
        state = NOT_DETECTED;
        lastDetectionTime = millis();
        //Serial.println("not detected");
      }
      break;
    case NOT_DETECTED:
      if(pir->isDetected()){
        state = DETECTED;
        //Serial.println("detected");
        
      }else if(!pir->isDetected() and millis()-lastDetectionTime >= T_IDLE){
        Serial.println("SLEEP");
        set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
        sleep_enable();
        sleep_mode();
        
        Serial.println("WAKE UP"); 
        sleep_disable();
      }
      break;
  }
}
