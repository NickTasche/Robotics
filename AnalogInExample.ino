
/*
 
  When the program first starts, there will be no readings taken and the red LED will be on.
  With the first button push the readings begin and will be displayed on the Monitor screen, 
  depending on the value the sensor reads.
*/  

const int SWITCH_PIN = 7; 
const int RED_LED1 = 12;
const int GREEN_LED1 = 13;
const int GREEN_LED2 = 11;
const int RED_LED2 = 10;
int val;
int val2;
int val3;
int buttonState;                
int buttonPresses = 0;                               //initial "buttonPresses" = 0
//int RED_LED = 3;                                     //Red LED pin 6
//int GREEN_LED = 5;                                   //Green LED pin 7


void setup() {

  pinMode(RED_LED1, OUTPUT);                          //Red LED output  
  pinMode(GREEN_LED1, OUTPUT);                        //Green LED output
  pinMode(RED_LED2, OUTPUT);                          //Red LED output  
  pinMode(GREEN_LED2, OUTPUT);                        //Green LED output
  pinMode(SWITCH_PIN, INPUT);                        //Push button input
  
  Serial.begin(9600);
  buttonState = digitalRead(SWITCH_PIN); 
  
}


void loop() {
  
  buttonState = val;                // buttonState is a global variable,
  int sensorValue = analogRead(A3); // whereas sensorValue is a local variable. Why?
  
  val = digitalRead(SWITCH_PIN);  
      
  if (val != buttonState) 
  {          
    if (val == LOW) 
    {                
      buttonPresses = buttonPresses + 1;                                   //Pressing button increases "buttonPresses"
    }
  }
  
  if (buttonPresses==0)                                 //Program starts with red LED on
  { 
    digitalWrite (RED_LED1, HIGH);
    digitalWrite (GREEN_LED1, LOW);
    digitalWrite (RED_LED2, LOW);
    digitalWrite (GREEN_LED2, LOW);
  }
  
  else if (buttonPresses==1)                                 //First button push
  {   
    digitalWrite (RED_LED1, LOW);
    digitalWrite (GREEN_LED1, HIGH);
    Serial.println( 265-(sensorValue/2));
    
    if (sensorValue > 500)
    {
      analogWrite (RED_LED2,(sensorValue/2));
      analogWrite (GREEN_LED2, LOW);
    }
    
    if (sensorValue <= 500)
    {
      analogWrite (GREEN_LED2, (265-(sensorValue/2)));
      analogWrite (RED_LED2, LOW);
    }
  }    
  else if (buttonPresses > 1) buttonPresses = 0;                   //Second button push resets program
}
