unsigned long distance_cm;
RoverUltraSonic roverUltraSonic(4,5); // (trig, echo)
void setupUltraSonic(){ 
  ROVER_LOG("Setup UltraSonic 4trig,5echo ");
  roverUltraSonic.begin();
}
float distance;

void updateUltraSonic(){ 
  //measure the distance
  ROVER_LOG("update Ultra");
  distance=roverUltraSonic.measureDistance();

}

void loopUltraSonicTest(){
  distance=roverUltraSonic.measureDistance();
    // //measure the distance);
  Serial.println(distance);
    // print distance
  delay(500);

}
