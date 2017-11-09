#include "Arduino.h"
#include "PCF8591.h"
#define PCF8591_I2C_ADDRESS 0x48

PCF8591 pcf8591(PCF8591_I2C_ADDRESS);

void setup()
{
	Serial.begin(115200);
	pcf8591.begin();
}

void loop()
{
	PCF8591::AnalogInput ai = pcf8591.analogReadAll();
	Serial.print(ai.ana0);
	Serial.print(" - ");
	Serial.print(ai.ana1);
	Serial.print(" - ");
	Serial.print(ai.ana2);
	Serial.print(" - ");
	Serial.println(ai.ana3);

	delay(3000);

	int ana = pcf8591.analogRead(ANA0);
	Serial.print("ANA0 --> ");
	Serial.println(ana);

	ana = pcf8591.analogRead(ANA1);
	Serial.print("ANA1 --> ");
	Serial.println(ana);

	ana = pcf8591.analogRead(ANA2);
	Serial.print("ANA2 --> ");
	Serial.println(ana);

	ana = pcf8591.analogRead(ANA3);
	Serial.print("ANA3 --> ");
	Serial.println(ana);
	delay(3000);

	pcf8591.analogWrite(0);
	delay(3000);
	pcf8591.analogWrite(128);
	delay(3000);
	pcf8591.analogWrite(255);
	delay(3000);
}
