#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;
int counter = 0;

void setup() {  
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  Serial.begin(9600);
  Braccio.begin();
  Braccio.ServoMovement(20, 90,  90, 90, 90,  90,  73);
}

void loop() {
  /*
  Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
  M1=base degrees. Allowed values from 0 to 180 degrees
  M2=shoulder degrees. Allowed values from 15 to 165 degrees
  M3=elbow degrees. Allowed values from 0 to 180 degrees
  M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
  M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
  M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */
 if(Serial.available()){
   char c = Serial.read();
   switch (c)
   {
      case 'R': pickRight(false); break;
      case 'L': pickLeft(false); break;
      case 'Z': pickLeft(true); break;
      case 'A' : pickRight(true); break;
      default: break;
   }
 }
}

void pickRight(bool isBottle){
  if(isBottle){
    bottlePickRight();
    bottleStorage();
  }
  else{
    boxPickRight();
    boxStorage();
  }
  delay(1000);
}

void pickLeft(bool isBottle){
  if(isBottle){
    bottlePickLeft();
    bottleStorage();
  }
  else{
    boxPickLeft();
    boxStorage();
  }
  delay(1000);
}

void bottlePickRight(){
  Braccio.ServoMovement(20, 90,  90, 90, 90,  90,  73);
  Braccio.ServoMovement(20, 90,  90, 0, 70,  0,  10);
  Braccio.ServoMovement(20, 90,  70, 0, 70,  0,  73);
}

void boxPickRight(){
  Braccio.ServoMovement(20, 90,  90, 90, 90,  90,  73);
  Braccio.ServoMovement(20, 90,  45, 30, 0,  0,  10);
  Braccio.ServoMovement(20, 90,  45, 30, 10,  0,  73);
}

void bottlePickLeft(){
  Braccio.ServoMovement(20, 180,  90, 90, 90,  90,  73);
  Braccio.ServoMovement(20, 180,  90, 0, 70,  0,  10);
  Braccio.ServoMovement(20, 180,  70, 0, 70,  0,  73);
  delay(1000);
}

void boxPickLeft(){
  Braccio.ServoMovement(20, 180,  90, 90, 90,  90,  73);
  Braccio.ServoMovement(20, 180,  90, 0, 70,  0,  10);
  Braccio.ServoMovement(20, 180,  70, 0, 70,  0,  73);
  delay(1000);
}

void bottleStorage(){
  Braccio.ServoMovement(20, 30,  90, 90, 90,  90,  73);
  Braccio.ServoMovement(20, 30,  45, 50, 50,  0,  73);
  Braccio.ServoMovement(20, 30,  45, 50, 50,  0,  10);
  delay(1000);
}

void boxStorage(){
  Braccio.ServoMovement(20, 0,  90, 90, 90,  90,  73);
  Braccio.ServoMovement(20, 0,  45, 50, 50,  0,  73);
  Braccio.ServoMovement(20, 0,  45, 50, 50,  0,  10);
  delay(1000);
}