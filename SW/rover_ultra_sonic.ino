unsigned long distance_cm;

String rover_direction;

RoverUltraSonic sonicpinFront(13,12); // (trig, echo)
RoverUltraSonic sonicpinBack(11,10);

void setupUltraSonic(){ 
  rover_direction="Front";
  isFront= true;
}

void loopUltraSonicBack(){ 
  distanceBack=sonicpinBack.measureDistance();
    // //measure the distance);
  Serial.print("%,4,2,");
  Serial.print(distanceBack);
  Serial.print(",");
  Serial.println(radar_servoBack.read());
  delay(200);
}

void loopUltraSonicFront(){
  distanceFront=sonicpinFront.measureDistance();
    // //measure the distance);
    Serial.print("%,4,2,");
  Serial.print(distanceFront);
  Serial.print(",");
  Serial.println(radar_servoFront.read());
  delay(200);
}
