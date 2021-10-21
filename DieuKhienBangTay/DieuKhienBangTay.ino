#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // Chọn chân kết nối CE, CSN

#include "TinhToan.h"
const byte address[][6] = {"00001","00002"}; // Địa chỉ cần truyền
#define X A0
#define Y A1
#define ButtonTARE    2
#define DenTruoc  8
#define DenPhai   7
#define DenSau    6
#define DenTrai   5

#define MinX    270
#define MinY    259
#define MaxX    407
#define MaxY    398

volatile int NamGiuaX, NamGiuaY;

String strX = "X ";

String strY = " Y ";

// Noi String
String string(int x,String strX){
  String X = String(x,DEC);
    return strX + X;
}

void setup() {

  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(ButtonTARE, INPUT_PULLUP);
  pinMode(DenTruoc, OUTPUT);
  pinMode(DenPhai, OUTPUT);
  pinMode(DenSau, OUTPUT);
  pinMode(DenTrai, OUTPUT);

  

 
// Setup truyen
  Serial.begin(9600);
  radio.begin();
  attachInterrupt(ButtonTARE,tareHand,FALLING);
  radio.openReadingPipe(1, address[1]); // Set địa chỉ truyền
  radio.openWritingPipe(address[0]); // Set địa chỉ truyền
  radio.setPALevel(1); // Set chế độ hoạt động
  radio.stopListening(); // Đặt module NRF24L01 ở chế độ phát
}

void loop() {
// CHU Y thay 300 bang NamGIUAX va NAMGIUAY
// Doc Gia Toc va Chuyen ve chuoi gui
    int Px,Py;
   DocCamBien(X,Y,Px,Py);
   TinhToanGui( X,  Y, Px, Py,MinX,  MaxX,  MinY,  MaxY , 300, 300) ;
   String StringX = string(Px,strX);
   String StringY = string(Py,strY);
   String strGUI = StringX  + StringY;
   char GUI[12];
   strGUI.toCharArray(GUI,12);
   
   //Bat dau gui
//   radio.openWritingPipe(address[0]);
   radio.stopListening(); 
   radio.write(&GUI,sizeof(GUI));
   Serial.println(GUI);
  
  //Bat dau nhan
   radio.startListening();
   int Nhan[4];
   unsigned long now = micros();
   unsigned long past = micros();
   while (now - past < 1000){
    //Neu co du lieu vao trong 1s
   if(radio.available()){
    while(radio.available()){
      Serial.println("Nhan");
      radio.read(&Nhan,sizeof(Nhan));
    }
    for(int i = 0; i <4;i++)
    Serial.println(Nhan[i]);
   }
   now = micros();
   }
 
}
void tareHand(){
  Tare(14,15,NamGiuaX,NamGiuaY);
}
