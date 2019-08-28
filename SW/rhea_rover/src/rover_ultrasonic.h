/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ....
*/

#ifndef RoverUltraSonic_h
#define RoverUltraSonic_h

#include "Arduino.h"

class RoverUltraSonic
{
  public:
    RoverUltraSonic(int trigPin, int echoPin);
    void begin();
    float measureDistance();
    //bool isDistanceInArea(unsigned long distance_cm , bool verbose);
    
  
  private:
    int _trigPin;
    int _echoPin;
    
};


#endif