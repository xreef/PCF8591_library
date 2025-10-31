/**
 * @file pcf8591_generate_sinusoidal.ino
 * @author Renzo Mischianti (www.mischianti.org), Yves Pelletier
 * @brief This example demonstrates how to generate a sinusoidal signal using the PCF8591's analog output.
 * @version 1.0
 * @date 2024-03-15
 *
 * This sketch generates a sinusoidal wave on the analog output of the PCF8591 module.
 * The output value is calculated using the sin() function and updated in a loop.
 * Original concept by Yves Pelletier.
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

// Counter for the sinusoidal wave calculation
int counter = 0;

void setup()
{
    // Initialize the PCF8591 module
    pcf8591.begin();
}

void loop(){
    // Calculate the sinusoidal value and write it to the analog output
    // The output will be a sine wave with an amplitude of 100 and an offset of 100.
    pcf8591.analogWrite(100 + 100 * sin(2 * 3.1416 * counter / 200));

    // Uncomment the line below to generate a sawtooth wave instead
    // pcf8591.analogWrite(counter);

    // Increment the counter and reset it to 0 if it exceeds 200
    counter++;
    if (counter > 200){
        counter = 0;
    }

    // A small delay to control the frequency of the wave
    delay(1);
}
