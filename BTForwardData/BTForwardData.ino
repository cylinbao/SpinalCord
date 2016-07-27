#include <SoftwareSerial.h>
SoftwareSerial BTSerial(12, 13); // RX | TX

const int dig[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int readDig = 0;
int count = 0;
int passData = 0;

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
  count = 0;
  passData = 0;
  while(count < 10){
    //BTSerial.print(digitalRead(dig[count++]), BIN);
    passData = passData*2 + int(digitalRead(dig[count++]));
  }

  BTSerial.println(passData, DEC);

  delay(100);
}
