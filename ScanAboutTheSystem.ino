#include <Servo.h>

Servo SERVO_LEFT;
Servo SERVO_RIGHT;
Servo SERVO_SWEEP;

const int SHARP_SENSOR_PIN = A1;
const int LEFT_SERVO_PIN = 11;
const int RIGHT_SERVO_PIN = 10;
const int SWEEP_SERVO_PIN = 12;
const int BUTTON = A5;        

boolean turnOnOff = 0;
int valButton;
unsigned long delayTime;

void setup() {
  // put your setup code here, to run once:
  SERVO_SWEEP.attach(SWEEP_SERVO_PIN);
  Serial.begin(9600);
  delayTime = millis();
   SERVO_SWEEP.write(90);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  int lDistance= analogRead(SHARP_SENSOR_PIN);
  int rDistance= analogRead(SHARP_SENSOR_PIN);
   
  turnOnOff=readButton();      // calls the function readButton to see if the button has been pressed(1)
  if(turnOnOff==1)            // check to see if the button value is 0, if it is continue
  {
  
  delayTime = millis();
    
  while(millis() - delayTime <= 1000)
  {
   if(millis() - delayTime >= 1000)
    { 
      SERVO_SWEEP.write(130);
      lDistance = analogRead(SHARP_SENSOR_PIN);
      Serial.println("Left       Right");
     
      Serial.print(rDistance);
      Serial.print("          ");
      Serial.println(lDistance);
   // Serial.println(millis()-delayTime);
      Serial.println("");
      
     delayTime = 0;
     }
     
    }
   
   delayTime = millis();  
   
   while(millis() - delayTime <= 1003)
  {   
     if(millis() - delayTime >= 1000)
    { 
      SERVO_SWEEP.write(50);
      
      
      
      rDistance = analogRead(SHARP_SENSOR_PIN);
      Serial.println("Left       Right");
     
     Serial.print(rDistance);
      Serial.print("          ");
      Serial.println(lDistance);
     // Serial.println(millis()-delayTime);
      Serial.println("");
      
      delayTime = 0;
     
    }
  }
  
  //delayTime = millis();
  
  }
  
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
