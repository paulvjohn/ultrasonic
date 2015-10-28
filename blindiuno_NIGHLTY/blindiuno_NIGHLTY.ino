const int trigPin = 2;
const int echoPin = 3;
void setup() 
{
  // initialize serial communication:
  Serial.begin(9600);
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
  //if (cm < 20){
  //digitalWrite(5, HIGH);
  //digitalWrite(8, LOW);
//}


  Serial.print(cm);
  Serial.print("cm to the wall");
  Serial.println();
  
  delay(100);
}

void lightoff(){
digitalWrite(8, LOW);
digitalWrite(5, LOW);
  }

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  long temp = microseconds / 74 / 2;
  if (temp == 0)
    return 60;
  else
    return temp;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  long temp = microseconds / 29 / 2;
    if (temp == 0)
    return 150;
  else
    return temp;
}
