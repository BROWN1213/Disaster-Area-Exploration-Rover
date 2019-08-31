unsigned long distance_cm;
RoverUltraSonic sonicpin(13,12); // (trig, echo)

void setupUltraSonic(){ 

}

void loopUltraSonic(){ 
   //measure the distance
  distance=sonicpin.measureDistance();
  Serial.print(F("distance:"));
  Serial.print(distance);
  Serial.println(F("cm"));
  //sonicpin.isDistanceInArea(20,1);
   //is Distance in Area??

   // Do someting

}

void loopUltraSonicTest(){
  distance=sonicpin.measureDistance();
    // //measure the distance);
  Serial.print(distance);
  Serial.println("cm");
  
    // print distance
  delay(500);

}
