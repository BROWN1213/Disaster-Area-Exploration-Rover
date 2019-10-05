unsigned long distance_cm;

String rover_direction;

RoverUltraSonic sonicpinFront(13,12); // (trig, echo)
RoverUltraSonic sonicpinBack(11,10);

void setupUltraSonic(){ 
  rover_direction="Front";
  isFront= true;
}

void loopUltraSonic(){ 
   //measure the distance
  distanceFront=sonicpinFront.measureDistance();
  distanceBack=sonicpinBack.measureDistance();
  String rover_direction = (isFront)? "Front" : "Back" ;
  //Serial.print("distance"+rover_direction+": ");
  Serial.print("%,4,2,");
  float distance = (isFront)? distanceFront : distanceBack ;
  Serial.print(distance);
  Serial.print(",");
  Serial.println(itest);
  //Serial.println(F("cm"));
}

void loopUltraSonicTest(){
  distanceFront=sonicpinFront.measureDistance();
    // //measure the distance);
    Serial.print("%,4,2,");
  Serial.print(distanceFront);
  Serial.print(",");
  Serial.println(itest);
  delay(200);
}
