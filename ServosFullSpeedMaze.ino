/*
Nick Tasche
1.25.2017
This program tells the robot, on button push, to pause and then to move forward at full speed until the IR sensor receives a value that it interprets as dark.
It pauses again and moves backward at full speed for three feet.

*/

#include <Servo.h>

//defines servos as type
Servo leftServo;
Servo rightServo;

//defines button input pin and variable for input detection
int PUSH_BUTTON = 9;
byte buttonState;

void setup()
{
  Serial.begin(9600);

  //specifies output pin for servos
  leftServo.attach(10);
  leftServo.write(1500);
  delay(15);
  rightServo.attach(11);
  rightServo.write(1500);
  delay(15);

  //button press detection. Pauses robot until button is pressed.
  while (digitalRead(PUSH_BUTTON) == HIGH)
  {
    Serial.println("Button is High");
    leftServo.write(1500);
    rightServo.write(1500);
    delay(15);
  }
  
  delay(500);

  for (int counter =0; counter < 270; counter = counter + 1)
  {
    rightServo.write(1428);
    leftServo.write(1563);
    delay(15);
  }

 
  leftServo.write(1500);
  rightServo.write(1500);
  delay(15);

   for (int counter =0; counter < 100; counter = counter + 1)
  {
    rightServo.write(1530);
    leftServo.write(1530);
    delay(15);
  }

  leftServo.write(1500);
  rightServo.write(1500);
  delay(15);

 for (int counter =0; counter < 310; counter = counter + 1)
  {
    rightServo.write(1428);
    leftServo.write(1563);
    delay(15);
  }
 
  leftServo.write(1500);
  rightServo.write(1500);
  delay(15);

   for (int counter =0; counter < 110; counter = counter + 1)
  {
    rightServo.write(1470);
    leftServo.write(1470);
    delay(15);
  }

  leftServo.write(1500);
  rightServo.write(1500);
  delay(15);

  for (int counter =0; counter < 80; counter = counter + 1)
  {
    rightServo.write(1428);
    leftServo.write(1563);
    delay(15);
  }
  leftServo.write(1500);
  rightServo.write(1500);
  delay(15);

 for (int counter =0; counter < 110; counter = counter + 1)
  {
    rightServo.write(1470);
    leftServo.write(1470);
    delay(15);
  }
  leftServo.write(1500);
  rightServo.write(1500);
  delay(15);
  for (int counter =0; counter < 310; counter = counter + 1)
  {
    rightServo.write(1428);
    leftServo.write(1563);
    delay(15);
  }
 
  leftServo.write(1500);
  rightServo.write(1500);
  delay(15);
   for (int counter =0; counter < 100; counter = counter + 1)
  {
    rightServo.write(1530);
    leftServo.write(1530);
    delay(15);
  }

  leftServo.write(1500);
  rightServo.write(1500);
  delay(15);
    for (int counter =0; counter < 230; counter = counter + 1)
  {
    rightServo.write(1428);
    leftServo.write(1563);
    delay(15);
  }

 
  leftServo.write(1500);
  rightServo.write(1500);
  delay(15);
}

void loop()
{
  
}

