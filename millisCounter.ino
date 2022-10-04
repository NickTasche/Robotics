

/*
 Nick Tasche
 1.5.2017
 This program lights a set of LEDs in sequence and then switches them off in reverse order.  
 
 I took my original millis() example from here:
 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */

// the number of the LED pin
const byte ledPin1 =  13;      
const byte ledPin2 =  12;
const byte ledPin3 =  11;
const byte ledPin4 =  10;

// ledState used to set the LED 
int ledState1 = LOW;       
int ledState2 = LOW;
int ledState3 = LOW;
int ledState4 = LOW;


// will store last time LED was updated
unsigned long previousMillis1 = 0;  

// interval at which to blink (milliseconds) 1.25 hz = 800
const long interval1 = 100; 
const long interval2 = 200;
const long interval3 = 300;
const long interval4 = 400;
const long interval5 = 500;
const long interval6 = 600;
const long interval7 = 700; 
const long interval8 = 800;

void setup() {
  // set the digital pin as output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // create and set variable to millisecond counter
  unsigned long currentMillis = millis();

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
  
  // On/Off LED 2
  if (currentMillis - previousMillis1 >= interval2){
      
    if (currentMillis - previousMillis1 <= interval7){ 
    ledState2 = HIGH;
    }
      
    if (currentMillis - previousMillis1 >= interval7){
    ledState2 = LOW;
    }
  }

  // On/Off LED 3
  if (currentMillis - previousMillis1 >= interval3){
      
    if(currentMillis - previousMillis1 <= interval6){ 
    ledState3 = HIGH;
    }
      
    if (currentMillis - previousMillis1 >= interval6){
    ledState3 = LOW;
    }
  }

    // On/Off LED 4
  if (currentMillis - previousMillis1 >= interval4){
      
    if(currentMillis - previousMillis1 <= interval5){ 
    ledState4 = HIGH;
    }
      
    if (currentMillis - previousMillis1 >= interval5){
    ledState4 = LOW;
    }
  }

  // set the LED with the ledState of the variable:
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
  digitalWrite(ledPin4, ledState4);

  // prints variables for On/Off conditions
  Serial.println(previousMillis1);
  Serial.println(currentMillis-previousMillis1);
 
}
