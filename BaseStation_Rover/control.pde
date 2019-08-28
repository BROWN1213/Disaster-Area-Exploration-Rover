public class HScrollbar {
  int swidth, sheight;    // width and height of bar
  float xpos, ypos;       // x and y position of bar
  float spos, newspos;    // x position of slider
  float sposMin, sposMax; // max and min values of slider
  int loose;              // how loose/heavy
  boolean over;           // is the mouse over the slider?
  boolean locked;
  float ratio;

  HScrollbar (float xp, float yp, int sw, int sh, int l) {
    swidth = sw;
    sheight = sh;
    int widthtoheight = sw - sh;
    ratio = (float)sw / (float)widthtoheight;
    xpos = xp;
    ypos = yp-sheight/2;
    spos = xpos + swidth/2 - sheight/2;
    newspos = spos;
    sposMin = xpos;
    sposMax = xpos + swidth - sheight;
    loose = l;
  }

  void update() {
    if (overEvent()) {
      over = true;
    } else {
      over = false;
    }
    if (mousePressed && over) {
      locked = true;
    }
    if (!mousePressed) {
      locked = false;
    }
    if (locked) {
      newspos = constrain(mouseX-sheight/2, sposMin, sposMax);
    }
    if (abs(newspos - spos) > 1) {
      spos = spos + (newspos-spos)/loose;
    }
  }

  float constrain(float val, float minv, float maxv) {
    return min(max(val, minv), maxv);
  }

  boolean overEvent() {
    if (mouseX > xpos && mouseX < xpos+swidth &&
       mouseY > ypos && mouseY < ypos+sheight) {
      return true;
    } else {
      return false;
    }
  }

  void display() {
    noStroke();
    fill(204);
    rect(xpos, ypos, swidth, sheight);
    if (over || locked) {
      fill(0, 0, 0);
    } else {
      fill(102, 102, 102);
    }
    rect(spos, ypos, sheight, sheight);
  }

  float getPos() {
    // Convert spos to be values between
    // 0 and the total width of the scrollbar
    //return spos * ratio;
    return 200*((spos-sposMin)/(sposMax-sposMin)-0.5);
    
  }
}  

  
public class VScrollbar
{
  int swidth, sheight;    // width and height of bar
  int xpos, ypos;         // x and y position of bar
  float spos, newspos;    // x position of slider
  int sposMin, sposMax;   // max and min values of slider
  int loose;              // how loose/heavy
  boolean over;           // is the mouse over the slider?
  boolean locked;
  float ratio;  
VScrollbar (int xp, int yp, int sw, int sh, int l) {
    swidth = sw;
    sheight = sh;
    int heighttowidth = sh - sw;
    ratio = (float)sh / (float)heighttowidth;
    xpos = xp-swidth/2;
    ypos = yp;
    spos = ypos + sheight/2 - swidth/2;
    newspos = spos;
    sposMin = ypos;
    sposMax = ypos + sheight - swidth;
    loose = l;
  }

  void update() {
    if(over()) {
      over = true;
    } else {
      over = false;
    }
    if(mousePressed && over) {
      locked = true;
    }
    if(!mousePressed) {
      locked = false;
    }
    if(locked) {
      newspos = constrain(mouseY-swidth/2, sposMin, sposMax);
    }
    if(abs(newspos - spos) > 1) {
      spos = spos + (newspos-spos)/loose;
    }
  }

  int constrain(int val, int minv, int maxv) {
    return min(max(val, minv), maxv);
  }

  boolean over() {
    if(mouseX > xpos && mouseX < xpos+swidth &&
    mouseY > ypos && mouseY < ypos+sheight) {
      return true;
    } else {
      return false;
    }
  }

  void display() {
    fill(204);
    rect(xpos, ypos, swidth, sheight);
    if(over || locked) {
      fill(0, 0, 0);
    } else {
      fill(102, 102, 102);
    }
    rect(xpos, spos, swidth, swidth);
  }

  float getPos() {
    // Convert spos to be values between
    // 0 and the total width of the scrollbar
    //return spos * ratio;
    return 200*((spos-sposMin)/(sposMax-sposMin)-0.5);
  }
}
  
void keyPressed(){
  
  if(key == CODED){
    if (keyCode == LEFT){
      hs.spos-=10;
    }
    if(keyCode == RIGHT){
      hs.spos+=10;      
    }
    if (keyCode == UP){
      vs.spos-=10;
    }
    if(keyCode == DOWN){
      vs.spos+=10;      
    }
    hs.spos = constrain(hs.spos, hs.sposMin, hs.sposMax);
    vs.spos = constrain(vs.spos, vs.sposMin, vs.sposMax);
    SendCommand(-(int)vs.getPos(),(int)hs.getPos());
    
  }
  
}

