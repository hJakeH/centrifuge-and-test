// Powering a servo from the arduino usually *DOES NOT WORK*.
#include <Servo.h>
int button1 = 7; //button pin, connect to ground to move servo
int led = 13;
Servo servo;

void setup(){
  pinMode(button1, INPUT);
  pinMode(led, OUTPUT);
  servo.attach(6);
}
  
void loop(){
  int press1 = digitalRead(button1);
  if (press1 == HIGH){
    servo.write(95);
    digitalWrite(led, HIGH);
  }
  else {
    servo.write(175);
    digitalWrite(led, LOW);
  }
}



