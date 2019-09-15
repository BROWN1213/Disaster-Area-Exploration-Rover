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
  Serial.print("distance"+rover_direction+": ");
  float distance = (isFront)? distanceFront : distanceBack ;
  Serial.print(distance);
  Serial.println(F("cm"));
  //sonicpin.isDistanceInArea(20,1);
   //is Distance in Area??

   // Do someting

}

void loopUltraSonicTest(){
  distanceFront=sonicpinFront.measureDistance();
    // //measure the distance);
  Serial.print(distanceFront);
  Serial.println("cm");
  
    // print distance
  delay(500);

}
