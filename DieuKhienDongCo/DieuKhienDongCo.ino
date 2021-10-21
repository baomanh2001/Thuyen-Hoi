#include <SerialCommand.h>
#include <SoftwareSerial.h>

#include <Servo.h> 
 
#define SERVO_PIN 10
#define INHOI1  7
#define INHOI2  6
#define INDUOI1 5
#define INDUOI2 4
#define ENHOI   A0
#define ENDUOI  A1



Servo servo;
SerialCommand scmd;
void setup() {
 // Setup truyen
  Serial.begin(9600);
  //Khai bao servo
  servo.attach(SERVO_PIN);
  pinMode(INHOI1,OUTPUT);
  pinMode(INHOI2,OUTPUT);
  pinMode(INDUOI1,OUTPUT);
  pinMode(INDUOI2,OUTPUT);
  pinMode(ENHOI,OUTPUT);
  pinMode(ENDUOI,OUTPUT);

  digitalWrite(INHOI1,HIGH);
  digitalWrite(INHOI2,LOW);
  //khai bao do bom hoi
  analogWrite(ENHOI,200);
  
  //lenh khi co chu X
  scmd.addCommand("X", DongCo);

  //lenh khi co chu Stop
  scmd.addCommand("Stop", Stop);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  scmd.readSerial();
}

void DongCo() {
  char *SoX;
  SoX = scmd.next();
  int valueX = atoi(SoX);
  DieuKhienTocDo(valueX);
  char *Y;
  Y = scmd.next();
  Serial.println(Y);
  
  char *SoY;
  SoY = scmd.next();
  if(Y ='Y')
  {
    int Goc = atoi(SoY);
   DieuKhienDuoi(Goc); 
  }

  
  
 
}
void Stop(){
  analogWrite(ENDUOI,0);
}
void DieuKhienTocDo(int x){
  
    // Queo Phai
    if(x >= 10 && x <=30){
       Tien(x);
    }
    // Queo Trai
    else if(x <= 51 && x >= 31){
      Lui(x);
    }
    // Di Thang
    else  analogWrite(ENDUOI,0);
}
void Tien(int x){
  Serial.println("TIEN");
  digitalWrite(INDUOI1,HIGH);
  digitalWrite(INDUOI2,LOW);
  x = map(x,10,30,20,1023);
  analogWrite(ENDUOI,x);
}
void Lui(int x){
  digitalWrite(INDUOI1,LOW);
  digitalWrite(INDUOI2,HIGH);
  x = map(x,10,30,20,1023);
  analogWrite(ENDUOI,x);
}
void DieuKhienDuoi(int x) {
    int Goc ;
    // Queo Phai
    if(x >= 10 || x <=30){
       Goc = map(x,10,30,100,150);
    }
    // Queo Trai
    else if(x <= 51 && x >= 31){
      Goc = map(x,31,51,80,30);
    }
    // Di Thang
    else Goc = 90;
    servo.write(Goc);
}
