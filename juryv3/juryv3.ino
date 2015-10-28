// changelog
// v3
//   >upgraded to NewPing library, leaner,cleaner and more accurate
//   >esp8266 is now a client
//   >configed esp8266 to connectify-me; ^utkarsh laptop
//   >for testing purpose switched for ultrasonic
// 
// ---------------------------------------------------------------------------

#include <NewPing.h>
#define DEBUG true
#define TRIGGER_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     2  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  Serial1.begin(115200);
//    sendData("AT+RESTORE\r\n",2000,DEBUG); // reset module
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
//  sendData("AT+CWJAP=\"Connectify-me\",\"passpass\"\r\n",1000,DEBUG); // setup WPA2
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,8000\r\n",1000,DEBUG); // turn on server on port 80

  
}

void loop() {
//  Serial.print("Ping: ");
//int depth = bugfix();
//Serial.print(depth);
//Serial.println("cm");
//http server
  if(Serial1.available()) // check if the esp is sending a message 
  {
    Serial.print("waiting for Serial1.available()");  
    /*
    while(Serial1.available())
    {

      // The esp has data so display its output to the serial window 
      char c = Serial1.read(); // read the next character.
      Serial.write(c);
    } */
    
    if(Serial1.find("+IPD,"))
    {
          Serial.print("waiting for +ipd");
     delay(1000);
 
     int connectionId = Serial1.read()-48; // subtract 48 because the read() function returns 
     int depth = bugfix();                                      // the ASCII decimal value and 0 (the first decimal number) starts at 48
     String data = String(depth);
     String webpage = "<html><head><meta http-equiv=\"refresh\" content=\"3\"></head><body><h1>"+data+"</h1>";
      
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     Serial.print("request to send");
     sendData(cipSend,1000,DEBUG);
     delay(100);
     sendData(webpage,1000,DEBUG);
     Serial.print("sending packet");
       delay(100);
         Serial.print("packet send");
         
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
            delay(100);
         Serial.print("end of packet");
    }
  }

}
 
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    Serial1.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(Serial1.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = Serial1.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

int bugfix()
{
//  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
//  int depth = sonar.ping_cm();
//if (depth == 0)
//    return 150;
//  else
    return 50;
}
