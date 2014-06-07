/*
 * serial_motor_control.pde
 * -----------------
 * Controls the speed of a motor depending on what is received
 * through the serial port.
 *
 * http://spacetinkerer.blogspot.com
 */


int input = 0;

void setup() {             
  // initialize the PWM pin #3 as an output.
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
    input = Serial.read();
    if (input == '0')
    {
      analogWrite(3, 0);
      Serial.println("Speed is 0!");
    }
    if (input == '1')
    {
      analogWrite(3, 32);
      Serial.println("Intensity is at 10%");
    }
    if (input == '2')
    {
      analogWrite(3, 64);
      Serial.println("Intensity is at 20%");
    }
    if (input == '3')
    {
      analogWrite(3, 96);
      Serial.println("Intensity is at 30%");
    }
    if (input == '4')
    {
      analogWrite(3,128);
      Serial.println("Intensity is at 40%");
    }
    if (input == '5')
    {
      analogWrite(3,160);
      Serial.println("Intensity is at 50%");
    }
    if (input == '6')
    {
      analogWrite(3,192);
      Serial.println("Intensity is at 60%");
    }
    if (input == '7')
    {
      analogWrite(3,224);
      Serial.println("Intensity is at 70%");
    }
    if (input == '8')
    {
      analogWrite(3,255);
      Serial.println("Intensity is at 100%");
    }
}
