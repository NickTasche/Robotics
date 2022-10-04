
/*
Nick Tasche
1.18.2017
This program moves between different LED lighting sequences depending on how many times a button has been pushed. There are currently 4 states the LEDs can be in. 

*/

//init LEDs
const int RED_LED = 13;
const int BLUE_LED = 12;
const int GREEN_LED = 11;

//init Button
const int PUSH_BUTTON = 6;

//creates two variables to compare based of digitalRead of the button for press detection. Val updates count to continue the input loop.
int buttonState = 0;
int val = 0;
int count = 0;

//variable for millis()
unsigned long previousMillis1 = 0;

//delay variables for millis()
const long interval1 = 300;
const long interval2 = 600; 



void setup()
{
  //set pins for output
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  Serial.begin (9600);
  
  //set buttonState at beginning of sequence
  buttonState = digitalRead(PUSH_BUTTON);
}

void loop()
{
  //Main loop assigns which sequence will be used
  while (count < 4) 
  {
    //create var for millis()
    unsigned long currentMillis = millis();
    
    //update val for compare to buttonState
    val = digitalRead(PUSH_BUTTON);
    
    //Serial.println(count); For checking the loop.
    
    //updates count once button is released.
    if(val != buttonState)
    {
      if (buttonState == LOW)
      {
      count = count + 1;
      }
      
    }
    //first sequence - off
    if (count == 0)  
    {
      digitalWrite (RED_LED,LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite (BLUE_LED,LOW);
    }  
    
    //second sequence - one LED on constant
    if (count == 1)  
    {
      digitalWrite (RED_LED,HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite (BLUE_LED,LOW);
    }
    
    //third sequence - blinks single LED
    if (count == 2)  
    {
      if (currentMillis - previousMillis1 >= interval1)
      {
        digitalWrite (RED_LED,LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite (BLUE_LED,LOW);
      }
     
      if (currentMillis - previousMillis1 < interval1)
      {
        digitalWrite (RED_LED,LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite (BLUE_LED,LOW);
      }
      
      if (currentMillis - previousMillis1 >= interval2)
      {
        previousMillis1 = currentMillis;
      }
      
     }
    
    //fourth sequence blinks between two LEDS  
    if (count == 3)  
    {
      if (currentMillis - previousMillis1 >= interval1)
      {
        digitalWrite (RED_LED,LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite (BLUE_LED,LOW);
      }
     
      if (currentMillis - previousMillis1 < interval1)
      {
        digitalWrite (RED_LED,HIGH);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite (BLUE_LED,LOW);
      }
      
      if (currentMillis - previousMillis1 >= interval2)
      {
        previousMillis1 = currentMillis;
      }
    }
    
    //update buttonState for comparison
    buttonState = val;
    
    }
    //reset count for loop
    count = 0;

}
