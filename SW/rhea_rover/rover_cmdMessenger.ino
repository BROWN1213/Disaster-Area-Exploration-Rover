
enum
{
  kAcknowledge, //0
  kError, //1
  kHomePosition, //2
  kDirivingMode, //3
  kManualControl, //4
  
};

void attachCommandCallbacks()
{
  // Attach callback methods
  cmdMessenger.attach(OnUnknownCommand);
  cmdMessenger.attach(kHomePosition, OnHomePosition);
  cmdMessenger.attach(kDirivingMode, OnDrivingMode); 
  cmdMessenger.attach(kManualControl, OnManualControl);
  
}

// Called when a received command has no attached function
void OnUnknownCommand()
{
  cmdMessenger.sendCmd(kError,F("Command without attached callback"));
}




void OnHomePosition(){

//   if(tskGps.getNumOfSatellites()>=6){
//     LocationInfo location=tskGps.getLocation();    
//     GpsCoordinates gps_coord;
//     gps_coord.lat=location.lat;
//     gps_coord.lng=location.lng;
//     gps_coord.alt=location.alt;
//     tskLocation.setDestination(gps_coord);
//     cmdMessenger.sendCmd(kAcknowledge,F("Home Position updated"));
//     cansatBT.send(F("lat:lng:alt= "));
//     cansatBT.send(location.lat);
//     cansatBT.sendln(location.lng);
//     cansatBT.sendln(location.alt);
//   }else{
//     cmdMessenger.sendCmd(kAcknowledge,F("Home Position Fail"));
//     Serial.println(F("We need at least 6 satellites ")); 
    
//   }
    cmdMessenger.sendCmd(kAcknowledge,F("Home Position updated"));
}

void OnDrivingMode(){
  // Read led state argument, 
  int trigger;
  trigger = cmdMessenger.readInt16Arg();
  if(trigger==0){ //automode
//     if(!tskNavigation.getNavigationMode()){
//        Serial.println(F("Navigation already automode ")); 
//     }else{
//        tskNavigation.setNavigationMode(0);
//     }    
    cmdMessenger.sendCmd(kAcknowledge,F("Driving:auto"));
    ROVER_LOG("Driving:auto");

  }
  if(trigger==1){ //manual mode
//     if(tskNavigation.getNavigationMode()){
//        Serial.println(F("Navigation already manualmode ")); 
//     }else{
//        tskNavigation.setNavigationMode(1);
//     }    
  cmdMessenger.sendCmd(kAcknowledge,F("Driving:manual"));
  ROVER_LOG("Driving:manual");
  }  
}

extern int velocity,radius;

void OnManualControl(){
  // Read led state argument, 
  
//   if(!tskNavigation.getNavigationMode()){
//     cmdMessenger.sendCmd(kAcknowledge,F("Control fail..Set manualmode first!!!")); 
//     return;  
//   }

  velocity = cmdMessenger.readInt16Arg();
  radius = cmdMessenger.readInt16Arg();

  //ROVER_LOG2(velocity,radius);
  cmdMessenger.sendCmd(kAcknowledge,F("ManualCmd ")); 
    // send velocity and radius to Lx16A
  
}

