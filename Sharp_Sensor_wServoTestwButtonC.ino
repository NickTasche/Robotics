/*Control the left and right servos depending on the value returned from the Sharp sensor. If the value 
is over 400 the servos will move stop and if the value is less than 400 the servos will
move. This program also uses the millis function to only allow the readings to take place every 100 ms*/

#include <Servo.h>

Servo SERVO_LEFT;
Servo SERVO_RIGHT;
Servo SERVO_SWEEP;

const int SHARP_SENSOR_PIN = A1;
const int LEFT_SERVO_PIN = 11;
const int RIGHT_SERVO_PIN = 10;
const int SWEEP_SERVO_PIN = 12;
const int BUTTON = A5;              // push button for starting

boolean turnOnOff = 0;
int valButton;
unsigned long delayTime;

void setup()
{
  SERVO_LEFT.attach(LEFT_SERVO_PIN);
  SERVO_RIGHT.attach(RIGHT_SERVO_PIN);
  SERVO_SWEEP.attach(SWEEP_SERVO_PIN);
  Serial.begin(9600);
  delayTime = millis();
}

void loop()
{
  turnOnOff=readButton(); 
  int distance; // calls the function readButton to see if the button has been pressed(1)
  if(turnOnOff==1)            // check to see if the button value is 0, if it is continue
  {
    
    SERVO_SWEEP.write(180);
    
    if(millis() - delayTime > 100)
    {
        distance = analogRead(SHARP_SENSOR_PIN);
        Serial.println(distance);
        /*
        if (distance >400)
        {
          stopServos();
        }
        else
        {
          forwardServos();
        }
        */
        delayTime = millis();
    }

    if(millis() - delayTime >= 1000)
    { 
      delayTime = millis();
    }
   
    SERVO_SWEEP.write(30);
    if(millis() - delayTime > 100)
    {
        distance = analogRead(SHARP_SENSOR_PIN);
        Serial.println(distance);
         /*
        if (distance >400)
        {
          stopServos();
        }
        else
        {
          forwardServos();
        }
        */
        delayTime = millis();
    }
    while(millis() - delayTime > 1000)
    {
      delayTime = millis();
    }
    
  }
}

//********************************** SUBROUTINES ************************************
//***********************************************************************************
 
//************************************************************************************
void stopServos()
{ 
  SERVO_LEFT.write(1500);
  SERVO_RIGHT.write(1500);
}
//************************************************************************************
void forwardServos()
{ 
  SERVO_LEFT.write(1582);
  SERVO_RIGHT.write(1400);
}
//****************************************************************************************
//----------------------- Read the button ----------------------------------
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
//****************************************************************************************
