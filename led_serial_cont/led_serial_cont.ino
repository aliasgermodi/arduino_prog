/* led control serially*/

int led = 13;   // led on pine 13

void setup()
{
  pinMode(led, OUTPUT);    //pin 13 as output
  
  Serial.begin(9600);    //initialize serial communication at 9600bps
  Serial.flush();  // wait for the transission to complete
}

void loop()
{
  String input = "";
  
  while(Serial.available()>0)    // read any serial input
  {
    input += (char) Serial.read();  // read one char at a time
    delay(5);  // delay of 5ms for next char 
  }
  
  if(input == "on")
  {
    digitalWrite(led, HIGH);    // led ON
  }
  else if(input == "off")
  {
    digitalWrite(led, LOW);    //led OFF
  }
}
  
   
  
  
