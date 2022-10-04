/* This is a program for the robot to send IR data to another robot and to read IR data
coming from another robot. The robot will start with the red LED on for 1 second. When the\
red LED goes off and the green LED comes on the robot is ready to listen. When the button is 
pushed the sending robot will send the listenings robot address and data to make the listening
robot move.This robots address is 1A, so until the robot receives the data 1A it will not process any data.
Once it receives 1A the robot will do whatever data it receives, tells it to do.
*/

#include <Servo.h>

Servo rightServo;
Servo leftServo;

////////////////// Constants //////////////////////////////////////////
const int LINE_SENSOR_PIN = A1;      // Use analog pins A1-A4 for the sensors
const int BUTTON = A5;         // push button for starting
const int RIGHT_SERVO_PIN = 11;  //Right Servo attached to pin 11, Left to 10
const int LEFT_SERVO_PIN = 10;
const int IR_RCVR_PIN = 7;          //Sensor pin 1
const int IR_TX_PIN = 5;          //IR send LED
const int GREEN_LED = 3;
const int RED_LED = 4;

const int START_BIT_IN = 1500;         //Start bit threshold (Microseconds)
const int BIN_1 = 800;             //Binary 1 threshold (Microseconds)
const int BIN_0 = 400;              //Binary 0 threshold (Microseconds)
const int SND_START_BIT = 2400;     //Sending start bit(Microseconds)
const int SND_BIN_1 = 840;         //Sending Binary 1 Microseconds)
const int SND_BIN_0 = 440;          //Sending Binary 0 (Microseconds)

const byte ROBOT_ADDRESS = 0x21; // Address for this robot (constant)
const byte SENDING_ROBOT_ADDRESS = 0xE; // This is the address of the robot where the data is sent. 
const byte FORWARD_DATA = 0xc;
const byte REVERSE_DATA = 0x10;
const byte STOP_DATA = 0x11;
/////////////////////// Variables /////////////////////////////////////////
int LineSensor = 0;        // Initialize sensor storage variables to zero
int routineCount = 1;
int offDelay = 500;        // delay (microseconds)between IR data bit transmissions
int NumBits = 16;          // How much data is being listened for
int dataToMoveRobotForward = ((SENDING_ROBOT_ADDRESS << 8)+ (ROBOT_ADDRESS << 8) + (FORWARD_DATA));  // 16 bits of data
int dataToMoveRobotBackward = ((SENDING_ROBOT_ADDRESS << 8)+(REVERSE_DATA));  // 16 bits of data
int dataToStopRobot = ((SENDING_ROBOT_ADDRESS << 8)+(STOP_DATA));  // 16 bits of data

boolean turnOnOff = 0;    // stores the button value; 1 is on and 0 is off
int valButton;            // stores the analog reading of the button
int debug = 0;                  //Serial connection must be started to debug
int rcv_bits = 16;             // Number of data bits to receive
int snd_bits = 16;             // Number of data bits to send

unsigned long delayTime = 0;

/////////////////////////////////////////////////////////////////////////

void setup()
{
  rightServo.attach(RIGHT_SERVO_PIN);       // pins for servos
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.write(1500);                     //stop servos
  leftServo.write(1500);
  pinMode(IR_TX_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);   // Turn on Red LED
  delay(1000);
  digitalWrite(RED_LED, LOW);   // Turn off Red LED
  digitalWrite(GREEN_LED, HIGH);   // Turn on green LED
  delayTime = millis();
  Serial.begin(9600);
}
//////////////////////////////////////////////////////////////////////////

void loop()
{ 
    if(pulseIn(IR_RCVR_PIN, LOW, 50000) > START_BIT_IN)  //Check to see if there is a long low being received by the IR detector.
      {
        int key = getIRKey();         // if there is, than fetch it
        Serial.print("key = ");Serial.println(key &0xFFFFF,HEX);
        if (key != -1)
        {
         if (key >> 8 == ROBOT_ADDRESS) // if the correct robot address is sent, print out data received
         {
          if(lowByte(key) == 0x01) 
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
        Serial.print("dataToMoveRobotForward = ");
      Serial.println(dataToMoveRobotForward,HEX);
      SendNumber(dataToMoveRobotForward);        // Send 16 bits of data to the other robot 2 times 
      delay(50);                                 // Move forward for 2 seconds.
      SendNumber(dataToMoveRobotForward);
      delay(2000);
    
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
          }
          else if(lowByte(key) == 0x10) moveBackward();
          else if(lowByte(key) == 0x11) stopRobot();
          
         }
          
        }
        else
        {
          //turn on red LED
        }
      }
  turnOnOff = readButton();    // calls the function readButton to see if the button has been pressed(1)
  if (turnOnOff == 1)     // Active Button sends code to the robot
    {
      Serial.print("dataToMoveRobotForward = ");
      Serial.println(dataToMoveRobotForward,HEX);
      SendNumber(dataToMoveRobotForward);        // Send 16 bits of data to the other robot 2 times 
      delay(50);                                 // Move forward for 2 seconds.
      SendNumber(dataToMoveRobotForward);
      delay(2000);
      
      SendNumber(dataToStopRobot);        // Stop Robot
      delay(50);                     
      SendNumber(dataToStopRobot);
      delay(200);
      
      SendNumber(dataToMoveRobotBackward);      // Move backward for 2 seconds
      delay(50);                 
      SendNumber(dataToMoveRobotBackward);
      delay(2000);

      SendNumber(dataToStopRobot);        // Stop Robot 
      delay(50);                      
      SendNumber(dataToStopRobot);
      delay(200);
      
      turnOnOff = 0;
    }
}

