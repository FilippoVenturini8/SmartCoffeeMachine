#include "shared_variables.h"
#include "scheduler.h"
#include "task.h"
#include "selection_task.h"
#include "making_task.h"
#include "delivery_task.h"
#include "user_detection_task.h"
#include "check_task.h"
#include "send_info_task.h"
#include "display.h"
#include "display_impl.h"
#include "servo_motor.h"
#include "servo_motor_impl.h"

bool selected;
bool productDone;
bool delivered;
bool canCheck;
bool assistanceRequired;
bool isWorking;

char* productList[3];
int quantityList[3];

int selectedIndex;
int nSelfTest;

Display* machineDisplay;
ServoMotor* servoMotor;

Scheduler sched;

void setup() {
  bootMachine();

  sched.init(50);

  Task* t1 = new SelectionTask(7,8,9, A0);
  t1->init(100);
  sched.addTask(t1);

  Task* t2 = new MakingTask();
  t2->init(150);
  sched.addTask(t2);

  Task* t3 = new DeliveryTask(4,2);
  t3->init(50);
  sched.addTask(t3);

  Task* t4 = new UserDetectionTask(12);
  t4->init(50);
  sched.addTask(t4);

  Task* t5 = new CheckTask(A0);
  t5->init(50);
  sched.addTask(t5);

  Task* t6 = new SendInfoTask();
  t6->init(100);
  sched.addTask(t6);

  Serial.begin(9600);
}

void bootMachine(){
  machineDisplay = new DisplayImpl();
  machineDisplay->displayMessage((char*)"Welcome User!");
  selected = false;
  productDone = false;
  delivered = false;
  isWorking = false;
  canCheck = true;
  assistanceRequired = false;
  selectedIndex = 0;
  nSelfTest = 0;
  productList[0] = (char*)"TEA";
  productList[1] = (char*)"COFFE";
  productList[2] = (char*)"CHOCOLATE";
  quantityList[0] = 2;
  quantityList[1] = 1;
  quantityList[2] = 0;
  servoMotor = new ServoMotorImpl(3);
  delay(2000);
  machineDisplay->displayMessage((char*)"Ready");
}

void loop() {
  sched.schedule();
}
