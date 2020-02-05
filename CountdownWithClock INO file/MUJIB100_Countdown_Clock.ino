/* >>>>> include the library code <<<<  */
#include<SPI.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h> 
#include <LiquidCrystal.h>
#include <Time.h>
#include "DigitLedDisplay.h"


/* Arduino Pin to Display Pin
   7 to DIN,
   6 to CS,
   5 to CLK */
DigitLedDisplay ld = DigitLedDisplay(7, 6, 5);

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup () {
    // MAX7912
   /* Set the brightness min:1, max:15 
    MAX7912 */
  ld.setBright(10);

  /* Set the digit count */
  ld.setDigitLimit(8);

  Serial.begin(9600);
//  lcd.begin(16, 2);
  //delay(1000);
  //lcd.clear();
 Serial.begin(9600);
  while (!Serial) ; // wait until Arduino Serial Monitor opens
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");
}

void loop () {
  if (timeStatus() == timeSet) {
    Serial.println("Rtc Ok");
  } else {
    Serial.println("The time has not been set.  Please run the Time");
    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
    Serial.println();
    delay(4000);
  }
  tmElements_t T1;
  tmElements_t T2;
//Today  date time
  T1.Hour = hour();
  T1.Minute = minute();
  T1.Second =second();
  T1.Day = day();
  T1.Month = month();
  T1.Year = year(); // because Year is offset from 1970
  
// Count Date from
  T2.Hour = 23;
  T2.Minute =58;
  T2.Second = 59;
  T2.Day = 17;
  T2.Month = 3;
  T2.Year = 2020; // because Year is offset from 1970
// convert T1 and T2 to seconds since 1/1/1970

  time_t T1sec = makeTime( T1 );
  time_t T2sec = makeTime( T2 );
  //Serial.print( "T1 in seconds since 1970: " );
  //Serial.println( T1sec );
  //Serial.print( "T2 in seconds since 1970: " );
  //Serial.println( T2sec );
  // differences in seconds
  int32_t diff = T2sec - T1sec;
  //Serial.print( "Difference between T1 and T2 in seconds: " );
 // Serial.println( diff );

  /*>>>>>>show difference in hours, minutes and seconds<<<<<*/
  //Serial print Option
  
  uint32_t days = diff /3600/24;
  uint32_t hours = (diff / 3600)%60;
  uint8_t minutes = (diff / 60) % 60;
  uint8_t seconds = diff % 60;
 /* Serial.print( "T1 was " );
  Serial.print( hours/24);
  Serial.print( " hour(s), " );
  Serial.print( minutes );
  Serial.print( " minute(s) and " );
  Serial.print( now.second() );
  Serial.println( " second(s) before T2." );
  */

if ( T1.Month = 3 )
{
  if( T1.Day > 17 )
  {
     /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Clock<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
  
  /*
  //LCD Print
  lcd.setCursor(2, 0);
  lcd.print(now.day(), DEC);
  lcd.print(':');
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  */

  /*
  //Serial Monitor Print
    Serial.print(days);
    Serial.print(':');
    Serial.print(hours);
    Serial.print(':');
    Serial.print(minutes);
    Serial.print(':');
    Serial.println(seconds);
    */
    }
  } 
  else {
  /**  
  /*
  //LCD Print
  lcd.setCursor(2, 0);
  lcd.print(day());
  lcd.print(':');
  lcd.print(hour());
  lcd.print(':');
  lcd.print(minute());
  lcd.print(':');
  lcd.print(second());
  */

  /*
  //Serial Monitor Print
    Serial.print(day);
    Serial.print(':');
    Serial.print(hour);
    Serial.print(':');
    Serial.print(minute);
    Serial.print(':');
    Serial.println(second);
    */
    //Max7912 Ic print
    ld.printDigit(days, 6);
    ld.printDigit(hours,4);
    ld.printDigit(minutes,2);
    ld.printDigit(seconds);
  }
 // delay(500);
 // lcd.clear();
 //ld.clear();
}
