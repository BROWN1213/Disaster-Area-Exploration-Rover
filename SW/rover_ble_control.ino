/*
#define J_MIN 0
#define J_MAX 100
#define J_STEP 25


SoftwareSerial bleJoystick(4,5);

void setupJoystick(){
  bleJoystick.begin(9600);
  //Serial.println("test start");

}

void loopJoystick(){

 
  if(bleJoystick.available()){
        
   char data= bleJoystick.read();
   //Serial.print("data; ");
   //Serial.write(data);
   //Serial.print(" ");
    
   
    switch(data){
      case 'A':  //ON

        break;
  
      case 'B':  //OFF
        break;
      case 'C':  // C~K left/right
        joy_raduis=-J_MAX;
        break;
      case 'D':
        joy_raduis=-(J_MIN+3*J_STEP);
        break;
     case 'E':
        joy_raduis=-(J_MIN+2*J_STEP);
        break;
      case 'F':
        joy_raduis=-(J_MIN+J_STEP);
        break;
      case 'G':
        joy_raduis=J_MIN;
        break;
      case 'H':
        joy_raduis=(J_MIN+J_STEP);
        break;
      case 'I':
        joy_raduis=(J_MIN+2*J_STEP);
        break;
      case 'J':
        joy_raduis=(J_MIN+3*J_STEP);
        break;
      case 'K':
        joy_raduis=J_MAX;
        break;
  
      case 'L':  // L~T foward/backward
       joy_velocity=-J_MAX;
       break;
      case 'M':
        joy_velocity=-(J_MIN+3*J_STEP);
        break;
      case 'N':
        joy_velocity=-(J_MIN+2*J_STEP);
        break;
      case 'O':
        joy_velocity=-(J_MIN+J_STEP);
        break;
      case 'P':
        joy_velocity=J_MIN;
        break;
      case 'Q':
        joy_velocity=(J_MIN+J_STEP);
        break;
      case 'R':
        joy_velocity=(J_MIN+2*J_STEP);
        break;
      case 'S':
        joy_velocity=(J_MIN+3*J_STEP);
        break;
      case 'T':
        joy_velocity=J_MAX;
        break;
      default :
        return;
         
      
        
      }//end switch case

    // send velocity and radius to Lx16A
    sendcommand(joy_velocity,joy_raduis);
      
    Serial.print("V:");
    Serial.print(joy_velocity);

    Serial.print("   R:");
    Serial.println(joy_raduis);
    
  }
  

}
*/
