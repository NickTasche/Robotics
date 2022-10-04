/*
Nick Tasche
2.15.2017
      
This program does the following: the robot stops when it is 5 inches away from an object, waits for 1
second, then back up 8 inches and rotates 90 degrees. The robot will only start after the button is pushed and after a .5 second delay.
      
*/

#include <Servo.h>

//Declare Servos
Servo SERVO_LEFT;
Servo SERVO_RIGHT;
Servo SERVO_SWEEP;

//Constants for Pin Assignments
const int SHARP_SENSOR_PIN = A1;
const int LEFT_SERVO_PIN = 11;
const int RIGHT_SERVO_PIN = 10;
const int SWEEP_SERVO_PIN = 12;
const int BUTTON = A5;        

//button state for starting/stopping
boolean turnOnOff = 0;
int valButton;

unsigned long delayTime;

//counter for lenth of movement/turns
volatile int Lindex = 0;

void setup() {
  // interrupt for wheel rorations
  attachInterrupt(0,ltEncoderInterrupt,CHANGE);
  
  //assigns servos to pins
  SERVO_SWEEP.attach(SWEEP_SERVO_PIN);
  SERVO_LEFT.attach(LEFT_SERVO_PIN);
  SERVO_RIGHT.attach(RIGHT_SERVO_PIN);
  
  
  Serial.begin(9600);
  delayTime = millis();
  
  //Keeps front Servo straight
  SERVO_SWEEP.write(90);
  halt();
   
}

void loop() {
  
   turnOnOff=readButton();      // calls the function readButton to see if the button has been pressed(1)
  Lindex = 0;    
  if(turnOnOff==1)
  { 
    int distance = analogRead(SHARP_SENSOR_PIN);
  
    //loop that keeps bot moving forward until it is within 8inches of barrier.
    delay(500);
    while(distance < 290)
    {
    distance = analogRead(SHARP_SENSOR_PIN);
    Serial.println(distance);
    forward();
    Lindex = 0;
    }
  
  halt();
  delay(1000);
  backward(110);
  
  halt();
  delay(500);
  turn(20);
  delay(500);
  
  }
  
 halt();
 delay(500);
}

   /************* Subroutine for reading the button switch********************/
      int readButton()
      {
        unsigned long contactTime;               //local variable; contactTime declared
        valButton=analogRead(BUTTON);            // Read the pushbutton on an analog pin
        if(valButton>512)                        // Since 5V will produce a value of 1023, < 512 means button not pushed
         return turnOnOff;                       // return the value of turnOnOff without changing it
        contactTime=millis();                    // set contactTime = to the millis() clock value
        while(valButton<=512)
        {                   // while the pushbutton is pushed
          valButton=analogRead(BUTTON);           // read the button value again and keep reading until valButton is less than 512
        } 
        if(millis()-contactTime<20)               // If the button is held for less than 20 ms
         return turnOnOff;                       // return the turnOnOff value unchanged
         return(1-turnOnOff);                      // if the button is held longer than 20 ms then change the turnOnOff
                                                 // to the opposite value to what it was
      } 
      /////////////////////////////////////////////////////////////////////////////
      
      /******************ISR for wheel count**************************************/
      void ltEncoderInterrupt()
      {        
        Lindex++;
      }
      ///////////////////////////////////////////////////////////////////////////////
      
      //moves bot forwards forever
      void forward()
      {
       SERVO_LEFT.write(1582);
       SERVO_RIGHT.write(1400);
      }
      
      //stops bot
       void halt()
      {
       SERVO_LEFT.write(1500);
       SERVO_RIGHT.write(1500);
      }
      
      //turns bot to degree specified in function call
       void turn(int angleCount)
      {
         SERVO_LEFT.write(1580);
         SERVO_RIGHT.write(1580);
         while (Lindex < angleCount)
          {           
          }
          Lindex = 0;
      }
      
      //moves bot backward to degree specified in function call
      void backward(int distanceCount)
      {
         SERVO_LEFT.write(1420);
         SERVO_RIGHT.write(1592);
          while (Lindex < distanceCount)
          {           
          }
          Lindex = 0;
      }
