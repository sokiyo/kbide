#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "bh1750.h"

BH1750::BH1750(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = BH1750_POLLING_MS;
}

void BH1750::init(void) {
	lux = 0;
	state = s_detect;
}

int BH1750::prop_count(void) {
	return 0;
}

bool BH1750::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool BH1750::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool BH1750::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool BH1750::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool BH1750::prop_write(int index, char *value) {
	// not supported
	return false;
}

void BH1750::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;

	switch (state) {
		case s_detect:
			if (i2c->detect(channel, address) == ESP_OK) {
				uint8_t buff = 0x10; // Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
				if (i2c->write(channel, address, &buff, 1) == ESP_OK) {
					error = false;
					initialized = true;

					state = s_read;
				} else {
					state = s_error;
				}
			} else {
				state = s_error;
			}
			break;

		case s_read:
			if (is_tickcnt_elapsed(polling_tickcnt, polling_ms)) {
				uint8_t buff[2];
				if (i2c->read(channel, address, NULL, 0, buff, 2) == ESP_OK) {
					uint16_t tmp = 0;
					tmp = buff[0];
					tmp <<= 8;
					tmp |= buff[1];
					lux = tmp;
					lux /= 1.2;

					polling_tickcnt = get_tickcnt();
					state = s_read;
				} else {
					state = s_error;
				}
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// init temperature
			lux = 0;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

		case s_wait:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;
	}
}

int BH1750::readLightLevel() {
	return lux;
}
