      /* This program will make the robot go forward for 2 revolutions and then stop*/
      #include <Servo.h>
      const int BUTTON = A5;              // push button for starting
      const int RIGHT_SERVO = 10;
      const int LEFT_SERVO = 11;
      Servo leftServo;
      Servo rightServo;
      int valButton;
      int turnOnOff=0;  // the val of the pull up button is set to zero to start with
     

      
      volatile int Lindex = 0;
      
      void setup()
      {
        attachInterrupt(0,ltEncoderInterrupt,CHANGE);
        Serial.begin(9600); 
        leftServo.attach(LEFT_SERVO);
        rightServo.attach(RIGHT_SERVO);
        
        halt();
        
      }
      void loop()
      { Serial.println(turnOnOff);
        turnOnOff=readButton();      // calls the function readButton to see if the button has been pressed(1)
        
        if(turnOnOff==1)
        { 
          
          delay(500);        
          forward(126);
          halt();
          
          delay(500);
          backward(126);
          halt();
          
          
          delay(500);  
          leftTurn(108);
          halt();
        
          delay(500);
          rightTurn(104);
          halt();

          turnOnOff = 0;
         
        }
        
        else
        {
          halt();       
        }
       }

      void forward(int distanceCount)
      {      
          leftServo.write(1582);
          rightServo.write(1400);
          while (Lindex < distanceCount)
          {           
          }
          Lindex = 0;
      }


      void backward(int distanceCount)
      {
         leftServo.write(1420);
         rightServo.write(1592);
          while (Lindex < distanceCount)
          {           
          }
          Lindex = 0;
      }

      void rightTurn(int angleCount)
      {
         leftServo.write(1400);
         rightServo.write(1400);
         while (Lindex < angleCount)
          {           
          }
          Lindex = 0;
      }


      void leftTurn(int angleCount)
      {
         leftServo.write(1585);
         rightServo.write(1585);
         while (Lindex < angleCount)
          {           
          }
          Lindex = 0;
      }
      void halt()
      {
         leftServo.write(1500);
         rightServo.write(1500);  
        
      }
      /************* Subroutine for reading the button switch********************/
      int readButton()
      {
        unsigned long contactTime;               //local variable; contactTime declared
        valButton=analogRead(BUTTON);            // Read the pushbutton on an analog pin
        if(valButton>512)                        // Since 5V will produce a value of 1023, < 512 means button not pushed
         return turnOnOff;                       // return the value of turnOnOff without changing it
        contactTime=millis();                    // set contactTime = to the millis() clock value
        while(valButton<=512)
        {                   // while the pushbutton is pushed
          valButton=analogRead(BUTTON);           // read the button value again and keep reading until valButton is less than 512
        } 
        if(millis()-contactTime<20)               // If the button is held for less than 20 ms
         return turnOnOff;                       // return the turnOnOff value unchanged
         return(1-turnOnOff);                      // if the button is held longer than 20 ms then change the turnOnOff
                                                 // to the opposite value to what it was
      } 
      /////////////////////////////////////////////////////////////////////////////
      
      /******************ISR for wheel count**************************************/
      void ltEncoderInterrupt()
      {        
        Lindex++;
      }
      ///////////////////////////////////////////////////////////////////////////////
