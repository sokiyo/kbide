#ifndef __SPEC_IOS_H__
#define __SPEC_IOS_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"
#include "driver/adc.h"

// ads-ws1 rain gauge
class SPEC_IOS : public Device {
	private:
		enum {
			s_read, s_idle
		} state;
		gpio_num_t sensor_gpio;
		gpio_num_t dig_gpio;
		adc1_channel_t adc_ch;
		TickType_t chkrtc_tickcnt;

	public:
		TickType_t tickcnt;
		int raw_data;				// analog read
		int dig_rd;					// digital read
		// constructor
		SPEC_IOS(int dev_addr);
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
		int get_analog_raw(void);
		int rd_digital(void);
};

#endif
