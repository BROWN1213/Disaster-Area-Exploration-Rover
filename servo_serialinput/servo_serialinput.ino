#include<Servo.h>
Servo servo;
int value = 0;

void setup() {
  servo.attach(6);
  Serial.begin(57600);
  servo.write(60);
}

void loop() {
  
  if(Serial.available())
  {
    char in_data;
    in_data = Serial.read();
    if(in_data == 'x')
    {
      value = 45;   //150
    }
    else if(in_data == 's'){
      value = 60;   //120
    }                    
    else if(in_data == 'w'){
      value =75;   //100
    }
    servo.write(value);
  }
  
}
