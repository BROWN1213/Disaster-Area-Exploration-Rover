float num_sat,distance,angle;
float lat,lng,alt,roll,pitch,yaw,motion_acc;
float velocity,pm2_5,speed_ms,course;
float ax,ay,az;

void setupText(){
  
}
void drawText(){  
  fill(255,255,255);
  textSize(25);
  
  text("roll,pitch,yaw: "+roll+","+pitch+","+yaw,0,50);
  text("Sat Num:"+num_sat,0,100);
  text("GPS Location:"+lat+","+lng+","+alt,0,150);
  text("PM2.5:"+pm2_5+" ppm",0,200);
  text(velocity+" Km",0,680);
  
}
void drawradarText(){
  text("distance from an object: "+distance+" at angle "+angle,0,250);
 
}
