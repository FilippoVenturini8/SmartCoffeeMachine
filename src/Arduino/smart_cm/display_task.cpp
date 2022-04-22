#include "display_task.h"

DisplayTask::DisplayTask(){
  
}
 
void DisplayTask::init(int period){
 Task::init(period);
 machineDisplay = new DisplayImpl(); 
 //state = OFF; 
}
 
void DisplayTask::tick(){
  machineDisplay->displayMessage("Prova");
}
