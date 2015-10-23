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

byte de = 5;
byte uni = 0, dec = 0, cen = 0, mil = 1;

void setup() {
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

}

void loop() { 
  int i;
  
  for (i = 0; i < 3000; i++) {
    bcdPrint(mil,cen,dec,uni);
  }
  
  uni++;
  if (uni >= 10) {
    uni = 0;
    dec++;
  }

  if (dec >= 10) {
    dec = 0;
    cen++;
  }

  if (cen >= 10) {
    cen = 0;
    mil++;
  }

  if (mil >= 10) {
    mil = 0;
  }
}

void bcdPrint(int n1, int n2, int n3, int n4) {
  digitalWrite(6, bitRead(n4,0));
  digitalWrite(7, bitRead(n4,1));
  digitalWrite(8, bitRead(n4,2));
  digitalWrite(9, bitRead(n4,3));
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);  
  delay(de);

  digitalWrite(6, bitRead(n3,0));
  digitalWrite(7, bitRead(n3,1));
  digitalWrite(8, bitRead(n3,2));
  digitalWrite(9, bitRead(n3,3));
  digitalWrite(3, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(de);

  digitalWrite(6, bitRead(n2,0));
  digitalWrite(7, bitRead(n2,1));
  digitalWrite(8, bitRead(n2,2));
  digitalWrite(9, bitRead(n2,3));
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(5, LOW);
  delay(de);

  digitalWrite(6, bitRead(n1,0));
  digitalWrite(7, bitRead(n1,1));
  digitalWrite(8, bitRead(n1,2));
  digitalWrite(9, bitRead(n1,3));
  digitalWrite(5, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  delay(de);
}

