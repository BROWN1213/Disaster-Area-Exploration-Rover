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
  int r;
  float cornerDeg[4],wh_angle[4],velocity_wheel[6];
  //float approxRadius=50;
  
  //myRover.getCornerDegree(cornerDeg);
  //myRover.approxTurningRadius(cornerDeg);
  //myRover.calculateTargetDeg(r,wh_angle);
  //myRover.cornerPosControl(wh_angle);
  /*
  for(int i=500;i<=1000;i+=100){
    //myRover.Move(11,i-10,1);
    //myRover.Move(33,-(i+10),1);
    //myRover.Move(44,i-27,1);
    myRover.OffsetAdjust(66,-(i+15));
    delay(3000);
  }
  int i=500;
  //myRover.Move(11,i,1);
    //myRover.Move(33,-(i+10),1);
    //myRover.Move(44,i-27,1);
    myRover.OffsetAdjust(66,-(i+15));
    delay(3000);
  for(int i=500;i<=0;i-=100){
    //myRover.Move(11,i-10,1);
    //myRover.Move(33,-(i+10),1);
    //myRover.Move(44,i-27,1);
    myRover.OffsetAdjust(66,-(i+15));
    delay(3000);
  }
  i=500;
  //m/yRover.Move(11,i-10,1);
  //myRover.Move(33,-(i+10),1);
  //myRover.Move(44,i-27,1);
  myRover.OffsetAdjust(66,-(i+15));
  delay(3000);
  */
  int i=-50;
  myRover.Move(11,490-i,1);
  delay(100);
  myRover.Move(33,510-i,1);
  delay(100);
  myRover.Move(44,460-i,1);
  delay(100);
  myRover.Move(66,560-i,1);
  delay(100);
  //delay(100);
  delay(3000);
  i=0;
  myRover.Move(11,490-i,1);
  delay(100);
  myRover.Move(33,510-i,1);
  delay(100);
  myRover.Move(44,460-i,1);
  delay(100);
  myRover.Move(66,560-i,1);
  delay(100);
  delay(3000);
  i=50;
  myRover.Move(11,490-i,1);
  delay(100);
  myRover.Move(33,510-i,1);
  delay(100);
  myRover.Move(44,460-i,1);
  delay(100);
  myRover.Move(66,560-i,1);
  delay(100);
  delay(3000);
  //myRover.OffsetAdjust(66,0);
  //delay(1000);
  //66:15
  //44:-27
  //33:10
  //11:-10
  
  /*
  for(int i=0;i<=100;i+=25){
    r=i;
    myRover.getCornerDegree(cornerDeg);
    myRover.approxTurningRadius(cornerDeg);
    myRover.calculateTargetDeg(r,wh_angle);
    myRover.cornerPosControl(wh_angle);
    delay(3000);
  }
  r=0;
  myRover.calculateTargetDeg(r,wh_angle);
  myRover.cornerPosControl(wh_angle);
  delay(3000);
  for(int i=0;i>=-100;i-=25){
    r=i;
    myRover.getCornerDegree(cornerDeg);
    myRover.approxTurningRadius(cornerDeg);
    myRover.calculateTargetDeg(r,wh_angle);
    myRover.cornerPosControl(wh_angle);
    delay(3000);
  }
  r=0;
  myRover.calculateTargetDeg(r,wh_angle);
  myRover.cornerPosControl(wh_angle);
  delay(3000);
  */
  /*
   char data=1;
   velocity_wheel[3]=50;
  myRover.wheelVelocityControl(velocity_wheel);
  //_Mport.write(data);
  delay(1000);
  */
  /*
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
  */
  
  /*
  myRover.calculateVelocity(v,approxRadius,velocity_wheel);
  myRover.wheelVelocityControl(velocity_wheel);
  delay(3000);
  */
}

void sendcommand(int v,int r=50){

  
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
