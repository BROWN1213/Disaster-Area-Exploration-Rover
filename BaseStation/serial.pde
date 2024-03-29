import processing.serial.*;
import controlP5.*;



Serial myPort;
DropdownList menu1, menu2;
ControlP5 cp5;


void setupSerial(){
  cp5 = new ControlP5(this);

  menu1 = cp5.addDropdownList("port")
    .setPosition(10,60)
    .setSize(200,500);    

  customize(menu1);
  
  

}

void customize(DropdownList ddl) {
  // a convenience function to customize a DropdownList
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
    myPort = new Serial(this, port_name, 115200);
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
   
   
  if(input.indexOf("%") == 0){ //header
     input=input.substring(2,input.length()-2); 
     //println(input);
     input = trim(input);
     String[] values = split(input, ",");
     //values[0]: class, values[1]: num, 
      if(int(values[0])==1){ //IMU
        roll =float(values[2]);
        pitch =float(values[3]);
        yaw =float(values[4]);
        ax =float(values[5]);
        ay =float(values[6]);
        az =float(values[7]);
        
        appendImuLog();
        
        motion_acc=float(values[8]);
      }
      if(int(values[0])==2){  //GPS
        GPStime =values[2];
        lat=float(values[3]);
        lng=float(values[4]);
        alt=float(values[5]);
        num_sat=float(values[6]);
        speed_ms=float(values[7]);
        course=float(values[8]);
        
        appendGpsLog();
      }
      if(int(values[0])==4){
        distance=float(values[2]);
        angle=float(values[3]);
        
      }
      println(angle);
      println(distance);
  }
}
