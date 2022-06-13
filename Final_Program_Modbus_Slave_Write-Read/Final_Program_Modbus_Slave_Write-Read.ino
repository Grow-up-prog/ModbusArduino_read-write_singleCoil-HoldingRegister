#include <ModbusMaster.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); //menggunakan LCD 16x2
#define MAX485_DE      3
#define MAX485_RE_NEG  2

int lastState1=LOW; //variabel penyimpan pembacaan state sebelumnya dari pin button
int lastState2=LOW;
int lastState3=LOW;
int lastState4=LOW;
int currentState1;int currentState2; int currentState3;int currentState4;
const int button1=7;
const int button2=6;
const int button3=5;
const int button4=4;
int nav=0;

ModbusMaster node;                    //object node for class ModbusMaster//write
void setup()
{
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  pinMode(button4,INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("PROTOTIPE V1.1");
  lcd.setCursor(0,1);
  lcd.print("Modbus Master");
  delay(1000);
  lcd.clear();
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
  Serial1.begin(9600);             //Baud Rate as 9600
  Serial.begin(19200);
  node.begin(1, Serial1);            //Slave ID as 1
  node.preTransmission(preTransmission);         //Callback for configuring RS-485 Transreceiver correctly
  node.postTransmission(postTransmission);
}
void loop()
{ 
//readCoilStatus();
//lcd.clear();
  buttonA();
  buttonB();  
  buttonC();
  buttonD();
//  readFreq();
  if (nav == 1)
  {
    writeCoilHigh();
    Serial.println("COIL RUN ON");
    delay(200);
  }else if (nav == 2)
  {
    uint8_t readFreq=node.readHoldingRegisters(0x31001,1);
    if(readFreq==node.ku8MBSuccess)
    {
      lcd.setCursor(0,1);
      lcd.print("nilai FREQ");
      lcd.setCursor(12,1);
      lcd.print(node.getResponseBuffer(0x00));
    }else{
      lcd.setCursor(0,1);
      lcd.print("Pembacaan Gagal");
    }
  }else if (nav == 3)
  {
    uint8_t readFreq=node.readHoldingRegisters(0x30002,1);      
    lcd.setCursor(0,1);
    lcd.print("nilai FREQ");
    if(readFreq==node.ku8MBSuccess)
    {
      lcd.setCursor(12,1);
      lcd.print(node.getResponseBuffer(0x00));
    }else{
      lcd.setCursor(0,1);
      lcd.print("Pembacaan Gagal");
    }
   }
   else if (nav == 4)
  {    
    writeCoilLow();
    Serial.println("COIL STOP ON");
    delay(200);
  }
  delay(1000);
  lcd.clear();
}
