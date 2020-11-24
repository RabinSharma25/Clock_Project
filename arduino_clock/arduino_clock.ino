/*
        _a
      f|_|b
      e|_|c
        d


*/

// this code is in a total working condition as expected //// it is stored for future reference 
#include<Wire.h>
#include<EEPROM.h>
#define deviceAddress 0b1101000 //0x68 the adddress of DS3231 clock module 
#include<LiquidCrystal_I2C.h> // including the library for the display 
LiquidCrystal_I2C lcd(0x27, 16, 2); // creating an display object (lcd), with address and size mentioned

///////////// PORTD pins to segement display /////////////
const uint8_t pinA = 2;
const uint8_t pinB = 3;
const uint8_t pinC = 4;
const uint8_t pinD = 5;
const uint8_t pinE = 6;
const uint8_t pinF = 7;
//
const uint8_t pinG = 0; // set to port b //connect to pin 8 // as the first bit shall correspond to 0;

////////////////// PORTB pins to segement display ////
const uint8_t cat1 = 1; // connect of pin 9 of arduino
const uint8_t cat2 = 2; // connect  to pin 10 of arduino
const uint8_t cat3 = 3; // donnect to pin 11 of arduino
const uint8_t cat4 = 4; // connect to pin 12 of arduino

int value1 ;
int value2 ;
int freq = 5;
int first_val ;
int second_val;

// setting up the digits in binary for ease

int val0D = B11111100; // fedcba00
int val0B = B00011110; // 0000000g

int val1D = B00011000;
int val1B = B00011110;

int val2D = B01101100;
int val2B = B00011111;

int val3D = B00111100;
int val3B = B00011111;

int val4D = B10011000;
int val4B = B00011111;

int val5D = B10110100;
int val5B = B00011111;

int val6D = B11110100;
int val6B = B00011111;

int val7D = B00011100;
int val7B = B00011110;

int val8D = B11111100;
int val8B = B00011111;

int val9D = B10111100;
int val9B = B00011111;

//////////// variables to store the data from the clock module //////////////

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


  DDRD |= (1 << pinA | 1 << pinB | 1 << pinC | 1 << pinD | 1 << pinE | 1 << pinF); // setting all pins to output
  DDRB |= (1 << pinG);
  DDRB |= (1 << cat1 | 1 << cat2 | 1 << cat3 | 1 << cat4);
  //Serial.print(val0);

  pinMode(btnPin, INPUT); // declaring pin 13 as input
  pinMode(button1, INPUT);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(12, OUTPUT);


}


