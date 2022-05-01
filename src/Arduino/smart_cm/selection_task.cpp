#include "selection_task.h"
#include <Arduino.h>
#include "display.h"
#include "display_impl.h"
#include "servo_motor.h"
#include "servo_motor_impl.h"

SelectionTask::SelectionTask(int pinUp, int pinDown, int pinMake, int pinPot){
  this->pin[0] = pinUp;
  this->pin[1] = pinDown;
  this->pin[2] = pinMake;
  this->pin[3] = pinPot;
  this->state = SELECTING;
}
 
void SelectionTask::init(int period){
  Task::init(period);
  buttonUp = new ButtonImpl(pin[0]); 
  buttonDown = new ButtonImpl(pin[1]);
  buttonMake = new ButtonImpl(pin[2]);
  potentiometer = new PotImpl(pin[3]);
}
 
void SelectionTask::tick(){
  switch(state){
    case SELECTING:
      checkButtonPressed();
      break;
    case WAIT_DELIVERY:
      if(delivered){
        state = SELECTING;
        delivered = false;
      }
      break;
  }
}

void SelectionTask::checkButtonPressed(){
  if(buttonUp->isPressed()){
    delta = 1;
    nextProduct();
  }else if(buttonDown->isPressed()){
    delta = -1;
    nextProduct();
  }else if(buttonMake->isPressed()){
    quantityList[selectedIndex]-=1;
    selected = true;
    canCheck = false;
    state = WAIT_DELIVERY;

    char msg[80];
    
    strcpy(msg, "Making a ");
    strcat(msg, productList[selectedIndex]);
    machineDisplay->displayMessage(msg);
  }
}

void SelectionTask::nextProduct(){
  int c = 0;
  do{
    if(selectedIndex == 2 and delta == 1){
      selectedIndex = 0;
    }else if(selectedIndex == 0 and delta == -1){
      selectedIndex = 2;
    }else{
      selectedIndex += delta;
    }
    c++;
  }while(quantityList[selectedIndex] == 0 and c < 3);
  
  if(quantityList[selectedIndex] == 0 and c == 3){
    machineDisplay->displayMessage((char*)"Assistance Required");
  }else{
    machineDisplay->displayMessage(productList[selectedIndex]);
  }
}
