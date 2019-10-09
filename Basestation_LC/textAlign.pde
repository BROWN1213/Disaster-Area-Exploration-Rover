float num_sat,distance,angle;
float lat,lng,alt,roll,pitch,yaw,motion_acc;
float pm2_5,speed_ms,course;
float ax,ay,az;
float temp,humid,dustDensity,co_ppm;

void setupText(){
  temp = 0;
  humid = 0;
  dustDensity =0;
  co_ppm =0;
}
void drawText(){  
  fill(255,255,255);
  textSize(25);
  
  text("roll,pitch,yaw: "+roll+","+pitch+","+yaw,0,50);
  text("Sat Num:"+num_sat,0,100);
  text("GPS Location:"+lat+","+lng+","+alt,0,150);
  text("PM2.5:"+str(dustDensity)+" ppm",0,200);
  text("Temp:"+str(temp)+"ºC",0,250);
  text("Humidity:"+str(humid)+"%",0,300);
  text("CO:"+str(co_ppm)+"ppm",0,350);
  text(speed_ms+"m/s",0,680);
  
}
void drawRadarText(){
  text("distance from an object: "+distance+" at angle "+angle,750,300);
  text("",0,0);
}
void drawControlText(){
  text("V",30,400);
  text("R",30,500);
  
  text(str(int(rover_velocity)),250,380);
  text(str(int(rover_radius)),250,480);
  
}
