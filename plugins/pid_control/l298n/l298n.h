#ifndef __L298N_H__
#define __L298N_H__

#include "driver.h"
#include "device.h"


class L298N : public Device {
	private:
		enum {
			s_detect, s_idle, s_error, s_wait
		} state;
		TickType_t tickcnt;
		int motor_num = 1;
		mcpwm_timer_t timer_num;

	public:
		// constructor
		L298N(int dev_addr);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		void speed(uint8_t dir, int percent);
		void stop(void); 			// stop motor drive
};

#endif
