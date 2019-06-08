/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#include "rover_ultrasonic.h"

#include "Arduino.h"


RoverUltraSonic::RoverUltraSonic(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  _trigPin = trigPin;
  _echoPin = echoPin;
}

float RoverUltraSonic::measureDistance()
{
  digitalWrite(_trigPin, LOW);
  digitalWrite(_echoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);

  unsigned long duration = pulseIn(_echoPin, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  _distance = ((float)(340.0 * duration) / 10000.0) / 2.0;  
  return _distance;
}

bool RoverUltraSonic::isDistanceInArea(unsigned long distance_cm, bool verbose)
{
  
  if(_distance < distance_cm){

    if(verbose)Serial.println("too close");
    return true;
  }else{
    if(verbose)Serial.println("not dangerous");
    return false;
  }
  //turn around
  
  
}

