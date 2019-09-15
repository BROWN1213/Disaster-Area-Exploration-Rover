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
#define RERSTEER_LEFT_ID 22
#define FRTSTEER_RIGHT_ID 33
#define RERSTEER_RIGHT_ID 44

/****    ID descriptions **************/
//
//      ID1,ID11 |-d1-|       ID4,ID33
//                    |
//                    d3   
//                    |
//      ID2 |---d4----|*      ID5    
//                    | 
//                    d2
//                    |
//      ID3,ID22      |       ID6,ID44
//
/**************************************/


void RoverMotor::getCornerDegree(float *corner_degree){
    //get degree of each corner

    corner_degree[0]= ReadPosition(FRTSTEER_LEFT_ID);
    corner_degree[1]= ReadPosition(RERSTEER_LEFT_ID);
    corner_degree[3]= ReadPosition(FRTSTEER_RIGHT_ID);
    corner_degree[1]= ReadPosition(RERSTEER_RIGHT_ID);
    
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
    wh_angle[0]=ang1; wh_angle[1]=-ang2;
    wh_angle[2]=ang3; wh_angle[3]=-ang4;
  }else{
    wh_angle[0]=-ang1; wh_angle[1]=ang2;
    wh_angle[2]=-ang3; wh_angle[3]=ang4;
  }
  

}
void RoverMotor::cornerPosControl(float *target_degree){
  int wh_ang[4];
  for(int i=0;i<4;i++){
    wh_ang[i]=(int)(target_degree[i]*0.24+500);
  }
  //Move(11,wh_ang[0],1);
  //Move(33,wh_ang[1],1);
  //Move(44,wh_ang[2],1);
  Move(66,wh_ang[3],1);
  
}

void RoverMotor::wheelVelocityControl(float *velocity_wheel){
  // wheel ID : 1~6
  int wh_vel[6];
  for(int i=0;i<3;i++){
    wh_vel[i]=-(int)map(velocity_wheel[i],-100,100,-1000,1000);
    SetMode(i+1,1,wh_vel[i]);
  }
  for(int i=3;i<6;i++){
    wh_vel[i]=(int)map(velocity_wheel[i],-100,100,-1000,1000);
    SetMode(i+1,1,wh_vel[i]);
  }
}
