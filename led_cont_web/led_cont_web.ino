	

    //simple button GET server code to control servo and arduino pin 5
    //for use with IDE 1.0
    //open serial monitor to see what the arduino receives
    //use the \ slash to escape the " in the html
    //for use with W5100 based ethernet shields
    //Powering a servo from the arduino usually DOES NOT WORK.
    //note that the below bug fix may be required
    
     
    #include <SPI.h>
    #include <Ethernet.h>
     
    #include <Servo.h>
    Servo myservo;  // create servo object to control a servo
     
    byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0x9E, 0x63 }; //physical mac address
    byte ip[] = { 192, 168, 1, 100 }; // ip in lan
    
    EthernetServer server(80); //server port
     
    String readString;
     
    //////////////////////
     
    void setup(){
     
      pinMode(6, OUTPUT); //pin selected to control
      //start Ethernet
      Ethernet.begin(mac, ip);
      server.begin();
      //the pin for the servo co
      //enable serial data print
      Serial.begin(9600);
      Serial.println("server LED test 1.0"); // so I can keep track of what is loaded
    }
     
    void loop(){
      // Create a client connection
      EthernetClient client = server.available();
      if (client) {
        while (client.connected()) {
          if (client.available()) {
            char c = client.read();
     
            //read char by char HTTP request
            if (readString.length() < 100) {
     
              //store characters to string
              readString += c;
              //Serial.print(c);
            }
     
            //if HTTP request has ended
            if (c == '\n') {
     
              ///////////////
              Serial.println(readString); //print to serial monitor for debuging
     
              client.println("HTTP/1.1 200 OK"); //send new page
              client.println("Content-Type: text/html");
              client.println();
     
              client.println("<HTML>");
              client.println("<HEAD>");
              client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
              client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
              client.println("<link rel='stylesheet' type='text/css' href='http://homeautocss.net84.net/a.css' />");
              client.println("<TITLE>Home Automation</TITLE>");
              client.println("</HEAD>");
              client.println("<BODY>");
              client.println("<H1>Home Automation</H1>");
              client.println("<hr />");
              client.println("<br />");
             
              client.println("<a href=\"/?lighton\"\">Turn On Light</a>");
              client.println("<a href=\"/?lightoff\"\">Turn Off Light</a><br />");        
     
              client.println("</BODY>");
              client.println("</HTML>");
     
              delay(1);
              //stopping client
              client.stop();
     
              ///////////////////// control arduino pin
              if(readString.indexOf("?lighton") >0)//checks for on
              {
                digitalWrite(6, HIGH);    // set pin 4 high
                Serial.println("Led On");
              }
              else{
              if(readString.indexOf("?lightoff") >0)//checks for off
              {
                digitalWrite(6, LOW);    // set pin 4 low
                Serial.println("Led Off");
              }
              }
              //clearing string for next read
              readString="";
     
            }
          }
        }
      }
    }


