
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
    roverAhrs.printAhrsInfo();
}
