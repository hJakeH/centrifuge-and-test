#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
#include <Servo.h>
int button1 = 7; //button pin, connect to ground to move servo
Servo servo;
int Det_RPM = 150;   //detachment RPM being tested
volatile int RPM_n;
volatile unsigned long time1;
volatile unsigned long time2;
int count = 0;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), Count1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), Count2, CHANGE);
  pinMode(button1, INPUT);
  servo.attach(6);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    //following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  Serial.println("START");
      DateTime now = rtc.now();
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print('.');
    Serial.print(now.minute(), DEC);
    Serial.print('.');
    Serial.print(now.second(), DEC);
    Serial.println();
  servo.write(100);
}

void loop() {
  if (time1 != 0  && time2 != 0 && time1 > time2){
    {
      int ET = (time1 - time2);
      int RPM = 5000 / ET;
      int RPM_n = abs(RPM);
      Serial.print(RPM_n);
      Serial.print(" RPM ");
      DateTime now = rtc.now();
      Serial.print(" ");
      Serial.print(now.hour(), DEC);
      Serial.print('.');
      Serial.print(now.minute(), DEC);
      Serial.print('.');
      Serial.print(now.second(), DEC);
      Serial.println();
      while(RPM_n >= Det_RPM){     //automatic routine to turn servo slightly below RPM threshold
        int Timer=millis();
        servo.write(175);
        delay(5000);
        }
    }
    noInterrupts();
    time1 = time2 = 0;
    interrupts();
  }
  int press1 = digitalRead(button1);
  if (press1 ==LOW) {
    noInterrupts();
    servo.write(175);
    //  delay(3000);
    interrupts();
    Serial.print(" MARK");
  }
  else {
    servo.write(100);
  }
}

void Count1(void) {
  time1 = millis();
  //time1 = micros();
}
void Count2(void) {
  time2 = millis();
  //time2 = micros();
}
