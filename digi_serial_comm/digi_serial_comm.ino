/* digital serial communcation
   state of push button on serial monitor
*/

int pushButton = 2;  //pin 2  has push button

void setup()
{
  Serial.begin(9600);    //initialize serial communication at 9600bps
  pinMode(pushButton, INPUT);    // push button as input
}

void loop()
{
  int buttonState = digitalRead(pushButton); //read input pin
  Serial.println(buttonState);  //print the button state
  delay(1);    //delay between read
}

