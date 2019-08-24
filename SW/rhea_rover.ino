#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
#include "src/rover_Lx16A.h"
#include "src/rover_motor.h"
#include "src/rover_rader.h"
#include <Servo.h>

/* software serial pin map */
// GPS : 10,11
// BLE : 4,5
// Lx16A : 6,7

int joy_velocity=0,joy_raduis=0;
int v=0;
void setup() {

  
  //Serial.begin(38400);     //MPU6050 default
  Serial.begin(9600);
  //setupRoverGps();
  //setupRoverAhrs();
  Serial.println("Setup Start!");
  setupRoverMotor();
  Serial.println("Setup Complete!");
  //setupJoystick();
  
}

void loop() {
  //loopRoverAhrs();
  //loopRoverGps(); 
   //loopJoystick();
  // put your setup code here, to run once:
  
  //setupRoverGps();
  //loopUltraSonicTest();
  Serial.println("Loop Start");
  RoverMotorTest();
  Serial.println("Loop Passed");
  //Serial.println("dd");
  

}
