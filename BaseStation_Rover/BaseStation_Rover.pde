//Thanks to Adrian Fernandez
//Communication updates by M.Furkan Bahat November 2014
//For more information http://mfurkanbahat.blogspot.com.tr/

import processing.serial.*;
import processing.opengl.*;
//import cc.arduino.*;

int W=1440;//1920 ;//My Laptop's screen width 
int H=900; //My Laptop's screen height 

float Pitch; 
float Bank; 
float Azimuth; 
float ArtificialHoizonMagnificationFactor=0.4;//0.7; 
float CompassMagnificationFactor=0.8;//0.85; 
float controllerFactor=3.1;
float SpanAngle=120; 
int NumberOfScaleMajorDivisions; 
int NumberOfScaleMinorDivisions; 
PVector v1, v2; 

int temp,hum,pm2_5,co_ppm ;  
float lat=37.558231,lon=127.006744;
float alt,num_sat,speed,course;

Serial myPort;
float Phi;    //Dimensional axis
float Theta;
float Psi;

//Controller sa;
float ctr_w=200,ctr_h=200;
HScrollbar hs;  
VScrollbar vs; 

PImage img;

public void settings() {
  size(W,H);
}

void setup() 
{ 
  //size(1280,720); 
  //rectMode(CENTER); 
  smooth(); 
  strokeCap(SQUARE);//Optional 
  
  //sa = new Controller();
  hs= new HScrollbar(round(ctr_w*0.22), round(ctr_h*0.5), round(ctr_w*0.7), 16, 16); 
  vs= new VScrollbar(round(ctr_w*0.13), round(ctr_h*0.15), 16,round(ctr_w*0.7), 16); 
  
  println(Serial.list()); //Shows your connected serial ports
  myPort = new Serial(this, "COM9", 57600); 
  //Up there you should select port which arduino connected and same baud rate.
  myPort.bufferUntil('\n'); 
  
  

 // hs= new VScrollbar(width/2-20, height/2-8, width/2, 16, 16); 
}

void draw() 
{ 
  background(0); 
   
  rectMode(CENTER);
  translate(W/5, 1.2*H/5);
  MakeAnglesDependentOnMPU6050(); 
  Horizon(); 
  rotate(-Bank); 
  PitchScale(); 
  Axis(); 
  rotate(Bank); 
  Borders(); 
  Plane(); 
  ShowAngles(); 
  Compass(); 
  ShowAzimuth(); 
  
  scale(controllerFactor);
  translate(-1.5*W/5,1.2*H/5);
  rectMode(CORNER);
  Controller(); 
  
  translate(2.2*W/5,-2*H/5);
  loadMap();
  
}



void serialEvent(Serial port) //Reading the datas by Processing.
{
   String input = port.readStringUntil('\n');
   //println(input.indexOf("%"));
   println(input);
   
  if(input.indexOf("%") == 0){
    input=input.substring(1,input.length()-1);
   // println(input);
    
   input = trim(input);
   String[] values = split(input, " ");
   //parsing IMU
   if(values.length == 3){
    float theta= float(values[0]); //roll
    float phi= float(values[1]);  //pitch
    float psi = float(values[2]);  //yaw
   // print(phi);
   // print(theta);
   // println(psi);
    Phi = phi;
    Theta = theta;
    Psi = -psi;
   }
   //parsing sensor
   if(values.length == 4){
    temp= int(values[0]); 
    hum= int(values[1]);  
    pm2_5 = int(values[2]);  
    co_ppm = int(values[3]);  
    //print("temp: ");print(temp);print(" ");
    //print("hum: ");print(hum);print("% ");
    //print("PM2.5: ");print(pm2_5);print("ug/m^3 ");
    //print("CO: ");print(co_ppm);println("ppm ");
   }
   
   //parsing GPS
   if(values.length == 6){
    lat= float(values[0]); 
    lon= float(values[1]);  
    alt = float(values[2]);  
    num_sat = int(values[3]);  
    speed = float(values[4]);  
    course = float(values[5]);     

   }
   
   
  }
  
 
  
}
void MakeAnglesDependentOnMPU6050() 
{ 
  Bank =-Theta/180*3.14; 
  Pitch=Phi*5; 
  Azimuth=Psi;
}

