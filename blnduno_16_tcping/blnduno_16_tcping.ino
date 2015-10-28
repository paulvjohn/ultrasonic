const int trigPin = 2;
const int echoPin = 3;
void setup() 
{
  // initialize serial communication:
  Serial.begin(9600);
  Serial1.begin(115200);
//hotspot setup
  Serial1.println("AT");
  delay(1000);
  Serial1.println("AT+RST");
  delay(1000);
  Serial1.println("AT+CWMODE=3");
  delay(1000);
  Serial1.println("AT+CWJAP=\"myserver\",\"kingtek1\"");
//Serial1.println("AT+CWSAP=\"blinduino\",\"nopassword\",4,3");
  delay(1000);
  Serial1.println("AT+CIPSTART=\"UDP\",\"192.168.4.2\",52340");
  delay(1000);
// led setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(8, OUTPUT); //red
  pinMode(5, OUTPUT); //green
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
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



 if (cm <60) { 
  if (cm > 30){
  digitalWrite(5, HIGH);
  digitalWrite(8, LOW);}
  else {
  digitalWrite(8, HIGH);
  digitalWrite(5, LOW);
  }}
  
  String depth = String(cm);
  Serial1.print("AT+CIPSEND=");
  Serial1.println(depth.length());
  while(Serial1.read() != '>')
  {
    ;
  }
  Serial1.println(depth);
  
  
  delay(100);
}

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
