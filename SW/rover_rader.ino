
float prev_servo_angle;
float _rotate_angle;
float servo_angle=130.;

RoverRadar radarFront(steer_angle);
RoverRadar radarBack(steer_angle);

void setupRadar(){
  radar_servoFront.attach(SERVO_PIN);
  radar_servoFront.write(steer_angle);
  radar_servoBack.attach(SERVO_PIN);
  radar_servoBack.write(steer_angle);
  //float steer_angle=radar.constrain_angle(steer_angle);
}

void loopRadar(){
  prev_servo_angle = servo_angle;
  if(isFront){
    servo_angle = radar_servoFront.read();
    _rotate_angle = radarFront.rotate_angle(steer_angle,servo_angle,prev_servo_angle);
    radar_servoFront.write(_rotate_angle);
  }else{
    servo_angle = radar_servoBack.read();
    _rotate_angle = radarBack.rotate_angle(steer_angle,servo_angle,prev_servo_angle);
    radar_servoBack.write(_rotate_angle);
  }
  Serial.print(F("angle: "));
  Serial.println(_rotate_angle);
  Serial.println("%,3,2,"+distance+","+_rotate_angle);
}
