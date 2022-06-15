#define pinModBusDE     8// logic 1 untuk kirim data
#define pinModBusRE     9// logic 0 untuk terima data
byte arrayData[100];
void kirimData()
{
  digitalWrite(pinModBusDE,HIGH);
  digitalWrite(pinModBusRE,LOW);
}
void terimaData()
{
  digitalWrite(pinModBusDE,HIGH);
  digitalWrite(pinModBusRE,LOW);
}
 
//byte perintah[] = {0x01, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0xCA};//readInputRegisters
 byte perintahRun[] = {0x01, 0x05, 0x00, 0x00, 0xFF, 0x00, 0x8C, 0x3A};//write coil RUN
 byte perintahStop[] = {0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0xCD, 0xCA};//write coil STOP

void setup() {
  pinMode(pinModBusDE, OUTPUT);
  pinMode(pinModBusRE, OUTPUT);
  Serial1.begin(9600);
  Serial.begin(19200);
//  ptr=bufferDataModbus;
}

void loop() {
  
  kirimData();
  delay(100);
  Serial1.write(perintahRun,sizeof(perintahRun));
//delay(1);
  terimaData();
  long responModbus = millis()+1000;
  while(!Serial1.available())
  {
    if(responModbus <millis())
    {
      break;//timeout
    }
  }
  while(Serial1.available())
  {
    byte b = Serial1.read();
//    Serial.println(b);
    Serial.println(b,HEX);
    delay(2);
  }
  Serial.print("=================\n");
  delay(3000);
//==================================   
  kirimData();
  delay(100);
  Serial1.write(perintahStop,sizeof(perintahStop));
//delay(1);
  terimaData();
  long responModbusStop = millis()+1000;
  while(!Serial1.available())
  {
    if(responModbusStop <millis())
    {
      break;//timeout
    }
  }
  while(Serial1.available())
  {
    byte b = Serial1.read();
//    Serial.println(b);
    Serial.println(b,HEX);
    delay(2);
  }
  Serial.print("=================\n");
  delay(3000);
}
