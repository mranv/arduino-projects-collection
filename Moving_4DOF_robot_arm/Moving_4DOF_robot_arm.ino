#include <MotorControl.h>
#include <Servo.h>
#include <PS2X_lib.h>  //for v1.6

#define PS2_DAT        13  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

//servo name part
int servoPin9 = 9;
int servoPin8 = 8;
int servoPin7 = 7;
int servoPin6 = 6;
Servo servo;  
Servo servo4; //servo name
Servo servo3;
Servo servo2;
Servo servo1;

int s4=90;  //65+- min , 100+- max //servo4 (gripper)
int s3=120; //70+- min , 180+- max //servo3 (right) 
int s2=120; //30+- min , 160+- max //servo2 (left)
int s1=90;  //0 +- min , 180+- max //servo1 (bottom) 

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false
MotorControl motorleft  (2,3,1,'H');
MotorControl motorright (4,5,1,'H');

PS2X ps2x; // create PS2 Controller Class

int error = 0;
byte type = 0;
byte vibrate = 0;

void setup() {

  Serial.begin(57600);
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //  Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
 //declare servo pin
   servo4.attach(9);
   servo3.attach(8);
   servo2.attach(7);
   servo1.attach(6); 
//let the servo go to the original position  
   servo4.write(s4); 
   servo3.write(s3);
   servo2.write(s2); 
   servo1.write(s1);
   delay(50); 
}

void loop() {

  if (error == 1) //skip loop if no controller found
    return;
  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

    if (ps2x.Button(PSB_START))
      Serial.println("Start is being held");
    else if (ps2x.Button(PSB_SELECT)){
      Serial.println("Select is being held");
    }
    if (ps2x.Button(PSB_PAD_UP))
    {
      Serial.println("UP");
      motorleft.speed(-255);
      motorright.speed(-255);
    }
    else if (ps2x.Button(PSB_PAD_RIGHT))
    {
      Serial.println("RIGHT");
      motorleft.speed(-255);
      motorright.speed(255);
    }
    else if (ps2x.Button(PSB_PAD_LEFT))
    {
      Serial.println("LEFT");
      motorleft.speed(255);
      motorright.speed(-255);
    }
    else if (ps2x.Button(PSB_PAD_DOWN))
    {
      Serial.println("DOWN");
      motorleft.speed(255);
      motorright.speed(255);
    }
    else
    {
      motorleft.speed(0);
      motorright.speed(0);
    }
    //arm part
    if(ps2x.Analog(PSS_LY)<50)
      {
        Serial.println(s1);
      s1-=5; 
        if (s1<=0)
        {
         s1=0;         
        } 
        servo1.write(s1);
        delay(10);
      }
     else if(ps2x.Analog(PSS_LY) > 250)
      {
          s1+=8;
          Serial.println(s1);      
        if(s1>140)
        {
          s1=140;     
        }
        servo1.write(s1);
        delay(10);
      }
     else if(ps2x.Analog(PSS_LX) <50)
      {
          Serial.println(s2);
      s2-=10; 
        if (s2<30)
        {  
         s2=30;      
        } 
        servo2.write(s2);
        delay(10);
      }
     else if(ps2x.Analog(PSS_LX) >250)
      {
          Serial.println(s2);
      s2+=8;
        if(s2>170)
        {          
          s2=170;
        }
        servo2.write(s2);
        delay(10);
      }
      
      else if(ps2x.Analog(PSS_RY) <50)
      {
          Serial.println(s4);
        s4+=10;  
        if(s4>100)
        {
          s4=100;
        }
        servo4.write(s4);
        delay(10);
      }
     else if(ps2x.Analog(PSS_RY) >200)
      {
          Serial.println(s4);
        s4-=10;
        if (s4<50)
        {
         s4=50;
         
        } 
        servo4.write(s4);
        delay(10);
      }
      else if(ps2x.Analog(PSS_RX) <50)
      {
        Serial.println(s3);
        s3-=8; 
        if (s3<40)
        {
         s3=40;
        } 
        servo3.write(s3);
        delay(10);
      }
      else if(ps2x.Analog(PSS_RX) >200)
      {
        Serial.println(s3);
        s3+=10;  
        if(s3>180)
        {
          s3=180;
        }
        servo3.write(s3);
        delay(10);
      }

  }
  delay(50);
}

/*
  else if(ps2x.Button(PSB_L2))
     {
       motorleft.speed(-250);
     }
  else if(ps2x.Button(PSB_R2))
      {
       motorright.speed(-250);
     }
  else if(ps2x.Button(PSB_L1))
     {
       motorleft.speed(250);
     }
  else if(ps2x.Button(PSB_R1))
      {
       motorright.speed(250);
     }
*/
