import processing.serial.*;
import controlP5.*;

Serial myPort;
DropdownList menu1, menu2;
ControlP5 cp5;

String num_sat;
String lat,lng,alt;
String velocity,pm2_5;
void setup(){
  size(1280,720,P2D);
  setupSerial();
  setupDelta();
}

void draw(){
  drawText();
  drawWebcam();
}
