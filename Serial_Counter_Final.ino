

/*
  Nick Tasche
  1.5.2017
  This program lights a set of LEDs in sequence and then switches them off in reverse order.

  I took my original millis() example from here:
  http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
*/

// the number of the LED pin
const byte LEDPIN1 =  13;
const byte LEDPIN2 =  12;
const byte LEDPIN3 =  11;
const byte LEDPIN4 =  10;


// ledState used to set the LED
int ledState1 = LOW;
int ledState2 = LOW;
int ledState3 = LOW;
int ledState4 = LOW;


// will store last time LED was updated
unsigned long previousMillis1 = 0;

// interval
const long interval1 = 500;

//variable for Serial.read
char receivedChar;
int receivedInt;

void setup() {
  // set the digital pin as output:
  pinMode(LEDPIN1, OUTPUT);
  pinMode(LEDPIN2, OUTPUT);
  pinMode(LEDPIN3, OUTPUT);
  pinMode(LEDPIN4, OUTPUT);
  

  Serial.begin(9600);
  Serial.println("Welcome to the LED control interface.");  
}

void loop() {
 Serial.println(" ");
 while (Serial.available() > 0 && receivedInt != '\n'){
  receivedChar = Serial.read();
  }
  
  switch (receivedChar) {
    case 'P':
     Serial.println("How many cycles? 1 min -- 5 max");
     
     while (Serial.available() == 0);
     receivedInt= Serial.read();

     if (receivedInt < '0' || receivedInt>= '6'){
      Serial.println(" ");
      Serial.println("Returned to start");
      Serial.println("Enter 'P' to Pulse the LEDS in sequence");
      Serial.println("Enter 'F' to Flash all of them on and off repeatedly");
     }
    
     
    else {
     receivedInt = receivedInt - 48;
     
     for (int i = 0; i < receivedInt; i = i + 1)
      {        
        digitalWrite (LEDPIN1, HIGH);
        digitalWrite (LEDPIN2, LOW);
        digitalWrite (LEDPIN3, LOW);
        delay(interval1);
        digitalWrite (LEDPIN1, LOW);
        digitalWrite (LEDPIN2, HIGH);
        digitalWrite (LEDPIN3, LOW);
        delay(interval1);
        digitalWrite (LEDPIN1, LOW);
        digitalWrite (LEDPIN2, LOW);
        digitalWrite (LEDPIN3, HIGH);
        delay(interval1);
        digitalWrite (LEDPIN1, LOW);
        digitalWrite (LEDPIN2, HIGH);
        digitalWrite (LEDPIN3, LOW);
        delay(interval1);
        digitalWrite (LEDPIN1, HIGH);
        digitalWrite (LEDPIN2, LOW);
        digitalWrite (LEDPIN3, LOW);
        delay(interval1);
        digitalWrite (LEDPIN1, LOW);
        digitalWrite (LEDPIN2, LOW);
        digitalWrite (LEDPIN3, LOW);
        delay(interval1);
      } 

   
      Serial.println(" ");
      Serial.println("Enter 'P' to Pulse the LEDS in sequence");
      Serial.println("Enter 'F' to Flash all of them on and off repeatedly");
     }
      break;

    case 'p':
    Serial.println("How many cycles? 1 min -- 5 max");
     
     while (Serial.available() == 0);
     receivedInt= Serial.read();

     if (receivedInt < '0' || receivedInt>= '6'){
      Serial.println(" ");
      Serial.println("Returned to start");
      Serial.println("Enter 'P' to Pulse the LEDS in sequence");
      Serial.println("Enter 'F' to Flash all of them on and off repeatedly");
     }
    
     
    else {
     receivedInt = receivedInt - 48;
     
     for (int i = 0; i < receivedInt; i = i + 1)
      {        
        digitalWrite (LEDPIN1, HIGH);
        digitalWrite (LEDPIN2, LOW);
        digitalWrite (LEDPIN3, LOW);
        delay(interval1);
        digitalWrite (LEDPIN1, LOW);
        digitalWrite (LEDPIN2, HIGH);
        digitalWrite (LEDPIN3, LOW);
        delay(interval1);
        digitalWrite (LEDPIN1, LOW);
        digitalWrite (LEDPIN2, LOW);
        digitalWrite (LEDPIN3, HIGH);
        delay(interval1);
        digitalWrite (LEDPIN1, LOW);
        digitalWrite (LEDPIN2, HIGH);
        digitalWrite (LEDPIN3, LOW);
        delay(interval1);
        digitalWrite (LEDPIN1, HIGH);
        digitalWrite (LEDPIN2, LOW);
        digitalWrite (LEDPIN3, LOW);
        delay(interval1);
        digitalWrite (LEDPIN1, LOW);
        digitalWrite (LEDPIN2, LOW);
        digitalWrite (LEDPIN3, LOW);
        delay(interval1);
      } 

   
      Serial.println(" ");
      Serial.println("Enter 'P' to Pulse the LEDS in sequence");
      Serial.println("Enter 'F' to Flash all of them on and off repeatedly");
     }
      break;
    
    case 'F':
    Serial.println("How many cycles? 1 min -- 5 max");
     
     while (Serial.available() == 0);
     receivedInt= Serial.read();

    if (receivedInt < '0' || receivedInt>= '6'){
      Serial.println(" ");
      Serial.println("Returned to start");
      Serial.println("Enter 'P' to Pulse the LEDS in sequence");
      Serial.println("Enter 'F' to Flash all of them on and off repeatedly");
     }

    else {
    receivedInt = receivedInt - 48;
    for (int i = 0; i < receivedInt; i = i + 1)
        {        
        digitalWrite (LEDPIN1, HIGH);
        digitalWrite (LEDPIN2, HIGH);
        digitalWrite (LEDPIN3, HIGH);
        digitalWrite (LEDPIN4, LOW);
        delay(interval1);
        digitalWrite (LEDPIN1, LOW);
        digitalWrite (LEDPIN2, LOW);
        digitalWrite (LEDPIN3, LOW);
        digitalWrite (LEDPIN4, LOW);
        delay(interval1);
        }
   
       Serial.println(" ");
      Serial.println("Enter 'P' to Pulse the LEDS in sequence");
      Serial.println("Enter 'F' to Flash all of them on and off repeatedly");
      }   
      break;
    case 'f':
    Serial.println("How many cycles? 1 min -- 5 max");
     
     while (Serial.available() == 0);
     receivedInt= Serial.read();

 if (receivedInt < '0' || receivedInt>= '6'){
      Serial.println(" ");
      Serial.println("Returned to start");
      Serial.println("Enter 'P' to Pulse the LEDS in sequence");
      Serial.println("Enter 'F' to Flash all of them on and off repeatedly");
     }

  else {
    receivedInt = receivedInt - 48;
    for (int i = 0; i < receivedInt; i = i + 1)
        {        
        digitalWrite (LEDPIN1, HIGH);
        digitalWrite (LEDPIN2, HIGH);
        digitalWrite (LEDPIN3, HIGH);
        digitalWrite (LEDPIN4, LOW);
        delay(interval1);
        digitalWrite (LEDPIN1, LOW);
        digitalWrite (LEDPIN2, LOW);
        digitalWrite (LEDPIN3, LOW);
        digitalWrite (LEDPIN4, LOW);
        delay(interval1);
        }
 
       Serial.println(" ");
      Serial.println("Enter 'P' to Pulse the LEDS in sequence");
      Serial.println("Enter 'F' to Flash all of them on and off repeatedly");
       }  
      break;
    
    default: 
        Serial.println("Enter 'P' to Pulse the LEDS in sequence");
        Serial.println("Enter 'F' to Flash all of them on and off repeatedly");
        
    break;
  }
 
 while (Serial.available() == 0);
 receivedChar = Serial.read();
  


  


  digitalWrite(LEDPIN1, ledState1);
  digitalWrite(LEDPIN2, ledState2);
  digitalWrite(LEDPIN3, ledState3);
  digitalWrite(LEDPIN4, ledState3);
  



}
