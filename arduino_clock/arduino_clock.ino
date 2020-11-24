#include<Wire.h>

#define deviceAddress 0b1101000 //0x68
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint8_t pinA = 2; 
const uint8_t pinB = 3; 
const uint8_t pinC = 4; 
const uint8_t pinD = 5; 
const uint8_t pinE = 6; 
const uint8_t pinF = 7; 
const uint8_t pinG = 0; // set to port b //connect to pin 8 // as the first bit shall correspond to 0;

const uint8_t cat1 = 1; // connect of pin 9
const uint8_t cat2 = 2; // connect  to pin 10
const uint8_t cat3 = 3; // donnect to pin 11
const uint8_t cat4 = 4; // connect to pin 12
int value1 ;
int value2 ;
float freq =  1;
float freq2 = 0;
int first_val;
int second_val;

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


  byte bcdSeconds ;
  byte bcdMinutes ;
  byte bcdHours ;  //ignore Hours reading
  byte bcdDay ;
  byte bcdDate;
  byte bcdMonth;
  byte bcdYear ;

  int secs,mins,hrs;


     int curSec  ;
    int curMin ;
    int curHr ; // current time = 4:40:32 

    int ArSec = 0; 
    int ArMin = 15;
    int ArHr = 5 ; // time = 5:30:5 s

void setup(){
  pinMode(13,LOW);
  Serial.begin(9600);
  Wire.begin();
    lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0); //DP0 of Topline

  
  //Serial.begin(9600);
  DDRD |= (1<<pinA|1<<pinB|1<<pinC|1<<pinD|1<<pinE|1<<pinF); // setting all pins to output 
  DDRB |= (1<<pinG);
  DDRB |= (1<<cat1|1<<cat2|1<<cat3|1<<cat4);
  //Serial.print(val0);

  
  
}


void loop(){




  ///////////////////////////////////////
   //showTimeOnLCD();
digit_splitter(value1);
display_seg_value1_f();
display_seg_value1_l();
CollectData();
digit_splitter(value2);
display_seg_value2_f();
display_seg_value2_l();
//showTimeOnLCD();
printOnLcd();
delay(2);

 if(curHr < 9) curHr+=24;
     if(ArHr<9) ArHr += 24;
    
   //cout<< HrConverter(ArHr,ArMin)<<endl;
    //cout<<HrConverter(curHr,curMin)<<endl;
    float diff = HrConverter(ArHr,ArMin) - HrConverter(hrs,mins);
   // printf("%f\n",diff);

    float to_min = diff*60; // converting to minutes ;;
    //cout<< "in minutes = " <<to_min<<endl;
    int hrss = to_min / 60;
   // cout<< "Time left in hrs =" << hrs<<endl;
    int  minss =int(to_min) %60;
   // cout<< "Time left in mins = " << mins<<endl;

value1=hrss ;
value2= minss;
}
void display_seg_value1_f(){

  if(first_val ==0){
      PORTD = val0D;
      PORTB = val0B;
      digitalWrite(9,LOW);
      delay(freq);
  }

    else if(first_val ==1){
      PORTD = val1D;
      PORTB = val1B;
      digitalWrite(9,LOW);
      delay(freq);
  }

    else if(first_val ==2){
      PORTD = val2D;
      PORTB = val2B;
      digitalWrite(9,LOW);
      delay(freq);
  }

    else if(first_val ==3){
      PORTD = val3D;
      PORTB = val3B;
      digitalWrite(9,LOW);
      delay(freq);      
  }

    else if(first_val ==4){
      PORTD = val4D;
      PORTB = val4B;
      digitalWrite(9,LOW);
      delay(freq);      
  }

    else if(first_val ==5){
      PORTD = val5D;
      PORTB = val5B;   
      digitalWrite(9,LOW);
      delay(freq);
      
}

    else if(first_val ==6){
      PORTD = val6D;
      PORTB = val6B;
      digitalWrite(9,LOW);
      delay(freq);
}  

    else if(first_val ==7){
      PORTD = val7D;
      PORTB = val7B;
      digitalWrite(9,LOW);
      delay(freq);
}

    else if(first_val ==8){
      PORTD = val8D;
      PORTB = val8B;
      digitalWrite(9,LOW);
      delay(freq);      
}

    else if(first_val ==9){
      PORTD = val9D;
      PORTB = val9B;
      digitalWrite(9,LOW);
      delay(freq);      
}

}


void display_seg_value1_l(){

  if(second_val ==0){
      PORTD = val0D;
      PORTB = val0B;
      digitalWrite(10,LOW);
      delay(freq);
  }

    else if(second_val ==1){
      PORTD = val1D;
      PORTB = val1B;
      digitalWrite(10,LOW);
      delay(freq);      
  }

    else if(second_val ==2){
      PORTD = val2D;
      PORTB = val2B;
      digitalWrite(10,LOW);
      delay(freq);      
  }

    else if(second_val ==3){
      PORTD = val3D;
      PORTB = val3B;
      digitalWrite(10,LOW);
      delay(freq);      
  }

    else if(second_val ==4){
      PORTD = val4D;
      PORTB = val4B;
      digitalWrite(10,LOW);
      delay(freq);      
  }

    else if(second_val ==5){
      PORTD = val5D;
      PORTB = val5B;
      digitalWrite(10,LOW);
      delay(freq);      
}

    else if(second_val ==6){
      PORTD = val6D;
      PORTB = val6B;
      digitalWrite(10,LOW);
      delay(freq);
}  

    else if(second_val ==7){
      PORTD = val7D;
      PORTB = val7B;
      digitalWrite(10,LOW);
      delay(freq);      
}

    else if(second_val ==8){
      PORTD = val8D;
      PORTB = val8B;
      digitalWrite(10,LOW);
      delay(freq);      
}

    else if(second_val ==9){
      PORTD = val9D;
      PORTB = val9B;
      digitalWrite(10,LOW);
      delay(freq);      
}

}


