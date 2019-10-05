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
