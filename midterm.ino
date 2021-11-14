#include <Wire.h>
#include "SSD1306Wire.h"
SSD1306Wire  display(0x3c, 21, 22);

const int ledPin = 13;
const int ledPin2 = 14;
const int ledPin3 = 27;

int signalPin = 12;                  //用來trigger及接收echo
long duration, cm;
int safetyDistance;

 
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  Serial.begin (115200);             // Serial Port begin
  display.init();
  display.flipScreenVertically(); //畫面上下顛倒顯示
  display.display(); //顯示畫面
}
 
void loop()
{
  pinMode(signalPin, OUTPUT); //發送超音波時切還為輸出
  digitalWrite(signalPin, LOW);
  delayMicroseconds(5);
  digitalWrite(signalPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(signalPin, LOW);

  pinMode(signalPin, INPUT);             // //讀取超音波時切還為輸入
  duration = pulseIn(signalPin, HIGH);   // 收到高電位時的時間
 
  cm = (duration/2) / 29.1;         // 將時間換算成距離 cm 

   int input = cm;
   display.setFont(ArialMT_Plain_16);   //設定字型與大小
   display.drawString(0, 0, "Distance");  //(x座標,y座標,"字串")
   display.setFont(ArialMT_Plain_24);   //設定字型與大小
   display.drawString(0, 16, String(input)); //(x座標,y座標,"字串")
   display.display(); //顯示畫面
   delay(200);
   display.clear(); //清空畫面


  safetyDistance = cm;
    if (safetyDistance <= 5){   
      delay(200);
      digitalWrite(ledPin, HIGH);        
    }
    else if (safetyDistance > 5 && safetyDistance<100){
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin3, HIGH);    
    }
    else{
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);       
     }
  
  Serial.print("Distance : ");  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
}