///////////////////////////////////

void display_seg_value2_f(){

  if(first_val ==0){
      PORTD = val0D;
      PORTB = val0B;
      digitalWrite(11,LOW);
      delay(freq);
  }

    else if(first_val ==1){
      PORTD = val1D;
      PORTB = val1B;
      digitalWrite(11,LOW);
      delay(freq);
  }

    else if(first_val ==2){
      PORTD = val2D;
      PORTB = val2B;
      digitalWrite(11,LOW);
      delay(freq);
  }

    else if(first_val ==3){
      PORTD = val3D;
      PORTB = val3B;
      digitalWrite(11,LOW);
      delay(freq);      
  }

    else if(first_val ==4){
      PORTD = val4D;
      PORTB = val4B;
      digitalWrite(11,LOW);
      delay(freq);      
  }

    else if(first_val ==5){
      PORTD = val5D;
      PORTB = val5B;   
      digitalWrite(11,LOW);
      delay(freq);
      
}

    else if(first_val ==6){
      PORTD = val6D;
      PORTB = val6B;
      digitalWrite(11,LOW);
      delay(freq);
}  

    else if(first_val ==7){
      PORTD = val7D;
      PORTB = val7B;
      digitalWrite(11,LOW);
      delay(freq);
}

    else if(first_val ==8){
      PORTD = val8D;
      PORTB = val8B;
      digitalWrite(11,LOW);
      delay(freq);      
}

    else if(first_val ==9){
      PORTD = val9D;
      PORTB = val9B;
      digitalWrite(11,LOW);
      delay(freq);      
}

}


void display_seg_value2_l(){

  if(second_val ==0){
      PORTD = val0D;
      PORTB = val0B;
      digitalWrite(12,LOW);
      delay(freq2);
  }

    else if(second_val ==1){
      PORTD = val1D;
      PORTB = val1B;
     // digitalWrite(8,HIGH);
      digitalWrite(12,LOW);
      delay(freq2);      
  }

    else if(second_val ==2){
      PORTD = val2D;
      PORTB = val2B;
      digitalWrite(12,LOW);
      delay(freq2);      
  }

    else if(second_val ==3){
      PORTD = val3D;
      PORTB = val3B;
      digitalWrite(12,LOW);
      delay(freq2);      
  }

    else if(second_val ==4){
      PORTD = val4D;
      PORTB = val4B;
      digitalWrite(12,LOW);
      delay(freq2);      
  }

    else if(second_val ==5){
      PORTD = val5D;
      PORTB = val5B;
      digitalWrite(12,LOW);
      delay(freq2);      
}

    else if(second_val ==6){
      PORTD = val6D;
      PORTB = val6B;
      digitalWrite(12,LOW);
      delay(freq2);
}  

    else if(second_val ==7){
      PORTD = val7D;
      PORTB = val7B;
      digitalWrite(12,LOW);
      delay(freq2);      
}

    else if(second_val ==8){
      PORTD = val8D;
      PORTB = val8B;
      digitalWrite(12,LOW);
      delay(freq2);      
}

    else if(second_val ==9){
      PORTD = val9D;
      PORTB = val9B;
      digitalWrite(12,LOW);
      delay(freq2);      
}

}
void digit_splitter(int a){

second_val = a%10;
first_val  = (a - second_val)/10;
//Serial.println(second_val);
//Serial.println(first_val);
}

void CollectData()
{
  Wire.beginTransmission(deviceAddress); //START, Roll Cal
  Wire.write(0x00); //pointing SEC Register at address 0x00 (Fig-2)
  Wire.endTransmission(); //Execute the above queued data, ACK, STOP

  Wire.requestFrom(deviceAddress, 7);   //SEC, MIN, and HRS to read from RTC as BCD
  bcdSeconds = Wire.read();
   bcdMinutes = Wire.read();
   bcdHours = Wire.read();  //ignore Hours reading
  bcdDay = Wire.read();
  bcdDate = Wire.read();
   bcdMonth = Wire.read();
   bcdYear = Wire.read();
}
  
  //---show Time on LCD---------------
  void printOnLcd(){

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
    hrs = (bcdHours>>4)*10 + (bcdHours &15);
    //lcd.print(hrs);lcd.print(":");
    mins = (bcdMinutes>>4)*10 + (bcdMinutes &15);
    //lcd.print(mins);lcd.print(":");
    secs = (bcdSeconds>>4)*10 + (bcdSeconds &15);
    //lcd.print(secs);lcd.print(":");
   

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

float HrConverter (float hr, float min){
   
    float hour = hr +  (min/60);
    //printf(hour);
   

    return hour;
}
