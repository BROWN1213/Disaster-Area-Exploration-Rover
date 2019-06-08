SoftwareSerial _Mport(6,7);
RoverMotor myRover(_Mport);

void setupRoverMotor(){
  float corner_degree[4];
  myRover.begin(115200);
  _Mport.begin(115200);

}

void loopRoverMotor(){
  
}



void RoverMotorTest(){

  
  float cornerDeg[4],wh_angle[4],velocity_wheel[6];
  float approxRadius=0;
  /*
   char data=1;
   velocity_wheel[3]=50;
  myRover.wheelVelocityControl(velocity_wheel);
  //_Mport.write(data);
  delay(1000);
  */
  
  for(int i=0;i<=60;i+=10){
    v=i;
    myRover.calculateVelocity(v,approxRadius,velocity_wheel);
    myRover.wheelVelocityControl(velocity_wheel);
    delay(3000);
  }
  for(int i=0;i<6;i++){
    velocity_wheel[i]=0;
  }
  myRover.wheelVelocityControl(velocity_wheel);
  for(int i=0;i>=-60;i-=10){
    v=i;
    myRover.calculateVelocity(v,approxRadius,velocity_wheel);
    myRover.wheelVelocityControl(velocity_wheel);
    delay(3000);
  }
  for(int i=0;i<6;i++){
    velocity_wheel[i]=0;
  }  
  myRover.wheelVelocityControl(velocity_wheel);
  
  
  /*
  myRover.calculateVelocity(v,approxRadius,velocity_wheel);
  myRover.wheelVelocityControl(velocity_wheel);
  delay(3000);
  */
}

void sendcommand(int v,int r){
  /*
  float cornerDeg[4],wh_angle[4],velocity_wheel[6];
  //myRover.getCornerDegree(cornerDeg);
  //float approxRadius=myRover.approxTurningRadius(cornerDeg);
    float approxRadius=40;
  myRover.calculateVelocity(v,approxRadius,velocity_wheel);
  myRover.wheelVelocityControl(velocity_wheel);
  //myRover.calculateTargetDeg(r,wh_angle);
  //cornerPosControl(targetDegree);
  //Serial.print(cornerDeg[0]);Serial.print(cornerDeg[1]); Serial.print(cornerDeg[2]); Serial.println(cornerDeg[3]); 
 */
}
