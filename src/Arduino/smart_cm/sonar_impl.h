#ifndef __SONAR_IMPL__
#define __SONAR_IMPL__

#include "sonar.h"

class SonarImpl: public Sonar {

public:
  SonarImpl(int trigPin, int echoPin);

  float getDistance();
    
private:
  int trigPin;
  int echoPin;
  const float vs = 331.45 + 0.62*20;
};

#endif
