#include <stdio.h>
#include <string.h>
//#include "driver/adc.h"
#include "esp_system.h"
#include "kidbright32.h"
#include "spec_ios.h"

SPEC_IOS::SPEC_IOS(int dev_addr) {
	address = dev_addr;
	sensor_gpio = (gpio_num_t)dev_addr;
	dig_gpio = (gpio_num_t)dev_addr;
	switch (sensor_gpio) {
		case GPIO_NUM_39 : adc_ch = ADC1_CHANNEL_3; break;
		case GPIO_NUM_32 : adc_ch = ADC1_CHANNEL_4; break;
		case GPIO_NUM_33 : adc_ch = ADC1_CHANNEL_5; break;
		case GPIO_NUM_34 : adc_ch = ADC1_CHANNEL_6; break;
		case GPIO_NUM_35 : adc_ch = ADC1_CHANNEL_7; break;
		default : adc_ch = ADC1_CHANNEL_6; break;		
	} 
}

void SPEC_IOS::init(void) {

/*    	adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(adc_ch,ADC_ATTEN_DB_0); */

	// init result
	raw_data = 0;
	state = s_read;
}

int SPEC_IOS::prop_count(void) {
	return 0;
}

bool SPEC_IOS::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool SPEC_IOS::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool SPEC_IOS::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool SPEC_IOS::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool SPEC_IOS::prop_write(int index, char *value) {
	// not supported
	return false;
}

void SPEC_IOS::process(Driver *drv) {

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

int SPEC_IOS::get_analog_raw(void) {
	int val;

   	adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(adc_ch,ADC_ATTEN_DB_0);
	raw_data = adc1_get_raw(adc_ch);
	val = raw_data;

	return val;
}

int SPEC_IOS::rd_digital(void) {

	gpio_set_direction(dig_gpio,GPIO_MODE_INPUT);
	gpio_pullup_en(dig_gpio);
	gpio_set_pull_mode(dig_gpio,GPIO_PULLUP_ONLY);

	return gpio_get_level(dig_gpio);
}
