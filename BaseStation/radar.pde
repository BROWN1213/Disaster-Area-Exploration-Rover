
float pixsDistance;
void drawRadar() {
  stroke(0);
  rect(800,-10,500,280,7);
  pushMatrix();
  translate(240,250); // moves the starting coordinats to new location
  noFill();
  strokeWeight(2);
  stroke(98,245,31);
  // draws the arc lines
  arc(800,0,450,450,PI,TWO_PI);
  arc(800,0,350,350,PI,TWO_PI);
  arc(800,0,250,250,PI,TWO_PI);
  arc(800,0,150,150,PI,TWO_PI);
  // draws the angle lines
  //line(240,0,240,0);
  line(800,0,-240*cos(radians(30))+800,-240*sin(radians(30)));
  line(800,0,-240*cos(radians(60))+800,-240*sin(radians(60)));
  line(800,0,-240*cos(radians(90))+800,-240*sin(radians(90)));
  line(800,0,-240*cos(radians(120))+800,-240*sin(radians(120)));
  line(800,0,-240*cos(radians(150))+800,-240*sin(radians(150)));
  line(-240*cos(radians(30))+780,0,1030,0);
  popMatrix();
}

void drawLine() {
  if(myPort!=null){
    pushMatrix();
    strokeWeight(3);
    stroke(30,250,60);  //green
    translate(1040,250); // moves the starting coordinats to new location
  
    line(0,0,240*cos(radians(float(angle))),-240*sin(radians(float(angle)))); // draws the line according to the angle
    popMatrix();
  }
}
void drawObject() {
  if(myPort!=null){
    pushMatrix();
    translate(1040,250); // moves the starting coordinats to new location
    strokeWeight(3);
    stroke(255,10,10); // red color
    pixsDistance = float(distance)*22.5/4; // covers the distance from the sensor from cm to pixels
    // limiting the range to 40 cms
    if(float(distance)<40){
      // draws the object according to the angle and the distance
    line(pixsDistance*cos(radians(float(angle))),-pixsDistance*sin(radians(float(angle))),240*cos(radians(float(angle))),-240*sin(radians(float(angle))));
    }
    popMatrix();
  }
}
void blur(){
fill(98,245,31);
  // simulating motion blur and slow fade of the moving line
  noStroke();
  fill(0,4); 
  rect(0, 0, width, 1010); 
  
  fill(98,245,31);
}
