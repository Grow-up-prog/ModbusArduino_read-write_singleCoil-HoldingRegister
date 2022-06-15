#define pinModBusDE     8// logic 1 untuk kirim data
#define pinModBusRE     9// logic 0 untuk terima data
const int bufferSize=50;
byte buf[bufferSize];

void kirimData()
{
  digitalWrite(pinModBusDE,HIGH);
  digitalWrite(pinModBusRE,LOW);
}
void terimaData()
{
  digitalWrite(pinModBusDE,LOW);
  digitalWrite(pinModBusRE,LOW);
}
void setup() {
  // put your setup code here, to run once:
  pinMode(pinModBusDE, OUTPUT);
  pinMode(pinModBusRE, OUTPUT);
Serial1.begin(9600);
Serial.begin(19200);
}

void loop() {
  terimaData();
  while(Serial1.available()){
//     Serial.print("nilai data = ");
//   Serial.println(Serial1.readString());
//==============================
  int nilai = Serial1.read();
//  Serial.println(&bufferSize);
  if(nilai>0){
     Serial.println(nilai);    
    }
  }
  
/*  for(int i =0; i<nilai; i++){
      Serial.print(buf[i]);
*/    
}
