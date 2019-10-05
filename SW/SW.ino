//initial for opening arduino file

#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
#include "src/rover_Lx16A.h"
#include "src/rover_motor.h"
#include "src/rover_radar.h"
#include <SimpleTimer.h>
#include <Servo.h>

#define SERVO_PIN_FRONT 3
#define SERVO_PIN_BACK 5

SimpleTimer timer; 

float distanceFront;
float distanceBack;
/* software serial pin map */
// GPS : 8,9
// BLE : 4,5
// Lx16A : 6,7
int id;
int joy_velocity=0, joy_raduis=0;
int v=0;
bool isFront;
int ii=4;
float steer_angle=90.;
///
int test = 30;
Servo radar_servoFront;
Servo radar_servoBack;
///

void setup() {
  
 
  //Serial.begin(38400);     //MPU6050 default
  Serial.begin(115200);
  setupRoverGps();
  setupRoverAhrs();
  Serial.println("Setup Start!");
  //setupRoverMotor();
  setupRadar();
  Serial.println("Setup Complete!");
  //setupJoystick();
  setupUltraSonic();
  int radar_timerId = timer.setInterval(700, timers);  
  steer_angle=60.;
  
}
void timers(){
  
  loopUltraSonic();
  loopRadar();
  loopRoverAhrs();
  //loopRoverGpsTEST();
  
}
void loop() {
  //loopRadarTest();
  //loopUltraSonicTest();
  /*test= test+10;
  if(test>160)test=30;
  radar_servoFront.write(test);
  radar_servoBack.write(test);
  Serial.print("test:");
  Serial.println(test);
  delay(500);*/

  timer.run();

}
