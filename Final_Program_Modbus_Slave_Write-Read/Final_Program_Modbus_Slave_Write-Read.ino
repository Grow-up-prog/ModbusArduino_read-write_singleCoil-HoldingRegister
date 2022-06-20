#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); //menggunakan LCD 16x2
//variabel state
int state=0;
int nav=0;
int freq=0;
int setFreq=0;
int aritmatika1=0;
int aritmatika2=0;

#define pinModBusDE 7 //logic 1 untuk kirim data
#define pinModBusRE 6 //logic 0 untuk terima data
const int bufferRequest =16;
byte Request [bufferRequest];
int readIndex=0;

void kirimData()
{
  digitalWrite(pinModBusDE,HIGH);
  digitalWrite(pinModBusRE,HIGH);
}
void terimaData()
{
  digitalWrite(pinModBusDE,LOW);
  digitalWrite(pinModBusRE,LOW);
}


//FRAME MODBUS 
byte enableMotor[] = {0x01,0x06,0x21,0x35,0x00,0x06,0x13,0xFA};//enable motor
byte reverseMotor[] = {0x01,0x06,0x21,0x35,0x08,0x0F,0xD4,0x3C};//reverse motor
byte forwardMotor[] = {0x01,0x06,0x21,0x35,0x00,0x0F,0xD3,0xFC};//forward motor
byte stopMotor[] = {0x01,0x06,0x21,0x35,0x10,0x0F,0xDE,0x3C};//stop motor
byte readFreqMotor[8] = {0x01,0x03,0x0C,0x82,0x00,0x01,0x27,0x72};//read freq motor
//setting no pin button
const int button3=8; //BAWAH
const int button2=9; //ATAS
const int button1=10; //OK
const int button4=11; //BACK
const int button5=12; //RUN
//variabel kondisi perubahan
int lastState1=LOW; //variabel penyimpan pembacaan state sebelumnya dari pin button
int lastState2=LOW;
int lastState3=LOW;
int lastState4=LOW;
int lastState5=LOW;
int currentState1;int currentState2;int currentState3;int currentState4;int currentState5; //variabel penyimpanan nilai yang sedang berlangsung



void setup() {
Serial.begin(9600);
  //modbus DE & RE
  Serial1.begin(19200);
  pinMode(pinModBusDE, OUTPUT);
  pinMode(pinModBusRE, OUTPUT);
  //PULLUP pada button pin
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  pinMode(button4,INPUT_PULLUP);
  pinMode(button5,INPUT_PULLUP);
  //pull up inpun pin akan HIGH apabila switch terbuka dan LOW ketika switch ter-tutup 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("PROTOTIPE V1.0");
  delay(300);
  lcd.clear();  
}

void loop() {
   switch(state){
    case 0:
    lcd.setCursor(3,0);
    lcd.print("MENU UTAMA");
    lcd.setCursor(1,1);
    lcd.print("KONTROL MOTOR");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==3){
      state=1;
    }else if(nav==1){
      state=2;
      lcd.clear();
    }
    break;      
    case 1:
    lcd.setCursor(3,0);
    lcd.print("MENU UTAMA");
    lcd.setCursor(0,1);
    lcd.print("MONITORING MOTOR");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();    
    if(nav==2){
      state=0;
    }else if(nav==1){
      state=8;
      lcd.clear();
    }
    break;
    
    case 2:
    lcd.setCursor(4,0);
    lcd.print("SETTING");
    lcd.setCursor(6,1);
    lcd.print("MENU");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==3){
      state=3;
    }else if(nav==2){
      state=3;
    }else if(nav==4){
      state=1;
    }   
    break;
    
    case 3:
    lcd.setCursor(4,0);
    lcd.print("SETTING");
    lcd.setCursor(3,1);
    lcd.print("ARAH MOTOR");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==2){
      state=4;
    }else if(nav==4){
      state=1;
    }else if(nav==1){
      state=5;
      lcd.clear();
    }
    break;

    case 4:
    lcd.setCursor(4,0);
    lcd.print("SETTING");
    lcd.setCursor(3,1);
    lcd.print("FREQ MOTOR");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==3){
      state=3;
    }else if(nav==4){
      state=1;
    }else if(nav==1){
      state=7;
    }
    break;
//  ================SET FREQ=================================
    case 7:
    lcd.setCursor(1,0);
    lcd.print("SET FREQ=");
    if(aritmatika1==HIGH&&aritmatika2==LOW){
      freq--;
      delay(100);
      lcd.clear();
    }else if(aritmatika1==LOW&&aritmatika2==HIGH){
      freq++;
      delay(100);
      lcd.clear();
    }
    lcd.setCursor(10,0);
    lcd.print(freq);
    lcd.setCursor(0,1);
    lcd.print("Save");
    lcd.setCursor(8,1);
    lcd.print("Back");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==5){
      setFreq=freq;//save nilai
    }else if(nav==4){
      state=0;
      analogWrite(5,0);
    }
    break;
//  ================SET ARAH PUTAR CW=========================
    case 5:
    lcd.setCursor(0,0);
    lcd.print("ARAH PUTAR=");
    lcd.setCursor(12,0);
    lcd.print("<--");
    lcd.setCursor(0,1);
    lcd.print("Save");
    lcd.setCursor(10,1);
    lcd.print("Back");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==5){
      for(char i=0;i<8;i++){
      Serial.print(forwardMotor[i],HEX);
      Serial.print(" ");
      Serial1.write(forwardMotor[i]);
      delay(1);
      }
    }else if(nav==4){
      lcd.clear();
      state=0;
    }else if(nav==2){
      state=6;
      lcd.clear();
    }
    break;  
//==============ARAH PUTAR CCW===================
    case 6:
    lcd.setCursor(0,0);
    lcd.print("ARAH PUTAR=");
    lcd.setCursor(12,0);
    lcd.print("-->");
    lcd.setCursor(0,1);
    lcd.print("Save");
    lcd.setCursor(10,1);
    lcd.print("Back");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==4){
      state=0   ;
      lcd.clear();
    }else if(nav==3){
      state=5;
      lcd.clear();
    }else if(nav==5){
      for(char i=0;i<8;i++){
      Serial.print(reverseMotor[i],HEX);
      Serial.print(" ");
      Serial1.write(reverseMotor[i]);
      delay(1);
      }
    }
     break;
//===========END OF KONTROL MENU================

//=========START PROGRAM MONITORING MENU=============
 case 8:
    lcd.setCursor(3,0);
    lcd.print("MONITORING");
    lcd.setCursor(6,1);
    lcd.print("MENU");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==3){
      state=9;
    }else if(nav==2){
      state=9;
    }else if(nav==4){
      state=1;
    }
  break;
  case 9:
    lcd.setCursor(3,0);
    lcd.print("MONITORING");
    lcd.setCursor(6,1);
    lcd.print("FREQUENCY");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==3){
      state=10;
    }else if(nav==4){
      state=8;
    }  lcd.clear();
    break; 
    case 10:
    lcd.setCursor(3,0);
    lcd.print("MONITORING FREQ");
    kirimData();
    for(char i=0;i<8;i++){
      Serial.print(readFreqMotor[i],HEX);
      Serial.print(" ");
      Serial1.write(readFreqMotor[i]);
      delay(1);
    }
    terimaData;
    delay(1);
    while(Serial1.available()){
      Request[readIndex]=Serial1.read();
      if(readIndex>=16){
        for(int i=9;i<=readIndex;i++){
          Serial.print(Request[i],HEX);
        }
        readIndex=0;
      }
    }
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();    
    if(nav==4){
      state=8;
    }   
    break;
  }
}

