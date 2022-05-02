#include "send_info_task.h"
#include <Arduino.h>

SendInfoTask::SendInfoTask(){
  this->modalityNames[0] = (char*)"IDLE";
  this->modalityNames[1] = (char*)"WORKING";
  this->modalityNames[2] = (char*)"ASSISTANCE";
  this->indexModality = 0;
}
 
void SendInfoTask::init(int period){
  Task::init(period);
}
 
void SendInfoTask::tick(){
  verifyMachineModality();
  sendMsg();
  Serial.flush();
}

void SendInfoTask::verifyMachineModality(){
  if(assistanceRequired){
    indexModality = 2;
  }else if(isWorking){
    indexModality = 1;
  }else{
    indexModality = 0;
  }
}

void SendInfoTask::sendMsg(){
  String msg = modalityNames[indexModality];
  msg += '|';
  msg += (String)nSelfTest;
  msg += '|';
  msg += (String)quantityList[0];
  msg += '|';
  msg += (String)quantityList[1];
  msg += '|';
  msg += (String)quantityList[2];
  
  Serial.println(msg);
}
