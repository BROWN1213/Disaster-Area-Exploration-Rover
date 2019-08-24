#include "rover_rader.h"
#include "Arduino.h"
#include <Servo.h>

RoverRader::RoverRader(Servo servo,int servo_pin){
    servo.attach(servo_pin);
}
void RoverRader::raderServo(Servo servo, float steer_angle){
    int i=0;
    constrain(steer_angle,-150,150);
    map(steer_angle,20,250,-150,150);
    if(i==0){
        servo.write(steer_angle+30);
        i=1;
    }else if(i==1){
        i=2
    }else{
        servo.write(steer_angle-30);
        i=0;
    }

}

