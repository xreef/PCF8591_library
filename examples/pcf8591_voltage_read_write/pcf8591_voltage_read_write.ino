/**
 * @file pcf8591_voltage_read_write.ino
 * @author Renzo Mischianti (www.mischianti.org)
 * @brief This example demonstrates how to use the voltage-based functions of the PCF8591 library.
 * @version 1.0
 * @date 2024-03-15
 *
 * This example shows how to write a specific voltage to the analog output and read the voltage from the analog inputs.
 * It sets the analog output to 2.7V and then reads the voltage from AIN0, AIN1, and AIN2, printing the values to the Serial Monitor.
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
    // Set the analog output to 2.7 Volts
    Serial.println("Writing 2.7V to analog output...");
	pcf8591.voltageWrite(2.7);
	delay(3000);

    // Read the voltage from the analog inputs
	float voltageAIN0 = pcf8591.voltageRead(AIN0);
	Serial.print("Voltage at AIN0: ");
	Serial.println(voltageAIN0);

	float voltageAIN1 = pcf8591.voltageRead(AIN1);
	Serial.print("Voltage at AIN1: ");
	Serial.println(voltageAIN1);

	float voltageAIN2 = pcf8591.voltageRead(AIN2);
	Serial.print("Voltage at AIN2: ");
	Serial.println(voltageAIN2);

	delay(3000);
}
