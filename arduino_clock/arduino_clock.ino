#include <Wire.h>
int add = 0x68;

void setup() {


  Wire.begin();
  Serial.begin(9600);


  //Wire.write(0x0Eh); // accessing the control register
  //Wire.write(0bv); // setting up the control register (page 13) // please recheck it
  //Wire.endTransmission();

  Wire.beginTransmission(add);
  Wire.write(0x0); // accessing the sec register
 // Wire.write(0b00100011);  // setting up the sec register initially  to 23 sec(can be any)
 Wire.write(26);
  Wire.endTransmission();

  Wire.beginTransmission(add);
  Wire.write(0x1); // accessing the min register
 // Wire.write(0b01010100); // setting up the min registe initially to 54 min(can be any)
 Wire.write(54);
  Wire.endTransmission();

  Wire.beginTransmission(add);
  Wire.write(0x2); // acccessing the hour register
 Wire.write( 0b00010011); // setting the hour hand to 13 in 24 hour format (bit6 as logic low for 24 hr format)
 //Wire.write(
  //Wire.write(01100001) // setting the hour hand to 1 in pm with 12 hour format
  //(bit 6 as logic high for 12 format and bit5 as logic low for AM)
  Wire.endTransmission();

  Wire.beginTransmission(add);
  Wire.write(0x3); // accessing the day register
  Wire.write(0b00000001); // setting the day register to monday
  Wire.endTransmission();

  Wire.beginTransmission(add);
  Wire.write(0x4); // accessing the date register
  Wire.write(B00100001); // setting the date to 21
  Wire.endTransmission();
}




void loop() {


  Wire.beginTransmission(add); // I2c address of the device
  Wire.write(0x0); // starting values reading
  Wire.endTransmission();
  Wire.requestFrom(add, 7); // request values registe from 00h to 06h
  while (Wire.available() < 7);
  byte sec = Wire.read();
  byte mins = Wire.read();
  byte hr = Wire.read();
  byte day = Wire.read();
  byte date = Wire.read();
  byte month = Wire.read();
  byte year = Wire.read();

  Serial.print(date);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.print(year);
  Serial.print("/");

  Serial.print(hr);
  Serial.print("/");
  Serial.print(mins);
  Serial.print("/");
  Serial.println(sec);
  //Serial.println("/");
  delay(1000);


}
