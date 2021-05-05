byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,1,1,1,0,0,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,0,1,1,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,0,0,1,1 }   // = 9
}; //設定七段顯示器0~9

int buttonPin= 9; //輸入訊號腳位

int num = 0; //顯示數字變數
int oldbtn=0; //紀錄按鈕高低位變化

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte seg = 0; seg < 7; seg++) {
    digitalWrite(pin, seven_seg_digits[digit][seg]);
    pin++;
  }
}//控制七段顯示器內容顯示

void setup() {
    Serial.begin(9600);
    
    for (int thisLed = 2; thisLed < 9; thisLed++) {
      pinMode(thisLed, OUTPUT); 
    }//設定2~8腳位為輸出
    
    pinMode(buttonPin, INPUT);//設定9腳位為輸入

    sevenSegWrite(num);//設定七段顯示器起始值
}

void loop() {
    int buttonstate=digitalRead(buttonPin);//偵測按鈕訊號
    
    if(buttonstate==HIGH && oldbtn==0){ //確認輸入訊號是從低位到高位
      Serial.println(num);
      num ++;
      if(num > 9){num = 0;} //num超過9時歸0
      sevenSegWrite(num); //呼叫七段顯示器內容顯示函式
    } 
    
    oldbtn=buttonstate; //紀錄現在按鈕的訊號
    delay(20);
}
