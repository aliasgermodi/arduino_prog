/* YourDuino Arduino Board TEST 
 Tests all Arduino I/O and Analog pins for Source and Sink ability
 Tests Analog Read on A0..A5
 terry@yourduino.com 
 
 This test assumes that pins 0 (RX Data) and 1 (TX Data) are OK
 if programs can be loaded, and that pin 13 is OK if it's attached LED
 can be blinked. Pin 13 is not tested for current sink ability.
 
 Test progress and pass-fail results are sent to the Serial Monitor.
 At the end of test, Pin 13 LED is blinked very slowly 
 for Pass and quickly for Fail.
 
 This test works with a "Test Shield" that is plugged on top
 of the Arduino under test. This shield has a common isolated 
 connection point. The Common Point has 17 220 ohm resistors 
 connected to every digital pin from 2 to 12, and to every analog
 pin from 0 to 5. It also has two 100,000 ohm resistors which 
 connect it to Ground and +5.0 volts, forming a voltage divider
 that sets the common point to 2.50 volts when all pins are in
 the reset high-impedance input condition. This is read by A0 to
 initially test if any of the pins are "stuck" or "leaking", which 
 will pull the common point away from 2.50 volts
 
 Next, pins 3 thru A5 are tested by setting them High or Low against
 an opposite load presented by pin 2. Each pin must be able to
 source and sink at least 10 ma to bring the common point near 2.50 volts.
 If pin 2 fails, all other pins will fail. 
 
 Next, A0 thru A5 are tested individually with voltages near 1.66, 2.50, 3.33volts
 and possibly others, using the resistors connected to the digital pins to
 make various voltage dividers. 
 
 This design and software is licensed under a Creative Commons 
 Attribution-Noncommercial-Share Alike 3.0 License:
 http://creativecommons.org/licenses/by-nc-sa/3
 */

/*-----( Import needed libraries )-----*/
#include <LED.h>    // Easy HAL blink routines

/*-----( Declare Constants )-----*/

const  int    FirstDigPort =  3;  //Pin 2 is used as reference
const  int    LastDigPort  =  12;
const  int    FirstAnaPort =  15;
const  int    LastAnaPort  =  19;
const  int    A2D_Delay    =  10; //ms delay for A-D to settle

const  float  LowStuckResultOK     =  2.40 ; 
const  float  HighStuckResultOK    =  2.60 ;   
const  float  LowVoltResultOK      =  2.30 ;    
const  float  HighVoltResultOK     =  2.70 ;   

/*-----( Declare objects )-----*/
LED  LED13(13);        // The only LED we can blink!

/*-----( Declare Variables )-----*/

int    DigPort2Test;
int    AnaPort2Test;
int    IntVoltsRead;      // Result of AnalogRead 0..1023
float  FloatVoltsRead;    // Result of AnalogRead 0.0 .. 5.0
int    Failure;          // Count failures that occur
byte   FailArray[20];    // Save Pass-Fail during a test
int    FailArrayPtr;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  delay(500);
  Serial.begin(9600);
  delay(500);
  Serial.println("Arduino Board Test V1.08");
  Serial.println("YourDuino.com terry@yourduino.com");
  delay(500);
  LED13.blink(300, 4);  // "HI" in Morse code
  delay(500);  
  LED13.blink(300, 2);  

}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  Failure = 0;
  Serial.println();  
  Serial.println("--- TEST START ---");
  
//-------------( TEST 1 )---------------------------------------------
  Serial.println("TEST 001 - Any stuck pins??");
  delay(500);
  IntVoltsRead = analogRead(A0);
  FloatVoltsRead = a2d2float (IntVoltsRead);
  Serial.print("VoltsRead = ");
  Serial.print(FloatVoltsRead,2);  

  if (FloatVoltsRead > LowStuckResultOK
    &&  FloatVoltsRead < HighStuckResultOK)
  {
    Serial.println("  -- OK!");
  }
  else
  {
    Failure ++;
    Serial.println("  ** STUCK OR LEAKY PIN FAIL ** ");    
  }

