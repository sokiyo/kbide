#include <stdio.h>
#include <string.h>
#include <math.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "tsl2591.h"

TSL2591::TSL2591(int bus_ch, int dev_addr)
{
	channel = bus_ch;
	address = dev_addr;
	polling_ms = TSL2591_POLLING_MS;
}

void TSL2591::init(void)
{
	first_read = true;
	illuminance = 0;
	_integration = 2;
	_gain = 16;
	state = s_detect;
}

int TSL2591::prop_count(void)
{
	return 1;
}

bool TSL2591::prop_name(int index, char *name)
{
	if (index == 0)
	{
		snprintf(name, DEVICE_PROP_NAME_LEN_MAX, "%s", "illuminance");
		return true;
	}

	// not supported
	return false;
}

bool TSL2591::prop_unit(int index, char *unit)
{
	if (index == 0)
	{
		snprintf(unit, DEVICE_PROP_UNIT_LEN_MAX, "%s", "lux");
		return true;
	}

	// not supported
	return false;
}

bool TSL2591::prop_attr(int index, char *attr)
{
	if (index == 0)
	{
		get_attr_str(attr, PROP_ATTR_READ_FLAG | PROP_ATTR_TYPE_NUMBER_FLAG); // read only, number
		return true;
	}

	// not supported
	return false;
}

bool TSL2591::prop_read(int index, char *value)
{
	if (index == 0)
	{
		snprintf(value, DEVICE_PROP_VALUE_LEN_MAX, "%f", illuminance);
		return true;
	}

	// not supported
	return false;
}

bool TSL2591::prop_write(int index, char *value)
{
	// not supported
	return false;
}

double TSL2591::calc_lux(unsigned int ch0, unsigned int ch1)
{
	float atime, again;
	float cpl, lux;

	// Check for overflow conditions first
	if ((ch0 == 0xFFFF) | (ch1 == 0xFFFF))
	{
		// Signal an overflow
		return -1;
	}

	switch (_integration)
	{
	case 0:
		atime = 100.0F;
		break;
	case 1:
		atime = 200.0F;
		break;
	case 2:
		atime = 300.0F;
		break;
	case 3:
		atime = 400.0F;
		break;
	case 4:
		atime = 500.0F;
		break;
	case 5:
		atime = 600.0F;
		break;
	default: // 100ms
		atime = 100.0F;
		break;
	}

	switch (_gain)
	{
	case 0:
		again = 1.0F;
		break;
	case 16:
		again = 25.0F;
		break;
	case 32:
		again = 428.0F;
		break;
	case 48:
		again = 9876.0F;
		break;
	default:
		again = 1.0F;
		break;
	}

	// cpl = (ATIME * AGAIN) / DF
	cpl = (atime * again) / 408.0F;
	lux = (((float)ch0 - (float)ch1)) * (1 - ((float)ch1 / (float)ch0)) / cpl;

	return lux;
}

void TSL2591::process(Driver *drv)
{
	I2CDev *i2c = (I2CDev *)drv;
	uint8_t byte, data[4];

	switch (state)
	{
	case s_detect:
		// stamp polling tickcnt
		polling_tickcnt = get_tickcnt();
		// detect i2c device
		if (i2c->detect(channel, address) == ESP_OK)
		{
			// set gain and integration time
			data[0] = 0xA1;
			data[1] = (_integration | _gain);
			if (i2c->write(channel, address, data, 2) == ESP_OK)
			{
				// power up
				data[0] = 0xA0;
				data[1] = 0x93;
				if (i2c->write(channel, address, data, 2) == ESP_OK)
				{
					// clear error flag
					error = false;
					// get current tickcnt
					tickcnt = get_tickcnt();
					state = s_get_lux;
				}
				else
				{
					state = s_error;
				}
			}
			else
			{
				state = s_error;
			}
		}
		else
		{
			state = s_error;
		}
		break;

	case s_get_lux:
		if (is_tickcnt_elapsed(tickcnt, (120 * _integration)) || (!first_read))
		{
			// clear first read flag
			first_read = false;

			// get channel 0
			byte = 0xb4;
			if (i2c->read(channel, address, &byte, 1, data, 2) == ESP_OK)
			{
				// get channel 1
				byte = 0xb6;
				if (i2c->read(channel, address, &byte, 1, &data[2], 2) == ESP_OK)
				{
					// calc illuminance in lux
					illuminance = calc_lux(data[0] | (data[1] << 8), data[2] | (data[3] << 8));
					// set initialized flag
					initialized = true;

					// load polling tickcnt
					tickcnt = polling_tickcnt;
					// goto wait and retry with detect state
					state = s_wait;
				}
				else
				{
					state = s_error;
				}
			}
			else
			{
				state = s_error;
			}
		}
		break;

	case s_error:
		// set error flag
		error = true;
		// clear initialized flag
		initialized = false;
		// set first read flag
		first_read = true;
		// get current tickcnt
		tickcnt = get_tickcnt();
		// goto wait and retry with detect state
		state = s_wait;
		break;

	case s_wait:
		// wait polling_ms timeout
		if (is_tickcnt_elapsed(tickcnt, polling_ms))
		{
			state = s_detect;
		}
		break;
	}
}

double TSL2591::get_illuminance(int gain, int integration)
{
	_gain = gain;
	_integration = integration;
	return illuminance;
}
