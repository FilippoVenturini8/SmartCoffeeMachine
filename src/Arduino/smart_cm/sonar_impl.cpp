#include "sonar_impl.h"
#include "Arduino.h"

SonarImpl::SonarImpl(int trigPin, int echoPin){
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  
  pinMode(this->trigPin, OUTPUT);
  pinMode(this->echoPin, INPUT);  
} 

float SonarImpl::getDistance(){ 
  
    digitalWrite(this->trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(this->trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigPin,LOW);
    
    float tUS = pulseIn(this->echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;
}