//-----------------------( TEST 2 )--------------------------------
  Serial.println();    
  Serial.println("TEST 002 - Digital Pins Source Current");  
  pinMode(2, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(2, LOW);              // Connect Low Load  
  FailArrayPtr    =  0 ;

  //---------( Write the Digital Pin Labels )---------------
  WriteDigitalPinLabels();

  //------( Loop thru pins, testing )-----------  
  for (  DigPort2Test = FirstDigPort; 
         DigPort2Test <= LastDigPort;
         DigPort2Test ++)
  {//Loop thru Source Tests
    FailArrayPtr ++ ;

    pinMode(DigPort2Test, OUTPUT);      // Set tested pin to Output mode
    digitalWrite(DigPort2Test, HIGH);  // Pin Sources current HIGH     
    delay(A2D_Delay);
    IntVoltsRead = analogRead(A0);
    FloatVoltsRead = a2d2float (IntVoltsRead);
    pinMode(DigPort2Test, INPUT);      // ReSet tested pin to Input mode   

    Serial.print(FloatVoltsRead,2);  
    Serial.print("   ");      

    if (FloatVoltsRead > LowVoltResultOK
      &&  FloatVoltsRead < HighVoltResultOK)
    {
      FailArray[FailArrayPtr]  = 0;      
    }
    else
    {
      Failure ++;   
      FailArray[FailArrayPtr]  = 1;
    }        

  }//END Loop thru Source Tests

  Serial.println();  

  //--------( Write the Digital Pin PASS-FAIL Strings )----------------------  
  WriteDigitalPassFail();


//--------------------( TEST 3 )----------------------------------------

  Serial.println("TEST 003 - Digital Pins Sink Current");  
  pinMode(2, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(2, HIGH);              // Connect HIGH Load  
  FailArrayPtr    =  0 ;

  //---------( Write the Digital Pin Labels )------------
  WriteDigitalPinLabels();

  //------( Loop thru pins, testing )-----------  
  for (  DigPort2Test = FirstDigPort; 
         DigPort2Test <= LastDigPort;
         DigPort2Test ++)
  {//Loop thru Source Tests
    FailArrayPtr ++ ;

    pinMode(DigPort2Test, OUTPUT);      // Set tested pin to Output mode
    digitalWrite(DigPort2Test, LOW);  // Pin Sinks current LOW   
    delay(A2D_Delay);
    IntVoltsRead = analogRead(A0);
    FloatVoltsRead = a2d2float (IntVoltsRead);
    pinMode(DigPort2Test, INPUT);      // ReSet tested pin to Input mode   

    Serial.print(FloatVoltsRead,2);  
    Serial.print("   ");      

    if (FloatVoltsRead > LowVoltResultOK
      &&  FloatVoltsRead < HighVoltResultOK)
    {
      FailArray[FailArrayPtr]  = 0;      
    }
    else
    {
      Failure ++;   
      FailArray[FailArrayPtr]  = 1;
    }        

  }//END Loop thru Source Tests

  Serial.println();  

  //--------( Write the Digital Pin PASS-FAIL Strings )--------------  
  WriteDigitalPassFail();


//-------------------------( TEST 4 )----------------------------------------
  Serial.println();    
  Serial.println("TEST 004 - Analog Pins Source Current");  
  pinMode(2, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(2, LOW);              // Connect Low Load  

  WriteAnalogPinLabels();

  for (  DigPort2Test = FirstAnaPort; 
         DigPort2Test <= LastAnaPort;
         DigPort2Test ++)
  {//Loop thru Source Tests

    pinMode(DigPort2Test, OUTPUT);      // Set tested pin to Output mode
    digitalWrite(DigPort2Test, HIGH);  // Pin Sources current HIGH     
    delay(A2D_Delay);
    IntVoltsRead = analogRead(A0);
    FloatVoltsRead = a2d2float (IntVoltsRead);
    pinMode(DigPort2Test, INPUT);      // ReSet tested pin to Input mode   
    Serial.print(FloatVoltsRead,2);  
    Serial.print("   ");   

    if (FloatVoltsRead > LowVoltResultOK
      &&  FloatVoltsRead < HighVoltResultOK)
    {
      FailArray[FailArrayPtr]  = 0;      
    }
    else
    {
      Failure ++;   
      FailArray[FailArrayPtr]  = 1;
    }        

  }//END Loop thru Source Tests
  Serial.println();
  WriteAnalogPassFail();

  /*---------( TEST 5 )----------------------*/

  Serial.println("TEST 005 - Analog Pins Sink Current");  
  pinMode(2, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(2, HIGH);              // Connect HIGH Load  

  WriteAnalogPinLabels();

  for (  DigPort2Test = FirstAnaPort; 
         DigPort2Test <= LastAnaPort;
         DigPort2Test ++)
  {//Loop thru Sink Tests

    pinMode(DigPort2Test, OUTPUT);      // Set tested pin to Output mode
    digitalWrite(DigPort2Test, LOW);    // Pin Sinks current LOW   
    delay(A2D_Delay);
    IntVoltsRead = analogRead(A0);
    FloatVoltsRead = a2d2float (IntVoltsRead);
    pinMode(DigPort2Test, INPUT);      // ReSet tested pin to Input mode   
    Serial.print(FloatVoltsRead,2);  
    Serial.print("   ");   

    if (FloatVoltsRead > LowVoltResultOK
      &&  FloatVoltsRead < HighVoltResultOK)
    {
      FailArray[FailArrayPtr]  = 0;      
    }
    else
    {
      Failure ++;   
      FailArray[FailArrayPtr]  = 1;
    }        

  }//END Loop thru Source Tests
  Serial.println();
  WriteAnalogPassFail();



  /*---------( TEST 6 )----------------------*/
  Serial.println();
  Serial.println("TEST 006 - Analog Pins A0 to A5: A to D (About 2.50 V)");  
  pinMode(2, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(2, HIGH);              // Connect HIGH Load
  pinMode(3, OUTPUT);      // Set Load pin to Output mode  
  digitalWrite(3, LOW);              // Connect LOW Load  

  WriteAnalogVoltLabels();

  for (  AnaPort2Test = FirstAnaPort -1; 
         AnaPort2Test <= LastAnaPort;
         AnaPort2Test ++)
  {// Loop thru Analog Tests
    delay(A2D_Delay);
    IntVoltsRead = analogRead(AnaPort2Test);
    FloatVoltsRead = a2d2float (IntVoltsRead);  
    Serial.print(FloatVoltsRead,2);  
    Serial.print("   ");     
  }// END Loop thru Analog Tests  


  /*---------( TEST 7 )----------------------*/
  Serial.println();
  Serial.println();
  Serial.println("TEST 007 - Analog Pins A0 to A5: A to D (About 3.33 V)");  
  pinMode(4, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(4, HIGH);              // Connect 2nd Resistor

  WriteAnalogVoltLabels();

  for (  AnaPort2Test = FirstAnaPort -1; 
         AnaPort2Test <= LastAnaPort;
         AnaPort2Test ++)
  {// Loop thru Analog Tests
    delay(A2D_Delay);
    IntVoltsRead = analogRead(AnaPort2Test);
    FloatVoltsRead = a2d2float (IntVoltsRead);  
    Serial.print(FloatVoltsRead,2);  
    Serial.print("   ");     
  }// END Loop thru Analog Tests    


  /*---------( TEST 8 )----------------------*/
  Serial.println();
  Serial.println();  
  Serial.println("TEST 008 - Analog Pins A0 to A5: A to D (About 1.66 V)");  
  pinMode(4, OUTPUT);      // Set Load pin to Output mode
  digitalWrite(4, LOW);              // Connect 2nd Resistor

  WriteAnalogVoltLabels();

  for (  AnaPort2Test = FirstAnaPort -1; 
         AnaPort2Test <= LastAnaPort;
         AnaPort2Test ++)
  {// Loop thru Analog Tests
    delay(A2D_Delay);
    IntVoltsRead = analogRead(AnaPort2Test);
    FloatVoltsRead = a2d2float (IntVoltsRead);  
    Serial.print(FloatVoltsRead,2);  
    Serial.print("   ");     
  }// END Loop thru Analog Tests     

  //----------( End Test Digital and Analog Ports: Reset everything)-------
  pinMode(2, INPUT);      // Reset Load pin to Input mode
  pinMode(3, INPUT);      // Reset Load pin to Input mode  
  pinMode(4, INPUT);      // Reset Load pin to Input mode 
  MCUCR |= ( 1 << PUD ); //Disable all Pullups

  /*------------( TEST COMPLETE )----------------*/
  Serial.println();    
  Serial.println("TEST COMPLETE");  
  if (Failure > 0)
  {
    Serial.print("!!!!!!!!!!  THERE WERE ");  
    Serial.print(Failure, DEC);            
    Serial.print(" FAILURES !!!!!!!!!!");  
    LED13.blink(150, 50);
  }
  else
  {
    LED13.blink(4000, 4);
  }
  Serial.println();  
  //  delay(10000);
  //--(end main loop )---
}
//----------------( Declare User-written Functions )--------------------------

/*---( fmap: Converts int Analog readings of 0..1023 to float)---*/
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
} 

float a2d2float (int raw)
{
  return fmap(raw, 0, 1023, 0.0, 5.0);
}

void WriteDigitalPinLabels()
{
  //---------( Write the Digital Pin Labels )---------------------
  for (  DigPort2Test = FirstDigPort; 
         DigPort2Test <= LastDigPort;
         DigPort2Test ++)     
  {//Write the label strings  
    Serial.print("PIN-"); 
    Serial.print(DigPort2Test, DEC);
    Serial.print("  ");         
  }// Write Labels  
  Serial.println();
}

void WriteAnalogPinLabels()
{
  //---------( Write the Analog Pin Labels )---------------------
  for (  DigPort2Test = FirstAnaPort; 
         DigPort2Test <= LastAnaPort;
         DigPort2Test ++)     
  {//Write the label strings  
    Serial.print("PIN-");                
    Serial.print(DigPort2Test -14 , DEC);
    Serial.print("  ");         
  }// Write Labels  
  Serial.println();
}


void WriteAnalogVoltLabels()
{
  //---------( Write the Analog Pin Labels )---------------------
  for (  DigPort2Test = FirstAnaPort - 1; 
         DigPort2Test <= LastAnaPort;
         DigPort2Test ++)     
  {//Write the label strings  
    Serial.print("PIN-");                
    Serial.print(DigPort2Test -14 , DEC);
    Serial.print("  ");         
  }// Write Labels  
  Serial.println();
}

//--------( Write the Digital Pin PASS-FAIL Strings )----------------------  
void WriteDigitalPassFail()
{
  FailArrayPtr   = 0;
  for (  DigPort2Test = FirstDigPort; 
         DigPort2Test <= LastDigPort;
         DigPort2Test ++)  
  {//Write the PASS-FAIL strings  
    FailArrayPtr ++;  
    if   (FailArray[FailArrayPtr]  == 1)  // Was a Fail
    {
      Serial.print("FAIL   "); 
    }
    else
    {
      Serial.print("-OK-   ");  
    }       

  }// Write PASS-FAIL
  Serial.println();  
}//End  WriteDigitalPassFail



//--------( Write the Analog Pin PASS-FAIL Strings )----------------------  
void WriteAnalogPassFail()
{
  FailArrayPtr   = 0;
  for (  DigPort2Test = FirstAnaPort; 
         DigPort2Test <= LastAnaPort;
         DigPort2Test ++)  
  {//Write the PASS-FAIL strings  
    FailArrayPtr ++;  
    if   (FailArray[FailArrayPtr]  == 1)  // Was a Fail
    {
      Serial.print("FAIL   "); 
    }
    else
    {
      Serial.print("-OK-   ");  
    }       

  }// Write PASS-FAIL
  Serial.println();  
}//End  WriteDigitalPassFail




//*********( THE END )***********









