#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h> 

SoftwareSerial mySerial(12, 13);

LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x23, 16, 2);

Servo myservo1;
Servo myservo2;

int Button_1 = 4;
int Button_2 = 5;
int Button_3 = 6;
int Button_4 = 7;

int Sensor_1 = A0;
int Sensor_2 = A1;
int Sensor_3 = A2;
int Sensor_4 = A3;

String Tag = "/3800A8C5F1A4/3800A8BB644F/39008F6BD30E/3900908B1F3D/39008F6BDE03" ;

String TagD ="AAAAAAAAAAAA";
String Tag1 ="3800A8C5F1A4";
String Tag2 ="3800A8BB644F";
String Tag3 ="39008F6BD30E";
String Tag4 ="3900908B1F3D";
String Tag5 ="39008F6BDE03";

int BAL[] = { 1000, 1000, 1000, 1000, 1000 };
int TIME[] = { 0,0,0,0,0 };

int Add_Bal;

int D_Time;
int T_Price = 2;
int B_Price = 10;

int Bill;

int Rem_Bal;
int Rec_Bal;
int Che_Bal;

int Mode;

uint8_t yes[8] = {
  0b00000,
  0b00001,
  0b00010,
  0b10100,
  0b01001,
  0b00010,
  0b10100,
  0b01000
};

uint8_t no[8] = {
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000
};

int Val;
 
void setup(){
  Tag = TagD+Tag1+Tag2+Tag3+Tag4+Tag5;
  
    Serial.begin(9600);
  mySerial.begin(9600);
 
  lcd1.begin();lcd1.setCursor(0,0);lcd1.print("    ENTRANCE    ");lcd1.setCursor(0,1);lcd1.print("      GATE      ");
  lcd2.begin();lcd2.setCursor(0,0);lcd2.print("      EXIT      ");lcd2.setCursor(0,1);lcd2.print("      GATE      ");

  lcd1.createChar(0, yes);
  lcd1.createChar(1, no);
  
  pinMode(Button_1,INPUT_PULLUP);
  pinMode(Button_2,INPUT_PULLUP);
  pinMode(Button_3,INPUT_PULLUP);
  pinMode(Button_4,INPUT_PULLUP);

  pinMode(Sensor_1,INPUT);
  pinMode(Sensor_2,INPUT);
  pinMode(Sensor_3,INPUT);
  pinMode(Sensor_4,INPUT);
  
  myservo2.attach(2);
  myservo1.attach(11);

  delay(3000);
}

void loop(){
  myservo1.write(100);
  myservo2.write(10);
  
  if ( digitalRead(Button_1) == LOW) { Mode = !Mode; delay(1000); }

  if ( Mode == 1 ) { RM(); }
  if ( Mode == 0 ) { BM(); }
}

void BM(){
  if (digitalRead(Sensor_1)==0){lcd1.setCursor(0,0);lcd1.print("SLOT1:");lcd1.write(1);lcd1.print(" ");} 
  else                         {lcd1.setCursor(0,0);lcd1.print("SLOT1:");lcd1.write(0);lcd1.print(" ");} 

  if (digitalRead(Sensor_2)==0){lcd1.setCursor(8,0);lcd1.print("SLOT2:");lcd1.write(1);lcd1.print(" ");} 
  else                         {lcd1.setCursor(8,0);lcd1.print("SLOT2:");lcd1.write(0);lcd1.print(" ");} 

  if (digitalRead(Sensor_3)==0){lcd1.setCursor(0,1);lcd1.print("SLOT3:");lcd1.write(1);lcd1.print(" ");} 
  else                         {lcd1.setCursor(0,1);lcd1.print("SLOT3:");lcd1.write(0);lcd1.print(" ");} 

  if (digitalRead(Sensor_4)==0){lcd1.setCursor(8,1);lcd1.print("SLOT4:");lcd1.write(1);lcd1.print(" ");} 
  else                         {lcd1.setCursor(8,1);lcd1.print("SLOT4:");lcd1.write(0);lcd1.print(" ");} 
 
  lcd2.setCursor(0,0);lcd2.print("      EXIT      ");lcd2.setCursor(0,1);lcd2.print("      GATE      ");
   
  ReadCard_M();
  ReadCard_S(); 
}

void RM(){
  if(Serial.available()){
    String R_Tag = Serial.readString();
    int ID;
    
    ID = Tag.indexOf(R_Tag);
    ID = ID/12 - 1;
   
    BAL[ID] = BAL[ID] + Add_Bal;

    Add_Bal = 0;

    lcd2.setCursor(0,0); lcd2.print("BALANCE: "); lcd2.print(BAL[ID]); lcd2.print(" INR ");

    if ( Add_Bal == 0 ) { lcd2.setCursor(0,1); lcd2.print("SELECT AMOUNT..."); }
    else                { lcd2.setCursor(0,1); lcd2.print("RECHARGE SUCESS "); }
    
    delay(4000);
    } 
 
  if      ( digitalRead(Button_2) == LOW) { Add_Bal = 1000; }
  else if ( digitalRead(Button_3) == LOW) { Add_Bal = 2000; }
  else if ( digitalRead(Button_4) == LOW) { Add_Bal = 5000; }
  
  if ( Add_Bal == 0 ){
    lcd2.setCursor(0,0); lcd2.print("RECHARGE MODE   ");
    lcd2.setCursor(0,1); lcd2.print("SELECT AMOUNT...");
    }

  else {
    lcd2.setCursor(0,0); lcd2.print("AMOUNT : ");  lcd2.print(Add_Bal);  lcd2.print(" INR");
    lcd2.setCursor(0,1); lcd2.print("SCAN CARD       ");
    }  
  }
  
void ReadCard_M() {
  if(mySerial.available()){
    String R_Tag = mySerial.readString();

    Val = Tag.indexOf(R_Tag);
    Val = Val/12 - 1;
 
    myservo1.write(10);
      
    lcd1.setCursor(0,0); lcd1.print("    WEL-COME    ");
    lcd1.setCursor(0,1); lcd1.print("BAL. = "); lcd1.print(BAL[Val]); lcd1.print(" INR ");

    TIME[Val] = millis()/1000 ;
             
    delay(4000); 

    myservo1.write(100);
    }   
  }

void ReadCard_S() {
  if(Serial.available()){
    String R_Tag = Serial.readString();

    int Val = Tag.indexOf(R_Tag);
    Val = Val/12 - 1;

    D_Time=millis()/1000-TIME[Val]; 
    Bill=D_Time*T_Price + B_Price; 

    if ( BAL[Val] > Bill ){    
      myservo2.write(100);
      
      BAL[Val]=BAL[Val]-Bill; 

      lcd2.setCursor(0,0); lcd2.print("TIME= ");  lcd2.print(D_Time);  lcd2.print(" Min "); 
      lcd2.setCursor(0,1); lcd2.print("BILL= ");  lcd2.print(Bill);    lcd2.print(" INR ");   delay(3000);
      
      lcd2.setCursor(0,0); lcd2.print("REM BAL= "); lcd2.print(BAL[Val]); lcd2.print(" INR ");
      lcd2.setCursor(0,1); lcd2.print("   THANK YOU    ");

      delay(4000);

      myservo2.write(10);
    }

    else { 
      lcd2.setCursor(0,0); lcd2.print("LOW BALANCE     ");
      lcd2.setCursor(0,1); lcd2.print("BAL. = "); lcd2.print(BAL[Val]); lcd2.print(" INR ");
      delay(4000);
      }
    }
  }
