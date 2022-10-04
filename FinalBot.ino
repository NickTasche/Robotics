/*
Nick Tasche
March 15, 2017

This program follows a black line using the bottom mounted 6 sensor array. It uses the center two sensors to keep in aligned and two of the outer sensors to check for intersections in the tape. 
It is designed to turn or stop based on the intersection counter in order to make it to the end of the course and back. 

The program also uses the servo mounted IR scanner to avoid obstacles by sensing which direction the robot should move avay from the course to avoid the blockage. The code then returns the bot back to the tape where it continues.

Finally, and well see if I ever get this working. Robot should stop at the end of the first lef of the course, send and receive information to a Control Panel and then make its way back on the second leg. 
*/

#include <Servo.h>
#include <math.h>

//Creates Servo Objects
Servo rightServo;
Servo leftServo;
Servo SERVO_SWEEP;

//Consts for pin assigments
const int Left_Sensor=A3;
const int Left_Center_Sensor=A2;
const int Right_Center_Sensor=A1;
const int Right_Sensor=A0;
const int SHARP_SENSOR_PIN = A4;
const int GREEN_LED = 3;            
const int RED_LED = 4;      
const int SWEEP_SERVO_PIN = 12;
const int LEFT_SERVO_PIN = 10;
const int RIGHT_SERVO_PIN = 11;
const int BUTTON = A5;

//distance to object in front of robot
const int LIMIT = 550; 

//vars for distance readings from from sensor
int lDistance= analogRead(SHARP_SENSOR_PIN);
int rDistance= analogRead(SHARP_SENSOR_PIN);
int distance= analogRead(SHARP_SENSOR_PIN);

//vars for bottom mounted sensor
int LeftSensor=0;
int LeftCenterSensor=0;
int RightCenterSensor=0;
int RightSensor=0;

//counts intersections in tape
int intersectionCounter = 0;

//vars for start button
unsigned long delayTime=0;
boolean turnOnOff = 0;
int valButton;

//interrupt counter
volatile int Lindex = 0;

/*************************************************************************************************************/

void setup()
{
  delayTime = millis();
  Serial.begin(9600);
  
  //ISR
  attachInterrupt(0,ltEncoderInterrupt,CHANGE);
  
  //pin assignments
  SERVO_SWEEP.attach(SWEEP_SERVO_PIN);
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);
  
  //stop/center servos
  leftServo.write(1500);
  rightServo.write(1500);
  SERVO_SWEEP.write(90);
  
  // Set all the LED pins to outputs
  pinMode (GREEN_LED, OUTPUT);   
  pinMode (RED_LED, OUTPUT);
  redLED_On();
}

/*************************************************************************************************************/

void loop()
{
  //calls the function readButton to see if the button has been pressed(1)
  turnOnOff=readButton();  
  
  //Serial.println(turnOnOff);
  delayTime = millis(); 
  
  // check to see if the button value is 0, if it is continue
  if(turnOnOff==1)           
  {

     greenLED_On();
     
     if (millis() - delayTime < 50)
     {
      //reads botton sensors
       readSensors();
      //checks for object in front of robot
      sharpScan();
     
     }
     
     /*
     Serial.print (LeftSensor);
     Serial.print("  ");
     Serial.print (LeftCenterSensor);
     Serial.print("  ");
     Serial.print (RightCenterSensor);
     Serial.print("  ");
     Serial.println (RightSensor);
     */
     
     //prints sensor info at junctions
     if (LeftSensor > 400 && RightSensor > 400)
     {
      ++intersectionCounter;   
      //Serial.println(intersectionCounter);
      Serial.print (LeftSensor);
      Serial.print("  ");
      Serial.print (LeftCenterSensor);
      Serial.print("  ");
      Serial.print (RightCenterSensor);
      Serial.print("  ");
      Serial.println (RightSensor);
       
      //first count moves the bot away from start line and on its own to the rest of the course
      if (intersectionCounter == 1)
      {
       stopServos();
       delay(500);
        
       forwardCount(110);
       stopServos();
       delay(500);
        
       rotateRight90CCW(27);
       stopServos();
       delay(500);
        
       forwardCount(90);
       stopServos();
       delay(500);
       }
        
      // turns robot right at intersection
      if (intersectionCounter == 3)
      {
       rotateLineSkip();
       
       rotateRight45CCW();
       
       readSensors();
       delay(300);
        
       centerBotRight();
      }
       
      // turns robot around at end of course
      if (intersectionCounter == 4)
      {
       rotate180CCW();
       delay(300);
        
       readSensors();
       centerBotLeft();
      }

      //turns robot left at junction
      if (intersectionCounter == 5)
       {
        rotateLineSkip();
        rotateLeft45CCW();
       
        readSensors();
        delay(300);
        
        centerBotLeft();
       }

      //unless intersection counter is at specific count - skip line to continue along course  
      else
       {
        rotateLineSkip();
       }

      }
      
     // unless prompted for action - move robot forward along line    
     else
     {
      leftServoMove();
      rightServoMove();
     }
      
     delayTime = millis(); 
     
    }
    
    else
    {
    redLED_On();
    stopServos();
    }
  }

/*************************************************************************************************************/
// reads buttom sensors
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

/*************************************************************************************************************/
//button read function
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

/*************************************************************************************************************/
//default track following servo control

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

/*************************************************************************************************************/
// move forward or backward a specific distance or move continuously 
void forwardCount(int distanceCount)
{      
  leftServo.write(1582);
  rightServo.write(1410);
  Lindex = 0;
  while (Lindex < distanceCount)
  {
    Serial.println(Lindex);           
  }
  
}

void backwardCount(int distanceCount)
{
  leftServo.write(1420);
  rightServo.write(1589); 
  Lindex = 0;
  while (Lindex < distanceCount)
  {           
  }
 
}

