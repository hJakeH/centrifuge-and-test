#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
#include <Servo.h>
int button1 = 7; //button pin, connect to ground to move servo
Servo servo;

volatile unsigned long time1;
volatile unsigned long time2;
int count = 0;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(0, Count1, FALLING);
  attachInterrupt(1, Count2, FALLING);
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

}

void loop() {
  if (time1 != 0  && time2 != 0){
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
    servo.write(95);
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
