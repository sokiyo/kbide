/*
	mJoystick Rev 0.0 developed by Dusadee Treeumnuk, EDT/NECTEC 
		- Rev 0.0 : works well but does not take release positions into account and no range settings for x and y axes  
*/
#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "mjoystick.h"

#undef __DEBUG__
//#define __DEBUG__

#ifdef __DEBUG__
#include "esp_log.h"
#endif

const char *TAG = "mjoystick";

#define TH_REL_UPPER	2395		// Upper threshold for joystick release
#define TH_REL_LOWER	1700		// Lower threshold for joystick release


MJOYSTICK::MJOYSTICK(int x, int y) {
	x_ch = (adc1_channel_t)x;
	y_ch = (adc1_channel_t)y;
}

void MJOYSTICK::init(void) {
#ifdef __DEBUG__
	esp_log_level_set(TAG, ESP_LOG_VERBOSE);
#endif

  	adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(x_ch, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(y_ch, ADC_ATTEN_DB_11);


	state = s_detect;
}

int MJOYSTICK::prop_count(void) {
	return 0;
}

bool MJOYSTICK::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool MJOYSTICK::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool MJOYSTICK::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool MJOYSTICK::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool MJOYSTICK::prop_write(int index, char *value) {
	// not supported
	return false;
}

void MJOYSTICK::process(Driver *drv) {
	gpio_config_t io_conf;
	int i, cal;

	switch (state) {
		case s_detect:
			error = false;
			initialized = true;

			state = s_idle;
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;

			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_idle;
			break;

		case s_idle:

			break;
	}
}


int MJOYSTICK::get_raw_position(int axis) {
	switch (axis) {
		case 0 : return (int)adc1_get_raw(x_ch); 
		case 1 : return (int)adc1_get_raw(y_ch); 
	}
	return 0;
}

//---------------------------------
int MJOYSTICK::fMapXleft(int x) {
  	float m = -90.0 / TH_REL_LOWER;
  	return (int)(m*x + 180);
}

int MJOYSTICK::fMapXright(int x) {
 	 float m = -90.0 / TH_REL_LOWER;
  	return (int)(m*(x - 4095));
}

int MJOYSTICK::fMapYup(int y) {
 	 float m = -100.0 / TH_REL_LOWER;
  	return (int)(m*(y - TH_REL_LOWER));
}

int MJOYSTICK::fMapYdown(int y) {
  	float m = -100.0 / TH_REL_LOWER;
  	return (int)(m*(y - TH_REL_UPPER));
}

int MJOYSTICK::fPosX(void) {

	int x_raw = get_raw_position(0);
	float m = (4095.0 - 0.0) / (x_raw_max - x_raw_min);
	int x = (int)(m*(x_raw - x_raw_min));
	if (( x > TH_REL_LOWER)  && (x < TH_REL_UPPER)) return 90;
	if (x > TH_REL_UPPER) return fMapXright(x);
	if (x < TH_REL_LOWER) return fMapXleft(x);
	return 0;
}

int MJOYSTICK::fPosY(void) {
 
	int y_raw = get_raw_position(1);
	float m = (4095.0 - 0.0) / (y_raw_max - y_raw_min);
	int y = (int)(m*(y_raw - y_raw_min));
	if (( y > TH_REL_LOWER)  && (y < TH_REL_UPPER)) return 0;
	if (y > TH_REL_UPPER) return fMapYdown(y);
	if (y < TH_REL_LOWER) return fMapYup(y);
	return 0;
}
//---------------------------------

int MJOYSTICK::get_position(int axis) {

	switch (axis) {
		case 0 : return fPosX(); 
		case 1 : return fPosY(); 
	}
	return 0;
}

void MJOYSTICK::calibrate_set_x(int release_value, int min_value, int max_value) {
	x_raw_min = min_value; 
	x_raw_max = max_value;
}

void MJOYSTICK::calibrate_set_y(int release_value, int min_value, int max_value) {
	y_raw_min = min_value; 
	y_raw_max = max_value;
}
