/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#ifndef roverMQ7_H
#define roverMQ7_H

/*
The coefficients are estimated from the sensitivity characteristics graph
of the MQ7 sensor for CO (Carbon Monoxide) gas by using Correlation function.
Explanation :
	The graph in the datasheet is represented with the function
	f(x) = a * (x ^ b).
	where
		f(x) = ppm
		x = Rs/R0
	The values were mapped with this function to determine the coefficients a and b.
*/

#define coefficient_A 19.32
#define coefficient_B -0.64

//Load resistance 10 Kohms on the sensor potentiometer
#define R_Load 10.0



class RoverMQ7 {
 	private:
		uint8_t analogPin;
		float v_in;
		float voltageConversion(int);
		
	public:
		RoverMQ7(uint8_t, float);
		void getPPM();
		float getSensorResistance();
		float getRatio();
		float co_ppm;
};

#endif