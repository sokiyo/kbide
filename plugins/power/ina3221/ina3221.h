#ifndef __INA3221_H__
#define __INA3221_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define INA3221_POLLING_MS					1000

class INA3221 : public Device {
	private:
		enum {
			s_detect, s_reset, s_get_config, s_get_voltages, s_error, s_wait
		} state;

	public:
		TickType_t tickcnt, polling_tickcnt;
		double voltages[3];
		double currents[3];
		uint32_t shunts[3];
		// constructor		
		INA3221(int bus_ch, int dev_addr);
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
		double get_voltage(int ch);
		double get_current(int ch);
		void set_shunt_resistor(int ch, uint32_t shunt_resistor_mohm);
};

#endif
