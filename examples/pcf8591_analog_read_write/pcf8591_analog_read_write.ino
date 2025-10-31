/**
 * @file pcf8591_analog_read_write.ino
 * @author Renzo Mischianti (www.mischianti.org)
 * @brief This example demonstrates how to read all analog inputs and write to the analog output of the PCF8591 module.
 * @version 1.0
 * @date 2024-03-15
 *
 * This example reads all four analog inputs sequentially and prints their values to the Serial Monitor.
 * It also demonstrates how to write different values (0, 128, 255) to the analog output.
 *
 * For a complete tutorial, visit:
 * https://www.mischianti.org/2019/01/03/pcf8591-i2c-analog-i-o-expander/
 *
 * @copyright Copyright (c) 2024 Renzo Mischianti
 *
 */

#include "Arduino.h"
#include "PCF8591.h"

// I2C address of the PCF8591 module
#define PCF8591_I2C_ADDRESS 0x48

// Create an instance of the PCF8591 library
PCF8591 pcf8591(PCF8591_I2C_ADDRESS);

void setup()
{
    // Initialize Serial communication
	Serial.begin(115200);

    // Initialize the PCF8591 module
	pcf8591.begin();
}

void loop()
{
    // Read all analog inputs at once
	PCF8591::AnalogInput allValues = pcf8591.analogReadAll();

    // Print the values of all analog inputs
	Serial.print("Reading all inputs: ");
	Serial.print(allValues.ain0);
	Serial.print(" - ");
	Serial.print(allValues.ain1);
	Serial.print(" - ");
	Serial.print(allValues.ain2);
	Serial.print(" - ");
	Serial.println(allValues.ain3);

	delay(3000);

    // Read each analog input individually
	int singleValue = pcf8591.analogRead(AIN0);
	Serial.print("Reading AIN0 individually: ");
	Serial.println(singleValue);

	singleValue = pcf8591.analogRead(AIN1);
	Serial.print("Reading AIN1 individually: ");
	Serial.println(singleValue);

	singleValue = pcf8591.analogRead(AIN2);
	Serial.print("Reading AIN2 individually: ");
	Serial.println(singleValue);

	singleValue = pcf8591.analogRead(AIN3);
	Serial.print("Reading AIN3 individually: ");
	Serial.println(singleValue);
	delay(3000);

    // Write different values to the analog output
	Serial.println("Writing 0 to analog output...");
	pcf8591.analogWrite(0);
	delay(3000);

	Serial.println("Writing 128 to analog output...");
	pcf8591.analogWrite(128);
	delay(3000);

	Serial.println("Writing 255 to analog output...");
	pcf8591.analogWrite(255);
	delay(3000);
}
