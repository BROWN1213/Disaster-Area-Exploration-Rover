/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/



#ifndef rover_sht_H
#define rover_sht_H

#include "Arduino.h"
#include "Wire.h"

class RoverSHT3x{
public:
	RoverSHT3x(uint8_t address=0x45);
	byte get();
  void begin();
	float cTemp=0;
	float fTemp=0;
	float humidity=0;

private:
	uint8_t _address;

};



#endif