#include <Servo.h>

Servo leftServo;
Servo rightServo;

int PUSH_BUTTON = 9;
byte buttonState;

void setup()
{
  Serial.begin(9600);
  leftServo.attach(11);
  rightServo.attach(10);
  while (digitalRead(PUSH_BUTTON) == HIGH)
  {
    Serial.println("Button is High");
    leftServo.write(1500);
    rightServo.write(1500);
    delay(15);
  }
  delay(500);
  for (int counter =0; counter < 500; counter = counter + 1){
    leftServo.write(1590);
    rightServo.write(1404);
    delay(15);
  }
    leftServo.write(1500);
    rightServo.write(1500);
    delay(15);
}
void loop()
{
  
}

