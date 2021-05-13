int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
int btnPin = 2;
//設定各接腳

int btnstate=0; //紀錄按鈕狀態
int oldbtn=0; //紀錄按鈕高低位變化
int picstate=1; //設定顯示圖案

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
byte rowDataMatrix3[8] = {
   B01100110,
   B10011001,
   B10000001,
   B10000001,
   B10000001,
   B01000010,
   B00100100,
   B00011000
}; //圖案1
byte rowDataMatrix4[8] = {
   B00000010,
   B00000011,
   B00000100,
   B00001000,
   B00010000,
   B10100000,
   B11000000,
   B11100000
}; //圖案2
       
void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(btnPin,INPUT_PULLUP);
}

void loop() {
  btnstate=digitalRead(btnPin);
  if(btnstate==LOW && oldbtn==0){
      if(picstate==0){
        while(1){
          for(int i = 0; i < 8 ; i++){
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
            shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix4[i]);
            digitalWrite(latchPin,HIGH);
            delay(delay_time);
          }
          picstate=1;
          btnstate=digitalRead(btnPin);
          if(btnstate==HIGH && oldbtn==0){delay(10);break;}
        }  
      }
      else if(picstate==1){
        while(1){
          for(int i = 0; i < 8 ; i++){
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
            shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix3[i]);
            digitalWrite(latchPin,HIGH);
            delay(delay_time);
          } 
          picstate=0;
          btnstate=digitalRead(btnPin);
          if(btnstate==HIGH && oldbtn==0){delay(10);break;}
        }
      }  
    }
    else{
      if(picstate==1){
        for(int i = 0; i < 8 ; i++){
          digitalWrite(latchPin,LOW);
          shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
          shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix4[i]);
          digitalWrite(latchPin,HIGH);
          delay(delay_time);
        }
      }
      else if(picstate==0){
        for(int i = 0; i < 8 ; i++){
          digitalWrite(latchPin,LOW);
          shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
          shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix3[i]);
          digitalWrite(latchPin,HIGH);
          delay(delay_time);
        } 
      }
    }
    oldbtn=btnstate; //紀錄現在按鈕的訊號
    delay(10);
}