////////////////////////////// Subroutines /////////////////////////////////////////////

//************************************************************************************

//----------------------- Read the button ----------------------------------
int readButton()
{
  unsigned long contactTime;               //local variable; contactTime declared
  valButton = analogRead(BUTTON);          // Read the pushbutton on an analog pin

  if (valButton > 512)                     // Since 5V will produce a value of 1023, > 512 means button not pushed
    return turnOnOff;                       // return the value of turnOnOff without changing it

  contactTime = millis();                  // set contactTime = to the millis() clock value
  while (valButton < 512)                     // while the pushbutton is pushed
  {
    valButton = analogRead(BUTTON);         // read the button value again and keep reading until valButton is less than 512
  }

  if (millis() - contactTime < 20)          // If the button is held for less than 20 ms
    return turnOnOff;                       // return the turnOnOff value unchanged

  return (1 - turnOnOff);                   // if the button is held longer than 20 ms then change the turnOnOff
  // to the opposite value to what it was
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++//
void SendNumber(long Number)
{
 boolean currentBit = 0;
 
 pulseIR(2400);
 delayMicroseconds(offDelay);
  
 for (int i=0; i < NumBits; i++)
 {
   currentBit = bitRead(Number, i);
   
   if(currentBit == 1)
   {
    pulseIR(SND_BIN_1);
    delayMicroseconds(offDelay); 
   }
   else
   {
    pulseIR(SND_BIN_0);
    delayMicroseconds(offDelay);     
   }
 }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++//
// Get IR key
int getIRKey() 
{
  int data[rcv_bits]; int i;
  for(i=0;i<rcv_bits;i++)         //Start measuring bits, I only want low pulses
  {
    data[i] = pulseIn(IR_RCVR_PIN, LOW);
  }

  if(debug == 1) 
    Serial.println("-----");
  
  for(i=0;i<rcv_bits;i++)         //Parse them
  {
    if (debug == 1)     
      Serial.println(data[i]);
    
    if(data[i] > BIN_1)       //is it a 1?    
      data[i] = 1;    
    else
    {
      if(data[i] > BIN_0)     //is it a 0?      
        data[i] = 0;      
      else       
        data[i] = 2;           //Flag the data as invalid; I don't know what it is!      
    }
  }

  for(i=0;i<rcv_bits;i++)         //Pre-check data for errors
  {
    if(data[i] > 1)     
      return -1;             //Return -1 on invalid data    
  }

  int result = 0;
  int seed = 1;
  for(i=0;i<rcv_bits;i++)         //Convert bits to integer
  {
    if(data[i] == 1)     
      result += seed;
    
    seed = seed * 2;
  }
  return result;            //Return key number
}
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
// This procedure sends a 38KHz pulse to the IRledPin
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs)
{
  // we'll count down from the number of microseconds we are told to wait
  cli();                                 // this turns off any background interrupts
  while (microsecs > 0)
  {
                                         // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(IR_TX_PIN, HIGH);          // this takes about 3 microseconds to happen
    delayMicroseconds(9);               // hang out for 10 microseconds, you can also change this to 9 if its not working
    digitalWrite(IR_TX_PIN, LOW);           // this also takes about 3 microseconds
    delayMicroseconds(9);               // hang out for 10 microseconds, you can also change this to 9 if its not working
                                         // so 26 microseconds altogether
    microsecs -= 26;
  }
  sei();                                 // this turns them back on
}
//*************************************************************************
void moveForward()
{
  leftServo.write(1600);
  rightServo.write(1400);
  delay(15);
}
//*************************************************************************
void moveBackward()
{
  leftServo.write(1400);
  rightServo.write(1600);
  delay(15);
}
//*************************************************************************
void stopRobot()
{
  leftServo.write(1500);
  rightServo.write(1500);
  delay(15);
}
