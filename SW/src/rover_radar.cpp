/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ....
*/
#include "rover_radar.h"
#include "Arduino.h"

RoverRadar::RoverRadar(float steer_angle){
  _steer_angle=steer_angle;
}  
float RoverRadar::constrain_angle(float steer_angle){
  constrain(steer_angle,40,140);
  map(steer_angle,-150,150,40,140);
  return steer_angle;
}
float RoverRadar::rotate_angle(float steer_angle,float servo_angle,float prev_servo_angle){
  constrain(steer_angle,20,160);
  float min_angle = steer_angle-40.;// "±30" can be changed
  float max_angle = steer_angle+40.;
  float steer_angle_servo = steer_angle;
  
  if(servo_angle<prev_servo_angle){ //prev_servo_angle is initialized by max_angle.
    if(servo_angle<steer_angle){
      return steer_angle;
    }else{
      return min_angle;
    }
  }else{
    if(servo_angle>steer_angle){
      return steer_angle;
    }else{
      return max_angle;
    }   
  }
}

void RoverRadar::sendRaderInfo(float distance, int angle){
  Serial.print("%,4,2,");
  Serial.print(distance);Serial.print(",");
  Serial.println(angle);
}
float RoverRadar::turn_angle(int angle){
    if(c){
    i=i+1;
    if(i>160)c=false;
  }else{
     i=i-1;
    if(i<20)c=true;
  }
  angle=i;
  return angle;
}

