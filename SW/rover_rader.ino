#define SERVO_PIN 3
float steer_angle=90;
int i=0;
Servo servo;
//RoverRader rader(servo,SERVO_PIN,steer_angle);
void setupRader(){
  servo.attach(SERVO_PIN);
  constrain(steer_angle,30,150);

}
void loopRader(){
  
  float min_angle=steer_angle-30.;// "±30" can be changed
  float max_angle=steer_angle+30.;
  if(i==0){
    servo.write(min_angle);
    i=1;
  }else{
    servo.write(max_angle);
    i=0;
  }
  delay(500);
  servo.write(steer_angle);
}
