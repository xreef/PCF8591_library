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
	Serial.print(ai.ain0);
	Serial.print(" - ");
	Serial.print(ai.ain1);
	Serial.print(" - ");
	Serial.print(ai.ain2);
	Serial.print(" - ");
	Serial.println(ai.ain3);

	delay(3000);

	int ana = pcf8591.analogRead(AIN0);
	Serial.print("AIN0 --> ");
	Serial.println(ana);

	ana = pcf8591.analogRead(AIN1);
	Serial.print("AIN1 --> ");
	Serial.println(ana);

	ana = pcf8591.analogRead(AIN2);
	Serial.print("AIN2 --> ");
	Serial.println(ana);

	ana = pcf8591.analogRead(AIN3);
	Serial.print("AIN3 --> ");
	Serial.println(ana);
	delay(3000);

	pcf8591.analogWrite(0);
	delay(3000);
	pcf8591.analogWrite(128);
	delay(3000);
	pcf8591.analogWrite(255);
	delay(3000);
}