void Horizon() 
{ 
  scale(ArtificialHoizonMagnificationFactor); 
  noStroke(); 
  fill(0, 180, 255); 
  rect(0, -100, 900, 500); 
  fill(95, 55, 40); 
  rotate(-Bank); 
  rect(0, 250+Pitch, 900, 500); 
  rotate(Bank); 
  rotate(-PI-PI/6); 
  SpanAngle=120; 
  NumberOfScaleMajorDivisions=12; 
  NumberOfScaleMinorDivisions=24;  
  CircularScale(); 
  rotate(PI+PI/6); 
  rotate(-PI/6);  
  CircularScale(); 
  rotate(PI/6); 
}
void ShowAzimuth() 
{ 
  fill(50); 
  noStroke(); 
  rect(20, 470, 440, 50); 
  int Azimuth1=round(Azimuth); 
  textAlign(CORNER); 
  textSize(35); 
  fill(255); 
  text("Azimuth:  "+Azimuth1+" Deg", 80, 477, 500, 60); 
  textSize(40);
  fill(25,25,150);
  //text("M.Furkan Bahat", -350, 477, 500, 60); 
}
void Controller(){
  //translate(3*W/5, 0); 
  //scale(1);   
  fill(50); 
  noStroke(); 
  rect(0, 0, ctr_w, ctr_h);
      //hs.update();
   hs.display();
    
    //vs.update();
   vs.display(); 
   ShowRoverData();
}
void ShowRoverData()
{ 

  int text_size=20,text_x=0,text_x_inte=200;
  int text_y=round(ctr_h+40),text_y_inte=text_size*2;
  textSize(text_size); 
  fill(255); 
  noStroke(); 


  text("Temp:  "+temp+" Deg", text_x, text_y); text("Humi:  "+hum+" %", text_x+text_x_inte, text_y); 
  text("PM2.5:  "+pm2_5+" ug/m3", text_x, text_y+text_y_inte);  text("C0:  "+co_ppm+" ppm", text_x+text_x_inte, text_y+text_y_inte);   
  text("Lat:  "+nf(lat,3,7), text_x, text_y+text_y_inte*2); text("Lon:  "+nf(lon,3,7), text_x+text_x_inte, text_y+text_y_inte*2); 
  text("Alt:  "+alt+"m", text_x,text_y+text_y_inte*3); text("Speed:  "+speed+"m/s", text_x+text_x_inte, text_y+text_y_inte*3); 
  text("Course:  "+course+"Deg", text_x, text_y+text_y_inte*4); text("Sat:  "+(int)num_sat, text_x+text_x_inte, text_y+text_y_inte*4);   
}
boolean on=true;
float prev_lon,prev_lat;
boolean first_map=false;
void loadMap(){
  String token = "pk.eyJ1IjoiY2NoYW1jaGkiLCJhIjoiY2plNDM0ZW8xMXo3NTJ3anI5NW81Y2xxZyJ9.QLsDM8E8nyuK2GMfGuUFDw";
  //String longitude = "127.1144943 ";
  //String latitude = "37.384931";
  String longitude = "127.006744";
  String latitude = "037.558231";  
  if(num_sat>=2){
    longitude=nf(lon,3,7);
    latitude=nf(lat,3,7);
  }

  String zoom = "15.2";
  String pitch = "0";
  //https://www.mapbox.com/api-documentation/#styles
  String style = "streets-v10"; // "streets-v10" "dark-v9" "light-v9" "satellite-streets-v10" "navigation-preview-day-v2"
  
  String url;
  
  url="https://api.mapbox.com/styles/v1/mapbox/"+style+"/static/"+longitude+","+latitude+","+zoom+",0,"+pitch+"/600x600?access_token="+token;
  if(abs(prev_lon-lon)>0.0001 || (first_map==false) ||abs(prev_lat-lat)>0.0001){//10m change->load map
    img =  loadImage(url,"jpg");  
    
    first_map=true;
  }
  //image(img,0,0);
  prev_lon=lon;
  prev_lat=lat;
  
  if(frameCount% 30 <20) {
      fill(203,67,53);
      ellipse(300, 300, 20, 20);

  }
  
}
void Compass() 
{ 
  translate(W/2, 0); 
  scale(CompassMagnificationFactor); 
  noFill(); 
  stroke(100); 
  strokeWeight(80); 
  ellipse(0, 0, 750, 750); 
  strokeWeight(50); 
  stroke(50); 
  fill(0, 0, 40); 
  ellipse(0, 0, 610, 610); 
  for (int k=255;k>0;k=k-5) 
  { 
    noStroke(); 
    fill(0, 0, 255-k); 
    ellipse(0, 0, 2*k, 2*k); 
  } 
  strokeWeight(20); 
  NumberOfScaleMajorDivisions=18; 
  NumberOfScaleMinorDivisions=36;  
  SpanAngle=180; 
  CircularScale(); 
  rotate(PI); 
  SpanAngle=180; 
  CircularScale(); 
  rotate(-PI); 
  fill(255); 
  textSize(60); 
  textAlign(CENTER); 
  text("W", -375, 0, 100, 80); 
  text("E", 370, 0, 100, 80); 
  text("N", 0, -365, 100, 80); 
  text("S", 0, 375, 100, 80); 
  textSize(30); 
  text("COMPASS", 0, -130, 500, 80); 
  rotate(PI/4); 
  textSize(40); 
  text("NW", -370, 0, 100, 50); 
  text("SE", 365, 0, 100, 50); 
  text("NE", 0, -355, 100, 50); 
  text("SW", 0, 365, 100, 50); 
  rotate(-PI/4); 
  CompassPointer(); 
}
void CompassPointer() 
{ 
  rotate(PI+radians(Azimuth));  
  stroke(0); 
  strokeWeight(4); 
  fill(100, 255, 100); 
  triangle(-20, -210, 20, -210, 0, 270); 
  triangle(-15, 210, 15, 210, 0, 270); 
  ellipse(0, 0, 45, 45);   
  fill(0, 0, 50); 
  noStroke(); 
  ellipse(0, 0, 10, 10); 
  triangle(-20, -213, 20, -213, 0, -190); 
  triangle(-15, -215, 15, -215, 0, -200); 
  rotate(-PI-radians(Azimuth)); 
}
void Plane() 
{ 
  fill(0); 
  strokeWeight(1); 
  stroke(0, 255, 0); 
  triangle(-20, 0, 20, 0, 0, 25); 
  rect(110, 0, 140, 20); 
  rect(-110, 0, 140, 20); 
}
void CircularScale() 
{ 
  float GaugeWidth=800;  
  textSize(GaugeWidth/30); 
  float StrokeWidth=1; 
  float an; 
  float DivxPhasorCloser; 
  float DivxPhasorDistal; 
  float DivyPhasorCloser; 
  float DivyPhasorDistal; 
  strokeWeight(2*StrokeWidth); 
  stroke(255);
  float DivCloserPhasorLenght=GaugeWidth/2-GaugeWidth/9-StrokeWidth; 
  float DivDistalPhasorLenght=GaugeWidth/2-GaugeWidth/7.5-StrokeWidth;
  for (int Division=0;Division<NumberOfScaleMinorDivisions+1;Division++) 
  { 
    an=SpanAngle/2+Division*SpanAngle/NumberOfScaleMinorDivisions;  
    DivxPhasorCloser=DivCloserPhasorLenght*cos(radians(an)); 
    DivxPhasorDistal=DivDistalPhasorLenght*cos(radians(an)); 
    DivyPhasorCloser=DivCloserPhasorLenght*sin(radians(an)); 
    DivyPhasorDistal=DivDistalPhasorLenght*sin(radians(an));   
    line(DivxPhasorCloser, DivyPhasorCloser, DivxPhasorDistal, DivyPhasorDistal); 
  }
  DivCloserPhasorLenght=GaugeWidth/2-GaugeWidth/10-StrokeWidth; 
  DivDistalPhasorLenght=GaugeWidth/2-GaugeWidth/7.4-StrokeWidth;
  for (int Division=0;Division<NumberOfScaleMajorDivisions+1;Division++) 
  { 
    an=SpanAngle/2+Division*SpanAngle/NumberOfScaleMajorDivisions;  
    DivxPhasorCloser=DivCloserPhasorLenght*cos(radians(an)); 
    DivxPhasorDistal=DivDistalPhasorLenght*cos(radians(an)); 
    DivyPhasorCloser=DivCloserPhasorLenght*sin(radians(an)); 
    DivyPhasorDistal=DivDistalPhasorLenght*sin(radians(an)); 
    if (Division==NumberOfScaleMajorDivisions/2|Division==0|Division==NumberOfScaleMajorDivisions) 
    { 
      strokeWeight(15); 
      stroke(0); 
      line(DivxPhasorCloser, DivyPhasorCloser, DivxPhasorDistal, DivyPhasorDistal); 
      strokeWeight(8); 
      stroke(100, 255, 100); 
      line(DivxPhasorCloser, DivyPhasorCloser, DivxPhasorDistal, DivyPhasorDistal); 
    } 
    else 
    { 
      strokeWeight(3); 
      stroke(255); 
      line(DivxPhasorCloser, DivyPhasorCloser, DivxPhasorDistal, DivyPhasorDistal); 
    } 
  } 
}
void Axis() 
{ 
  stroke(255, 0, 0); 
  strokeWeight(3); 
  line(-115, 0, 115, 0); 
  line(0, 280, 0, -280); 
  fill(100, 255, 100); 
  stroke(0); 
  triangle(0, -285, -10, -255, 10, -255); 
  triangle(0, 285, -10, 255, 10, 255); 
}
void ShowAngles() 
{ 
  textSize(30); 
  fill(50); 
  noStroke(); 
  rect(-150, 400, 280, 40); 
  rect(150, 400, 280, 40); 
  fill(255); 
  Pitch=Pitch/5;
  int Pitch1=round(Pitch); 
  int roll=round(Theta);
  text("Pitch:  "+Pitch1+" Deg", -20, 411, 500, 60); 
  text("Roll:  "+roll+" Deg", 280, 411, 500, 60); 
  
}

   
void Borders() 
{ 
  noFill(); 
  stroke(0); 
  strokeWeight(400); 
  rect(0, 0, 1100, 1100); 
  strokeWeight(200); 
  ellipse(0, 0, 1000, 1000); 
  fill(0); 
  noStroke(); 
  rect(4*W/5, 0, W, 2*H); 
  rect(-4*W/5, 0, W, 2*H); 
}
void PitchScale() 
{  
  stroke(255); 
  fill(255); 
  strokeWeight(3); 
  textSize(24); 
  textAlign(CENTER); 
  for (int i=-4;i<5;i++) 
  {  
    if ((i==0)==false) 
    { 
      line(110, 50*i, -110, 50*i); 
    }  
    text(""+i*10, 140, 50*i, 100, 30); 
    text(""+i*10, -140, 50*i, 100, 30); 
  } 
  textAlign(CORNER); 
  strokeWeight(2); 
  for (int i=-9;i<10;i++) 
  {  
    if ((i==0)==false) 
    {    
      line(25, 25*i, -25, 25*i); 
    } 
  } 
}
