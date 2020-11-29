#include<Wire.h>
#define deviceAddress 0b1101000 //0x68 the adddress of DS3231 clock module 
#include<LiquidCrystal_I2C.h> // including the library for the display 
LiquidCrystal_I2C lcd(0x27, 16, 2); // creating an display object (lcd), with address and size ment

byte Seconds ;
byte Minutes ;
byte Hours ;
byte Day ;
byte Date ;
byte Month ;
byte Year ;

int hrs, mins, secs; // variables to store the numeric time values from the clock

////// setting up variable for the alaram system
int curSec  ;
int curMin ;
int curHr ; // current time = 4:40:32

int ArSec = 0;
int ArMin = 15;
int ArHr = 5 ; // time = 5:30:5 s
const int ArMins = ArMin;//,ArHrs;
const int ArHrs = ArHr;

////////////// setting up variables for the pushbuttons /////////
const int btnPin = 13;
int State = 1 ;
int counter = 1;
int cnt = 0;
int button_state_old = 0;
int button_state_new;

int  btst_new1, btst_new2, state1, state2;
int btst_old1 = 1;
int btst_old2 = 1;
//int btst_old3 = 1;

int button1 = A2;
int button2 = A1;
int button3 = A0;

int counter1 = 0;
int counter2 = 0;
int counter2_2 =0;
int counter3 ;

int variable = 0;

int btst_new3;
int btst_old3 = 1;
int value ;
//int  counter3 = 0;

String app = "Time: 23:32:11";


void setup() {

  Serial.begin(9600); // beginging the serial commmunication for debugging
  Wire.begin(); // initializing the wire library
  lcd.begin(); // initializing the lcd display
  lcd.backlight();  // initalizing the lcd backlight
  lcd.setCursor(0, 0);// setting up the lcd cursor to left top


  pinMode(btnPin, INPUT); // declaring pin 13 as input
  pinMode(button1, INPUT);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);


}


void loop() {
  //
  button_state_new = digitalRead(btnPin);  // reading the state of  btnpin
  if (button_state_old == 1 && button_state_new == 0) {
    lcd.clear();
    counter++; // incrementing the counter variable to flip the pages in the scree


  }


  ///////////////////////////// 1 ////////////////////

  btst_new1 = digitalRead(button1);  // reading the state of  btnpin
  if (btst_old1 == 1 && btst_new1 == 0) {
    lcd.clear();
    counter1++;
  }

  //////////////////////////////// 2 /////////////////////////

  btst_new2 = digitalRead(button2);  // reading the state of  btnpin
  if (btst_old2 == 1 && btst_new2 == 0) {
    counter3 = 0;
    if(counter == 3 && counter1 ==1)counter2_2++;
    else if(counter == 3 && counter1 ==2) counter2++;

  }
  
  btst_new3 = digitalRead(button3);  // reading the state of  btnpin
  if (btst_old3 == 1 && btst_new3 == 0) {
    counter3 ++;
  }

  CollectData(); // function that collects data from the clock module


  if (counter == 1) {

    ShowOnLcd(); // function that prints on the lcd screen

  }

  else if (counter == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Temp :");
    lcd.print(32); lcd.print(" deg"); lcd.print(" C");
    lcd.setCursor(5, 1);
    lcd.print(":");
    lcd.print(100); lcd.print(" deg"); lcd.print(" F");
  }
  else if (counter == 3 && counter1 ==0) {
    lcd.setCursor(1, 0);
    lcd.print("Setting Menu");
   // lcd.setCursor(5, 1);
    //lcd.print("Ahead");
  }


    else if(counter1 == 1 && counter ==3){
      //counter =0;
       lcd.setCursor(1,0);lcd.print("SetTime");
      lcd.setCursor(10,0);lcd.print("SetAlr");
      lcd.setCursor(1,1);lcd.print("SetDate");
      lcd.setCursor(10,1);lcd.print("SetDay");
      switch(counter2_2){
        case 1:lcd.setCursor(0,0);lcd.print(">");lcd.setCursor(9,1);lcd.print(" ");
        break;
        case 2:lcd.setCursor(0,1);lcd.print(">");lcd.setCursor(0,0);lcd.print(" ");
        break;
        case 3:lcd.setCursor(9,0);lcd.print(">");lcd.setCursor(0,1);lcd.print(" ");
        break;
        case 4:lcd.setCursor(9,1);lcd.print(">");lcd.setCursor(9,0);lcd.print(" ");
        break;

        
  
  
      }
      if (counter2_2 ==5)counter2_2 = 1;
      }
         if (counter2_2 ==1 && counter1 ==2){

    lcd.setCursor(0, 0);

    lcd.print("Time: ");
    lcd.setCursor(8, 0);
    lcd.print(':');
    lcd.setCursor(11, 0);
    lcd.print(":");



    if (counter2 == 1) {
      ClockEdit(6, 0, 0x02, "Hour");
    }

    else if (counter2 == 2) {
      ClockEdit(9, 0, 0x01, "Minute");
    }

    else if (counter2 == 3) {
      ClockEdit(12, 0, 0x00, "Second");
    }


 if(counter2 ==4)counter2 =1;
     }
     else if(counter2_2 ==2 && counter1 ==2){

      
    lcd.setCursor(0, 0);

    lcd.print("Date: ");
    lcd.setCursor(8, 0);
    lcd.print(':');
    lcd.setCursor(11, 0);
    lcd.print(":");

   

      if (counter2 == 1)  {

      ClockEdit(6, 0, 0x04, "Date");
    }
    else if (counter2 == 2) {
      ClockEdit(9, 0, 0x05, "Month");
    }
    else if (counter2 ==3) {
      ClockEdit(12, 0, 0x06, "Year");
    }
    if(counter2 ==4)counter2 =1;
      
     }
     

     else if(counter2_2 ==3 && counter1 ==2){

      /////////// alaram ///////////////
      lcd.setCursor(0,0);
      lcd.print("Alaram Done");

      
     }

     else if(counter2_2 ==4 && counter1 ==2){

      lcd.setCursor(0,0);
      lcd.print("Day : ");

         if (counter2 == 1) {
      ClockEdit(6, 0, 0x03, "Day");
     
    }
     if(counter2 ==2)counter2 =1;
      
     }

  button_state_old = button_state_new; // updating the variable
  btst_old1 = btst_new1;
  btst_old2 = btst_new2;
  if (counter == 4) counter = 1; // setting the max num of pages in the screen to 3
  if (counter1 == 3) counter1 = 0;

}


