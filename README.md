<div>
<a href="https://www.mischianti.org/forums/forum/mischiantis-libraries/pcf8591-i2c-analog-expander/"><img
  src="https://github.com/xreef/LoRa_E32_Series_Library/raw/master/resources/buttonSupportForumEnglish.png" alt="Support forum pcf8591 English"
   align="right"></a>
</div>
<div>
<a href="https://www.mischianti.org/it/forums/forum/le-librerie-di-mischianti/pcf8591-expander-analogico-i2c/"><img
  src="https://github.com/xreef/LoRa_E32_Series_Library/raw/master/resources/buttonSupportForumItaliano.png" alt="Forum supporto pcf8591 italiano"
  align="right"></a>
</div>


#
#

You can find updated version of documentation on my site​ [PCF8591](https://www.mischianti.org/2019/01/03/pcf8591-i2c-analog-i-o-expander/)

Library to use i2c analog IC with arduino and esp8266. Can read analog value and write analog value with only 2 wire (perfect for ESP-01).

 - 01/02/2024: v1.1.2 Add the possibility to insert address at begin() function 
 - 10/07/2023: v1.1.1 Add support for Arduino UNO R4 
 - 16/02/2023: v1.1.0 
    - Fix STM32 support and add support for Raspberry Pi Pico and other rp2040 boards
    - Add support for custom SERCOM interface of Arduino SAMD devices. Force SDA SCL to use GPIO numeration for STM32 bug (https://www.mischianti.org/forums/topic/compatible-with-stm32duino/). 
    - Force SDA SCL to use GPIO numeration (https://www.mischianti.org/forums/topic/cannot-set-sda-clk-on-esp8266/).
    - Fix the SDA SCL type #58 and add basic support for SAMD device.
 - 06/04/2022: v1.0.2 Fix package size

Tutorial: 

To download. click the DOWNLOADS button in the top right corner, rename the uncompressed folder PCF8591. Check that the PCF8591 folder contains `PCF8591\\.cpp` and `PCF8591.h`. Place the DHT library folder your `<arduinosketchfolder>/libraries/` folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.

# Reef complete PCF8591 Analog input and analog output to digital converter with i2c bus.
I try to simplify the use of this IC, with a minimal set of operation.

Constructor:
you must pas the address of i2c (to check the adress use this guide [I2cScanner](https://playground.arduino.cc/Main/I2cScanner)) 
```cpp
	PCF8591(uint8_t address);
```
for esp8266 if you want specify SDA e SCL pin use this:

```cpp
	PCF8591(uint8_t address, uint8_t sda, uint8_t scl);
```

then IC as you can see in the image have 4 analog input and 1 analog output:

![PCF8591 schema](https://github.com/xreef/PCF8591_library/blob/master/resources/PCF8591-Pin-Outs.png)

So to read all analog input in one trasmission you can do (the value is from 0 to 255):
```cpp
	PCF8591::AnalogInput ai = pcf8591.analogReadAll();
	Serial.print(ai.ain0);
	Serial.print(" - ");
	Serial.print(ai.ain1);
	Serial.print(" - ");
	Serial.print(ai.ain2);
	Serial.print(" - ");
	Serial.println(ai.ain3);
```


if you want read a single analog input or channel:

```cpp
	int ana = pcf8591.analogRead(AIN0); // read analog 0
```

This IC have multiple type of read and you can use Analog input or analog channel (when you use single read analog input and channel are the same:

![Channel selection](https://github.com/xreef/PCF8591_library/blob/master/resources/channel_selection.PNG)	

For example to read the value of channel 0 in Two differential input you must do:
```cpp
	int ana = pcf8591.analogRead(CHANNEL0, TWO_DIFFERENTIAL_INPUT); // read analog 0
```

If you want write an analog value you must do (the value is from 0 to 255):
```cpp
	pcf8591.analogWrite(128);
```

Additional feature is to read a write voltage:
For the calculation of voltage you must pass some parameter:
 - microcontrollerReferenceVoltage: get voltage from microcontroller voltage (only AVR no esp8266 for esp 3.3v fixed)
 - referenceVoltage: if microcontrollerReferenceVoltage false take this value
 

The command are:
```cpp
	void voltageWrite(float value, bool microcontrollerReferenceVoltage = true, float referenceVoltage = 5.0);
	float voltageRead(uint8_t analogPin, bool microcontrollerReferenceVoltage = true, float referenceVoltage = 5.0);
```

An examples is:
```cpp
	pcf8591.voltageWrite(2.7); // 2.7Volts output
	delay(3000);

	float ana0V = pcf8591.voltageRead(AIN0); // Read voltage from analog 0
	Serial.println(ana0V);
```

For the examples I use this wire schema on breadboard:
![Breadboard](https://github.com/xreef/PCF8591_library/blob/master/resources/simpleschema_bb.png)

