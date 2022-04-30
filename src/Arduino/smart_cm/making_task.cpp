#include "making_task.h"
#include <Arduino.h>

MakingTask::MakingTask(){
}
 
void MakingTask::init(int period){
  Task::init(period);
  this->state = WAIT_SELECTION;
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
      servoMotor->on();
      for(int i=0; i < 180; i++){
        servoMotor->setPosition(i);
        delay(55);
      }
      servoMotor->off();
      productDone = true;
      state = WAIT_DELIVERY;

      char msg[80];
    
      strcpy(msg, "The ");
      strcat(msg, productList[selectedIndex]);
      strcat(msg, " is ready");
      machineDisplay->displayMessage(msg);
      break;
    case WAIT_DELIVERY:
      if(delivered or !selected){
        state = WAIT_SELECTION;
      }
      break;
  }
}
