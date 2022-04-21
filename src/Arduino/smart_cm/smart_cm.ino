#include "display.h"
#include "display_impl.h"
#include "sonar.h"
#include "sonar_impl.h"

Display* chooseDisplay;
Sonar* sonar;

void setup() {
  Serial.begin(9600);
  chooseDisplay = new DisplayImpl();
  sonar = new SonarImpl(7,8);
  chooseDisplay->displayMessage("Prova");
  float distance = sonar->getDistance();
  Serial.println(distance);
}

void loop() {
  
}
