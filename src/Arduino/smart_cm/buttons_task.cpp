#include "buttons_task.h"

ButtonsTask::ButtonsTask(int pinUp, int pinDown, int pinMake){
  this->pin[0] = pinUp;
  this->pin[1] = pinDown;
  this->pin[2] = pinMake;
}
 
void ButtonsTask::init(int period){
  Task::init(period);
  buttonUp = new ButtonImpl(pin[0]); 
  buttonDown = new ButtonImpl(pin[1]);
  buttonMake = new ButtonImpl(pin[2]);
}
 
void ButtonsTask::tick(){
  checkState();
  switch(state){
    case UP:
      Serial.println("UP");
      break;
    case DOWN:
      Serial.println("DOWN");
      break;
    case MAKE:
      Serial.println("MAKE");
      break;
  }
}

void ButtonsTask::checkState(){
  if(state != UP and buttonUp->isPressed()){
    state = UP;
  }else if(state != DOWN and buttonDown->isPressed()){
    state = DOWN;
  }else if(state != MAKE and buttonMake->isPressed()){
    state = MAKE;
  }
}
