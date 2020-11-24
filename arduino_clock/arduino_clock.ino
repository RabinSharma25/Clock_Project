#include<EEPROM.h>

int integer;     // inital integer which we take from the user
int divisor = 2; // global divisor

int last_digits;  // for seconds
int first_digits; // for seconds
//int *nums;
int bits[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int flag2 = 0;

String bitval;
String sec, minss, hr, day, date, month, year;
int flag;

int secs,mins,hrs,days,dates,months,years; // converting to int (variables to store data);

int bitvals;

void setup()
{
  Serial.begin(9600);

String entered_day;


    String names;
    //int v;
    Serial.println("Enter the initial time in seconds  ");
    while (Serial.available()==0){
    
    }
    integer = Serial.parseInt();
    digit_splitter(integer);
    binary_converter(first_digits, last_digits);
    bits_conc();
    initial_bits();
    //Serial.print(/n);
    flag = 1;
    flag2 = 1;

    Serial.println("Enter the initial time in  minutes ") ;
    while (Serial.available()==0){
   
    }
     integer = Serial.parseInt();
    digit_splitter(integer);
    binary_converter(first_digits, last_digits);
    bits_conc();
    initial_bits();
    //Serial.println(/n);
    flag = 2;
    flag2 = 2;

    Serial.println("Enter the initial time in hours in whichever format you want that is 12 or 24 " );
    while(Serial.available() ==0){
    }
    integer = Serial.parseInt();
    digit_splitter(integer);
    binary_converter(first_digits, last_digits);
    bits_conc();
    initial_bits();
    //Serial.println(/n);
    flag = 0;
    flag2 = 3;

    Serial.println( "Enter the day which you want to set initially " );
    while(Serial.available() ==0){
    }
     entered_day =Serial.readString();
    day_set(entered_day);
    names = bitval;
    Serial.println(names);
    //cout << endl;
    flag2 = 4;

    Serial.println("Enter the initial date ") ;
      while (Serial.available()==0){
    
    }
    integer = Serial.parseInt();
    digit_splitter(integer);
    binary_converter(first_digits, last_digits);
    bits_conc();
    initial_bits();
    //cout << endl;
    flag2 = 5;

    Serial.println("Enter the initial month " );
      while (Serial.available()==0){
    
    }
    integer = Serial.parseInt();
    digit_splitter(integer);
    binary_converter(first_digits, last_digits);
    bits_conc();
    initial_bits();
    flag2 = 6;

    Serial.println( "Enter the initial year " );
      while (Serial.available()==0){
    
    }
    integer = Serial.parseInt();
    digit_splitter(integer);
    binary_converter(first_digits, last_digits);
    bits_conc();
    initial_bits();


    //////////////////////////


    
}

void loop(){

  //Serial.println("you are in the loop ");
}





int digit_splitter(int integers){
    last_digits = integers % 10;
    first_digits = (integers - last_digits) / 10;
    // cout<<first_digits<<endl;
    // cout<<last_digits<<endl;
    return 0;
}

int day_set(String day)
{

    if (day == "Sunday")
    {
        bitval = "0b00000001";
        bitvals = binaryStringToInt(bitval);
    }
    else if (day == "Monday")
    {
        bitval = "0b00000010";
        bitvals = binaryStringToInt(bitval);
    }
    else if (day == "Tuesday")
    {
        bitval = "0b00000011";
        bitvals = binaryStringToInt(bitval);
    }
    else if (day == "Wednesday")
    {
        bitval = "0b00000100";
        bitvals = binaryStringToInt(bitval);
    }
    else if (day == "Thrusday")
    {
        bitval = "0b00000101";
        bitvals = binaryStringToInt(bitval);
    }
    else if (day == "Friday")
    {
        bitval = "0b00000110";
        bitvals = binaryStringToInt(bitval);
    }
    else if (day == "Saturday")
    {
        bitval = "0b00000111";
        bitvals = binaryStringToInt(bitval);
    }
    else
    {
        bitval = "0b00000000";
        bitvals = binaryStringToInt(bitval);
    }

    EEPROM[6] = bitvals;

    return 0;
}

int binary_converter(int first_digit, int last_digit)
{

    int j = 7;
    int k = 3;
    int result1 = 3;
    int result2 = 3;

    while (divisor <= result1)
    {

        result1 = last_digit / divisor;
        bits[j] = last_digit % divisor;
        last_digit = result1;
        bits[j--];
        if (result1 < divisor)
        {
            bits[j--] = result1;
        }
        else
            continue;
    }

    while (divisor <= result2)
    {

        result2 = first_digit / divisor;
        bits[k] = first_digit % divisor;
        first_digit = result2;
        bits[k--];
        if (result2 < divisor)
        {
            bits[k--] = result2;
        }
        else
            continue;

        if (flag == 2)
        {
            Serial.println("Enter the time format. ");
            Serial.println("For 12 hr time format enter 12, and for 24 hr time  format enter 24");
            String period;
            while(Serial.available() == 0){
              
            }
            period = Serial.readString();
            if (period == "12")
            {bits[1] = 1; // sets the time format to 12 hr format
             }
            else bits[1]=0;// sets to 24 hr format 
            if (bits[1] == 1)
            {    
                String cycle;
                Serial.println(" Enter the clock  cycle that is am or pm");
                Serial.println("For am clock cycle enter AM and for pm clock cycle enter PM");
                while(Serial.available() ==0){
                  
                }
                 cycle = Serial.readString();
            if(cycle =="AM"){

            }
                bits[2] = 0; // setting it to am 
            }
            else bits[2] = 1;
        }
        else
            continue;
    }

    return 0;
}



////////////////////////////////////////////////////////////////////
void bits_conc(){ // concatenating the strings 
    int v0, v1, v2, v3, v4, v5, v6, v7, v8;
    String s0, s1, s2, s3, s4, s5, s6, s7;

    for (int i = 0; i <= 8; i++)
    {

        if (i == 0)
        {
            v0 = bits[i];
            s0 = String(v0);
        }
        else if (i == 1)
        {
            v1 = bits[i];
            s1 = String(v1);
        }
        else if (i == 2)
        {
            v2 = bits[i];
            s2 = String(v2);
        }
        else if (i == 3)
        {
            v3 = bits[i];
            s3 = String(v3);
        }
        else if (i == 4)
        {
            v4 = bits[i];
            s4 = String(v4);
        }
        else if (i == 5)
        {
            v5 = bits[i];
            s5 = String(v5);
        }
        else if (i == 6)
        {
            v6 = bits[i];
            s6 = String(v6);
        }
        else if (i == 7)
        {
            v7 = bits[i];
            s7 = String(v7);
        }
    }
    String cha = "0b";
    if (flag2 == 0)
    {
        sec = cha + s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;
        
        Serial.println(sec);
        secs = binaryStringToInt(sec);
        Serial.println(secs);
        EEPROM[3] = secs;
    }
    else if (flag2 == 1)
    {
        minss = cha + s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;
        Serial.println(minss);
        mins = binaryStringToInt(minss);
        Serial.println(mins);
        EEPROM[4] = mins;
    }
    else if (flag2 == 2)
    {
        hr = cha + s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;
        Serial.println(hr);
        hrs = binaryStringToInt(hr);
        Serial.println(hrs);
        EEPROM[5] = hrs;
    }
    else if (flag2 == 4)
    {
        date = cha + s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;
        Serial.println(date);
        dates = binaryStringToInt(date);
        Serial.println(dates);
        EEPROM[7] = dates;
    }
    else if (flag2 == 5)
    {
        month = cha + s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;
        Serial.println(month);
        months = binaryStringToInt(month);
        Serial.println(months);
        EEPROM[8] = months;
    }
    else if (flag2 == 6)
    {
        year = cha + s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;
       Serial.println(year);
        years = binaryStringToInt(year);
        Serial.println(years);
        EEPROM[9] = years;
    }

    return 0;
}

//////////////////////////////////////////////
   void initial_bits(){
    bits[0] = 0;
    bits[1] = 0;
    bits[2] = 0;
    bits[3] = 0;
    bits[4] = 0;
    bits[5] = 0;
    bits[6] = 0;
    bits[7] = 0;
    bits[8] = 0;
   }



unsigned int binaryStringToInt(String str)
{
    unsigned int mask = 1;
    unsigned int result = 0;

    for (int i = str.length() - 1; i >= 0; i--)
    {
        if (str[i] == '1')
            result = result | mask;

        if (str[i] == 'b')
            break;

        mask = mask << 1;
    }

    return result;
}
