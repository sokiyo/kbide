#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "kb_joy_api.h"

KB_JOY::KB_JOY(int bus_ch, int dev_addr) {
	polling_ms = KB_JOY_POLLING_MS;
	channel = bus_ch;
	address = 0;
}

void KB_JOY::init(void) {

	initialized = true;
	error = false;

}

int KB_JOY::prop_count(void) {
	return 0;
}

bool KB_JOY::prop_name(int index, char* name) {
	// not supported
	return false;
}

bool KB_JOY::prop_unit(int index, char* unit) {
	// not supported
	return false;
}

bool KB_JOY::prop_attr(int index, char* attr) {
	// not supported
	return false;
}

bool KB_JOY::prop_read(int index, char* value) {
	// not supported
	return false;
}

bool KB_JOY::prop_write(int index, char* value) {
	// not supported
	return false;
}


void KB_JOY::process(Driver* drv) {
	i2c_p = (I2CDev*)drv;

}

void KB_JOY::wdt_feed() {
	wdt_cnt = 50;
}

long KB_JOY::map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int16_t KB_JOY::read(uint8_t channel) {
	int16_t val = 0;

	if (i2c_p == NULL)
		return 0;
	if (channel > 3)
	{
		return 0;
	}


	
	// Start with default values
	uint16_t config = ADS1015_REG_CONFIG_CQUE_NONE | // Disable the comparator (default val)
		ADS1015_REG_CONFIG_CLAT_NONLAT | // Non-latching (default val)
		ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
		ADS1015_REG_CONFIG_CMODE_TRAD | // Traditional comparator (default val)
		(0x00E0) | // 860 samples per second (default)
		ADS1015_REG_CONFIG_MODE_SINGLE;   // Single-shot mode (default)

	// Set PGA/voltage range
	config |= adsGain_t::GAIN_ONE;

	// Set single-ended input channel
	switch (channel)
	{
	case (0):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
		break;
	case (1):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
		break;
	case (2):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
		break;
	case (3):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
		break;
	}
	// Set 'start single-conversion' bit
	config |= ADS1015_REG_CONFIG_OS_SINGLE;

	uint8_t tmp[3];

	tmp[0] = ADS1015_REG_POINTER_CONFIG;
	tmp[1] = (uint16_t)config >> 8;
	tmp[2] = (uint16_t)config >> 0;
	if (i2c_p->write(0, kb_joy_addr, tmp, 3) != ESP_OK) {
		return 0;
	}

	// Wait for the conversion to complete
	// delay(m_conversionDelay);  // 2ms
	tickcnt = get_tickcnt() + 2;
	while (tickcnt > get_tickcnt())
	{
		asm("nop");
	}
	// vTaskDelay(10 / portTICK_RATE_MS);

	tmp[0] = ADS1015_REG_POINTER_CONVERT; // address pointer 0x00 for conversion register
	if (i2c_p->write(0, kb_joy_addr, tmp, 1) != ESP_OK) {
		return 0;
	}
	if (i2c_p->read(0, kb_joy_addr, NULL, 0, tmp, 2) == ESP_OK) {
		val = ((uint16_t)tmp[0] << 8 | (uint16_t)tmp[1]);

		switch (channel)
		{
		case (0):
			val = map(val, 26470, 130, -105, 105);
			break;
		case (1):
			val = map(val, 130, 26470, -105, 105);
			break;
		case (2):
			val = map(val, 26470, 130, -105, 105);
			break;
		case (3):
			val = map(val, 130, 26470, -105, 105);
			break;
		}
		if (val > 100)
			val = 100;

		if (val < -100)
			val = -100;

	}
	return val;
}

