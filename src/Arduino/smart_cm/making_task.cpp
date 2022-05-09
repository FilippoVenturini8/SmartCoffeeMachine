#include "making_task.h"
#include <Arduino.h>

MakingTask::MakingTask(){
}
 
void MakingTask::init(int period){
  Task::init(period);
  this->state = WAIT_SELECTION;
  this->servoPosition = 0;
}
 
void MakingTask::tick(){
  switch(state){
    case WAIT_SELECTION:
      if(selected){
        selected = false;
        state = MAKING;
      }
      break;
    case MAKING:
      if(servoPosition <= 180){
        servoMotor->on();
        
        servoMotor->setPosition(servoPosition);
        delay(20);
        servoPosition+=2;
        servoMotor->off();
      }else{
        servoPosition = 0;
        productDone = true;
        state = WAIT_SELECTION;
  
        char msg[80];
      
        strcpy(msg, "The ");
        strcat(msg, productList[selectedIndex]);
        strcat(msg, " is ready");
        machineDisplay->displayMessage(msg);
      }
      
      break;
  }
}
