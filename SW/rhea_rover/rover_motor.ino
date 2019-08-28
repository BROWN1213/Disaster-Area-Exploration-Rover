SoftwareSerial _Mport(6,7);
RoverMotor myRover(_Mport);

int prev_velocity=0,prev_radius=0;
int velocity=0,radius=0;
void setupRoverMotor(){
  float corner_degree[4];
  myRover.begin(115200);
  _Mport.begin(115200);
  prev_velocity=0;
  prev_radius=0;
  velocity=0;
  radius=0;
 
 float wh_angle[4];


  for(int k=0;k<4;k++)wh_angle[k]=0;
  myRover.cornerPosControl(wh_angle);
}

void updateRoverMotor(){

  if(prev_velocity!=velocity || prev_radius!=radius){
      sendcommand(velocity,radius);
      prev_velocity=velocity;
      prev_radius=radius;
  }
}


void RoverMotorTest(){
  float velocity_wheel[6];
  
  //forward
  for(int i=0;i<100;i=i+25){
    for(int k=0;k<6;k++)velocity_wheel[k]=i;
    myRover.wheelVelocityControl(velocity_wheel,0.6);
    delay(3000);
  }
  //stop
    for(int k=0;k<6;k++)velocity_wheel[k]=0;
    myRover.wheelVelocityControl(velocity_wheel,0.6);  
    delay(1000);
  //backward
  for(int i=0;i>-100;i=i-25){
    for(int k=0;k<6;k++)velocity_wheel[k]=i;
    myRover.wheelVelocityControl(velocity_wheel,0.6);
    delay(3000);
  }  
  //stop
    for(int k=0;k<6;k++)velocity_wheel[k]=0;
    myRover.wheelVelocityControl(velocity_wheel,0.6);   
    delay(1000);
}

void RoverPositionTest(){
  float cornerDeg[4],wh_angle[4];

  //set -45 deg
  for(int k=0;k<4;k++)wh_angle[k]=-45;
  myRover.cornerPosControl(wh_angle);
  delay(500);

  //turn right
  for(int i=-45;i<45;i=i+15){
    for(int k=0;k<4;k++)wh_angle[k]=i;
    myRover.cornerPosControl(wh_angle);
    delay(1000);
    //get corner degree and print
    myRover.getCornerDegree(cornerDeg);
    Serial.print(F("cornerDeg : ")); 
    Serial.print(cornerDeg[0]);Serial.print(F(","));
    Serial.print(cornerDeg[1]);Serial.print(F(","));
    Serial.print(cornerDeg[2]);Serial.print(F(","));
    Serial.println(cornerDeg[3]);
  }
   //turn left
  for(int i=45;i>-45;i=i-15){
    for(int k=0;k<4;k++)wh_angle[k]=i;
    myRover.cornerPosControl(wh_angle);
    delay(1000);
    //get corner degree and print
    myRover.getCornerDegree(cornerDeg);
    Serial.print(F("cornerDeg : ")); 
    Serial.print(cornerDeg[0]);Serial.print(F(","));
    Serial.print(cornerDeg[1]);Serial.print(F(","));
    Serial.print(cornerDeg[2]);Serial.print(F(","));
    Serial.println(cornerDeg[3]);    
  }
}

void sendcommand(int v,int r){

  float cornerDeg[4],wh_angle[4],velocity_wheel[6],approxRadius;
  // myRover.getCornerDegree(cornerDeg);
  // approxRadius=myRover.approxTurningRadius(cornerDeg);
  // myRover.calculateVelocity(v,approxRadius,velocity_wheel);
  // myRover.wheelVelocityControl(velocity_wheel,0.3);
  // myRover.calculateTargetDeg(r,wh_angle);
  // myRover.cornerPosControl(wh_angle);


  //myRover.getCornerDegree(cornerDeg);
  //approxRadius=myRover.approxTurningRadius(cornerDeg);
  myRover.calculateTargetDeg(r,wh_angle);
  myRover.cornerPosControl(wh_angle);
  myRover.calculateVelocity(v,r,velocity_wheel);
  myRover.wheelVelocityControl(velocity_wheel,0.7);


}
