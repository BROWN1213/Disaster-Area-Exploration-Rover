boolean cmdFirst;

void setupDelta(){
  PFont pfont = createFont("Arial",20,true); // use true/false for smooth/no-smooth
  ControlFont font = new ControlFont(pfont,241);  
  cmdFirst=false;
  
  cp5.addButton("camup")
     .setPosition(500,660)
     .setSize(100,50)
     .setValue(0)
     .activateBy(ControlP5.RELEASE);
     ;
  cp5.getController("camup")
     .getCaptionLabel()
     .setFont(font)
     .toUpperCase(false)
     .setSize(20)
     .setText("CAMUP")
     ;     
     
  cp5.addButton("cammid")
     .setPosition(620,660)
     .setSize(100,50)
     .setValue(0)
     .activateBy(ControlP5.RELEASE);
     ;
  cp5.getController("cammid")
     .getCaptionLabel()
     .setFont(font)
     .toUpperCase(false)
     .setSize(20)
     .setText("CAMMID")
     ;     
     
  cp5.addButton("camdown")
     .setPosition(740,660)
     .setSize(100,50)
     .setValue(0)
     .activateBy(ControlP5.RELEASE);
     ;
  cp5.getController("camdown")
     .getCaptionLabel()
     .setFont(font)
     .toUpperCase(false)
     .setSize(20)
     .setText("CAMDOWN")
     ;     
  
  cmdFirst=true;
}//rovercontrol

void cmdcontrolEvent(ControlEvent theEvent) 
{
  
  if(cmdFirst) {

    if(theEvent.getController().getName()=="camup")sendCmdMessege("w");
    if(theEvent.getController().getName()=="cammid")sendCmdMessege("s");
    if(theEvent.getController().getName()=="camdown")sendCmdMessege("x");
    
  }
 if(theEvent.getController().getName()=="saving")saveLog();
}
void sendCmdMessege(String cmd){
  if(myPort!=null)myPort.write(cmd);
}
