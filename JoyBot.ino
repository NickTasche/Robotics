/*
   Read the two axes of the joystick and display values. 
   */
#include <Servo.h>
Servo rightServo;
Servo leftServo;

const int LEFT_SERVO_PIN = 10;
const int RIGHT_SERVO_PIN = 11;

const long SERIAL_DATA_SPEED_9600_BPS = 9600;
     
 int JOYSTICK_X = A5;     // The analog pins the joystick is connected to
 int JOYSTICK_Y = A1; 
 
 
 int UDvalue;      // Readings from the joystick will be stored in 
 int LRvalue;      // UDvalue and LRvalue.     
 int UDmap;
 int LRmap;
 int dMapL;
 int dMapR; 
 
void setup()
{
    Serial.begin(SERIAL_DATA_SPEED_9600_BPS);
   leftServo.attach(LEFT_SERVO_PIN);
    rightServo.attach(RIGHT_SERVO_PIN);    
}

void loop()
{
        UDvalue = analogRead(JOYSTICK_Y);            // take a reading from the joystick
        LRvalue = analogRead(JOYSTICK_X);   
    
        Serial.print(" UDvalue= ");
        Serial.print(UDvalue);
        Serial.print("\t");
        Serial.print(" LRvalue= ");
        Serial.println(LRvalue);
        
       UDmap = map(UDvalue,0,1023,-100,100);
       LRmap = map(LRvalue,0,1023,-40,40);
      
      /* 
       Serial.println("");
       Serial.println("UDmap:");
       Serial.println(UDmap);
       Serial.println("");
       
       
       Serial.println("LRmap:");
       Serial.println(LRmap);
       Serial.println("");
       */

      if (UDmap >= 0)
        {
         if (LRmap <= 0)
           {
             dMapR = UDmap;
             dMapL = UDmap + LRmap;
           } 
          
           if (LRmap > 0)
           {
           dMapR = UDmap - LRmap;
           dMapL = UDmap;
           }   
        }
       
       if (UDmap < 0)
        {
         if (LRmap <= 0)
           {
             dMapR = UDmap;
             dMapL = UDmap - LRmap;
           } 
          
           if (LRmap > 0)
           {
           dMapR = UDmap + LRmap;
           dMapL = UDmap;
           }   
        }
       
       
       
       leftServo.write(map(dMapL,-100,100,1400,1600));   
       rightServo.write(map(dMapR,-100,100,1600,1400)); 
       
       
   //delay(1000);    
}



