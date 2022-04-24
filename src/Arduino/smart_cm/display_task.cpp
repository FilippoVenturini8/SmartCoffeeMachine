#include "display_task.h"

DisplayTask::DisplayTask(){
  
}
 
void DisplayTask::init(int period){
 Task::init(period);
 machineDisplay = new DisplayImpl(); 
 state = READY; 
}
 
void DisplayTask::tick(){
  switch(state){
    case READY:
      machineDisplay->displayMessage((char*)"READY");
      break;
    case CHOOSING:
      machineDisplay->displayMessage((char*)"CHOOSING");
      break;
    case MAKING:
      machineDisplay->displayMessage((char*)"MAKING");
      break;
  }
}
