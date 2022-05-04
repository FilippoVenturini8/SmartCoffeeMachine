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
  this->sugarLevel = 0;
}
 
void SelectionTask::init(int period){
  Task::init(period);
  buttonUp = new ButtonImpl(pin[0]); 
  buttonDown = new ButtonImpl(pin[1]);
  buttonMake = new ButtonImpl(pin[2]);
  potentiometer = new PotImpl(pin[3]);
}
 
void SelectionTask::tick(){
  if(assistanceRequired){
    return;
  }
  switch(state){
    case SELECTING:
      if(millis() - lastIteration >= T_READY){
        machineDisplay->displayMessage((char*)"Ready");
        lastIteration = millis();
        isReady = true;
      }
      checkSugarLevel();
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
    lastIteration = millis();
    isReady = false;
  }else if(buttonDown->isPressed()){
    delta = -1;
    nextProduct();
    lastIteration = millis();
    isReady = false;
  }else if(buttonMake->isPressed() and !isReady){
    quantityList[selectedIndex]-=1;
    selected = true;
    isWorking = true;
    state = WAIT_DELIVERY;

    char msg[50];
    
    strcpy(msg, "Making a ");
    strcat(msg, productList[selectedIndex]);
    machineDisplay->displayMessage(msg);
  }
}

void SelectionTask::checkSugarLevel(){
  if(isReady){
    return;
  }
  int potValue = potentiometer->getValue();

  if(potValue != sugarLevel){
    String msg = "Sugar ";
    msg += potValue; 
    char buf [50];
    msg.toCharArray(buf,50);
    sugarLevel = potValue;
    machineDisplay->displayMessage(buf);
    delay(1000);
    machineDisplay->displayMessage(productList[selectedIndex]);
    lastIteration = millis();
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
  
  machineDisplay->displayMessage(productList[selectedIndex]);
}
