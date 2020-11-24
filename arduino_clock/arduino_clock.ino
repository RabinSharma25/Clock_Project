#include<Wire.h>
#define deviceAddress 0b1101000 //0x68
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  Wire.begin();   //I2C Bus is formed/eanbaled
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0); //DP0 of Topline
//
 //--setting up intial time -- 00:54:23
  Wire.beginTransmission(deviceAddress); //START, Roll Cal
  Wire.write(0x00); //SEC Register address in Address Counter of RTC
 Wire.write(0b000000000); //data for SEC Register (23 sec = 0010 0011; BCD format)
  Wire.endTransmission();

 Wire.beginTransmission(deviceAddress);
 Wire.write(0x01);
 Wire.write(0b00000111); //data for MIN Register (54 Min = 0101 0100; BCD format)
//Wire.write(0x00); //data for HRS Register ignore it now
 Wire.endTransmission(); //Execute the above Tasks, ACK STOP

   Wire.beginTransmission(deviceAddress);
  Wire.write(0x02);
 Wire.write(0b00010010); //data for MIN Register (54 Min = 0101 0100; BCD format)
//Wire.write(0x00); //data for HRS Register ignore it now
  Wire.endTransmission(); //Execute the above Tasks, ACK STOP

   Wire.beginTransmission(deviceAddress);
  Wire.write(0x3); // accessing the day register
  Wire.write(0b00000001); // setting the day register to sunday 
  Wire.endTransmission();

  Wire.beginTransmission(deviceAddress);
  Wire.write(0x4); // accessing the date register
  Wire.write(0b00001000); // setting the date to 21
  Wire.endTransmission();

  // month 
  Wire.beginTransmission(deviceAddress);
  Wire.write(0x5); // accessing the day register
  Wire.write(0b00010001); // setting the month to 11  
  Wire.endTransmission();

  // year 
  Wire.beginTransmission(deviceAddress);
  Wire.write(0x6); // accessing the date register
  Wire.write(0b00100000); // setting the date to 2020
  Wire.endTransmission();



  
}

void loop()
{
  showTimeOnLCD();
}

void showTimeOnLCD()
{
  Wire.beginTransmission(deviceAddress); //START, Roll Cal
  Wire.write(0x00); //pointing SEC Register at address 0x00 (Fig-2)
  Wire.endTransmission(); //Execute the above queued data, ACK, STOP

  Wire.requestFrom(deviceAddress, 7);   //SEC, MIN, and HRS to read from RTC as BCD
  byte bcdSeconds = Wire.read();
  byte bcdMinutes = Wire.read();
  byte bcdHours = Wire.read();  //ignore Hours reading
  byte bcdDay = Wire.read();
  byte bcdDate = Wire.read();
  byte bcdMonth = Wire.read();
  byte bcdYear = Wire.read();
  
  //---show Time on LCD---------------

  int day = bcdDay & 15;
  String pot;

  switch(day){
 case 1: pot = "Sun";
 break;
 case 2:pot = "Mon";
 break;
 case 3:pot = "Tue";
 break;
 case 4:pot = "Wed";
 break;
 case 5:pot = "Thr";
 break;
 case 6:pot = "Fri";
 break;
 case 7:pot = "Sat";
 break;
 default: Serial.print("Invalid Input");
 break;

  }

  
  lcd.print("Time: ");
  lcd.print(bcdHours >> 4); lcd.print(bcdHours & 15); lcd.print(':');
  lcd.print(bcdMinutes>> 4); lcd.print(bcdMinutes & 15); lcd.print(':');
  lcd.print(bcdSeconds >> 4); lcd.print(bcdSeconds & 0x0F);

  lcd.setCursor(0,1);// first argument which column second argument which row (up or down )
  lcd.print(pot);
  lcd.print(" : ");
  lcd.print(bcdDate>>4);lcd.print(bcdDate & 15);lcd.print("/");
  lcd.print(bcdMonth>>4);lcd.print(bcdMonth &15);lcd.print("/");
  lcd.print(bcdYear>>4);lcd.print(bcdYear & 15);
  lcd.setCursor(0,0);  //re=position the cursor
  //delay(100);

//  Serial.print("Time: ");
//  Serial.print(bcdHours);
//  Serial.print(":");
//  Serial.print(bcdMinutes);
//  Serial.print(":");
//  Serial.println(bcdSeconds);
  
//  Serial.print(bcdHours >> 4);Serial.print(bcdHours & 0x0F); Serial.print(':');
//  //Serial.print(":");
//  // Serial.println(bcdMinutes & 0x0F);
//  Serial.println(bcdMinutes>> 4);// Serial.print(bcdMinutes & 0x0F); Serial.print(':');
//  Serial.print(bcdSeconds >> 4); Serial.println(bcdSeconds & 0x0F);
 // lcd.setCursor(0, 0);  //re=position the cursor
}
