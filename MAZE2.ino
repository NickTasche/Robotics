#include <Servo.h>

Servo rightServo;
Servo leftServo;
Servo SERVO_SWEEP;


const int SHARP_SENSOR_PIN = A1;
const int LEFT_SERVO_PIN = 11;
const int RIGHT_SERVO_PIN = 10;
const int SWEEP_SERVO_PIN = 12;
const int BUTTON = A5;      
const int LIMIT = 500;  
int lDistance= analogRead(SHARP_SENSOR_PIN);
int rDistance= analogRead(SHARP_SENSOR_PIN);
int distance= analogRead(SHARP_SENSOR_PIN);

boolean turnOnOff = 0;
int valButton;
unsigned long delayTime;

void setup() {
  // put your setup code here, to run once:
  SERVO_SWEEP.attach(SWEEP_SERVO_PIN);
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);
  Serial.begin(9600);
  delayTime = millis();
  SERVO_SWEEP.write(90);
   
}

void loop() 
{
  // put your main code here, to run repeatedly:

   
  turnOnOff=readButton();  // calls the function readButton to see if the button has been pressed(1)
  //Serial.println(turnOnOff);
  if(turnOnOff==1)            // check to see if the button value is 0, if it is continue
  {

   if(millis() - delayTime > 100)
    {

      distance = analogRead(SHARP_SENSOR_PIN);

      if (distance < LIMIT) //if path is clear
      {
        forwardServos();
      }
      else //if path is blocked
      {
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
    delayTime = millis();
    }
  }
}

//*************************************************************************************************************
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

//*************************************************************************************************************
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
    reverseSpecific();
    stopServos();
    delay(400);
    rotateLeft180CCW();
    stopServos();
    delay(400);
    
  }
  else if (lDistance<rDistance) //if left is less obstructed 
  {
    Serial.println("Go Left");
     Serial.println("");
    rotateLeft90CCW();
  }
  else if (rDistance<lDistance) //if right is less obstructed
  {
    Serial.println("Go Right");
    Serial.println("");
   rotateRight90CCW();
  }
  
   else  //If there doesn't seem to be anything in the way
  {
    Serial.println("Tally Ho!");
    Serial.println("");
    forwardServos();
  }
}

//********************************** SUBROUTINES ************************************
//***********************************************************************************
 
//************************************************************************************
void stopServos()
{ 
  leftServo.write(1500);
  rightServo.write(1500);
}
//************************************************************************************
void forwardServos()
{ 
  leftServo.write(1590);
  rightServo.write(1410);
}

//************************************************************************************
void backwardServos()
{ 
  for (int i = 0; i < 40; i++)
  {
    leftServo.write(1420);
    rightServo.write(1592);
    delay(15);
  }
  

}
//************************************************************************************
void rotateLeft90CCW()
{ 
  for (int i = 0; i < 35; i++)
  {
    leftServo.write(1400);
    rightServo.write(1400);
    delay(15);
  }
}

void rotateRight90CCW()
{ 
  for (int i = 0; i < 35; i++)
  {
    leftServo.write(1580);
    rightServo.write(1580);
    delay(15);
  }
}

void rotateLeft180CCW()
{ 
  for (int i = 0; i < 60; i++)
  {
    leftServo.write(1400);
    rightServo.write(1400);
    delay(15);
  }
}
//************************************************************************************
void reverseSpecific()
{ 
  for (int i = 0; i < 100; i++)
  {
    leftServo.write(1420);
    rightServo.write(1592);
    delay(15);
  }
}

