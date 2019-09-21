import processing.serial.*;
import controlP5.*;

int savedTime;
int totalTime = 10000;

void setup(){
  size(1280,720,P2D);
  setupSerial();
  setupDelta();
  setupFileLog();
  savedTime = millis();
}

void draw(){
  drawText();
  drawWebcam();
  drawradarText();
  int passedTime = millis() - savedTime;
  // Has 10 seconds passed?
  if (passedTime > totalTime) {
    if(myPort!=null){
      saveLog();
      println("[auto-saving...]");
    }
    savedTime = millis(); // Save the current time to restart the timer!
  }
}
