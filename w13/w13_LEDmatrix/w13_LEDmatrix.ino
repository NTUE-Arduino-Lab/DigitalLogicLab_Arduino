int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
int btnPin = 2;
//設定各接腳

int btnstate=0; //紀錄按鈕狀態
int picstate=0; //設定顯示圖案

int delay_time = 1; //設定Matrix延遲時間

byte colDataMatrix[8] = {
   B01111111,
   B10111111,
   B11011111,
   B11101111,
   B11110111,
   B11111011,
   B11111101,
   B11111110
};                  
byte rowDataMatrix[8] = {
   B11111111,
   B10000001,
   B10000001,
   B10000001,
   B10000001,
   B10000001,
   B10000001,
   B11111111
}; //圖案1
byte rowDataMatrix2[8] = {
   B10000001,
   B01000010,
   B00100100,
   B00011000,
   B00011000,
   B00100100,
   B01000010,
   B10000001,
}; //圖案2
         
void setup() {
  Serial.begin(9600);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(btnPin,INPUT_PULLUP);
}

void loop() {
  btnstate = digitalRead(btnPin);
  Serial.println(btnstate);
 
  if(btnstate==LOW){
    for(int i = 0; i < 8 ; i++){
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
      shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix2[i]);
      digitalWrite(latchPin,HIGH);
      delay(delay_time);
    }
  }
  else{
    for(int i = 0; i < 8 ; i++){
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
      shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
      digitalWrite(latchPin,HIGH);
      delay(delay_time);
    } 
  }
  delay(10);
}
