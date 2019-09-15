SoftwareSerial _GPSport(8,9);

RoverGPS<SoftwareSerial> roverGPS(_GPSport);

void setupRoverGps(){

  // Causion!! When using a Software serial, 
  // must use 9600 baud rate, cause a Software read speed is too late
  roverGPS.begin(9600);
}

void loopRoverGps(){
 
  if(roverGPS.read()){  
       Serial.print("%,2,8,");
       Serial.print(roverGPS.date()); Serial.print(",");
       Serial.print(roverGPS.time()/100.); Serial.print(",");
       Serial.print((roverGPS.location().lat* 1.0e-7f),7); Serial.print(",");
       Serial.print((roverGPS.location().lng* 1.0e-7f),7); Serial.print(",");
       Serial.print(roverGPS.location().alt/100.); Serial.print(",");
       Serial.print(roverGPS.num_sats()); Serial.print(",");
       Serial.print(roverGPS.ground_speed_km()); Serial.print(",");
       Serial.println(roverGPS.ground_course()); 
  }   
       
}
void loopRoverGpsTEST(){
  Serial.println("%,2,8, 1,2,3,4,5,6,7,8");
}

void loopPassthru(){
   
   while (roverGPS.available()) Serial.write(roverGPS.readRaw());
}
