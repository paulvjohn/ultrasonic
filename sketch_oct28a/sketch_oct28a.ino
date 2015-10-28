// #include <SoftwareSerial.h>
 
#define DEBUG true
const int trigPin = 3;
const int echoPin = 2;
 
// SoftwareSerial Serial1(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
//                              // This means that you need to connect the TX line from the esp to the Arduino's pin 2
//                              // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  Serial1.begin(115200); // your esp's baud rate might be different
  delay(3000);
  //dstance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(8, OUTPUT); //red
  pinMode(5, OUTPUT); //green
  
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+RESTORE\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CWSAP=\"blinduino\",\"nopassword\",4,3",1000,DEBUG);
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop()
{
//echo distance
 long duration, inches, cm;


  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  

lightoff();


//led glow
 if (cm <60) { 
  if (cm > 30){
  digitalWrite(5, HIGH);
  digitalWrite(8, LOW);}
  else {
  digitalWrite(8, HIGH);
  digitalWrite(5, LOW);
  }}


  
//http server
  if(Serial1.available()) // check if the esp is sending a message 
  {
    /*
    while(Serial1.available())
    {
      // The esp has data so display its output to the serial window 
      char c = Serial1.read(); // read the next character.
      Serial.write(c);
    } */
    
    if(Serial1.find("+IPD,"))
    {
     delay(1000);
 
     int connectionId = Serial1.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
     String depth = String(cm);
     String webpage = "<html><head><meta http-equiv=\"refresh\" content=\"3\"></head><body><h1>";
 
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     
     webpage=depth+"</h1>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
 
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
    }
  }
}

//end of loop



//Distance functions


void lightoff(){
digitalWrite(8, LOW);
digitalWrite(5, LOW);
  }

long microsecondsToInches(long microseconds)
{
 // Documentation: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  long temp = microseconds / 74 / 2;
  if (temp == 0)
    return 60;
  else
    return temp;
}

long microsecondsToCentimeters(long microseconds)
{
  long temp = microseconds / 29 / 2;
    if (temp == 0)
    return 150;
  else
    return temp;
}

//http function define

 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    Serial1.print(command); // send the read character to the Serial1
    
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
