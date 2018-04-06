//always ground your breadboard
int led = 13;
int button1 = 7;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  pinMode(button1, INPUT);
}
// the loop routine runs over and over again forever:
void loop() {
  int press1 = digitalRead(button1);
  if (press1 == LOW)
  {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}
