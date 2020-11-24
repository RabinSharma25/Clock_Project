#include<Wire.h>
#include<EEPROM.h>
#define deviceAddress 0b1101000         //i2c address of the clock module  //  0x68 
void setup()
{
  Wire.begin();                         // initalize the i2c module 


////////////////// setting up the clock system /////////////////////

// all the binaries are in bcd format 

 // seconds
 Wire.beginTransmission(deviceAddress); // begining transmission with the i2c module 
 Wire.write(0x00);                      // acccessing the seconds register 
 Wire.write(0b000000000);               // writing to the seconds register 
 Wire.endTransmission();                // ending transmission to the module

 //minutes
 Wire.beginTransmission(deviceAddress);
 Wire.write(0x01);                     // accessing the minutes  register 
 Wire.write(0b00000111);               //writing to the minutes register
 Wire.endTransmission();               //ending transmission to the module 

 //hour
 Wire.beginTransmission(deviceAddress);
 Wire.write(0x02);                     // assessing the hour  register 
 Wire.write(0b00010010);               // wrinting to the hour register 
 Wire.endTransmission();               //ending transmission to the module 

  // day
  Wire.beginTransmission(deviceAddress);
  Wire.write(0x3);                     // accessing the day register
  Wire.write(0b00000001);              // setting the day register to sunday 
  Wire.endTransmission();              // ending transmission to the module 

  // date
  Wire.beginTransmission(deviceAddress);
  Wire.write(0x4);                    // accessing the date register
  Wire.write(0b00001000);             // setting the date register
  Wire.endTransmission();

  // month 
  Wire.beginTransmission(deviceAddress);
  Wire.write(0x5);                    // accessing the month  register
  Wire.write(0b00010001);             // setting the month to register 
  Wire.endTransmission();

  // year 
  Wire.beginTransmission(deviceAddress);
  Wire.write(0x6);                    // accessing the year register
  Wire.write(0b00100000);             // setting the year to register
  Wire.endTransmission();



  
}

void loop()
{

// do nothing 
}
