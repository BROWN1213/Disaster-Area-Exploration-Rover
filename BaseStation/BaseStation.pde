import processing.serial.*;
import controlP5.*;

int savedTime;
int totalTime = 10000;

void setup(){
  size(1280,720,P2D);
  background(200);
  setupSerial();
  setupDelta();
  setupFileLog();
  savedTime = millis();
}

void draw(){
  fill(200);
  
  rect(0,0,640,720);
  rect(640,0,200,720);
  rect(800,270,480,450);

  noStroke();
  drawText();
  drawWebcam();
  drawradarText();
  int passedTime = millis() - savedTime;
  // Has 10 seconds passed?
  if (passedTime > totalTime) {
    if(myPort!=null){
      //saving();
      println("[auto-saving...]");
    }
    savedTime = millis(); // Save the current time to restart the timer!
  }
  
  drawRadar();
  blur();
  drawLine();
  drawObject();
}
