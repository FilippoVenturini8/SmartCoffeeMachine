#include "selection_task.h"
#include <Arduino.h>

bool selected;

char* productList[3];

int quantityList[3];

int selectedIndex;

char* msg;


SelectionTask::SelectionTask(int pinUp, int pinDown, int pinMake, int pinPot){
  this->pin[0] = pinUp;
  this->pin[1] = pinDown;
  this->pin[2] = pinMake;
  this->pin[3] = pinPot;
  this->state = SELECTING;

  //TEMPORNEO
  selected = false;
  selectedIndex = 0;
  productList[0] = (char*)"TEA";
  productList[1] = (char*)"COFFE";
  productList[2] = (char*)"CHOCOLATE";
  quantityList[0] = 3;
  quantityList[1] = 3;
  quantityList[2] = 3;
  msg = (char*)"Prova";
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
      msg = productList[selectedIndex];
      checkButtonPressed();
      break;
    case WAIT_FOR_DELIVERY:
      break;
  }
}

void SelectionTask::checkButtonPressed(){
  if(buttonUp->isPressed()){
    if(selectedIndex == 2){
      selectedIndex = 0;
    }else{
      selectedIndex++;
    }
  }else if(buttonDown->isPressed()){
    if(selectedIndex == 0){
      selectedIndex = 2;
    }else{
      selectedIndex--;
    }
  }else if(buttonMake->isPressed()){
    selected = true;
    state = WAIT_FOR_DELIVERY;

    char result[80];
    
    strcpy(result, "making a ");
    strcat(result, productList[selectedIndex]);
    msg = result;
  }
}
