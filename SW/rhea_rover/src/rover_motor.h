/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/


#ifndef RoverMotor_H
#define RoverMotor_H
#include "rover_Lx16A.h"
#include <SoftwareSerial.h>

class RoverMotor :public RoverLx16A {
    public:
        RoverMotor(SoftwareSerial& stream):stream(stream),RoverLx16A(){
            // float currunt_radius=0;
            // memset( corner_degree, 0, sizeof(corner_degree));
            // memset( velocity_wheel, 0, sizeof(velocity_wheel));
            }
        void getCornerDegree(float *corner_degree);
        float approxTurningRadius(float *corner_degree);
        void calculateVelocity(int vel_joy,float radius,float *velocity_wheel);
        void calculateTargetDeg(int radius_joy,float *target_degree );        
        void cornerPosControl(float *target_degree);
        void wheelVelocityControl(float *velocity_wheel,float speed_ratio);
        void ledControl(int id, int onoff);
        void begin(int baudrate){
            beginLx16(stream);
            stream.begin(baudrate);
        }
 
    private:
        SoftwareSerial& stream;
        // float currunt_radius;
        // float corner_degree[4];
        // float target_degree[4];
        // float velocity_wheel[6];
        //const float d1=7.254,d2=10.5,d3=10.5,d4=10.073; // distance of wheel from centor
        const float d1=9.252,d2=9.843,d3=11.811,d4=10.631; // distance of wheel from centor [inches]
        //const float d1=23.5,d2=25,d3=30,d4=27; // distance of wheel from centor [centi]
};


#endif