
void drawText(){  
  fill(0,0,0);
  textSize(25); 
  text("Sat Num:"+num_sat,0,100);
  text("GPS Location:"+lat+","+lng+","+alt,0,150);
  text("PM2.5:"+pm2_5+" ppm",0,200);
  text(velocity+" Km",0,680);
}
