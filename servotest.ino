#include<Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(7);
  Serial.begin(9600);
  servo1.write(30);
  servo2.write(30);
  servo3.write(30);
}

void loop() {
  servo1.write(30);
  servo2.write(30);
  servo3.write(30);  
  delay(2000);
  servo1.write(60);
  servo2.write(60);
  servo3.write(60);
  delay(2000);
  servo1.write(100);
  servo2.write(100);
  servo3.write(100);
  delay(2000);  
  servo1.write(60);
  servo2.write(60);
  servo3.write(60);
  delay(2000);
}
