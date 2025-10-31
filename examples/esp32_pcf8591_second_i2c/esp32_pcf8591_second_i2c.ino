/**
 * @file esp32_pcf8591_second_i2c.ino
 * @author Renzo Mischianti (www.mischianti.org)
 * @brief This example demonstrates how to use the PCF8591 with a secondary I2C bus on an ESP32.
 * @version 1.0
 * @date 2024-03-15
 *
 * This sketch shows how to configure and use the PCF8591 library with a non-default I2C interface on the ESP32.
 * It initializes a second I2C bus on pins 21 (SDA) and 22 (SCL) and then performs the same analog read and write
 * operations as the basic example.
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

// Instantiate a second I2C bus on the ESP32
TwoWire I2Ctwo = TwoWire(1);

// Create an instance of the PCF8591 library, passing the custom I2C bus and pins
PCF8591 pcf8591(&I2Ctwo, PCF8591_I2C_ADDRESS, 21, 22); // SDA: 21, SCL: 22

void setup()
{
    // Initialize Serial communication
	Serial.begin(115200);

    // Initialize the second I2C bus
    I2Ctwo.begin(21, 22, 100000); // SDA pin 21, SCL pin 22, 100kHz frequency

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

    // ... (individual reads for AIN1, AIN2, AIN3) ...

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
