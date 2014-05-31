//blinking led and see status on web page

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0x9E, 0x63 };//change accordingly
IPAddress ip(192 ,168 ,1 ,100);  //change accordingly

EthernetServer server(80);

int led = 13;  //led on pin 13

void setup()
{
  pinMode(led, OUTPUT);    //pin 13 as output
  digitalWrite(led,HIGH);
  Serial.begin(9600);
  Serial.flush();
  //pinMode(8, OUTPUT);
  Ethernet.begin(mac, ip);
  server.begin();
  
  
}


void loop()
{
  EthernetClient client = server.available();
  client.println("LED STATUS");
  
     delay(500);
    
      digitalWrite(led, LOW);    // led ON
      client.print("LED is OFF   ");
      delay(500);
      digitalWrite(led, HIGH);    //led OFF
      client.print("LED is ON    ");
}
