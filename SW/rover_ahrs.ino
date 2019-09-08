
#include "src/rover_ahrs.h"

RoverAhrs roverAhrs;

void setupRoverAhrs() {
    roverAhrs.begin();
    // initialize device
    Serial.println("Initializing I2C devices...");
    roverAhrs.accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(roverAhrs.accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loopRoverAhrs() {
    roverAhrs.update();
    Serial.println("%,1,6,1,2,3,4,5,6");
    //roverAhrs.printAhrsInfo();
    //Serial.print("ax=");
    //Serial.println(roverAhrs.ax);
    
}
