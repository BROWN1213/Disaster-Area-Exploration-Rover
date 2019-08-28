
/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#ifndef RoverKALMAN_H
#define RoverKALMAN_H

#include <math.h> 

struct GyroKalman{
	/* These variables represent our state matrix x */
	float x_angle, x_bias;

	/* Our error covariance matrix */
	float P_00, P_01, P_10, P_11;
	
	/*
	* Q is a 2x2 matrix of the covariance. Because we
	* assume the gyro and accelerometer noise to be independent
	* of each other, the covariances on the / diagonal are 0.
	* Covariance Q, the process noise, from the assumption
	* x = F x + B u + w
	* with w having a normal distribution with covariance Q.
	* (covariance = E[ (X - E[X])*(X - E[X])' ]
	* We assume is linear with dt
	*/
	float Q_angle, Q_gyro;

	/*
	* Covariance R, our observation noise (from the accelerometer)
	* Also assumed to be linear with dt
	*/
	float R_angle;
};
/*
* R represents the measurement covariance noise. In this case,
* it is a 1x1 matrix that says that we expect 0.3 rad jitter
* from the accelerometer.
*/
static const float R_angle = 0.3; 		//.3 default

/*
* Q is a 2x2 matrix that represents the process covariance noise.
* In this case, it indicates how much we trust the acceleromter
* relative to the gyros
*/
static const float Q_angle = 0.01;	//0.01 (Kalman)
static const float Q_gyro = 0.04;	//0.04 (Kalman)

//These are the limits of the values I got out of the Nunchuk accelerometers (yours may vary).
const int lowX = -2150;
const int highX = 2210;
const int lowY = -2150;
const int highY = 2210;
const int lowZ = -2150;
const int highZ = 2550;


class Kalman{
    public:
    Kalman();
    void initGyroKalman(struct GyroKalman *kalman, const float Q_angle, const float Q_gyro, const float R_angle);
    void predict(struct GyroKalman *kalman, float dotAngle, float dt);
    float update(struct GyroKalman *kalman, float angle_m);
    void calculateKalman(int ax,int ay, int az, int x_gyro,int y_gyro,int z_gyro,float loopTime  );
    float angleInDegrees(int lo, int hi, int measured);
    private:
    GyroKalman angX;
    GyroKalman angY;
    GyroKalman angZ;
};

#endif