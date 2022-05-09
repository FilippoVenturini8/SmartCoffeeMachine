#include "send_info_task.h"
#include <Arduino.h>

bool msgAvailable;
String recivedMsg;

SendInfoTask::SendInfoTask(){
  this->modalityNames[0] = (char*)"IDLE";
  this->modalityNames[1] = (char*)"WORKING";
  this->modalityNames[2] = (char*)"ASSISTANCE";
  this->state = VERIFY_MODALITY;
  this->indexModality = 0;
  msgAvailable = false;
  recivedMsg = "";
}
 
void SendInfoTask::init(int period){
  Task::init(period);
}
 
void SendInfoTask::tick(){
  switch(state){    
    case VERIFY_MODALITY: 
      verifyMachineModality();
      state = SEND;
      break;
      
    case SEND: 
      sendMsg();
      Serial.flush();
      state = RECEIVE;
      break;
      
    case RECEIVE:
      if(msgAvailable){
        readMsg();
      }
      state = VERIFY_MODALITY;
      break;
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
    quantityList[0] = N_MAX;
    quantityList[1] = N_MAX;
    quantityList[2] = N_MAX;
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