void stopServos()
{ 
  leftServo.write(1500);
  rightServo.write(1500);
}

void forwardServos()
{ 
  leftServo.write(1590);
  rightServo.write(1410);
}

/*************************************************************************************************************/
//Rotation fucntions
void rotateRight45CCW()
{ 
  for (int i = 0; i < 17; i++)
  {
    leftServo.write(1600);
    rightServo.write(1600);
    delay(15);
  }
}

void rotateLeft45CCW()
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

void rotateLeft90CCW(int distanceCount)
{      
  leftServo.write(1400);
  rightServo.write(1400);
  Lindex = 0;
  while (Lindex < distanceCount)
  {           
  }
 
}

void rotateRight90CCW(int distanceCount)
{      
  leftServo.write(1600);
  rightServo.write(1600);
  Lindex = 0;
  while (Lindex < distanceCount)
  {           
  }
  
}

/*************************************************************************************************************/
//rotates robot until it recenters the bottom sensors on the line
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

/*************************************************************************************************************/
//moves forward a specific distance for bottom senseors to miss lines.
 void rotateLineSkip()
{ 
  for (int i = 0; i < 10; i++)
  {
    leftServo.write(1580);
    rightServo.write(1410);
    delay(15);
  }
}

void rotateLineSkipTwo()
{ 
  for (int i = 0; i < 15; i++)
  {
    leftServo.write(1580);
    rightServo.write(1410);
    delay(15);
  }
}


/******************ISR for wheel count**************************************/
void ltEncoderInterrupt()
{        
 Lindex++;
}
     


/*************************************************************************************************************/
void sharpScan()
{
   distance = analogRead(SHARP_SENSOR_PIN);
   if (distance > LIMIT) 
      {
        Serial.println("");
        Serial.println(distance);
        Serial.println("");
        
         stopServos(); 
   
          delay(300);   
    
   // Serial.println(millis()-delayTime);
   delayTime = millis();
   while(millis() - delayTime <= 703)
  {   
      SERVO_SWEEP.write(175);
      
     if(millis() - delayTime >= 700)
    { 
     
      lDistance = analogRead(SHARP_SENSOR_PIN);
      
      Serial.println("Left       Right");
      Serial.print(lDistance);
      Serial.print("          ");
      Serial.println(rDistance);
    //Serial.println(millis()-delayTime);
      Serial.println("");
    
      delayTime = 0;
     
    }
  }
  
   
   
   // Serial.println(delayTime);
  // Serial.println(millis()-delayTime);
   //Serial.println("");
    
  
  delayTime = millis();
  while(millis() - delayTime <= 703)
  {
    SERVO_SWEEP.write(5);
   
   if(millis() - delayTime >= 700)
    { 
      
      rDistance = analogRead(SHARP_SENSOR_PIN);
       
      Serial.println("Left       Right");
    
      Serial.print(lDistance);
      Serial.print("          ");
      Serial.println(rDistance);
      
      Serial.println("");
      
     //Serial.println(millis()-delayTime);
     delayTime = 0;
     }
     
    }
  
        SERVO_SWEEP.write(90); //return to center
        delay(100);
        compareDistance();
      }
  

}

void compareDistance()
{ 
  Serial.println("Left       Right");   
  Serial.print(lDistance);
      Serial.print("          ");
      Serial.println(rDistance);
    //Serial.println(millis()-delayTime);
      Serial.println("");
      
  if (rDistance > 350 && lDistance > 350)//if they are equally obstructed
  {
    Serial.println("It's a Trap!");
    Serial.println("");
    stopServos();
    delay(400);
  //  reverseSpecific();
    stopServos();
    delay(400);
    rotate180CCW();
    stopServos();
    delay(400);
    
  }
  else if (lDistance<rDistance) //if left is less obstructed 
  {
    Serial.println("Go Left");
     Serial.println("");
     stopServos();
    delay(400);
    rotateLeft90CCW(26);
      stopServos();
    forwardCount(70);
     stopServos();
    delay(400);
    rotateRight90CCW(25);
    stopServos();
    forwardCount(100);
     stopServos();
    delay(400);
     rotateRight90CCW(25);
    stopServos();
   forwardServos();
    while (  LeftSensor < 400 && RightSensor < 400)
    {
     readSensors();
     forwardServos();
     //delay(15);
    }
     stopServos();
     delay(400);
     rotateLineSkipTwo();
    rotateLeft90CCW(5);
    stopServos();
     delay(400);   
    readSensors();
    delay(400);
  
    centerBotLeft();
    
  }
  else if (rDistance<lDistance) //if right is less obstructed
  {
    Serial.println("Go Right");
    Serial.println("");
    stopServos();
    delay(400);
   rotateRight90CCW(26);
    stopServos();
    delay(400);
   forwardCount(70);
    stopServos();
    delay(400);
     rotateLeft90CCW(25);
      stopServos();
    forwardCount(100);
     stopServos();
    delay(400);
     rotateLeft90CCW(25);
      stopServos();
     while (  LeftSensor < 400 && RightSensor < 400)
    {
      readSensors();
     forwardServos();
      //delay(15);
    }
    
     stopServos();
     delay(400);
     rotateLineSkipTwo();
     rotateRight90CCW(5);
     stopServos();
     delay(400); 
    readSensors();
    delay(400); 
    centerBotRight();
  }
  
   else  //If there doesn't seem to be anything in the way
  {
    Serial.println("Tally Ho!");
    Serial.println("");
    readSensors();
    //leftServoMove();
   // rightServoMove();
  }
}



//************************************************************************************
void redLED_On()
{
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
}
//************************************************************************************
void greenLED_On()
{
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
}
