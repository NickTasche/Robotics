//robot is using the 2 middle sensors of the QTR8-A sensor Array
//from Pololu. This code will read and display the values for the 
//readings on the Display
#include <Servo.h>
#include <math.h>

Servo rightServo;
Servo leftServo;

const int Left_Sensor=A3;
const int Left_Center_Sensor=A2;
const int Right_Center_Sensor=A1;
const int Right_Sensor=A0;

const int LEFT_SERVO_PIN = 10;
const int RIGHT_SERVO_PIN = 11;
const int BUTTON = A5;      

int LeftSensor=0;
int LeftCenterSensor=0;
int RightCenterSensor=0;
int RightSensor=0;
int intersectionCounter = 0;


unsigned long delayTime=0;
boolean turnOnOff = 0;
int valButton;

//////////////////////////////////////

void setup()
{
  delayTime = millis();
  Serial.begin(9600);
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);
  leftServo.write(1500);
  rightServo.write(1500);
}
///////////////////////////////////////////////////

void loop()
{
  
  turnOnOff=readButton();  // calls the function readButton to see if the button has been pressed(1)
  
  //Serial.println(turnOnOff);
  delayTime = millis(); 
  if(turnOnOff==1)            // check to see if the button value is 0, if it is continue
  {

  
    if (millis() - delayTime < 50)
    {
      readSensors();
      /*
      Serial.print (LeftSensor);
      Serial.print("  ");
      Serial.print (LeftCenterSensor);
      Serial.print("  ");
      Serial.print (RightCenterSensor);
      Serial.print("  ");
      Serial.println (RightSensor);
      */
   
      if (  LeftSensor > 400 && RightSensor > 400)
      {
       ++intersectionCounter;   
       Serial.println(intersectionCounter);
       
       
       if (intersectionCounter == 3)
       {
        rotateLineSkip();
        rotateRight90CCW();
       
     
        readSensors();
        delay(300);
        centerBotRight();
        
        }
       
       if (intersectionCounter == 4)
       {
    
        rotate180CCW();
        delay(300);
        readSensors();
        centerBotLeft();
        }

          if (intersectionCounter == 5)
       {
        rotateLineSkip();
        rotateLeft90CCW();
       
     
        readSensors();
        delay(300);
        centerBotLeft();
        
        }

        else
        {
          rotateLineSkip();
        }

      }
         
     else
     {
      leftServoMove();
      rightServoMove();
     }
      
    delayTime = millis(); 
    } 
    //delay(300);
  }
}
//////////////////////////////////////////////////////
void readSensors()
{
  LeftSensor=analogRead(Left_Sensor);
  delayMicroseconds(200);
  LeftCenterSensor=analogRead(Left_Center_Sensor);
  delayMicroseconds(200);
  RightCenterSensor=analogRead(Right_Center_Sensor);
  delayMicroseconds(200);
  RightSensor=analogRead(Right_Sensor);
  delayMicroseconds(200);
}

int readButton()
{
   unsigned long contactTime;               //local variable; contactTime declared
   valButton=analogRead(BUTTON);            // Read the pushbutton on an analog pin

   if(valButton>512)                        // Since 5V will produce a value of 1023, > 512 means button not pushed
     return turnOnOff;                       // return the value of turnOnOff without changing it
     
   contactTime=millis();                    // set contactTime = to the millis() clock value
   while(valButton<=512)                   // while the pushbutton is pushed
   {
     valButton=analogRead(BUTTON);           // read the button value again and keep reading until valButton is less than 512
   }
   
   if(millis()-contactTime<20)               // If the button is held for less than 20 ms
     return turnOnOff;                       // return the turnOnOff value unchanged
   
   return(1-turnOnOff);                      // if the button is held longer than 20 ms then change the turnOnOff
                                           // to the opposite value to what it was
}

void leftServoMove()
{
 int lServoPrint = map(RightCenterSensor,0,650,1500,1580);
 //Serial.println("");
// Serial.println(lServoPrint);
// Serial.println("");
 leftServo.write(map(RightCenterSensor,0,650,1500,1580));
 

}

void rightServoMove()
{
 int rServoPrint = map(LeftCenterSensor,0,650,1500,1410);
 //Serial.println("");
// Serial.println(rServoPrint);
// Serial.println("");
 rightServo.write(map(LeftCenterSensor,0,650,1500,1410));
 

}

void rotateRight90CCW()
{ 
  for (int i = 0; i < 17; i++)
  {
    leftServo.write(1600);
    rightServo.write(1600);
    delay(15);
  }
}

void rotateLeft90CCW()
{ 
  for (int i = 0; i < 17; i++)
  {
    leftServo.write(1400);
    rightServo.write(1400);
    delay(15);
  }
}

void rotate180CCW()
{ 
  for (int i = 0; i < 40; i++)
  {
    leftServo.write(1400);
    rightServo.write(1400);
    delay(15);
  }
}

void centerBotLeft()
{
   while (LeftCenterSensor < 150 || RightCenterSensor < 150)
        {
          readSensors();
          leftServo.write(1400);
          rightServo.write(1400);
          delay(15);
         }
  
}

void centerBotRight()
{
   while (LeftCenterSensor < 150 || RightCenterSensor < 150)
        {
          readSensors();
          leftServo.write(1600);
          rightServo.write(1600);
          delay(15);
         }
  
}

  void forwardLineSkip()
{ 
  for (int i = 0; i < 15; i++)
  {
    leftServo.write(1580);
    rightServo.write(1410);
    delay(15);
  }
}

 void rotateLineSkip()
{ 
  for (int i = 0; i < 10; i++)
  {
    leftServo.write(1580);
    rightServo.write(1410);
    delay(15);
  }
}


