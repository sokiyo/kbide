#ifndef __SLEEP_H__
#define __SLEEP_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"

class SLEEP : public Device {
	private:
		enum {
			s_detect, s_idle
		} state;

	public:
		TickType_t tickcnt;
		// constructor
		SLEEP(void);
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
		void deep_gpio(gpio_num_t gpio);
		void deep_timeout(uint32_t timeout_ms);
		void deep_gpio_timeout(gpio_num_t gpio, uint32_t timeout_ms);
};

#endif
