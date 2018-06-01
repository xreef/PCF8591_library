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
	pcf8591.voltageWrite(2.7); // 2.7Volts output
	delay(3000);

	float ana0V = pcf8591.voltageRead(AIN0);
	Serial.println(ana0V);

	float ana1V = pcf8591.voltageRead(AIN1);
	Serial.println(ana1V);

	float ana2V = pcf8591.voltageRead(AIN2);
	Serial.println(ana2V);
	delay(3000);

}
