#ifndef __RD_ANALOG_H__
#define __RD_ANALOG_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"
#include "driver/adc.h"

// ads-ws1 rain gauge
class RD_ANALOG : public Device {
	private:
		enum {
			s_read, s_idle
		} state;
		gpio_num_t sensor_gpio;
		adc1_channel_t adc_ch;
		TickType_t chkrtc_tickcnt;

	public:
		TickType_t tickcnt;
		int raw_data;
		// constructor
		RD_ANALOG(int dev_addr);
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
};

#endif
