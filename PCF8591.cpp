#include "PCF8591.h"
#include "Wire.h"

/**
 * Constructor
 * @param address: i2c address
 */
PCF8591::PCF8591(uint8_t address){
	_address = address;
};
#ifndef __AVR
	/**
	 *
	 * @param address: i2c address
	 * @param sda: sda pin
	 * @param scl: scl pin
	 */
	PCF8591::PCF8591(uint8_t address, uint8_t sda, uint8_t scl){
		_address = address;
		_sda = sda;
		_scl = scl;
	};
#endif

/**
 * wake up i2c controller
 */
void PCF8591::begin(){
	#ifndef __AVR
		Wire.begin(_sda, _scl);
	#else
	//			Default pin for AVR some problem on software emulation
	//			#define SCL_PIN _scl
	// 			#define SDA_PIN _sda
		Wire.begin();
	#endif
}

/**
 * Read all analog input in one trasmission
 * @param readType read datasheet for info
 * 	SINGLE_ENDED_INPUT
 *	TREE_DIFFERENTIAL_INPUT
 *	TWO_SINGLE_ONE_DIFFERENTIAL_INPUT
 * 	TWO_DIFFERENTIAL_INPUT
 * @return
 */
struct PCF8591::AnalogInput PCF8591::analogReadAll(byte readType){
	DEBUG_PRINTLN("Begin trasmission");
	Wire.beginTransmission(_address); // wake up PCF8591

	byte operation = AUTOINCREMENT_READ | readType | (_outputStatus&OUTPUT_MASK);

	DEBUG_PRINTLN("Write operation");
	Wire.write(operation); // control byte: reads ADC0 then auto-increment
	DEBUG_PRINTLN("End write (If code stop here add pullup resistor on SDA SCL)");
	Wire.endTransmission(); // end tranmission
	DEBUG_PRINTLN("Request response");
	Wire.requestFrom(_address, (uint8_t)5);

	/*uint8_t control =*/Wire.read();
	analogInput.ain0=Wire.read();
	analogInput.ain1=Wire.read();
	analogInput.ain2=Wire.read();
	analogInput.ain3=Wire.read();

	return analogInput;
};

/**
 * Read one specified channel
 * @param channel channel or analog identify (if readType is SINGLE_ENDED_INPUT)
 * @param readType read datasheet for info
 * 	SINGLE_ENDED_INPUT
 *	TREE_DIFFERENTIAL_INPUT
 *	TWO_SINGLE_ONE_DIFFERENTIAL_INPUT
 * 	TWO_DIFFERENTIAL_INPUT
 * @return
 */
uint8_t PCF8591::analogRead(uint8_t channel, byte readType){
	DEBUG_PRINTLN("Begin trasmission");
	Wire.beginTransmission(_address); // wake up PCF8591

	byte operation = channel | readType| (_outputStatus&OUTPUT_MASK);

	DEBUG_PRINTLN("Write operation");
	Wire.write(operation); // control byte: reads ADC0 then auto-increment
	DEBUG_PRINTLN("End write (If code stop here add pullup resistor on SDA SCL)");
	Wire.endTransmission(); // end tranmission
	DEBUG_PRINTLN("Request response");
	Wire.requestFrom(_address, (uint8_t)2);
	/*uint8_t control = */Wire.read();
	uint8_t ana=Wire.read();

	return ana;
};

/**
 * Read voltage of analog input
 * @param analogPin (Analog identifier)
 * @param microcontrollerReferenceVoltage get voltage from microcontroller voltage (only AVR no esp8266 for esp 3.3v fixed)
 * @param referenceVoltage if microcontrollerReferenceVoltage false take this value
 * @return
 */
float PCF8591::voltageRead(uint8_t analogPin, bool microcontrollerReferenceVoltage, float referenceVoltage){
	float voltageRef = referenceVoltage;
	if (microcontrollerReferenceVoltage) voltageRef = PCF8591::readVcc()/1000.0;
	float ana = PCF8591::analogRead(analogPin);
	return ana*voltageRef/255;
};
/**
 * To write votlage on output
 * @param value voltage to write
 * @param microcontrollerReferenceVoltage get voltage from microcontroller voltage (only AVR no esp8266 for esp 3.3v fixed)
 * @param referenceVoltage if microcontrollerReferenceVoltage false take this value
 */
void PCF8591::voltageWrite(float value, bool microcontrollerReferenceVoltage, float referenceVoltage){
	if (microcontrollerReferenceVoltage) referenceVoltage = PCF8591::readVcc()/1000.0;
	uint8_t ana = value*255/referenceVoltage;
	PCF8591::analogWrite(ana);
};

/**
 * Write value on output pin
 * @param value votlage in volts
 */
void PCF8591::analogWrite(uint8_t value){
	_outputStatus = ENABLE_OUTPUT;
	DEBUG_PRINTLN("Begin trasmission");
	Wire.beginTransmission(_address);
	DEBUG_PRINTLN("Write operation");
	Wire.write(ENABLE_OUTPUT); // sets the PCF8591 into a DA mode
	DEBUG_PRINTLN("Write value");
	Wire.write(value); // sets the output
	DEBUG_PRINTLN("End write (If code stop here add pullup resistor on SDA SCL)");
	Wire.endTransmission();
};

long PCF8591::readVcc(void) {
	#ifdef __AVR
		// Read 1.1V reference against AVcc
		// set the reference to Vcc and the measurement to the internal 1.1V reference
	#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
		ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
	#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
		ADMUX = _BV(MUX5) | _BV(MUX0);
	#else
		ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
	#endif

		delay(2); // Wait for Vref to settle
		ADCSRA |= _BV(ADSC); // Start conversion
		while (bit_is_set(ADCSRA, ADSC))
			; // measuring

		uint8_t low = ADCL; // must read ADCL first - it then locks ADCH
		uint8_t high = ADCH; // unlocks both

		long result = (high << 8) | low;

		  result = 1083630L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
		  // scale_constant = internal1.1Ref * 1023 * 1000
		  // internal1.1Ref = 1.1 * Vcc1 (per voltmeter) / Vcc2 (per readVcc() function)
		return result; // Vcc in millivolts
	#else
//		float vdd = readVcc(); //  ESP.getVdd33(); //ESP.getVcc();
		return 3300;
	#endif
}

