#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); //menggunakan LCD 16x2
//variabel state
int state=0;
int nav=0;
int freq=0;
int setFreq=0;
//define modbus
#include <ModbusMaster.h>
#define MAX485_DE 7
#define MAX485_RE_NEG 6
ModbusMaster node;
void preTransmission()
{
  digitalWrite(MAX485_DE,HIGH);
  digitalWrite(MAX485_RE_NEG,HIGH);
}
void postTransmission()
{
  digitalWrite(MAX485_DE,LOW);
  digitalWrite(MAX485_RE_NEG,LOW);
}

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
Serial.begin(19200);
Serial1.begin(9600);
  //PULLUP pada button pin
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  pinMode(button4,INPUT_PULLUP);
  pinMode(button5,INPUT_PULLUP);
//define modbus
  pinMode(MAX485_DE,OUTPUT);
  pinMode(MAX485_RE_NEG,OUTPUT);
  postTransmission();
  node.begin(1,Serial1);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  //pull up inpun pin akan HIGH apabila switch terbuka dan LOW ketika switch ter-tutup 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("PROTOTIPE");
  lcd.setCursor(0,1);
  lcd.print("MODBUS ARDUINO");
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
      node.writeSingleRegister(0x2135,0x06);
      state=7;
    }
    break;
//  ================SET FREQ=================================
    case 7:
    lcd.setCursor(1,0);
    lcd.print("SET FREQ");
    lcd.setCursor(3,1);
    lcd.print("FREQ 10 Hz");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==3){
      state=11;
    }else if(nav==4){
      delay(100);
      state=6;
    }else if(nav==5){
      Serial.println("set freq 10Hz");
      node.writeSingleRegister(0x0C20,0x0A);
      delay(3000);
      if(nav==3||nav==2){
      node.writeSingleRegister(0x0C20,0x0);
      delay(1000);
      state=11;
      }else if(nav==4){
      node.writeSingleRegister(0x0C20,0x0);
      delay(1000);
      state=6;
      }
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
    node.writeSingleRegister(0x2135,0x080F);
      if(nav==4){
        lcd.clear();
        state=0;
      }else if(nav==2||nav==3){
        state=6;
        lcd.clear();
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
      node.writeSingleRegister(0x2135,0x0F);
      if(nav==4){
        lcd.clear();
        state=0;
      }else if(nav==2||nav==3){
        state=5;
        lcd.clear();
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
    lcd.print("MONITORING");
    lcd.setCursor(0,1);
    lcd.print("Pembacaan Gagal");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==4){
      node.writeSingleRegister(0x2135,0x80);
      state=8;
    }   
 break;
 case 11:
    lcd.setCursor(1,0);
    lcd.print("SET FREQ");
    lcd.setCursor(3,1);
    lcd.print("FREQ 20 Hz");
    buttonA();
    buttonB();
    buttonC();
    buttonD();
    buttonE();
    if(nav==2){
      state=7;
    }else if(nav==4){
      state=5;
    }else if(nav==5){
      node.writeSingleRegister(0x0C20,0x14);
      delay(3000);
      if(nav==2||nav==3){
      node.writeSingleRegister(0x0C20,0x0);
      delay(1000);
      state=7;
      }else if(nav==4){
      node.writeSingleRegister(0x0C20,0x0);
      delay(1000);
      state=5;
      }
    }
 break;
  }
}
