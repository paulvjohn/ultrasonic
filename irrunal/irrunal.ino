int output =49;
int input=50;
int state=0;

void setup() {
  // put your setup code here, to run once:
pinMode (output, OUTPUT);
pinMode (input, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
state = digitalRead(input);

if (state == LOW){
  digitalWrite(output, HIGH);
}
else {
digitalWrite(output, LOW);
}

}