void loop() {
  //
  button_state_new = digitalRead(btnPin);  // reading the state of  btnpin
  if (button_state_old == 1 && button_state_new == 0) {
    lcd.clear();
    counter++; // incrementing the counter variable to flip the pages in the screen
    //if(counter !=6||counter!=7||counter!=5) counter1 = 1;
    //lcd.clear(); // clearing the screen for removing the previous output


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
    if(counter == 5 && counter1 ==1)counter2_2++;
    else if(counter ==5 && counter ==2) counter2++;
    else counter2++;

  }



  btst_new3 = digitalRead(button3);  // reading the state of  btnpin
  if (btst_old3 == 1 && btst_new3 == 0) {
    counter3 ++;
  }



  //    if(counter2 ==5);counter2 = 1;
  //  }




  ///////////////////////////////////////

  CollectData(); // function that collects data from the clock module


  if (counter == 1) {

    ShowOnLcd(); // function that prints on the lcd screen
    digitalWrite(12, HIGH); // for turning off the last digit in the segment display after a page fli

  }

  else if (counter == 2) {

    if (curHr < 9) curHr += 24;
    if (ArHr < 9) ArHr += 24;

    float diff = HrConverter(ArHr, ArMin) - HrConverter(hrs, mins);

    float to_min = diff * 60; // converting to minutes ;;
    int hrss = to_min / 60;
    int  minss = int(to_min) % 60;
    //lcd.setCursor(0,0);
    //lcd.print("Segment Time");

    value1 = hrss ; // passing the first value to be printed in the segment display
    value2 = minss; // passing the second value to be printed in the segment display
    digit_splitter(value1); // function that splits the two digit number into two seprate ditits for printing in the segement display (value1 as argument)
    display_seg_value1_f(); // function that prints the first ditit of value1 in the screen
    display_seg_value1_l(); // function that prints the last digit of the value1 in the screen
    digit_splitter(value2);  // function that splits the two digit number into two seprate ditits for printing in the segement display (value2 as argumemnt)
    display_seg_value2_f();  //function that prints the first ditit of value2 in the screen
    display_seg_value2_l();  // function that prints the last digit of the value2 in the screen


  }

  else if (counter == 3) {

    ///// here we show the configured time for the alaram by the useer in the lcd display (when conter is 3 that is set to page 3 )///

    digitalWrite(12, HIGH); // turing off the last digit in the segement display(bug);
    lcd.setCursor(1, 0); // setting the cursor position
    lcd.print("Alarm Set for :");
    lcd.setCursor(1, 1);
    if (ArHrs < 10 && ArMins > 10) {
      lcd.print(0);
      lcd.print(ArHrs);
      lcd.print(":");
      lcd.print(ArMins);
    }
    else if (ArMins < 10 && ArHrs > 10) {
      lcd.print(ArHrs);
      lcd.print(":");
      lcd.print(0);
      lcd.print(ArMins);
    }
    else if (ArHrs < 10 && ArMins < 10) {
      lcd.print(0);
      lcd.print(ArHrs);
      lcd.print(":");
      lcd.print(0);
      lcd.print(ArMins);
    }
    else {
      lcd.print(ArHrs);
      lcd.print(":");
      lcd.print(ArMins);
    }
  }
  else if (counter == 4) {
    lcd.setCursor(0, 0);
    lcd.print("Temp :");
    lcd.print(32); lcd.print(" deg"); lcd.print(" C");
    lcd.setCursor(5, 1);
    lcd.print(":");
    lcd.print(100); lcd.print(" deg"); lcd.print(" F");
  }
  else if (counter == 5 && counter1 ==0) {
    lcd.setCursor(1, 0);
    lcd.print("Setting Menu");
   // lcd.setCursor(5, 1);
    //lcd.print("Ahead");
  }
//  else if (counter == 6 && counter1 == 0) {
//    lcd.setCursor(0, 0);
//    lcd.print("Edit Date");
//    lcd.setCursor(0, 1);
//    lcd.print("and Time");
//  }
//  else if (counter == 7) {
//    lcd.setCursor(0, 0);
//    lcd.print("Edit Alarm");
//  }

//  else if (counter1 == 1 && counter ==5) {
//    //lcd.clear();
//    //counter = 0;
//    lcd.setCursor(0, 0);
//
//    lcd.print("Time: ");
//    ////lcd.print(counter3); lcd.print(" ");
//    lcd.setCursor(8, 0);
//    lcd.print(':');
//    lcd.setCursor(11, 0);
//    lcd.print(":");
//    // // lcd.print(" "); lcd.print(" " ); lcd.print(':');
//    ////lcd.print(" " ); lcd.print(0);
//
//    lcd.setCursor(0, 1); // first argument which column second argument which row (up or down )
//    lcd.print("Day");
//    lcd.print(" : ");
//    ////lcd.print(0); lcd.print(0);
//    lcd.setCursor(8, 1);
//    lcd.print("/");
//    // //lcd.print(0); lcd.print(0);
//    lcd.setCursor(11, 1);
//    lcd.print("/");
//    lcd.print("  "); //lcd.print(0);
//    lcd.setCursor(0, 0); //re=position the cursor
//
//    if (counter2 == 1) {
//      ClockEdit(0, 1, 0x03, "Day");
//      //lcd.setCursor(0,1)
//    }
//    else if (counter2 == 2) {
//
//      ClockEdit(6, 1, 0x04, "Date");
//    }
//    else if (counter2 == 3) {
//      ClockEdit(9, 1, 0x05, "Month");
//    }
//    else if (counter2 == 4) {
//      ClockEdit(12, 1, 0x06, "Year");
//    }
//    else if (counter2 == 5) {
//      ClockEdit(6, 0, 0x02, "Hour");
//    }
//
//    else if (counter2 == 6) {
//      ClockEdit(9, 0, 0x01, "Minute");
//    }
//
//    else if (counter2 == 7) {
//      ClockEdit(12, 0, 0x00, "Second");
//    }
//
//
//
//    if (counter2 == 8) counter2 = 1;
//    //
//  }

    else if(counter1 == 1 && counter ==5){
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
    ////lcd.print(counter3); lcd.print(" ");
    lcd.setCursor(8, 0);
    lcd.print(':');
    lcd.setCursor(11, 0);
    lcd.print(":");

    lcd.setCursor(0, 1); // first argument which column second argument which row (up or down )
    lcd.print("Day");
    lcd.print(" : ");
    lcd.setCursor(8, 1);
    lcd.print("/");
    lcd.setCursor(11, 1);
    lcd.print("/");
    lcd.print("  "); //lcd.print(0);
    lcd.setCursor(0, 0); //re=position the cursor

    if (counter2 == 1) {
      ClockEdit(0, 1, 0x03, "Day");
    }
    else if (counter2 == 2) {

      ClockEdit(6, 1, 0x04, "Date");
    }
    else if (counter2 == 3) {
      ClockEdit(9, 1, 0x05, "Month");
    }
    else if (counter2 == 4) {
      ClockEdit(12, 1, 0x06, "Year");
    }
    else if (counter2 == 5) {
      ClockEdit(6, 0, 0x02, "Hour");
    }

    else if (counter2 == 6) {
      ClockEdit(9, 0, 0x01, "Minute");
    }

    else if (counter2 == 7) {
      ClockEdit(12, 0, 0x00, "Second");
    }



//    if (counter2 == 8) counter2 = 1;
     }
//      else if (counter2 ==3 && counter1 ==2){
//        lcd.setCursor(0,0);lcd.print("You did it");
     // }






  button_state_old = button_state_new; // updating the variable
  btst_old1 = btst_new1;
  btst_old2 = btst_new2;
  // btst_old3 = btst_new3;
  if (counter == 6) counter = 1; // setting the max num of pages in the screen to 3
  if (counter1 == 3) counter1 = 0;

}



