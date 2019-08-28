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
#include "rover_ahrs.h"
#include "rover_debug.h"


bool RoverAhrs::begin()
{
  Wire.begin();
  //initiate MPU6050
  initialize();
  // verify connection
  //Serial.println(F("Testing device connections..."));
  //Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
  delay(200);
  calibrate();
  _ahrs_data_flag=false;
  return testConnection();
}

// fiters : 0(No filter), 1(Complementary Filter), 2(kalman)
void RoverAhrs::update(int fiters)
{
  int16_t raw_ax,raw_ay,raw_az,raw_gx,raw_gy,raw_gz;  
  unsigned long t_now;
  
  if(fiters==0){
    // read raw accel/gyro measurements from device
    getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    norm_ax=NORM_ACC(ax);norm_ay=NORM_ACC(ay);norm_az=NORM_ACC(az);
    pitch=GYRO2DEG(gx);roll=GYRO2DEG(gy);yaw=GYRO2DEG(gz);

  }else if(fiters==1){
    
    getMotion6(&raw_ax, &raw_ay, &raw_az, &raw_gx, &raw_gy, &raw_gz);
    t_now=millis();
    norm_ax=NORM_ACC(ax);norm_ay=NORM_ACC(ay);norm_az=NORM_ACC(az);
    ComplementaryFilter(raw_ax,raw_ay,raw_az,raw_gx,raw_gy,raw_gz,t_now);
    

  }else{
    //To DO : kalman filter
    getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    norm_ax=NORM_ACC(ax);norm_ay=NORM_ACC(ay);norm_az=NORM_ACC(az);
    pitch=GYRO2DEG(gx);roll=GYRO2DEG(gy);yaw=GYRO2DEG(gz);    
  }

  caculrateMotionAcceleration();


}
//http://www.geekmomprojects.com/gyroscopes-and-accelerometers-on-a-chip/

void RoverAhrs::ComplementaryFilter(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz,unsigned long t_now){
// Convert gyro values to degrees/sec
  float gyro_x = GYRO2DEG((gx-base_gx));
  float gyro_y = GYRO2DEG((gy-base_gy));
  float gyro_z = GYRO2DEG((gz-base_gz));
  // float gyro_x = GYRO2DEG(gx);
  // float gyro_y = GYRO2DEG(gy);
  // float gyro_z = GYRO2DEG(gz);
  // Get raw acceleration values  ... try normalized value
  float accel_x = NORM_ACC(ax);
  float accel_y = NORM_ACC(ay);
  float accel_z = NORM_ACC(az);

  // Get angle values from accelerometer
  float RADIANS_TO_DEGREES = 180/3.14159;
//  float accel_vector_length = sqrt(pow(accel_x,2) + pow(accel_y,2) + pow(accel_z,2));
  float accel_angle_y = atan(-1*accel_x/sqrt(pow(accel_y,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
  float accel_angle_x = atan(accel_y/sqrt(pow(accel_x,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
  float accel_angle_z = 0;

  // Compute the (filtered) gyro angles
  float dt =(t_now - last_read_time)/1000.0;
  float gyro_angle_x = gyro_x*dt + last_x_angle;
  float gyro_angle_y = gyro_y*dt + last_y_angle;
  float gyro_angle_z = gyro_z*dt + last_z_angle;

   // Compute the drifting gyro angles
  float unfiltered_gyro_angle_x = gyro_x*dt + last_gyro_x_angle;
  float unfiltered_gyro_angle_y = gyro_y*dt + last_gyro_y_angle;
  float unfiltered_gyro_angle_z = gyro_z*dt + last_gyro_z_angle; 

  // Apply the complementary filter to figure out the change in angle - choice of alpha is
  // estimated now.  Alpha depends on the sampling rate...
  float alpha = 1/(1+dt);
  pitch = alpha*gyro_angle_x + (1.0 - alpha)*accel_angle_x;
  roll  = alpha*gyro_angle_y + (1.0 - alpha)*accel_angle_y;
  yaw = gyro_angle_z;  //Accelerometer doesn't give z-angle

  // Update the saved data with the latest values
  set_last_read_angle_data(t_now, pitch, roll, yaw, unfiltered_gyro_angle_x, unfiltered_gyro_angle_y, unfiltered_gyro_angle_z);

}
void RoverAhrs::set_last_read_angle_data(unsigned long time, float x, float y, float z, float x_gyro, float y_gyro, float z_gyro) {
  last_read_time = time;
  last_x_angle = x;
  last_y_angle = y;
  last_z_angle = z;
  last_gyro_x_angle = x_gyro;
  last_gyro_y_angle = y_gyro;
  last_gyro_z_angle = z_gyro;
}
void RoverAhrs::caculrateMotionAcceleration()
{
  float x,y,z;
  x=(float)ax/32767.;
  y=(float)ay/32767.;
  z=(float)az/32767.;

  motion_acceleration=pow( (x*x+y*y+z*z),0.5);
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

// The sensor should be motionless on a horizontal surface 
//  while calibration is happening
void RoverAhrs::calibrate() {
  int num_readings = 10;
  float x_accel = 0,y_accel = 0,z_accel = 0;
  float x_gyro = 0,y_gyro = 0,z_gyro = 0;
  int16_t raw_ax,raw_ay,raw_az,raw_gx,raw_gy,raw_gz;
  //Serial.println("Starting Calibration");

  // Discard the first set of values read from the IMU
  getMotion6(&raw_ax, &raw_ay, &raw_az, &raw_gx, &raw_gy, &raw_gz);
  
  ROVER_LOG("IMU Calibration !! Don't MOVE")
  // Read and average the raw values from the IMU
  for (int i = 0; i < num_readings; i++) {
    getMotion6(&raw_ax, &raw_ay, &raw_az, &raw_gx, &raw_gy, &raw_gz);
    x_accel += raw_ax; y_accel += raw_ay; z_accel += raw_az;
    x_gyro += raw_gx; y_gyro += raw_gy; z_gyro += raw_gz;
    delay(100);
  }
  x_accel /= num_readings; y_accel /= num_readings; z_accel /= num_readings; 
  x_gyro /= num_readings; y_gyro /= num_readings; z_gyro /= num_readings;
  
  // Store the raw calibration values 
  base_ax = x_accel; base_ay = y_accel; base_az = z_accel;
  base_gx = x_gyro; base_gy = y_gyro; base_gz = z_gyro;

  // Serial.println(base_gx);
  // Serial.println(base_gy);
  // Serial.println(base_gz);
  ROVER_LOG("end Calibration")
  // supply your own gyro offsets here, scaled for min sensitivity
  //setXGyroOffset(220);
  //setYGyroOffset(76);
  //setZGyroOffset(-85);
  //setZAccelOffset(1788); // 1688 factory default for my test chip 
  
}
