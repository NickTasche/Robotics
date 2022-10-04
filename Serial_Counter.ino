

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


// ledState used to set the LED
int ledState1 = LOW;
int ledState2 = LOW;
int ledState3 = LOW;
int ledState4 = LOW;


// will store last time LED was updated
unsigned long previousMillis1 = 0;

// interval
const long interval1 = 100;
char receivedChar;
int receivedInt;

boolean newData = false;
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

void setup() {
  // set the digital pin as output:
  pinMode(LEDPIN1, OUTPUT);
  pinMode(LEDPIN2, OUTPUT);
  pinMode(LEDPIN3, OUTPUT);

  Serial.begin(9600);
  Serial.println("Welcome to the LED control interface. Press anything to continue.");
   
  static byte sizeArray = 0;
  char endMarker = '\n';
  char rc;
   
  while (Serial.available() == 0) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[sizeArray] = rc;
            sizeArray++;
            if (sizeArray >= numChars) {
                sizeArray = numChars - 1;
            }
        }
        else {
            receivedChars[sizeArray] = '\0'; // terminate the string
            sizeArray = 0;    
        }
    }
}

void loop() {
  // create and set variable to millisecond counter
  unsigned long currentMillis = millis();
 Serial.println(" ");
 while (Serial.available() > 0 && receivedInt != '\n'){
  receivedChar = Serial.read();
  }
  
  switch (receivedChar) {
    case 'P':
     Serial.println("Printed P");
      break;

    case 'p':
     Serial.println("Printed p");
      break;
    
    case 2:
    Serial.println("Printed 2");
      break;
    
    default: 
        Serial.println("Enter 'P' to Pulse the LEDS in sequence");
        Serial.println("Enter 'F' to Flash all of them on and off repeatedly");
        //Serial.println(receivedChar);
    break;
  }
 
 while (Serial.available() == 0);
 receivedChar = Serial.read();
  


  
  /*
    // On/Off LED 1. Also updates previousMillis for end of cycle.
    if (currentMillis - previousMillis1 >= interval1){

      if (currentMillis - previousMillis1 <= interval8){
          ledState1 = HIGH;
      }

      if (currentMillis - previousMillis1 >=interval8){
          ledState1 = LOW;
          previousMillis1 = currentMillis;
      }
    }
  */

  digitalWrite(LEDPIN1, ledState1);
  digitalWrite(LEDPIN2, ledState2);
  digitalWrite(LEDPIN3, ledState3);


  // prints variables for On/Off conditions
  //Serial.println(previousMillis1);
  //Serial.println(currentMillis - previousMillis1);

}