void display_seg_value1_f() {

  if (first_val == 0) {
    PORTD = val0D;
    PORTB = val0B;
    digitalWrite(9, LOW);
    delay(freq);
  }

  else if (first_val == 1) {
    PORTD = val1D;
    PORTB = val1B;
    digitalWrite(9, LOW);
    delay(freq);
  }

  else if (first_val == 2) {
    PORTD = val2D;
    PORTB = val2B;
    digitalWrite(9, LOW);
    delay(freq);
  }

  else if (first_val == 3) {
    PORTD = val3D;
    PORTB = val3B;
    digitalWrite(9, LOW);
    delay(freq);
  }

  else if (first_val == 4) {
    PORTD = val4D;
    PORTB = val4B;
    digitalWrite(9, LOW);
    delay(freq);
  }

  else if (first_val == 5) {
    PORTD = val5D;
    PORTB = val5B;
    digitalWrite(9, LOW);
    delay(freq);

  }

  else if (first_val == 6) {
    PORTD = val6D;
    PORTB = val6B;
    digitalWrite(9, LOW);
    delay(freq);
  }

  else if (first_val == 7) {
    PORTD = val7D;
    PORTB = val7B;
    digitalWrite(9, LOW);
    delay(freq);
  }

  else if (first_val == 8) {
    PORTD = val8D;
    PORTB = val8B;
    digitalWrite(9, LOW);
    delay(freq);
  }

  else if (first_val == 9) {
    PORTD = val9D;
    PORTB = val9B;
    digitalWrite(9, LOW);
    delay(freq);
  }

}


void display_seg_value1_l() {

  if (second_val == 0) {
    PORTD = val0D;
    PORTB = val0B;
    digitalWrite(10, LOW);
    delay(freq);
  }

  else if (second_val == 1) {
    PORTD = val1D;
    PORTB = val1B;
    digitalWrite(10, LOW);
    delay(freq);
  }

  else if (second_val == 2) {
    PORTD = val2D;
    PORTB = val2B;
    digitalWrite(10, LOW);
    delay(freq);
  }

  else if (second_val == 3) {
    PORTD = val3D;
    PORTB = val3B;
    digitalWrite(10, LOW);
    delay(freq);
  }

  else if (second_val == 4) {
    PORTD = val4D;
    PORTB = val4B;
    digitalWrite(10, LOW);
    delay(freq);
  }

  else if (second_val == 5) {
    PORTD = val5D;
    PORTB = val5B;
    digitalWrite(10, LOW);
    delay(freq);
  }

  else if (second_val == 6) {
    PORTD = val6D;
    PORTB = val6B;
    digitalWrite(10, LOW);
    delay(freq);
  }

  else if (second_val == 7) {
    PORTD = val7D;
    PORTB = val7B;
    digitalWrite(10, LOW);
    delay(freq);
  }

  else if (second_val == 8) {
    PORTD = val8D;
    PORTB = val8B;
    digitalWrite(10, LOW);
    delay(freq);
  }

  else if (second_val == 9) {
    PORTD = val9D;
    PORTB = val9B;
    digitalWrite(10, LOW);
    delay(freq);
  }

}


