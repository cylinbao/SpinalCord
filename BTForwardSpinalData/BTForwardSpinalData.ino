#include <SoftwareSerial.h>
SoftwareSerial BTSerial(12, 13); // RX | TX

int dataClock = 20; // 20 microseconds
int count;
int dataPoint[] = {1, 12, 11};
int repeat[] = {50, 2, 150, 9};
int data1[] = {3};
int data2[] = {2, 1, 0, 1, 2, 3, 4, 6, 7, 6, 4, 3};
int data3[] = {4, 5, 4, 3, 2, 1, 2, 3, 4, 5, 4};
               
void setup()
{
  Serial.begin(9600);
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
} 

void loop()
{ 
  int i, j;
  
  for(i = 0; i < dataPoint[0]; i++){
    for(j = 0; j < repeat[0]; j++){
      BTSerial.println(data1[i], DEC);
      delayMicroseconds(dataClock);
    }
  }
  for(i = 0; i < dataPoint[1]; i++){
    for(j = 0; j < repeat[1]; j++){
      BTSerial.println(data2[i], DEC);
      delayMicroseconds(dataClock);
    }
  }
  for(i = 0; i < dataPoint[0]; i++){
    for(j = 0; j < repeat[2]; j++){
      BTSerial.println(data1[i], DEC);
      delayMicroseconds(dataClock);
    }
  }
  for(i = 0; i < dataPoint[2]; i++){
    for(j = 0; j < repeat[3]; j++){
      BTSerial.println(data3[i], DEC);
      delayMicroseconds(dataClock);
    }
  }
  for(i = 0; i < dataPoint[0]; i++){
    for(j = 0; j < repeat[0]; j++){
      BTSerial.println(data1[i], DEC);
      delayMicroseconds(dataClock);
    }
  }
}
