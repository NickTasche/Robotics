

#include <Servo.h>
const long SERIAL_DATA_SPEED_9600_BPS = 9600;
     
int JOYSTICK_X = A5;     // The analog pins the joystick is connected to
int JOYSTICK_Y = A1; 

Servo rightServo;
Servo leftServo;

const int LEFT_SERVO_PIN = 10;
const int RIGHT_SERVO_PIN = 11;
 
int UDvalue;      // Readings from the joystick will be stored in 
int LRvalue;      // UDvalue and LRvalue.     
 
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

   int UDmap = map(UDvalue,0,1023,-100,100);
   int LRmap = map(LRvalue,0,1023,-100,100);
        
   Serial.print("\t");
   Serial.print(" UDvalue= ");
   Serial.print(UDmap);
   Serial.print(" ");
   Serial.print(" LRvalue= ");
   Serial.println(LRmap);
        
   moveRobot(LRmap, UDmap);

}

//*************** Calculate motor values **************************************************      
void moveRobot (int valueX, int valueY)//subroutine to send pulses to the correct servo.
{
  //Use the X direction to set the forward and backward motion
  int leftMotorVal = valueY;
  int rightMotorVal = valueY;
  
  //Apply the X as a "twist" effect. (about 40% of the calculated value)
  if (valueY >= 40)
  {
    leftMotorVal = leftMotorVal + (valueX * 4)/10;
    rightMotorVal = rightMotorVal - (valueX * 4)/10;
  }
  
 else if (valueY <= -40)
  {
    leftMotorVal = leftMotorVal - (valueX * 4)/10;
    rightMotorVal = rightMotorVal + (valueX * 4)/10;
  }

  else
  {
    if (valueX <= 0)
    {
    leftMotorVal = 0;
    }
     
    else
    {
    rightMotorVal = 0;
    }
     
  }
    leftMotorVal = constrain(leftMotorVal,-100,100);
    rightMotorVal =constrain(rightMotorVal,-100,100);

    //Serial.print("\t");
    Serial.print("leftMotorVal=");
    Serial.print(leftMotorVal);
    Serial.print(" ");
    Serial.print("rightMotorVal=");
    Serial.print(rightMotorVal);
    //Serial.print("\t");
    SendNewMotorValues(leftMotorVal,rightMotorVal);
}

//*************** Map and Drive Servos **************************************************      
void SendNewMotorValues(int valueL, int valueR)
{
   leftServo.write(map(valueL,-100,100,70,110));   
   rightServo.write(map(valueR,-100,100,110,70)); 
   Serial.print("\t");
   Serial.print("ValL=");
   Serial.print(map(valueL,-100,100,70,110));
   Serial.print("  ");
   Serial.print("ValR=");
   Serial.print(map(valueR,-100,100,110,70));
}

