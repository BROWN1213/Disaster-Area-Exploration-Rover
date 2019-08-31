#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
#include "src/rover_Lx16A.h"
#include "src/rover_motor.h"
#include "src/rover_radar.h"
#include <SimpleTimer.h>
#include <Servo.h>

#define SERVO_PIN 3

SimpleTimer timer; 
Servo radar_servo;
/* software serial pin map */
// GPS : 10,11
// BLE : 4,5
// Lx16A : 6,7
int id;
int joy_velocity=0,joy_raduis=0;
int v=0;
float distance;
float steer_angle=90.;

void setup() {

 
  //Serial.begin(38400);     //MPU6050 default
  Serial.begin(9600);
  //setupRoverGps();
  //setupRoverAhrs();
  Serial.println("Setup Start!");
  //setupRoverMotor();
  setupRadar();
  Serial.println("Setup Complete!");
  //setupJoystick();
  
  int timerId = timer.setInterval(700, timers); 
  steer_angle=60.;
}
void timers(){
  steer_angle= steer_angle+10;
  loopUltraSonic();
  loopRadar();
  if(steer_angle>135)steer_angle=60.;
}
void loop() {
  //loopRoverAhrs();
  //loopRoverGps(); 
   //loopJoystick();
  // put your setup code here, to run once:
  //setupRoverGps();
  //for(int angle = 60;angle<151;angle = angle+10){
    //steer_angle = angle;
    
    timer.run();
 // }
  //Serial.println("Loop Start");
  //RoverMotorTest();
 
  //Serial.println("Loop Passed");
  //Serial.println("dd");
  

}
