#ifndef rover_Rader_H
#define rover_Rader_H
#include <Servo.h>

class RoverRader{
    public:
      RoverRader(Servo servo,int servo_pin,float steer_angle);
      

    
    private:
      Servo _servo;
      
};














#endif