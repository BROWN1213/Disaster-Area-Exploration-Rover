/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/
#include <arduino.h>
#include "rover_motor.h"


#define R_MIN 20.0 //inch
#define R_MAX 250.0

#define V_MIN -100
#define V_MAX 100

#define FRTWHEEL_LEFT_ID 1
#define MIDWHEEL_LEFT_ID 2
#define RERWHEEL_LEFT_ID 3
#define FRTWHEEL_RIGHT_ID 4
#define MIDWHEEL_RIGHT_ID 5
#define RERWHEEL_RIGHT_ID 6

#define FRTSTEER_LEFT_ID 11
#define RERSTEER_LEFT_ID 33
#define FRTSTEER_RIGHT_ID 44
#define RERSTEER_RIGHT_ID 66

#define FRTSTEER_LEFT_OFFSET 10
#define RERSTEER_LEFT_OFFSET 10
#define FRTSTEER_RIGHT_OFFSET 0 //-40
#define RERSTEER_RIGHT_OFFSET -10//60

#define SERVO_NEUTRAL 500  // servo 0~1000 is 0~240deg.   500 is 120 deg  

#define S_GAP 5 //5ms
#define MSPERDEG   10.0//ms per deg

#define DEG2SERVO(deg) deg/0.24
#define SERV2DEG(servo) servo*0.24
#define DEG2TIME 1000

/****    ID descriptions **************/
//
//      ID1,ID11 |-d1-|       ID4,ID44
//                    |
//                    d3   
//                    |
//      ID2 |---d4----|*      ID5    
//                    | 
//                    d2
//                    |
//      ID3,ID33      |       ID6,ID66
//
/**************************************/


