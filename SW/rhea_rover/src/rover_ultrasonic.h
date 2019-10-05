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
<<<<<<< HEAD:SW/rhea_rover/src/rover_ultrasonic.h
    //bool isDistanceInArea(unsigned long distance_cm , bool verbose);
=======
    bool isDistanceInArea(float distance,unsigned long distance_cm , bool verbose);
>>>>>>> 6306a64f6ed1b2e7d687ce7bb96068265a74f95b:SW/src/rover_ultrasonic.h
    
  
  private:
    int _trigPin;
    int _echoPin;
    
};


#endif