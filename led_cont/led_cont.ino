void setup()
{
  Serial.begin(9600);
  pinMode(9,OUTPUT);
}
 
void loop()
{
  if(Serial.available())
  {
    int brightness = (int)Serial.read();
    int value = map(brightness,0,127,0,255);
    analogWrite(9,value);
  }
}
