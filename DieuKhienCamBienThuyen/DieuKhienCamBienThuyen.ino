#include <NewPing.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <avr/interrupt.h>
  
  NewPing sonar2 ( 2, 2, 400);
  volatile int flag2 = 0; // flag vat can
  NewPing sonar3 ( 3, 3, 400);
  volatile int flag3 = 0;
  NewPing sonar4 ( 4, 4, 400);
  volatile int flag4 = 0;
  NewPing sonar5 ( 5, 5, 400);
  volatile int flag5 = 0;
 
  RF24 radio(9, 10); // Chọn chân kết nối CE, CSN
  const byte address[][6] = {"00002","00001"}; // Địa chỉ cần truyền

void setup() {
  Serial.begin(9600);

  //Set Timer
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12) | (1 << CS10) |(1 <<CS11) ; // prescale = 64 and CTC mode 4
    OCR1A = 49999;// initialize OCR1A
    TIMSK1 = (1 << OCIE1A);     // Output Compare Interrupt Enable Timer/Counter1 channel A
    sei();             
  
  radio.begin();
 radio.openWritingPipe(address[0]); // Set địa chỉ truyền
 radio.openReadingPipe(1,address[1] ); // Set địa chỉ truyền
  radio.setPALevel(3 ); // Set chế độ hoạt động
  radio.stopListening(); // Đặt module NRF24L01 ở chế độ phát
}
void loop()
{ 
//  Serial.println("Vao");
  CamBien(sonar2,flag2);
  CamBien(sonar3,flag3);
  CamBien(sonar4,flag4);
  CamBien(sonar5,flag5);
  delay(2000);
}

// Chua xet flag xong
void CamBien(NewPing sonar, volatile int &flag){
   unsigned long duration; 
    int distance;           
    duration = sonar.ping_median(2); 
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    if(distance < 30) flag = 1; // co vat can
    else flag  = 0;
//    Serial.print(distance);
//    Serial.println("cm");
//    Serial.println(flag);
    long past = micros();
    long future = micros();
    while ((future - past) <100)
    future = micros();
}

ISR (TIMER1_COMPA_vect)  
{   //Serial.println("Interrupt");
    char Nhan[12];
    radio.startListening();
    if(radio.available()){
    while(radio.available()){
      radio.read(&Nhan,11);
    }
    Serial.println(Nhan);
    Serial.println();
     radio.stopListening(); // Đặt module NRF24L01 ở chế độ phát
     int text[4] = {flag2, flag3, flag4, flag5};
     
    for(int i = 0; i <4;i++){
      Serial.println(text[i]); 
    }
     radio.write(&text, sizeof(text));
     
    }
     
}
