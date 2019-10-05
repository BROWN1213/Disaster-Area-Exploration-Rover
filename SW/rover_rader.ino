
float prev_servo_angle;
float _rotate_angle;
float servo_angle=130.;
float distance_per_angle;
int itest=15;
bool c=true;
RoverRadar radarFront(steer_angle);
RoverRadar radarBack(steer_angle);


void radarTest(){
  int test = 30;
  radar_servoFront.write(test);
  radar_servoBack.write(test);
  Serial.println(radar_servoFront.read());
  Serial.println(radar_servoFront.read());
  delay(500);
}
void setupRadar(){
  radar_servoFront.attach(3);
  radar_servoFront.write(steer_angle);
  radar_servoBack.attach(5);
  radar_servoBack.write(steer_angle);
  Serial.println("*************************");
  Serial.println(radar_servoFront.read());
  Serial.println("*************************");
  Serial.println(radar_servoFront.read());
  Serial.println("*************************");
  
}

void loopRadar(){
  prev_servo_angle = servo_angle;
  if(isFront){
    servo_angle = radar_servoFront.read();
    _rotate_angle = radarFront.rotate_angle(steer_angle,servo_angle,prev_servo_angle);
    radar_servoFront.write(_rotate_angle);
    //send to BS
    radarFront.sendRaderInfo(distanceFront,_rotate_angle);
  }else{
    servo_angle = radar_servoBack.read();
    _rotate_angle = radarBack.rotate_angle(steer_angle,servo_angle,prev_servo_angle);
    radar_servoBack.write(_rotate_angle);
    //send to BS
    radarBack.sendRaderInfo(distanceBack,_rotate_angle);
  }
  Serial.print(F("angle: "));
  Serial.println(_rotate_angle);
  
}
void loopRadarTest(){
  
  if(c){
    itest=itest+10;
    if(itest>160)c=false;
  }else{
     itest=itest-10;
    if(itest<20)c=true;
  }
  radar_servoFront.write(itest);
}
