float prev_servo_angle;
int _rotate_angle;
float servo_angle=130.;
float distance_per_angle;
int itest=20;
bool c= true;
RoverRadar radar(steer_angle);


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
  if(isFront){
    _rotate_angle = radar.turn_angle(radar_servoFront.read());
    radar_servoFront.write(_rotate_angle);
  }else{
    _rotate_angle = radar.turn_angle(radar_servoBack.read());
    radar_servoFront.write(_rotate_angle);
  }
  float _angle = (isFront)? radar_servoFront.read() : radar_servoBack.read();
  Serial.print(F("angle: "));
  Serial.println(_angle);
  
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
  Serial.println(itest);
}
