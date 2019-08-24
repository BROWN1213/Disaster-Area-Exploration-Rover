
Servo servo;
void setupRader(){
  rover_rader rader(servo,3);
}
void loopRader(){
  raderServo(servo,steer_angle);
}
