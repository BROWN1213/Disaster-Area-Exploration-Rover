
/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/
// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//      2013-05-08 - added multiple output formats
//                 - added seamless Fastwire support
//      2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#ifndef RoverAHRS_h
#define RoverAHRS_h

#include "Arduino.h"

//========================== MPU6050
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#define OUTPUT_READABLE_ACCELGYRO                                                         
//========================== MPU6050

// Convert gyro values to degrees/sec
#define GYRO_RANGE 250.0
#define DEGSEC_RATIO GYRO_RANGE/32767.
#define GYRO2DEG(gyro) (float)gyro*DEGSEC_RATIO

// Convert accel values to degrees/sec
#define ACC_RANGE 2
#define ACCSEC_RATIO ACC_RANGE/32767.
#define NORM_ACC(acc) acc*ACCSEC_RATIO

#define NO_FILTER 0
#define COMP_FILTER 1
#define KALMAN_FILTER 2

struct AhrsInfo {
  int16_t roll;
  int16_t pitch;
  int16_t yaw;
  int16_t ax;
  int16_t ay;
  int16_t az;
};
struct GyroInfo {
  int16_t roll;
  int16_t pitch;
  int16_t yaw;
};
struct AcceleroInfo {
  int16_t ax;
  int16_t ay;
  int16_t az;
};


class RoverAhrs : public MPU6050 {
  public:
    RoverAhrs():MPU6050(),roll(0),pitch(0),yaw(0),ax(0),ay(0),az(0)
    {}
 
    bool begin();
    void update(int filters);
    void caculrateMotionAcceleration();
    bool isAhrsDataNew();
    void set_last_read_angle_data(unsigned long time, float x, float y, float z, float x_gyro, float y_gyro, float z_gyro);
    void ComplementaryFilter(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz,unsigned long t_now);
    void calibrate();
    float roll,pitch,yaw;    //angle(degree)
    int16_t ax,ay,az;
    int16_t gx,gy,gz;
    float motion_acceleration;
    float norm_ax,norm_ay,norm_az; //normalized accel

  private:    
    bool _ahrs_data_flag;
    int _print_count;
    float base_ax,base_ay,base_az;
    float base_gx,base_gy,base_gz;
    unsigned long last_read_time;
    float         last_x_angle;  // These are the filtered angles
    float         last_y_angle;
    float         last_z_angle;  
    float         last_gyro_x_angle;  // Store the gyro angles to compare drift
    float         last_gyro_y_angle;
    float         last_gyro_z_angle;

};


#endif
