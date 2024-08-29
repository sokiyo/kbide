#include "esp_system.h"
#include "esp_sleep.h"
#include "kidbright32.h"
#include "ina3221.h"

#undef __DEBUG__
//#define __DEBUG__

#ifdef __DEBUG__
#include "esp_log.h"
const char *TAG = "ina3221";
#endif

#define INA3221_REG_CONFIG                      (0x00)
#define INA3221_REG_SHUNTVOLTAGE_1              (0x01)
#define INA3221_REG_BUSVOLTAGE_1                (0x02)
#define INA3221_REG_SHUNTVOLTAGE_2              (0x03)
#define INA3221_REG_BUSVOLTAGE_2                (0x04)
#define INA3221_REG_SHUNTVOLTAGE_3              (0x05)
#define INA3221_REG_BUSVOLTAGE_3                (0x06)
#define INA3221_REG_CRITICAL_ALERT_1            (0x07)
#define INA3221_REG_WARNING_ALERT_1             (0x08)
#define INA3221_REG_CRITICAL_ALERT_2            (0x09)
#define INA3221_REG_WARNING_ALERT_2				(0x0a)
#define INA3221_REG_CRITICAL_ALERT_3            (0x0b)
#define INA3221_REG_WARNING_ALERT_3             (0x0c)
#define INA3221_REG_SHUNT_VOLTAGE_SUM           (0x0d)
#define INA3221_REG_SHUNT_VOLTAGE_SUM_LIMIT     (0x0e)
#define INA3221_REG_MASK                        (0x0f)
#define INA3221_REG_VALID_POWER_UPPER_LIMIT     (0x10)
#define INA3221_REG_VALID_POWER_LOWER_LIMIT     (0x11)
#define INA3221_REG_MANUFACTURER_ID				(0xfe)
#define INA3221_REG_DIE_ID						(0xff)

// ### esps-idf-lib
// https://github.com/UncleRus/esp-idf-lib/tree/master/components

// https://github.com/UncleRus/esp-idf-lib/blob/master/components/ina3221/ina3221.c#L233
#define INA3221_BUS_VOLTAGE_STEP				(0.001)
// https://github.com/UncleRus/esp-idf-lib/blob/master/components/ina3221/ina3221.c#L250
#define INA3221_SHUNT_VOLTAGE_STEP				(0.000005)
#define INA3221_R_SHUNT_MILLI_OHM				(100)		// 100 milli-ohm

INA3221::INA3221(int bus_ch, int dev_addr) {
	int i;

	channel = bus_ch;
	address = dev_addr;
	polling_ms = INA3221_POLLING_MS;

	for (i = 0; i < 3; i++) {
		voltages[i] = 0;
		currents[i] = 0;
		shunts[i] = INA3221_R_SHUNT_MILLI_OHM;
	}
}

void INA3221::init(void) {
#ifdef __DEBUG__
	esp_log_level_set(TAG, ESP_LOG_VERBOSE);
#endif

	state = s_detect;
}

int INA3221::prop_count(void) {
	// not supported
	return 0;
}

bool INA3221::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool INA3221::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool INA3221::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool INA3221::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool INA3221::prop_write(int index, char *value) {
	// not supported
	return false;
}

void INA3221::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	uint8_t addr;
	uint8_t data[6];
	int16_t val;
	int i;

	switch (state) {
		case s_detect:
			// stamp polling tickcnt
			polling_tickcnt = get_tickcnt();
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {				
				if (i2c->write(channel, address, data, 2) == ESP_OK) {					
					// clear error flag
					error = false;
					state = s_reset;
				}
				else {
					state = s_error;
				}
			}
			else {
				state = s_error;
			}
			break;

		case s_reset:			
			data[0] = INA3221_REG_CONFIG;
			data[1] = 0xf1; // reset bit set
			data[2] = 0x27;
			if (i2c->write(channel, address, data, 3) == ESP_OK) {
				// goto get config state
				state = s_get_config;
			}
			else {
				state = s_error;
			}
			break;

		case s_get_config:			
			addr = INA3221_REG_CONFIG;
			if (i2c->read(channel, address, &addr, 1, data, 2) == ESP_OK) {	
				// #ifdef __DEBUG__
				// 	ESP_LOGI(TAG, "Configuration = 0x%2.2x%2.2x", data[0], data[1]);
				// #endif
				// goto get voltages state
				state = s_get_voltages;
			}
			else {
				state = s_error;
			}
			break;

		case s_get_voltages:
			addr = INA3221_REG_SHUNTVOLTAGE_1;
			for (i = 0; i < 6; i++) {
				if (i2c->read(channel, address, &addr, 1, data, 2) == ESP_OK) {
					// #ifdef __DEBUG__
					// 	ESP_LOGI(TAG, "%d = 0x%2.2x%2.2x", i, data[0], data[1]);
					// #endif
					val = (int16_t)(((data[0] << 8) & 0xff00) | (data[1] & 0xff));
					if ((i % 2) == 0) {						
						currents[i / 2] = ((val * INA3221_SHUNT_VOLTAGE_STEP) * 1000) / shunts[i / 2];
					}
					else {						
						voltages[(i - 1) / 2] = (val * INA3221_BUS_VOLTAGE_STEP);
					}					
					addr++;					
				}
				else {
					state = s_error;
					break;
				}
			}

			if (state != s_error) {
				for (i = 0; i < 3; i++) {
					#ifdef __DEBUG__
						ESP_LOGI(TAG, "CH%d %f V, %f A", i + 1, voltages[i], currents[i]);
					#endif
				}
				#ifdef __DEBUG__
					printf("\n");
				#endif

				// set initialized flag
				initialized = true;
				// get current tickcnt
				tickcnt = get_tickcnt();
				// goto wait and retry with detect state
				state = s_wait;
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

		case s_wait:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_get_voltages;
			}
			break;
	}
}

double INA3221::get_voltage(int ch) {
	if ((ch >= 0) && (ch <= 2)) {
		return voltages[ch];
	}
	else {
		return 0;
	}	
}

double INA3221::get_current(int ch) {
	if ((ch >= 0) && (ch <= 2)) {
		return currents[ch];
	}
	else {
		return 0;
	}
}

void INA3221::set_shunt_resistor(int ch, uint32_t shunt_resistor_mohm) {
	if ((ch >= 0) && (ch <= 2)) {
		shunts[ch] = shunt_resistor_mohm;
	}
}
