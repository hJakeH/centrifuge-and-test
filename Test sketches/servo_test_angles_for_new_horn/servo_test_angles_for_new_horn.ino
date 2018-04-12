#include <Wire.h>
#include <Servo.h>
int button1 = 7; //button pin, connect to ground to move servo
Servo servo;

void setup()
{
  Serial.begin(9600);
  pinMode(button1, INPUT);
  servo.attach(6);
}
void loop() {
  int press1 = digitalRead(button1);
  if (press1 == LOW) {
    noInterrupts();
    servo.write(175);
    //  delay(3000);
    interrupts();
    Serial.print("MARK");
  }
  else {
    servo.write(100);
  }
}

