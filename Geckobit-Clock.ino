/*
 * Pinout
 * 02 - EN x1
 * 03 - EN x10
 * 04 - EN x100
 * 05 - EN x1000
 * 06 - A
 * 07 - B
 * 08 - C
 * 09 - D
 * 10 - 
 * 11 - 
 * 12 - 
 */

#include <DS3232RTC.h>
#include <Wire.h>
#include <Time.h>

const byte de = 5;
byte uni = 1, dec = 0, cen = 1, mil = 0;
byte hours, minutes;
boolean clk = false;

void setup() {
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  setSyncProvider(RTC.get);

  if (timeStatus() == timeSet) {
    clk = true;
  }

  Serial.begin(9600);
}

void loop() {
  int i;
  while (!clk) {
    /*
     * Failed to communicate with the time module
     */
    for (i = 0; i <= 25; i++) {
      printTime();
    }
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(500);
  }

  getTime();
  for (i = 0; i <= 100; i++){
    printTime();
  }
}

void getTime() {
  
  hours = getBCD(hour());
  minutes = getBCD(minute());

  mil = hours & B11110000;
  cen = hours & B00001111;
  dec = minutes & B11110000;
  uni = minutes & B00001111;
  mil >>= 4;
  dec >>= 4;
}

byte getBCD(byte bin) {
  /*
  If any column (100's, 10's, 1's, etc.) is 5 or greater, add 3 to that column.

  Shift all #'s to the left 1 position.

  If 8 shifts have been performed, it's done! Evaluate each column for the BCD values.

  Go to step 1.
  */
  byte bcd = 0;
  int i;
  for (i = 0; i < 8; i++) {

    if ((bcd & B00001111) >= 0x05) {
      bcd += 0x03;
    }

    if ((bcd & B11110000) >= 0x50) {
      bcd += 0x30;
    }

    bcd <<= 1;
    if (bin & B10000000) {
      bcd |= 1;
    }
    bin <<= 1;
  }   
  return bcd;
}



void printTime() {
  /*
   * This function prints the time on the display
   */
  digitalWrite(6, bitRead(uni,0));
  digitalWrite(7, bitRead(uni,1));
  digitalWrite(8, bitRead(uni,2));
  digitalWrite(9, bitRead(uni,3));
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);  
  delay(de);

  digitalWrite(6, bitRead(dec,0));
  digitalWrite(7, bitRead(dec,1));
  digitalWrite(8, bitRead(dec,2));
  digitalWrite(9, bitRead(dec,3));
  digitalWrite(3, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(de);

  digitalWrite(6, bitRead(cen,0));
  digitalWrite(7, bitRead(cen,1));
  digitalWrite(8, bitRead(cen,2));
  digitalWrite(9, bitRead(cen,3));
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(5, LOW);
  delay(de);

  digitalWrite(6, bitRead(mil,0));
  digitalWrite(7, bitRead(mil,1));
  digitalWrite(8, bitRead(mil,2));
  digitalWrite(9, bitRead(mil,3));
  digitalWrite(5, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  delay(de);
}
