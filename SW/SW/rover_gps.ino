
SoftwareSerial _GPSport(8,9);

RoverGPS<SoftwareSerial> roverGPS(_GPSport);
bool gps_connected=false;
void setupRoverGps(){

  // Causion!! When using a Software serial, 
  // must use 9600 baud rate, cause a Software read speed is too late
  ROVER_LOG("Setup GPS: wait 6sec ");
  roverGPS.begin(9600);
  //_GPSport.begin(9600);
    unsigned long t_now=millis();
    unsigned long wait_time;
    do{
      wait_time=millis()-t_now;
    }while(!roverGPS.available() && (wait_time<6000)); 

  if(roverGPS.available()>0){
    ROVER_LOG("GPS connected");
    gps_connected=true;
    roverGPS.rx_empty();
  }else{
    ROVER_LOG("No GPS found");
    gps_connected=false;
  }
}
#define GSP_WAIT 900 //wait until 600ms
void updateRoverGps(){
  if(gps_connected){
    //ROVER_LOG("updateRoverGPS ");
    //roverGPS.rx_empty();
    //wait until next GPS info.. GPS info comes every 5sec
    // unsigned long t_now=millis();
    // unsigned long wait_time;
    // bool gps_updated;
    // do{
    //   wait_time=millis()-t_now;
    //   gps_updated=roverGPS.read();
    // }while(!gps_updated && (wait_time<GSP_WAIT)); 

    if(roverGPS.read()){
      // ROVER_LOG("updateRoverGPS ");
      // roverGPS.rx_empty();
      // Serial.print("date=");
      // Serial.println(roverGPS.date());
      // Serial.print("time=");
      // Serial.println(roverGPS.time()/100.);
      // Serial.print("lat=");
      // Serial.println((roverGPS.location().lat* 1.0e-7f),7);
      // Serial.print("lon=");
      // Serial.println((roverGPS.location().lng* 1.0e-7f),7);       
  //      Serial.print("altitude(m)=");
  //      Serial.println(roverGPS.location().alt/100.); 
      // Serial.print("num_sat=");
      // Serial.println(roverGPS.num_sats()); 
  //      Serial.print("speed(km/s)=");
  //      Serial.println(roverGPS.ground_speed_km());
  //      Serial.print("cource=");
  //      Serial.println(roverGPS.ground_course());
    //processing
    Serial.print(F("%,2,6,"));  //header
    Serial.print((roverGPS.location().lat* 1.0e-7f),7);Serial.print(F(","));
    Serial.print((roverGPS.location().lng* 1.0e-7f),7);Serial.print(F(","));
    Serial.print(roverGPS.location().alt/100.);Serial.print(F(","));
    Serial.print(roverGPS.num_sats());Serial.print(F(","));
    Serial.print(roverGPS.ground_speed_ms());Serial.print(F(","));
    Serial.println(roverGPS.ground_course());  

  

    } //if(roverGPS.read())
  }else{
    ROVER_LOG("No GPS found");
  } //if(gps_connected)
       
}


void loopPassthru(){
  while (roverGPS.available()) Serial.write(roverGPS.readRaw());
}