void RoverMotor::getCornerDegree(float *corner_degree){
    //get degree of each corner
 
    int pos_value;
    pos_value=ReadPosition(FRTSTEER_LEFT_ID)-(SERVO_NEUTRAL-FRTSTEER_LEFT_OFFSET);
    corner_degree[0]=SERV2DEG(pos_value);
    pos_value=ReadPosition(RERSTEER_LEFT_ID)-(SERVO_NEUTRAL-RERSTEER_LEFT_OFFSET);
    corner_degree[1]=SERV2DEG(pos_value);
    pos_value=ReadPosition(FRTSTEER_RIGHT_ID)-(SERVO_NEUTRAL-FRTSTEER_RIGHT_OFFSET);
    corner_degree[2]=SERV2DEG(pos_value);
    pos_value=ReadPosition(RERSTEER_RIGHT_ID)-(SERVO_NEUTRAL-RERSTEER_RIGHT_OFFSET);
    corner_degree[3]=SERV2DEG(pos_value);
    
}
float RoverMotor::approxTurningRadius(float *corner_degree){
    //calculate a approxmate radius of rover using coner's degree
    //Takes the list of current corner angles and approximates the current turning radius [inches]
    //param list [int] enc: List of encoder ticks for each corner motor  
		// if enc[0] == None:
		// 	return 250
		// try:
		// 	if enc[0] > 0:
		// 		r1 = (self.d1/math.tan(math.radians(abs(enc[0])))) + self.d3
		// 		r2 = (self.d2/math.tan(math.radians(abs(enc[1])))) + self.d3
		// 		r3 = (self.d2/math.tan(math.radians(abs(enc[2])))) - self.d3
		// 		r4 = (self.d1/math.tan(math.radians(abs(enc[3])))) - self.d3
		// 	else:
		// 		r1 = -(self.d1/math.tan(math.radians(abs(enc[0])))) - self.d3
		// 		r2 = -(self.d2/math.tan(math.radians(abs(enc[1])))) - self.d3
		// 		r3 = -(self.d2/math.tan(math.radians(abs(enc[2])))) + self.d3
		// 		r4 = -(self.d1/math.tan(math.radians(abs(enc[3])))) + self.d3
		// 	radius = (r1 + r2 + r3 + r4)/4
		// 	return radius
		// except:
		// 	return 250
    float r1,r2,r3,r4,radius;
    r1 = d3/tan(radians(abs(corner_degree[0]))) - d1;
    r2 = d2/tan(radians(abs(corner_degree[1]))) - d1;
    r3 = d3/tan(radians(abs(corner_degree[2]))) + d1;
    r4 = d2/tan(radians(abs(corner_degree[1]))) + d1;
    radius = (r1 + r2 + r3 + r4)/4;
    //range limit
    if(radius<R_MIN)radius=R_MIN;
    if(radius>R_MAX)radius=R_MAX;

    if(corner_degree[0]>0){  //turn right
      radius = radius;
    }else{ //turn left
      radius = -radius;
    }
    return radius;
}
void RoverMotor::calculateVelocity(int vel_joy,float radius,float *velocity_wheel){

		// Returns a list of speeds for each individual drive motor based on current turning radius
		// :param int vel_joy: Drive speed command range from -100 to 100
		// :param float radius: curruent radius  range from -R_MAX to R_MAX
    // :velocity_wheel : each velocity range from -100 to 100 



  //Drive speed command velco_rover range from V_MIN to V_MAX

	if ( (radius == 0) || (radius>= 250) || ( radius <= -250)){
    	for(int i=0;i<6;i++) velocity_wheel[i]= vel_joy; //all wheels same speed
  	}else{
      // TO-DO : calculate velocity of each wheel
      
      float x = (float)vel_joy/((abs(radius) + d4));                 
      float a = pow(d2,2);
      float b = pow(d3,2);
      float c = pow((abs(radius)+d1),2);
      float d = pow((abs(radius)-d1),2);
      float e = abs(radius)-d4;

      float v1 = x*sqrt(b + c);
      float v2 = (float)vel_joy;       // Fastest wheel
      float v3 = x*sqrt(a + c);
      float v4 = x*sqrt(b + d);
      float v5 = x*e;           // Slowest wheel      
      float v6 = x*sqrt(a + d);


      
      if (radius > 0){
        velocity_wheel[0]=v1; velocity_wheel[1]=v2; velocity_wheel[2]=v3;
        velocity_wheel[3]=v4; velocity_wheel[4]=v5; velocity_wheel[5]=v6;
      }
      else if (radius < 0){
        velocity_wheel[0]=v4; velocity_wheel[1]=v5; velocity_wheel[2]=v6;
        velocity_wheel[3]=v1; velocity_wheel[4]=v2; velocity_wheel[5]=v3;
      }
      
  }
}
void RoverMotor::calculateTargetDeg(int radius_joy,float *wh_angle ){

		// '''
		// Takes a turning radius and calculates what angle [degrees] each corner should be at
		// :param int radius: Radius drive command, ranges from -100 (turning left) to 100 (turning right)
		// '''


 	//Radius drive command,r_rover  ranges from -100 (turning left) to 100 (turning right)

  	//Scaled from 250(R_MAX) to 20(R_MIN) inches.

  	float r;

  if(radius_joy == 0) r=R_MAX;
  else if (-100 <= radius_joy <= 100) r = map(abs(radius_joy),0,100,R_MAX,R_MIN);
  else r=R_MAX;

  if (r == R_MAX){
    memset (wh_angle, 0, sizeof(wh_angle));
    return;
  }
  // TO-DO : calculate angle of each wheel 
  //   ang1     ang3
  //   ang2     ang4

  int ang1 = int(degrees(atan(d3/(abs(r)+d1))));
  int ang2 = int(degrees(atan(d2/(abs(r)+d1))));
  int ang3 = int(degrees(atan(d3/(abs(r)-d1))));
  int ang4 = int(degrees(atan(d2/(abs(r)-d1))));

  if (radius_joy > 0){
    wh_angle[0]=ang1; wh_angle[2]=ang3;
    wh_angle[1]=-ang2; wh_angle[3]=-ang4;
     
  }else{
    wh_angle[0]=-ang3; wh_angle[2]=-ang1;
    wh_angle[1]=ang4; wh_angle[3]=ang2;
     
  }
  
  
  Serial.print(wh_angle[0]);Serial.print(",");
  Serial.print(wh_angle[1]);Serial.print(",");
  Serial.print(wh_angle[2]);Serial.print(",");
  Serial.println(wh_angle[3]);

}


void RoverMotor::cornerPosControl(float *target_degree){
 // Move position sequentially to avoid a current peak
  Move(FRTSTEER_LEFT_ID,SERVO_NEUTRAL-FRTSTEER_LEFT_OFFSET+DEG2SERVO(target_degree[0]),DEG2TIME);
  Move(RERSTEER_LEFT_ID,SERVO_NEUTRAL-RERSTEER_LEFT_OFFSET+DEG2SERVO(target_degree[1]),DEG2TIME);
  Move(FRTSTEER_RIGHT_ID,SERVO_NEUTRAL-FRTSTEER_RIGHT_OFFSET+DEG2SERVO(target_degree[2]),DEG2TIME);
  Move(RERSTEER_RIGHT_ID,SERVO_NEUTRAL-RERSTEER_RIGHT_OFFSET+DEG2SERVO(target_degree[3]),DEG2TIME);
 
}

void RoverMotor::wheelVelocityControl(float *velocity_wheel,float speed_ratio){

    // wheel ID : 1~6
    int wh_vel[6];
    for(int i=0;i<3;i++){
      wh_vel[i]=(int)map(velocity_wheel[i],-100,100,-1000*speed_ratio,1000*speed_ratio);
      SetMode(i+1,1,wh_vel[i]);
      delay(S_GAP); // to avoid a current peak
    }
    for(int i=3;i<6;i++){
      wh_vel[i]=-(int)map(velocity_wheel[i],-100,100,-1000*speed_ratio,1000*speed_ratio);
      SetMode(i+1,1,wh_vel[i]);
      delay(S_GAP); // to avoid a current peak
    }


}

