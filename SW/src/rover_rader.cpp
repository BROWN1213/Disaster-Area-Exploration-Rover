#include "rover_rader.h"
#include "Arduino.h"
#include <Servo.h>

RoverRader::RoverRader(Servo servo,int servo_pin,float steer_angle){
    
    servo.attach(servo_pin);
    
    constrain(steer_angle,30,150);
    //map(steer_angle,20,150,-150,150);
}