///////////////////////////////////

void display_seg_value2_f() {

  if (first_val == 0) {
    PORTD = val0D;
    PORTB = val0B;
    digitalWrite(11, LOW);
    delay(freq);
  }

  else if (first_val == 1) {
    PORTD = val1D;
    PORTB = val1B;
    digitalWrite(11, LOW);
    delay(freq);
  }

  else if (first_val == 2) {
    PORTD = val2D;
    PORTB = val2B;
    digitalWrite(11, LOW);
    delay(freq);
  }

  else if (first_val == 3) {
    PORTD = val3D;
    PORTB = val3B;
    digitalWrite(11, LOW);
    delay(freq);
  }

  else if (first_val == 4) {
    PORTD = val4D;
    PORTB = val4B;
    digitalWrite(11, LOW);
    delay(freq);
  }

  else if (first_val == 5) {
    PORTD = val5D;
    PORTB = val5B;
    digitalWrite(11, LOW);
    delay(freq);

  }

  else if (first_val == 6) {
    PORTD = val6D;
    PORTB = val6B;
    digitalWrite(11, LOW);
    delay(freq);
  }

  else if (first_val == 7) {
    PORTD = val7D;
    PORTB = val7B;
    digitalWrite(11, LOW);
    delay(freq);
  }

  else if (first_val == 8) {
    PORTD = val8D;
    PORTB = val8B;
    digitalWrite(11, LOW);
    delay(freq);
  }

  else if (first_val == 9) {
    PORTD = val9D;
    PORTB = val9B;
    digitalWrite(11, LOW);
    delay(freq);
  }

}


void display_seg_value2_l() {

  if (second_val == 0) {
    PORTD = val0D;
    PORTB = val0B;
    digitalWrite(12, LOW);
    delay(freq);
  }

  else if (second_val == 1) {
    PORTD = val1D;
    PORTB = val1B;
    // digitalWrite(8,HIGH);
    digitalWrite(12, LOW);
    delay(freq);
  }

  else if (second_val == 2) {
    PORTD = val2D;
    PORTB = val2B;
    digitalWrite(12, LOW);
    delay(freq);
  }

  else if (second_val == 3) {
    PORTD = val3D;
    PORTB = val3B;
    digitalWrite(12, LOW);
    delay(freq);
  }

  else if (second_val == 4) {
    PORTD = val4D;
    PORTB = val4B;
    digitalWrite(12, LOW);
    delay(freq);
  }

  else if (second_val == 5) {
    PORTD = val5D;
    PORTB = val5B;
    digitalWrite(12, LOW);
    delay(freq);
  }

  else if (second_val == 6) {
    PORTD = val6D;
    PORTB = val6B;
    digitalWrite(12, LOW);
    delay(freq);
  }

  else if (second_val == 7) {
    PORTD = val7D;
    PORTB = val7B;
    digitalWrite(12, LOW);
    delay(freq);
  }

  else if (second_val == 8) {
    PORTD = val8D;
    PORTB = val8B;
    digitalWrite(12, LOW);
    delay(freq);
  }

  else if (second_val == 9) {
    PORTD = val9D;
    PORTB = val9B;
    digitalWrite(12, LOW);
    delay(freq);
  }

}
void digit_splitter(int a) {

  second_val = a % 10;
  first_val  = (a - second_val) / 10;
  //Serial.println(second_val);
  //Serial.println(first_val);
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
  //if(counter2 ==1)counter3 = hrs;
  // else if(counter2 ==2) counter3 = mins;
  //else if (counter2 ==3) counter3 = secs;
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
  if (counter2 == 1) {

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
  //lcd.print(counter3);
  //lcd.print("  ");
  value = ((value / 10) << 4) + (value % 10);
  Wire.beginTransmission(deviceAddress);
  Wire.write(reg_address);                     // assessing the hour  register
  Wire.write(value);               // wrinting to the hour register
  Wire.endTransmission();
  delay(300);

}
