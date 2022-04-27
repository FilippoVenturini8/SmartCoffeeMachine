#include "display_task.h"
#include <string.h>
#include "Arduino.h"

DisplayTask::DisplayTask(){
  
}
 
void DisplayTask::init(int period){
 Task::init(period);
 machineDisplay = new DisplayImpl(); 
}
 
void DisplayTask::tick(){
  if(strcmp(msg,lastPrint) != 0){
    machineDisplay->displayMessage(msg);
    lastPrint = msg;
  }
}
