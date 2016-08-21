#include <SoftwareSerial.h>
SoftwareSerial BTSerial(12, 13); // RX | TX

const int dig[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int pinNum = 10;
int readDig[10];
int count = 0;
int passData = 0;
int dataClock = 2; // 5 microseconds

void setup()
{
  pinMode(dig[0], INPUT);
  pinMode(dig[1], INPUT);
  pinMode(dig[2], INPUT);
  pinMode(dig[3], INPUT);
  pinMode(dig[4], INPUT);
  pinMode(dig[5], INPUT);
  pinMode(dig[6], INPUT);
  pinMode(dig[7], INPUT);
  pinMode(dig[8], INPUT);
  pinMode(dig[9], INPUT);
  
  Serial.begin(9600);
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
} 

void loop()
{ 
	/*
  count = 0;
  passData = 0;
  while(count < pinNum){
    //BTSerial.print(digitalRead(dig[count++]), BIN);
    passData = passData*2 + int(digitalRead(dig[count++]));
  }
	*/
  
  readDig[0] = digitalRead(dig[0]) << 9;
  readDig[1] = digitalRead(dig[1]) << 8;
  readDig[2] = digitalRead(dig[2]) << 7;
  readDig[3] = digitalRead(dig[3]) << 6;
  readDig[4] = digitalRead(dig[4]) << 5;
  readDig[5] = digitalRead(dig[5]) << 4;
  readDig[6] = digitalRead(dig[6]) << 3;
  readDig[7] = digitalRead(dig[7]) << 2;
  readDig[8] = digitalRead(dig[8]) << 1;
  readDig[9] = digitalRead(dig[9]);

  passData = readDig[0] + readDig[1];
  passData += readDig[2] + readDig[3];
  passData += readDig[4] + readDig[5];
  passData += readDig[6] + readDig[7];
  passData += readDig[8] + readDig[9];

  BTSerial.println(passData, DEC);
  Serial.println(passData, DEC);

  delayMicroseconds(dataClock);
}
