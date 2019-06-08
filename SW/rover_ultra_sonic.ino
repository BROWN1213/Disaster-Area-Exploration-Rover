unsigned long distance_cm;
RoverUltraSonic sonicpin(13,12); // (trig, echo)
void setupUltraSonic(){ 

}
float distance;

void loopUltraSonic(){ 
   //measure the distance
  distance=sonicpin.measureDistance();
  
  sonicpin.isDistanceInArea(20,1);
   //is Distance in Area??

   // Do someting

}

void loopUltraSonicTest(){
  distance=sonicpin.measureDistance();
    // //measure the distance);
  Serial.println(distance);
    // print distance
  delay(500);

}
