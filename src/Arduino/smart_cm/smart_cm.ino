#include "sonar.h"
#include "sonar_impl.h"
#include "scheduler.h"
#include "task.h"
#include "display_task.h"
#include "selection_task.h"
#include "servo_motor_impl.h"

Sonar* sonar;
Button* bUp;
Button* bDown;
Scheduler sched;
ServoMotor* servo;
int pos;
int delta;

void setup() {
  Serial.begin(9600);
  /*chooseDisplay = new DisplayImpl();
  sonar = new SonarImpl(7,8);
  float distance = sonar->getDistance();
  Serial.println(distance);*/
  /*sched.init(50);
   
  Task* t0 = new DisplayTask();
  t0->init(50);
  sched.addTask(t0);

  Task* t1 = new SelectionTask(7,8,9, A0);
  t1->init(100);
  sched.addTask(t1);*/

  servo = new ServoMotorImpl(3);
  
  pos = 0;
  delta = 1;
}

void loop() {
  //sched.schedule();
  servo->on();
  for (int i = 0; i < 180; i++) {
    //Serial.println(pos);
    servo->setPosition(pos);         
    delay(5);            
    pos += delta;
  }
  servo->off();
  pos -= delta;
  delta = -delta;
  delay(1000);
}
