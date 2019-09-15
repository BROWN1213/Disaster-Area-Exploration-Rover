/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#include "rover_ahrs.h"

void RoverAhrs::ahrsBegin()
{
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
}

void RoverAhrs::begin()
{
  ahrsBegin();
  _ahrs_data_flag=false;
}
void RoverAhrs::update()
{
  if(isAhrsDataReady()){
    readAhrsData();
    caculrateMotionAcceleration();
    _ahrs_data_flag=true;
  }
}

void RoverAhrs::testupdate()
{
  if(isAhrsDataReady()){
    testreadAhrsData();
    caculrateMotionAcceleration();
    _ahrs_data_flag=true;
  }
}
GyroInfo RoverAhrs::getGyro()
{
  GyroInfo gyro;
  gyro.roll=roll;
  gyro.pitch=pitch;
  gyro.yaw=yaw;
  return gyro;
}
AcceleroInfo RoverAhrs::getAccelero()
{
  AcceleroInfo accelero;
  accelero.ax=ax;
  accelero.ay=ay;
  accelero.az=az;
  return accelero;
}
float RoverAhrs::getMotionAcceleration()
{
  return _motion_acceleration;
}

void RoverAhrs::caculrateMotionAcceleration()
{
  float x,y,z;
  x=ax;
  y=ay;
  z=az;

  _motion_acceleration=pow( (x*x+y*y+z*z),0.5);
}

bool RoverAhrs::isAhrsDataNew()
{
  if(_ahrs_data_flag){
    _ahrs_data_flag=false;
    return(true);
  }else{
    return(false);
  }

}

void RoverAhrs::rx_empty(){
  rx_empty();
}

void RoverAhrs::printAhrsInfo()
{
  if(_print_count>=10){
    
    Serial.print(F("%,1,7,"));
    Serial.print(roll,1);Serial.print(F(","));
    Serial.print(pitch,1);Serial.print(F(","));
    Serial.print(yaw,1);Serial.print(F(","));
    Serial.print(ax,1);Serial.print(F(","));
    Serial.print(ay,1);Serial.print(F(","));
    Serial.print(az,1);
    Serial.print(F(","));
    Serial.println(_motion_acceleration,3);
    //Serial.println(F("++++++++++++++++++++++++++++++++++"));
    _print_count=0;
 }
 _print_count++;

}

void RoverAhrs::readAhrsData()
{
  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &roll, &pitch, &yaw);

}

void RoverAhrs::testreadAhrsData()
{
  roll=10;
  pitch=20;
  yaw=30;
  ax=40;
  ay=50;
  az=60;

}

bool RoverAhrs::isAhrsDataReady()
{
  bool ready;
  ready;

  
  ready=true;
  

  return ready;
}
