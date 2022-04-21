#include "display.h"
#include "display_impl.h"

Display* chooseDisplay;

void setup() {
  chooseDisplay = new DisplayImpl();
  chooseDisplay->displayMessage("Prova");
}

void loop() {

}
