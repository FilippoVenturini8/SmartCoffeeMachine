#include "sonar.h"
#include "sonar_impl.h"
#include "button.h"
#include "button_impl.h"
#include "scheduler.h"
#include "task.h"
#include "display_task.h"

Sonar* sonar;
Button* bUp;
Button* bDown;
Scheduler sched;

void setup() {
  Serial.begin(9600);
  /*chooseDisplay = new DisplayImpl();
  sonar = new SonarImpl(7,8);
  float distance = sonar->getDistance();
  Serial.println(distance);*/
  sched.init(50);
   
  Task* t0 = new DisplayTask();
  t0->init(3000);
  sched.addTask(t0);
}

void loop() {
  sched.schedule();
}
