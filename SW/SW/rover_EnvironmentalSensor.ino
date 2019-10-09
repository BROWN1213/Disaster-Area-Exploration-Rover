
RoverPM2_5 roverPM2_5(A1,2);  //GP2Y10 dust sensor
RoverSHT3x roverSHT3x(0x45);  //SHT 30 temp/hum sensor
RoverMQ7 roverMQ7(A0,5.0);    //CO (Carbon Monoxide Gas) sensor

void setupEnvironmentalSensor(){
  ROVER_LOG("Setup Environmental Sensors");

  roverSHT3x.begin();
  roverPM2_5.begin();
}

void updateEnvironmentalSensor(){
  //ROVER_LOG("update Sensors");
  //Temperature and Humidity
  if(roverSHT3x.get()!=0){
    ROVER_LOG("SHT error");
  }
  //PM 2.5
  roverPM2_5.calulatePM2_5();

  //CO
  roverMQ7.getPPM();

  ROVER_LOG("Temp(C) Hum(%) PM2.5(μg/m^3) CO(ppm) ");
  //ROVER_LOG4((int)roverSHT3x.cTemp,(int)roverSHT3x.humidity,(int)roverPM2_5.dustDensity,roverMQ7.co_ppm)

  //processing
  Serial.print("%,3,4,");  //header
  Serial.print((int)roverSHT3x.cTemp);Serial.print(",");
  Serial.print((int)roverSHT3x.humidity);Serial.print(",");
  Serial.print((int)roverPM2_5.dustDensity);Serial.print(",");
  Serial.println((int)roverMQ7.co_ppm);  

}
