unsigned long distance_cm;
RoverUltraSonic sonicpinFront(4,5); // (trig, echo)
RoverUltraSonic sonicpinBack(11,10);
String rover_direction;
void setupUltraSonic(){ 
  ROVER_LOG("Setup UltraSonic 4trig,5echo ");
  sonicpinFront.begin();
  sonicpinBack.begin();
  rover_direction="Front";
  isFront= true;
}
float distance;

void updateUltraSonic(){ 
  //measure the distance
  //ROVER_LOG("update Ultra");
  if(isFront){
    UltraSonicFront();
  }else{
    UltraSonicBack();
  }

}
void UltraSonicBack(){ 
  /*float distanceBack=sonicpinBack.measureDistance();
  if(distanceBack>=1000)distanceBack=1000;
    // //measure the distance);
  Serial.print(F("%,4,2,"));
  Serial.print(distanceBack);
  Serial.print(F(","));
  Serial.println(radar_servoBack.read());
  delay(200);*/
}

void UltraSonicFront(){ 
  float distanceFront=sonicpinFront.measureDistance();
  if(distanceFront>=400)distanceFront=400; //Max distance is 400(cm).
    // //measure the distance);
  Serial.print(F("%,4,2,"));
  Serial.print(distanceFront);
  Serial.print(F(","));
  Serial.println(radar_servoFront.read());
  //
  delay(200);
}
void loopUltraSonicTest(){
  //distance=roverUltraSonic.measureDistance();
    // //measure the distance);
  Serial.println(distance);
    // print distance
  delay(500);

}