void CollectData()
{
  Wire.beginTransmission(deviceAddress); // begining the transmission from the device
  Wire.write(0x00); // the first register out of the 7 registers
  Wire.endTransmission(); // end the transmission

  Wire.requestFrom(deviceAddress, 7); // requesting data from the 7 register of the clock module
  Seconds = Wire.read();
  Minutes = Wire.read();
  Hours = Wire.read();
  Day = Wire.read();
  Date = Wire.read();
  Month = Wire.read();
  Year = Wire.read();

  ////// calculating the numerical values of hrs mins and secs from the clock module /////
  hrs = (Hours >> 4) * 10 + (Hours & 15);
  mins = (Minutes >> 4) * 10 + (Minutes & 15);
  secs = (Seconds >> 4) * 10 + (Seconds & 15);
}


void ShowOnLcd() {

  int day = Day & 15;
  String pot;

  switch (day) {
    case 1: pot = "Sun";
      break;
    case 2: pot = "Mon";
      break;
    case 3: pot = "Tue";
      break;
    case 4: pot = "Wed";
      break;
    case 5: pot = "Thr";
      break;
    case 6: pot = "Fri";
      break;
    case 7: pot = "Sat";
      break;
    default: lcd.print("Invalid Input");
      break;

  }


  lcd.print("Time: ");
  lcd.print(Hours >> 4); lcd.print(Hours & 15); lcd.print(':');
  lcd.print(Minutes >> 4); lcd.print(Minutes & 15); lcd.print(':');
  lcd.print(Seconds >> 4); lcd.print(Seconds & 0x0F);

  lcd.setCursor(0, 1); // first argument which column second argument which row (up or down )
  lcd.print(pot);
  lcd.print(" : ");
  lcd.print(Date >> 4); lcd.print(Date & 15); lcd.print("/");
  lcd.print(Month >> 4); lcd.print(Month & 15); lcd.print("/");
  lcd.print(Year >> 4); lcd.print(Year & 15);
  lcd.setCursor(0, 0); //re=position the cursor

}

float HrConverter (float hr, float min) {

  float hour = hr +  (min / 60);


  return hour;
}

void ClockEdit(int column, int row, int reg_address, String bucket) {

  if (bucket == "Second") {
    if (counter3 == 61)counter3 = 0;
  }
  if (bucket == "Minute") {
    if (counter3 == 61)counter3 = 0;
  }
  if (bucket == "Hour") {
    if (counter3 == 25)counter3 = 0;
    lcd.setCursor(7, 0);
    lcd.print(" ");
  }
  if (bucket == "Day") {
    if (counter3 == 8)counter3 = 1;
  }
  if (bucket == "Date") {
    if (counter3 == 32)counter3 = 1;
  }
  if (bucket == "Year") {
    if (counter3 == 100)counter3 = 1;
  }


  lcd.setCursor(column, row); // for hours
  lcd.blink();
  delay(300);
  value = counter3;

  lcd.setCursor(column, row);
  if (counter2 == 1 && counter2_2 ==4&&counter1 ==2) {

    if (counter3 == 0)lcd.print("non");
    else if (counter3 == 1)lcd.print("Sun");
    else if (counter3 == 2)lcd.print("Mon");
    else if (counter3 == 3)lcd.print("Tue");
    else if (counter3 == 4)lcd.print("Wed");
    else if (counter3 == 5)lcd.print("Thr");
    else if (counter3 == 6)lcd.print("Fri");
    else if (counter3 == 7)lcd.print("Sat");
  }
  else lcd.print(counter3);
  value = ((value / 10) << 4) + (value % 10);
  Wire.beginTransmission(deviceAddress);
  Wire.write(reg_address);                     // assessing the hour  register
  Wire.write(value);               // wrinting to the hour register
  Wire.endTransmission();
  delay(300);

}
