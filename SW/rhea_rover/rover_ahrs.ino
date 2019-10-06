
RoverAhrs roverAhrs;

void setupRoverAhrs() {
    ROVER_LOG("Setup MPU6050");    
    //roverAhrs.begin();
    if(roverAhrs.begin()){
        ROVER_LOG("MPU6050 connected");
    }else{
        ROVER_LOG("No MPU6050 found");
    }
}

void updateRoverAhrs() {
   //ROVER_LOG("update AHRS"); 
    roverAhrs.update(COMP_FILTER);
    //roverAhrs.update(NO_FILTER);
    //Serial.print("r:");Serial.print(roverAhrs.roll);
    //Serial.print("p:");Serial.print(roverAhrs.pitch);
    //Serial.print("y:");Serial.println(roverAhrs.yaw);
    //processing
    Serial.print("%");  //header
    Serial.print(roverAhrs.roll);Serial.print(" ");
    Serial.print(roverAhrs.pitch);Serial.print(" ");
    Serial.println(roverAhrs.yaw);
}