void SendCommand(int velocity,int radius){
    if(abs(velocity)<9)velocity=0;
    if(abs(radius)<9)radius=0;
    String cmd="4,"+velocity+","+radius+";\r\n";
    myPort.write(cmd);  
    println(cmd);

}

/*
public class Controller extends PApplet {
  

Button auto_button;  // the button
Button manu_button;  // the button


Button left0_button;  // the button
Button left1_button;  // the button
Button center_button;  // the button
Button right0_button;  // the button
Button right1_button;  // the button

Button savefile_button;  // the button
  
HScrollbar hs;  
VScrollbar vs; 

  Controller() {
    super();
    PApplet.runSketch(new String[] {this.getClass().getSimpleName()}, this);
  } 
  public void settings() {
    size(400, 250);
   
  }
  void setup() {
    background(80);
    smooth();
   buttonSetup();
   hs= new HScrollbar(width/2-20, height/2-8, width/2, 16, 16); 
   vs= new VScrollbar(width/2-40, height/4-44, 16,width/2, 16); 
}  
  public void draw() {
   
    buttonDraw();
    

    //hs.update();
    hs.display();
    
    //vs.update();
    vs.display();    
  }

  
void buttonSetup(){
  // create the button object

  auto_button = new Button("AUTO", 20, 75, 50, 30); 
  manu_button = new Button("MANU", 80, 75, 50, 30); 

  left0_button = new Button("<<", 170, 20, 30, 50);
  left1_button = new Button("<", 205, 20, 30, 50);
  center_button = new Button("O", 240, 20, 30, 50);
  right1_button = new Button(">", 275, 20, 30, 50);  
  right0_button = new Button(">>", 310, 20, 30, 50);
  savefile_button = new Button("SAVE LOG", 20, 20, 100, 30);
}
void buttonDraw(){
  // draw the button in the window

  auto_button.Draw(); 
  manu_button.Draw(); 

  //left0_button.Draw();
  //left1_button.Draw();
  //center_button.Draw();
  //right1_button.Draw();
  //right0_button.Draw();  
  savefile_button.Draw();  
}
// mouse button clicked
void mousePressed()
{


  if (auto_button.MouseIsOver()) {
    // print some text to the console pane if the button is clicked
    String cmd="3,0;\r\n";
    myPort.write(cmd);
  }  
  if (manu_button.MouseIsOver()) {
    // print some text to the console pane if the button is clicked
    String cmd="3,1;\r\n";
    myPort.write(cmd);
  }   
  
  if (left0_button.MouseIsOver()) {
    // print some text to the console pane if the button is clicked
    String cmd="5,-2;\r\n";
    myPort.write(cmd);
  } 
  if (left1_button.MouseIsOver()) {
    // print some text to the console pane if the button is clicked
    String cmd="5,-1;\r\n";
    myPort.write(cmd);
  } 
  if (center_button.MouseIsOver()) {
    // print some text to the console pane if the button is clicked
    String cmd="5,0;\r\n";
    myPort.write(cmd);
  } 
  if (right1_button.MouseIsOver()) {
    // print some text to the console pane if the button is clicked
    String cmd="5,1;\r\n";
    myPort.write(cmd);
  } 
  if (right0_button.MouseIsOver()) {
    // print some text to the console pane if the button is clicked
    String cmd="5,2;\r\n";
    myPort.write(cmd);
  }   
  if (savefile_button.MouseIsOver()) {
     //output.flush(); // Writes the remaining data to the file
     //output.close(); // Finishes the file
     println("save is not supported");
  } 

}

// the Button class
public class Button {
  String label; // button label
  float x;      // top left corner x position
  float y;      // top left corner y position
  float w;      // width of button
  float h;      // height of button
  
  // constructor
  Button(String labelB, float xpos, float ypos, float widthB, float heightB) {
    label = labelB;
    x = xpos;
    y = ypos;
    w = widthB;
    h = heightB;
  }
  
  void Draw() {
    fill(218);
    stroke(145);
    rect(x, y, w, h, 8);
    textAlign(CENTER, CENTER);
    fill(0);
    text(label, x + (w / 2), y + (h / 2));
  }
  
  boolean MouseIsOver() {
    if (mouseX > x && mouseX < (x + w) && mouseY > y && mouseY < (y + h)) {
      return true;
    }
    return false;
  }
}

  

  
void keyPressed(){
  
  if(key == CODED){
    if (keyCode == LEFT){
      hs.spos-=10;
    }
    if(keyCode == RIGHT){
      hs.spos+=10;      
    }
    if (keyCode == UP){
      vs.spos-=10;
    }
    if(keyCode == DOWN){
      vs.spos+=10;      
    }
    hs.spos = constrain(hs.spos, hs.sposMin, hs.sposMax);
    vs.spos = constrain(vs.spos, vs.sposMin, vs.sposMax);
    SendCommand(-(int)vs.getPos(),(int)hs.getPos());
    
  }
  
}

void SendCommand(int velocity,int radius){
    if(abs(velocity)<9)velocity=0;
    if(abs(radius)<9)radius=0;
    String cmd="4,"+velocity+","+radius+";\r\n";
    myPort.write(cmd);  
    println(cmd);

}
  
public class HScrollbar {
  int swidth, sheight;    // width and height of bar
  float xpos, ypos;       // x and y position of bar
  float spos, newspos;    // x position of slider
  float sposMin, sposMax; // max and min values of slider
  int loose;              // how loose/heavy
  boolean over;           // is the mouse over the slider?
  boolean locked;
  float ratio;

  HScrollbar (float xp, float yp, int sw, int sh, int l) {
    swidth = sw;
    sheight = sh;
    int widthtoheight = sw - sh;
    ratio = (float)sw / (float)widthtoheight;
    xpos = xp;
    ypos = yp-sheight/2;
    spos = xpos + swidth/2 - sheight/2;
    newspos = spos;
    sposMin = xpos;
    sposMax = xpos + swidth - sheight;
    loose = l;
  }

  void update() {
    if (overEvent()) {
      over = true;
    } else {
      over = false;
    }
    if (mousePressed && over) {
      locked = true;
    }
    if (!mousePressed) {
      locked = false;
    }
    if (locked) {
      newspos = constrain(mouseX-sheight/2, sposMin, sposMax);
    }
    if (abs(newspos - spos) > 1) {
      spos = spos + (newspos-spos)/loose;
    }
  }

  float constrain(float val, float minv, float maxv) {
    return min(max(val, minv), maxv);
  }

  boolean overEvent() {
    if (mouseX > xpos && mouseX < xpos+swidth &&
       mouseY > ypos && mouseY < ypos+sheight) {
      return true;
    } else {
      return false;
    }
  }

  void display() {
    noStroke();
    fill(204);
    rect(xpos, ypos, swidth, sheight);
    if (over || locked) {
      fill(0, 0, 0);
    } else {
      fill(102, 102, 102);
    }
    rect(spos, ypos, sheight, sheight);
  }

  float getPos() {
    // Convert spos to be values between
    // 0 and the total width of the scrollbar
    //return spos * ratio;
    return 200*((spos-sposMin)/(sposMax-sposMin)-0.5);
    
  }
}  

  
public class VScrollbar
{
  int swidth, sheight;    // width and height of bar
  int xpos, ypos;         // x and y position of bar
  float spos, newspos;    // x position of slider
  int sposMin, sposMax;   // max and min values of slider
  int loose;              // how loose/heavy
  boolean over;           // is the mouse over the slider?
  boolean locked;
  float ratio;  
VScrollbar (int xp, int yp, int sw, int sh, int l) {
    swidth = sw;
    sheight = sh;
    int heighttowidth = sh - sw;
    ratio = (float)sh / (float)heighttowidth;
    xpos = xp-swidth/2;
    ypos = yp;
    spos = ypos + sheight/2 - swidth/2;
    newspos = spos;
    sposMin = ypos;
    sposMax = ypos + sheight - swidth;
    loose = l;
  }

  void update() {
    if(over()) {
      over = true;
    } else {
      over = false;
    }
    if(mousePressed && over) {
      locked = true;
    }
    if(!mousePressed) {
      locked = false;
    }
    if(locked) {
      newspos = constrain(mouseY-swidth/2, sposMin, sposMax);
    }
    if(abs(newspos - spos) > 1) {
      spos = spos + (newspos-spos)/loose;
    }
  }

  int constrain(int val, int minv, int maxv) {
    return min(max(val, minv), maxv);
  }

  boolean over() {
    if(mouseX > xpos && mouseX < xpos+swidth &&
    mouseY > ypos && mouseY < ypos+sheight) {
      return true;
    } else {
      return false;
    }
  }

  void display() {
    fill(204);
    rect(xpos, ypos, swidth, sheight);
    if(over || locked) {
      fill(0, 0, 0);
    } else {
      fill(102, 102, 102);
    }
    rect(xpos, spos, swidth, swidth);
  }

  float getPos() {
    // Convert spos to be values between
    // 0 and the total width of the scrollbar
    //return spos * ratio;
    return 200*((spos-sposMin)/(sposMax-sposMin)-0.5);
  }
}
  
  
  
}

*/
