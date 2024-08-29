#include <stdio.h>
#include <string.h>
//#include "driver/adc.h"
#include "esp_system.h"
#include "kidbright32.h"
#include "rd_analog.h"

RD_ANALOG::RD_ANALOG(int dev_addr) {
	address = dev_addr;
	sensor_gpio = (gpio_num_t)dev_addr;
	switch (sensor_gpio) {
		case GPIO_NUM_39 : adc_ch = ADC1_CHANNEL_3; break;
		case GPIO_NUM_34 : adc_ch = ADC1_CHANNEL_6; break;
		case GPIO_NUM_35 : adc_ch = ADC1_CHANNEL_7; break;
		default : adc_ch = ADC1_CHANNEL_6; break;		
	} 
}

void RD_ANALOG::init(void) {

   	adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(adc_ch,ADC_ATTEN_DB_0);

	// init result
	raw_data = 0;
	state = s_read;
}

int RD_ANALOG::prop_count(void) {
	return 0;
}

bool RD_ANALOG::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool RD_ANALOG::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool RD_ANALOG::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool RD_ANALOG::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool RD_ANALOG::prop_write(int index, char *value) {
	// not supported
	return false;
}

void RD_ANALOG::process(Driver *drv) {

	switch (state) {
		case s_read:

    		raw_data = adc1_get_raw(adc_ch);

			// clear error flag
			error = false;
			// set initialized flag
			initialized = true;

			// go to wait state
			//state = s_idle;
			break;

		case s_idle:

			break;
	}
}

int RD_ANALOG::get_analog_raw(void) {
	int val;

	val = raw_data;

	return val;
}
