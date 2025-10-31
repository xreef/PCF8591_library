/** \mainpage PCF8591 library
 * PCF8591 Analog Port Expand
 * https://www.mischianti.org/2019/01/03/pcf8591-i2c-analog-i-o-expander/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Renzo Mischianti www.mischianti.org All right reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef PCF8591_h
#define PCF8591_h

#include "Wire.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Uncomment to enable printing out nice debug messages.
// #define PCF8591_DEBUG

// Define where debug output will be printed.
#define DEBUG_PRINTER Serial

// Setup debug printing macros.
#ifdef PCF8591_DEBUG
	#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
	#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
	#define DEBUG_PRINT(...) {}
	#define DEBUG_PRINTLN(...) {}
#endif

#include <math.h>

#define AIN0 0b00000000
#define AIN1 0b00000001
#define AIN2 0b00000010
#define AIN3 0b00000011

#define CHANNEL0 0b00000000
#define CHANNEL1 0b00000001
#define CHANNEL2 0b00000010
#define CHANNEL3 0b00000011

#define AUTOINCREMENT_READ 0b00000100

#define SINGLE_ENDED_INPUT 	0b00000000
#define TREE_DIFFERENTIAL_INPUT 0b00010000
#define TWO_SINGLE_ONE_DIFFERENTIAL_INPUT 0b00100000
#define TWO_DIFFERENTIAL_INPUT 0b00110000

#define ENABLE_OUTPUT 0b01000000
#define DISABLE_OUTPUT 0b01000000

#define OUTPUT_MASK 0b01000000

class PCF8591 {
public:
	struct AnalogInput {
	   uint8_t ain0;
	   uint8_t ain1;
	   uint8_t ain2;
	   uint8_t ain3;
	} analogInput;

	PCF8591(uint8_t address);

#if !defined(__AVR) && !defined(ARDUINO_ARCH_SAMD) && !defined(TEENSYDUINO) && !defined(ARDUINO_ARCH_RENESAS)
	PCF8591(uint8_t address, int sda, int scl);
#endif

#if defined(ESP32) || defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_RENESAS)
	///// changes for second i2c bus
	PCF8591(TwoWire *pWire, uint8_t address);
#endif
#if defined(ESP32)
	PCF8591(TwoWire *pWire, uint8_t address, int sda, int scl);
#endif

	void begin();
	void begin(uint8_t address);
	struct AnalogInput analogReadAll(byte readType = SINGLE_ENDED_INPUT);
	uint8_t analogRead(uint8_t channel, byte readType = SINGLE_ENDED_INPUT);
	void analogWrite(uint8_t value);

	void voltageWrite(float value, bool microcontrollerReferenceVoltage = true, float referenceVoltage = 5.0);
	float voltageRead(uint8_t analogPin, bool microcontrollerReferenceVoltage = true, float referenceVoltage = 5.0);
private:
	TwoWire *_wire;

	uint8_t _address;
	uint8_t _sda = SDA;
	uint8_t _scl = SCL;

	byte _outputStatus = DISABLE_OUTPUT;

	long readVcc(void);
};

#endif
