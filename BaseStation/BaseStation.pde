import processing.serial.*;
import controlP5.*;

int savedTime;
int totalTime = 10000;

Serial myPort;
DropdownList menu1, menu2;
ControlP5 cp5;

void setup(){
  size(1280,720,P2D);
  setupSerial();
  setupDelta();
  savedTime = millis();
}

void draw(){
  drawText();
  drawWebcam();
  drawradarText();
  int passedTime = millis() - savedTime;
  // Has 10 seconds passed?
  if (passedTime > totalTime) {
    //saveLog();
    println("[saved]");
    
    savedTime = millis(); // Save the current time to restart the timer!
  }
}
