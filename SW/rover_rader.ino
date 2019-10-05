
float prev_servo_angle;
float _rotate_angle;
float servo_angle=130.;

RoverRadar radar(steer_angle);

void setupRadar(){
  radar_servo.attach(SERVO_PIN);
  radar_servo.write(steer_angle);
  //float steer_angle=radar.constrain_angle(steer_angle);
}

void loopRadar(){
  prev_servo_angle = servo_angle;
  servo_angle = radar_servo.read();
  
  _rotate_angle = radar.rotate_angle(steer_angle,servo_angle,prev_servo_angle);
  radar_servo.write(_rotate_angle);
  
  Serial.print(F("angle: "));
  Serial.println(_rotate_angle);
  
}
