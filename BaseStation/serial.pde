String roll,pitch,yaw;
//imu ok gps ok pm2.5 radar cam ......
void setupSerial(){
  
  
  cp5 = new ControlP5(this);

  menu1 = cp5.addDropdownList("port")
    .setPosition(10,10)
    .setSize(300,500);    

  customize(menu1);
}

void customize(DropdownList ddl) {
  // a convenience function to customize a DropdownList
  PFont pfont = createFont("Arial",20,true); // use true/false for smooth/no-smooth
  ControlFont font = new ControlFont(pfont,12);
  //ddl.setFont(font);
  ddl.setBackgroundColor(color(190));
  ddl.setItemHeight(15);
  ddl.setBarHeight(17);
  //ddl.captionLabel().set("port");
  ddl.getCaptionLabel().getStyle().marginTop = 3;
  ddl.getCaptionLabel().getStyle().marginLeft = 3;
  ddl.getValueLabel().getStyle().marginTop = 3;
  
  for(int i=0;i<Serial.list().length;i++)
    ddl.addItem(Serial.list()[i], i);
  

   
  //ddl.scroll(0);
  ddl.setColorBackground(color(60));
  ddl.setColorActive(color(255, 128));
  
  
}
void controlEvent(ControlEvent theControlEvent) 
{
  
  if (theControlEvent.isFrom(menu1))
  { int list_num= (int)theControlEvent.controller().getValue();
    String port_name=Serial.list()[list_num];
    println(port_name);
    myPort = new Serial(this, port_name, 57600);
    myPort.bufferUntil('\n');   
    delay(1000);
    String cmd="AT\r\n";
    myPort.write(cmd); 
    delay(1000);
    cmd="ATD\r\n";
    myPort.write(cmd);   
    
  }
  if(theControlEvent.isController())
    cmdcontrolEvent(theControlEvent); // toss to cmdMessege  


}

void reConnect(){
    String cmd="AT\r\n";
    myPort.write(cmd); 
    delay(1000);
    cmd="ATD\r\n";
    myPort.write(cmd);  
    delay(1000);
}

void serialEvent(Serial port) //Reading the datas by Processing.
{
   String input = port.readStringUntil('\n');
   //println(input);
   appendSerialLog(input);
   
  if(input.indexOf("%") == 0){ //header
     input=input.substring(2,input.length()-2); 
     //println(input);
     input = trim(input);
     String[] values = split(input, ",");
     //values[0]: class, values[1]: num, 
      if(int(values[0])==1){ //IMU
      
        roll=values[2];
        pitch=values[3];
        yaw=values[4];
      
        //print("[");print(millis());print("]");
        //print(roll);print(",");
        //print(pitch);print(",");
        //println(yaw);
        //print("[");print(millis());print("]");
        //print(float(values[5]));print(",");
        //print(float(values[6]));print(",");
        //println(float(values[7]));

        appendImuLog();
      }
      if(int(values[0])==2){ //GPS
        lat=values[2];
        lng=values[3];
        alt=values[4];
        num_sat=values[5];
        //speed_ms=float(values[6];
        //course=values[7]);
        
        //gps_new_messege=true; //

        print("[");print(millis());print("gps");print("]");
        print(lat);print(",");
        print(lng);print(",");
        println(alt);
        appendGpsLog();
      }
    }
  }
