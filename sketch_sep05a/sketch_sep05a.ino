/*
            FPS Gaming Air Mouse
      
      개발자: 신현규(LionKingSmasher)

      사용언어: 아두이노(C++ or Processing)
      사용 모듈: 자이로센서
*/

#include <Keyboard.h>
#include <Mouse.h>
#include <Wire.h>

const int MPU = 0x68;
int16_t gyroX, gyroZ;
int Sensitivity = 500;
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ, push, posX, posY;
int mouseX, mouseY;
int sw=7;
int past_val=0;
int wheel;

uint32_t timer;

void get6050();

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  Mouse.begin();
  Keyboard.begin();
  pinMode(sw, INPUT);
  pinMode(5, INPUT);
  timer = micros();
}

void loop(){
  get6050();
  GetJoyStick();
  int val = analogRead(A2)/500;
  if(val>past_val) wheel = 1;
  else if(val<past_val) wheel = -1;
  else wheel = 0;
  past_val = val;
  /*
  Serial.print("Push: ");
  Serial.println(push);
  Serial.print("posX: ");
  Serial.println(posX);
  Serial.print("posY: ");
  Serial.println(posY);
  */
//  Serial.print("Acx:");
//  Serial.println(AcX);
//  Serial.print("AcY:");
//  Serial.println(AcY);
//  Serial.print("AcZ:");
//  Serial.println(AcZ);
//  Serial.print("Tmp:");
//  Serial.println(Tmp);
//  Serial.print("GyX:");
//  Serial.println(GyX);
//  Serial.print("GyY:");
//  Serial.println(GyY);
//  Serial.print("GyZ:");
//  Serial.println(GyZ);  
  gyroX = GyX/Sensitivity/1.1*-1;
  gyroZ = GyY/Sensitivity*1;
  Mouse.move(gyroZ, gyroX, wheel);
  if(digitalRead(5)==1) Mouse.click();
  else Mouse.release();
  if(posX>600) Keyboard.press('w');
  else if(posX<450) Keyboard.press('s');
  else {
    Keyboard.release('w');
    Keyboard.release('s');
  }
  if(posY>600) Keyboard.press('d');
  else if(posY<450) Keyboard.press('a');
  else {
    Keyboard.release('d');
    Keyboard.release('a');
  }
  if(digitalRead(7)==1)Keyboard.press('r');
  else Keyboard.release('r');
  delay(3);
}

void get6050(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);
  AcX = Wire.read()<<8|Wire.read();
  AcY = Wire.read()<<8|Wire.read();
  AcZ = Wire.read()<<8|Wire.read();
  Tmp = Wire.read()<<8|Wire.read();
  GyX = Wire.read()<<8|Wire.read();
  GyY = Wire.read()<<8|Wire.read();
  GyZ = Wire.read()<<8|Wire.read();
}

void GetJoyStick(){
   posX = analogRead(A0);
   posY = analogRead(A1);
}
