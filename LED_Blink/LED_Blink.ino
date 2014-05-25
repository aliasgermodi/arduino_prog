/* LED blink
   turns LED on for one second and the off for one second
*/

int led = 13; //led connected to pin 13

void setup()
{
   pinMode(led, OUTPUT); //initialize pin as output
}

void loop()
{
  digitalWrite(led, HIGH);  //turn led ON
  delay(1000);              //wait for one second
  digitalWrite(led, LOW);   //turn led OFF
  delay(1000);              //wait for one second
}
