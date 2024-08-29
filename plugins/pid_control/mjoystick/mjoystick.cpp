/*
	mJoystick rev 0.1 developed by Dusadee Treeumnuk, EDT/NECTEC 
		- rev 0.0 (Nov 6, 2023): works well but does not take the release positions into account and no range settings for x and y axes
		- rev 0.1 (Nov 7, 2023): modified calibrate_set_x and calibrate_set_y to take the release positions into account and have range settings for x and y axes
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

#define THRESHOLD_TOL	500			// Threshold tolerance


MJOYSTICK::MJOYSTICK(int x, int y) {
	x_ch = (adc1_channel_t)x;
	y_ch = (adc1_channel_t)y;
}

void MJOYSTICK::init(void) {
#ifdef __DEBUG__
	esp_log_level_set(TAG, ESP_LOG_VERBOSE);
#endif

  	adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(x_ch, ADC_ATTEN_DB_11);		// for 12 bit ADC 
    adc1_config_channel_atten(y_ch, ADC_ATTEN_DB_11);		// for 12 bit ADC


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

int MJOYSTICK::fMapX(int x) {
	return (int)(x_slope_map*x + x_out_min);
}

int MJOYSTICK::fMapY(int y) {
	return (int)(y_slope_map*y + y_out_min);
}

int MJOYSTICK::fPosX(void) {

	int x_raw = get_raw_position(0);
	int x = (int)(x_slope_cal*(x_raw - x_raw_min));

	if (( x > x_th_lower)  && (x < x_th_upper)) return x_out_mid; else return fMapX(x);
	return 0;
}

int MJOYSTICK::fPosY(void) {
 
	int y_raw = get_raw_position(1);
	int y = (int)(y_slope_cal*(y_raw - y_raw_min));

	if (( y > y_th_lower)  && (y < y_th_upper)) return y_out_mid; else return fMapY(y);
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

void MJOYSTICK::calibrate_set_x(int release_value, int min_value, int max_value, int out_min, int out_max) {

	x_raw_min = min_value;
	x_slope_cal = (4095.0 - 0.0) / (max_value - min_value);
	int x_th = (int)(x_slope_cal*(release_value - x_raw_min));
	x_slope_map = (out_max - out_min) / 4095.0;

	x_th_upper = x_th + THRESHOLD_TOL;
	x_th_lower = x_th - THRESHOLD_TOL;
	x_out_min = out_min;
	x_out_max = out_max;
	x_out_mid = (x_out_max + x_out_min) / 2;
}

void MJOYSTICK::calibrate_set_y(int release_value, int min_value, int max_value, int out_min, int out_max) {

	y_raw_min = min_value;
	y_slope_cal = (4095.0 - 0.0) / (max_value - min_value);
	int y_th = (int)(y_slope_cal*(release_value - y_raw_min));
	y_slope_map = (out_max - out_min) / 4095.0;

	y_th_upper = y_th + THRESHOLD_TOL;
	y_th_lower = y_th - THRESHOLD_TOL;
	y_out_min = out_min;
	y_out_max = out_max;
	y_out_mid = (y_out_max + y_out_min) / 2;
}
