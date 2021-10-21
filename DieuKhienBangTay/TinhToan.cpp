#include "TinhToan.h"
void DocCamBien(int X, int Y,int &x, int &y){
  x = analogRead(X);
  unsigned long Now = millis();
  unsigned long Past = millis();
  while (Now - Past <= 10)
     Now = millis();
  y = analogRead(Y);
}

void Tare(int X, int Y, volatile int NamGiuaX,volatile int  NamGiuaY){
  
  NamGiuaX = analogRead(X);
  unsigned long Now = millis();
  unsigned long Past = millis();
  while (Now - Past <= 10)
     Now = millis();
  NamGiuaY = analogRead(Y);
}


void TinhToanGui(int X, int Y,int &Px,int &Py,int MinX, int MaxX, int MinY, int MaxY ,int NamGiuaX, int NamGiuaY){
  int x,y;
  DocCamBien(X,Y,x,y);
  Px = constrain(x,MinX,MaxX);
  Py = constrain(y,MinY,MaxY);
  if(x < NamGiuaX - 1)
      Px = constrain(map(Px,MinX,(NamGiuaX - 1), 10, 30),10,30); 
  else if(x > NamGiuaX + 1)
      Px = constrain(map(x,(NamGiuaX +1), MaxX, 31, 51),31,51);
  else Px = 52;

  if(y < NamGiuaY - 1)  
      Py = constrain(map(y,MinY,(NamGiuaY - 1), 10, 30),10,30); 
  else if(y > NamGiuaY + 1)
      Py = constrain(map(y,(NamGiuaY + 1), MaxY, 31, 51),31,51);
  else Py = 52;

}
