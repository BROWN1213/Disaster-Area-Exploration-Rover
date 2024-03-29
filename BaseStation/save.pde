// https://www.instructables.com/id/Data-Logging-SensorsInputs-With-Processing/

Table gpsLog;
Table imuLog;
float gpstime = 10.;
String filename;

String GPStime;
boolean save_first;
void setupFileLog(){
  
  gpsLog = new Table();
  gpsLog.addColumn("gpsTime");
  gpsLog.addColumn("sysTime"); 
  gpsLog.addColumn("Lat");
  gpsLog.addColumn("Lng");
  gpsLog.addColumn("Alt");  
  gpsLog.addColumn("Num_sat");  
  gpsLog.addColumn("Speed_ms");  
  gpsLog.addColumn("Course");  
  
  imuLog = new Table();
  imuLog.addColumn("sysTime");
  imuLog.addColumn("roll");
  imuLog.addColumn("pitch");
  imuLog.addColumn("yaw");
  imuLog.addColumn("ax");
  imuLog.addColumn("ay");
  imuLog.addColumn("az");
  
  cp5.addButton("saveLog")
     .setPosition(860,660)
     .setSize(100,50)
     .setValue(0)
     .activateBy(ControlP5.RELEASE);
     ;
  PFont pfont = createFont("Arial",20,true); // use true/false for smooth/no-smooth
  ControlFont font = new ControlFont(pfont,24);
  
  cp5.getController("saveLog")
     .getCaptionLabel()
     .toUpperCase(false)
     .setSize(20)
     .setFont(font)
     .setText("SAVE")
     ;   
   
  save_first=true;  
}

void appendGpsLog(){
  
  TableRow newRow = gpsLog.addRow();  
  newRow.setString("gpsTime", GPStime);
  newRow.setString("sysTime", str(day()) + ":" + str(hour()) + ":" + str(minute()) + ":" + str(second())+":" + str(millis()));
  newRow.setString("Lat", str(lat));
  newRow.setString("Lng", str(lng));
  newRow.setString("Alt", str(alt));
  newRow.setString("Speed_ms", str(speed_ms));
  newRow.setString("Course", str(course));
}

void appendImuLog(){
  
  //add a new row for each value
  TableRow newRow = imuLog.addRow();  
  newRow.setString("sysTime", str(day()) + ":" + str(hour()) + ":" + str(minute()) + ":" + str(second())+":" + str(millis()));
  newRow.setString("roll", str(roll));
  newRow.setString("pitch", str(pitch));
  newRow.setString("yaw", str(yaw));
  newRow.setString("ax", str(ax));
  newRow.setString("ay", str(ay));
  newRow.setString("az", str(az));
}
  
public void saveLog(int theValue){
  if(myPort!=null)saving();
}
void saving(){
  if(save_first){
    
      println("[saved]");
    
      saveTable(gpsLog, filename);
      filename = "data/" +"GPS"+ str(month()) + "-" + str(day()) + "--" + str(hour()) + "-" + str(minute()) + ".csv";

      saveTable(imuLog, filename);
      filename = "data/" +"IMU"+ str(month()) + "-" + str(day()) + "--" + str(hour()) + "-" + str(minute()) + ".csv";
    
    //save as a table in csv format(data/table - data folder name table)  
  }
  save_first=true;
}
