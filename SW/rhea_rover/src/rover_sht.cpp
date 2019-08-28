/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

/*  https://github.com/wemos/WEMOS_SHT3x_Arduino_Library */

#include "rover_sht.h"
#include "rover_debug.h"
RoverSHT3x::RoverSHT3x(uint8_t address)
{

	_address=address;
}

void RoverSHT3x::begin(){
  Wire.begin();
}

byte RoverSHT3x::get()
{
	unsigned int data[6];

	// Start I2C Transmission
	Wire.beginTransmission(_address);
	// Send measurement command
	Wire.write(0x2C);
	Wire.write(0x06);
	// Stop I2C transmission
	if (Wire.endTransmission()!=0){
    ROVER_LOG("SHT30 fail to endTransmission");
		return 1;  
  	}


	delay(50);

	// Request 6 bytes of data
	Wire.requestFrom(_address, (uint8_t)6);

	// Read 6 bytes of data
	// cTemp msb, cTemp lsb, cTemp crc, humidity msb, humidity lsb, humidity crc
	for (int i=0;i<6;i++) {
		data[i]=Wire.read();
	};
	
	delay(50);
	
	if (Wire.available()!=0){
    ROVER_LOG("SHT30 fail to read");
		return 2;
  }

	// Convert the data
	cTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
	fTemp = (cTemp * 1.8) + 32;
	humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);

	return 0;
}
