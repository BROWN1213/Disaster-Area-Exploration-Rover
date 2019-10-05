/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ....
*/
#ifndef rover_Radar_H
#define rover_Radar_H

class RoverRadar
{
    public:
      RoverRadar(float steer_angle);
      float rotate_angle(float steer_angle,float servo_angle,float prev_servo_angle);
      float constrain_angle(float steer_angle);
      void sendRaderInfo(float distance, int angle);
      float turn_angle(int angle);

    private:
      float _steer_angle;
      int i=20;
      bool c=true;
     
};
#endif