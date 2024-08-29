#ifndef __MJOYSTICK_H__
#define __MJOYSTICK_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"
#include "driver/adc.h"

class MJOYSTICK : public Device {
	private:
		enum {
			s_detect, s_error, s_idle
		} state;
		adc1_channel_t x_ch, y_ch;

	public:
		TickType_t tickcnt;
		int x_pos, y_pos;
		float x_slope_cal = 1, y_slope_cal = 1;
		float x_slope_map = 0, y_slope_map = 0;
		int x_raw_min = 0, y_raw_min = 0;
		int x_th_upper = 2395, x_th_lower = 1700;
		int y_th_upper = 2395, y_th_lower = 1700;
		int x_out_min = 0, x_out_max = 180, x_out_mid = 90;
		int y_out_min = -100, y_out_max = 100, y_out_mid = 0;

		// constructor
		MJOYSTICK(int x, int y);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		// method
		int get_raw_position(int axis);
		int get_position(int axis);
		void calibrate_set_x(int release_value, int min_value, int max_value, int out_min, int out_max);
		void calibrate_set_y(int release_value, int min_value, int max_value, int out_min, int out_max);
		//---
		int fMapX(int x);
		int fMapY(int y);
		int fPosX(void);
		int fPosY(void);
};

#endif
