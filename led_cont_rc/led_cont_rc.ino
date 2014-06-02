/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;
int led = 13;
int i=0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(led, OUTPUT);  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    if(results.value==752&& i==0)
    {
      digitalWrite(led, HIGH);
      i=1;
    }
    else if(results.value==752 && i==1)
    {
      digitalWrite(led, LOW);
      i=0;
    }
      
    
    irrecv.resume(); // Receive the next value
  }
}
