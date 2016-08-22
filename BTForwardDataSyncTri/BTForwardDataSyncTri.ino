#include <SoftwareSerial.h>
SoftwareSerial BTSerial(12, 13); // RX | TX

const int dig[5] = {2, 3, 4, 5, 6};
const int extClock = 11;
const int triggerPin = 10;
const int ledPin = 13;
const int signalT = 224;
//const int signalT2 = 500;
//const int windowL = 50;
int readDig[5];
int passData;
int clkVal, lastVal;
bool stimStart, windowStart;
int minData;
unsigned long curTime, startTime;

void setup()
{
  pinMode(extClock, INPUT);
  pinMode(dig[0], INPUT);
  pinMode(dig[1], INPUT);
  pinMode(dig[2], INPUT);
  pinMode(dig[3], INPUT);
  pinMode(dig[4], INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);

  lastVal = LOW;
  clkVal = LOW;
  stimStart = false;
  windowStart = false;
  minData = 1024;
  Serial.begin(230400);
  //BTSerial.begin(115200);  // HC-05 default speed in AT command more
} 

void loop()
{ 
	if(stimStart == false){
		digitalWrite(triggerPin, HIGH);
		delayMicroseconds(500);
		digitalWrite(triggerPin, LOW);
    digitalWrite(ledPin, LOW);

		stimStart = true;
    minData = 1024;
		lastVal = LOW;
    
	  startTime = millis();
}
	else{
		curTime = millis();

		if(((curTime - startTime) < 7) && ((curTime - startTime) > 1)){
			clkVal = digitalRead(extClock);

			if((clkVal != lastVal) && (clkVal == HIGH)){
				readDig[0] = digitalRead(dig[0]) << 9;
				readDig[1] = digitalRead(dig[1]) << 8;
				readDig[2] = digitalRead(dig[2]) << 7;
				readDig[3] = digitalRead(dig[3]) << 6;
				readDig[4] = digitalRead(dig[4]) << 5;

				passData = readDig[0] + readDig[1];
				passData += readDig[2] + readDig[3];
				passData += readDig[4];

				Serial.println(passData, DEC);
				//BTSerial.println(passData, DEC);
				if((passData < minData) && (passData > 64))
        //if(passData < minData)
					minData = passData;
			}

			lastVal = clkVal;
		}
		else if(((curTime - startTime) >= 7) && (windowStart == false)){
      windowStart = true;
			Serial.write("minData: ");
			Serial.println(minData, DEC);

			if(minData > signalT){
				digitalWrite(ledPin, HIGH);
			}
		}
		else if((curTime - startTime) > 400){
      windowStart = false;
			stimStart = false;  
		} 
	}
}
