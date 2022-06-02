//=======================FUNGSI=========================

void preTransmission()            //Function for setting stste of Pins DE & RE of RS-485
{
  digitalWrite(MAX485_RE_NEG, 1);             
  digitalWrite(MAX485_DE, 1);
}
void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}
void buttonA(){
  currentState1=digitalRead(button1);
  if(lastState1==HIGH&&currentState1==LOW){
    Serial.println("lampuA_ON");
    nav=1;
    lcd.clear();
  } else if(lastState1==LOW&&currentState1==HIGH){
    Serial.println("LampuA_OFF");
  }
  lastState1=currentState1;
}
void buttonB(){
  currentState2=digitalRead(button2);
  if(lastState2==HIGH&&currentState2==LOW){
    Serial.println("LampuB_ON");
    nav=2;
    lcd.clear();
  } else if(lastState2==LOW&&currentState2==HIGH){
    Serial.println("LampuB_OFF");
  }
  lastState2=currentState2;
}

void buttonC(){
  currentState3=digitalRead(button3);
  if(lastState3==HIGH&&currentState3==LOW){
    Serial.println("LampuC_ON");
    nav=3;
    lcd.clear();
  } else if(lastState3==LOW&&currentState3==HIGH){
    Serial.println("LampuC_OFF");
  }
  lastState3=currentState3;
}
void buttonD(){
  currentState4=digitalRead(button4);
  if(lastState4==HIGH&&currentState4==LOW){
    Serial.println("LampuD_ON");
    nav=4; 
    lcd.clear();
  } else if(lastState4==LOW&&currentState4==HIGH){
    Serial.println("LampuD_OFF");
  }
  lastState4=currentState4;
}

//FUNGSI READ==========================================
    void readFreq(){
    uint8_t resultA =node.readHoldingRegisters(0x30001,1);               //Writes 1 to 0x00000 RUN COMMAND
    if(resultA==node.ku8MBSuccess)
    {
      lcd.setCursor(0,0);
      lcd.print("nilai FREQ");
      lcd.setCursor(12,0);
      lcd.print(node.getResponseBuffer(0x00));
    }      
    }

    void readVolt(){
    uint8_t resultB =node.readHoldingRegisters(0x0000,1);               //Writes 1 to 0x00000 RUN COMMAND
    if(resultB==node.ku8MBSuccess)
    {
      Serial.print("nilai VOLT");Serial.print("   ");
      Serial.println(node.getResponseBuffer(0x00));
      delay(200);
    }
          
    }
  /*  
    void readCoilStatus(){
    uint8_t resultC =node.readCoils(0x0000,1);               //Writes 1 to 0x00000 RUN COMMAND
    if(resultC==node.ku8MBSuccess)
    {
      Serial.println("");
      Serial.print("nilai Status");Serial.print("   ");
      lcd.setCursor(0,0);
      lcd.print(node.getResponseBuffer(0x00));
      delay(200);
    }
    */      
    
    void writeCoilLow(){
    node.writeSingleCoil(0x0000,0);               //Writes 1 to 0x00000 RUN COMMAND
    lcd.setCursor(0,0);
    lcd.print("CMD:STOP");
    digitalWrite(8,LOW);      
    }
    void writeCoilHigh(){
    node.writeSingleCoil(0x0000,1);               //Writes 1 to 0x00000 RUN COMMAND
    lcd.setCursor(0,0);
    lcd.print("CMD:RUN");
    digitalWrite(8,HIGH);      
    }
   void writeHoldingRegisterFreq20(){
    node.writeSingleRegister(0x40001,120);              //Writes 100 to 0x40002 holding register
    lcd.setCursor(0,0);
    lcd.print("MONITORING");
    lcd.setCursor(12,0);
    lcd.print("FREQ");
    Serial.println("kecepatan 20Hz");
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
   }
    void writeHoldingRegisterFreq10(){
    node.writeSingleRegister(0x40001,100);              //Writes 100 to 0x40002 holding register
    lcd.setCursor(0,0);
    lcd.print("MONITORING");
    lcd.setCursor(12,0);
    lcd.print("FREQ");
    Serial.println("kecepatan 10Hz");
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    }

//======================END OF FUNGSI===================
