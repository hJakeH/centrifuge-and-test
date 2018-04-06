#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

volatile unsigned long time1, time2;
int count = 0;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(0,Count1,FALLING);
  attachInterrupt(1,Count2, FALLING);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  Serial.println("START");
}

void loop(){
  DateTime now = rtc.now();
  if (time1 != 0  && time2 != 0)
  {
    if (time2 > time1){ 
      int ET = (time2 - time1);
      count++;
      Serial.print(ET);
      Serial.print(" ET, ");
      Serial.print(count);
    }
    
    else{ 
      int ET = (time1 - time2);
      count++;
      Serial.print(ET);
      Serial.print(" ET, ");
      Serial.print(count);
    }
    
    noInterrupts();
        Serial.print("   ");
        Serial.print(now.hour(), DEC);
        Serial.print('.');
        Serial.print(now.minute(), DEC);
        Serial.print('.');
        Serial.print(now.second(), DEC);
        Serial.println();
    time1 = time2 = 0;
    interrupts();
  }
}


void Count1(void){
  time1 = micros();
}
void Count2(void){
  time2 = micros();
}
