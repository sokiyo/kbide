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
		int x_raw_min = 0, x_raw_max = 4095;
		int y_raw_min = 0, y_raw_max = 4095;

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
		void calibrate_set_x(int release_value, int min_value, int max_value);
		void calibrate_set_y(int release_value, int min_value, int max_value);
		//---
		int fMapXleft(int x);
		int fMapXright(int x);
		int fMapYup(int y);
		int fMapYdown(int y);
		int fPosX(void);
		int fPosY(void);
};

#endif
