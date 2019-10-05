#include <CmdMessenger.h>  // CmdMessenger
#include<SimpleTimer.h>   //Task scheduler 
#include "src/rover_debug.h"
#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_ahrs.h"
#include "src/rover_Lx16A.h"
#include "src/rover_motor.h"
#include "src/rover_PM2_5.h"
#include "src/rover_MQ7.h"
#include "src/rover_sht.h"
/*  pin map */
// GPS : 8,9
// Lx16A : 6,7
// SD : 13,12,11,10
// MQ7 carbon Monoxide:  A0
// UltraSonic : 4,5     // BLE or UltraSonic
// PM2.5 :  A1, 2
// RF communication : 0,1 (Serial)  
//  SHT3x : I2C 0x45
// MPU6050 : I2C 0x68 

CmdMessenger cmdMessenger = CmdMessenger(Serial);




// the timer scheduler object
SimpleTimer schedule_timer;
int gps_timer_id,ahrs_timer_id,e_sensor_timer_id;
int ultra_sonic_timer_id;
void setup() {

  ROVER_LOG("Start setup ");
  //Serial.begin(38400);     //MPU6050 default
  Serial.begin(57600);  //57600 telemetry
  pinMode(13,OUTPUT);
  pirintLogo();  

  setupEnvironmentalSensor();
  setupRoverAhrs();
  setupRoverMotor();
  setupUltraSonic();  // BLE or UltraSonic
  setupRoverGps();   // GPS setup must be the last .. I don't know the reason


  //setup Command Messenger 
  attachCommandCallbacks();
  cmdMessenger.printLfCr();

  //setup scheduler  
  // GPS use polling in loop() 
  //gps_timer_id=schedule_timer.setInterval(1000, updateRoverGps); //1Hz
  ahrs_timer_id=schedule_timer.setInterval(500, updateRoverAhrs); //2Hz
  e_sensor_timer_id=schedule_timer.setInterval(2000, updateEnvironmentalSensor); //0.5Hz
  //ultra_sonic_timer_id=schedule_timer.setInterval(300, updateUltraSonic); //0.33Hz
  schedule_timer.setInterval(1000, heatbeat);
  
  
  
}

void loop() {
  
  schedule_timer.run();
  updateRoverGps();
  updateRoverMotor();
  cmdMessenger.feedinSerialData();
}

void pirintLogo(){

  Serial.println(F("************************************************"));
  Serial.println(F("*    Rhea Rover                                *"));
  Serial.println(F("*    SeungMin Shin, Haneulbit Kim, Chan Lee    *"));
  Serial.println(F("*                  powered by Asgardia 2019    *"));  
  Serial.println(F("*      https://github.com/cchamchi/rhea_rover  *"));
  Serial.println(F("************************************************"));

}
bool heatbeat_tog;
void heatbeat(){
  if(heatbeat_tog){
    digitalWrite(13,LOW);
    heatbeat_tog=false;
  }else{
    digitalWrite(13,HIGH);
    heatbeat_tog=true;
  }

}
