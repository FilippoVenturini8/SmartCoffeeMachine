#include "send_info_task.h"
#include <Arduino.h>

bool msgAvailable;
String recivedMsg;

SendInfoTask::SendInfoTask(){
  this->modalityNames[0] = (char*)"IDLE";
  this->modalityNames[1] = (char*)"WORKING";
  this->modalityNames[2] = (char*)"ASSISTANCE";
  this->indexModality = 0;
  msgAvailable = false;
  recivedMsg = "";
}
 
void SendInfoTask::init(int period){
  Task::init(period);
}
 
void SendInfoTask::tick(){
  verifyMachineModality();
  sendMsg();
  Serial.flush();
  if(msgAvailable){
    readMsg();
  }
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

void SendInfoTask::readMsg(){
  if(recivedMsg == "REFILL"){
    if(quantityList[0] == 0 and quantityList[1] == 0 and quantityList[2] == 0){
      assistanceRequired = false;
    }
    quantityList[0] = 3;
    quantityList[1] = 3;
    quantityList[2] = 3;
    machineDisplay->displayMessage(productList[selectedIndex]);
  }else if(recivedMsg == "RECOVER"){
    if(quantityList[0] != 0 or quantityList[1] != 0 or quantityList[2] != 0){
      assistanceRequired = false;
    }
  }
  msgAvailable = false;
  recivedMsg = "";
}

void serialEvent(){
  while(Serial.available()){
    char ch = (char) Serial.read();
    if (ch == '\n'){
      msgAvailable = true;      
    } else {
      recivedMsg += ch;      
    }
  }
}
