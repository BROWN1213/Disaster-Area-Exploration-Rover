import processing.serial.*;
import controlP5.*;

int savedTime;
int totalTime = 10000;

void setup(){
  size(1280,720,P2D);
  background(0);
  setupSerial();
  setupDelta();
  setupFileLog();
  savedTime = millis();
  setupRadar();
  
}

void draw(){
  
  fill(0);
  noStroke();
  rect(0,0,640,720);
  rect(640,0,160,720);
  rect(800,270,480,450);
  
  
  drawText();
  drawWebcam();
  drawRadarText();
  int passedTime = millis() - savedTime;
  // Has 10 seconds passed?
  if (passedTime > totalTime) {
    if(myPort!=null){
      saving();
      println("[auto-saving...]");
    }
    savedTime = millis(); // Save the current time to restart the timer!
  }
  blur();
  drawRadar();
  
  drawLine();
  drawObject();
}
