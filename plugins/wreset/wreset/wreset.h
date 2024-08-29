#ifndef __WRESET_H__
#define __WRESET_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"
#include <esp_int_wdt.h>
#include <esp_task_wdt.h>


class WRESET : public Device {
	private:
		enum {
			s_detect, s_blink
		} state;
		int blink_status;
		bool blink_flag;

	public:
		TickType_t tickcnt;
		// constructor
		WRESET(void);
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
		void start(void);
// now wut has only 1 function		void stop(void);
		void startwdt(void);
};

#endif