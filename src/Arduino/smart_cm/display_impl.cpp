#include "display_impl.h"
#include "Arduino.h"

DisplayImpl::DisplayImpl(){
  this->lcd.init();
  this->lcd.backlight();
  this->lcd.setCursor(0,0);
} 

void DisplayImpl::displayMessage(char* msg){ 
  this->lcd.clear();
  this->lcd.print(msg);     
}
