#ifndef __PLANTOWER_PMS7003_H__
#define __PLANTOWER_PMS7003_H__

#include "driver.h"
#include "device.h"

#define PLANTOWER_POLLING_MS 1000

class PLANTOWER : public Device
{
private:
	enum
	{
		s_detect,
		s_power_on,
		s_change_passive_mode,
		s_read,
		s_error,
		s_wait,
		s_idle
	} state;
	TickType_t tickcnt;
	int tx_pin;
	int rx_pin;
	int pm2_5;
	int pm10;
	int error_count;
	int error_clear_count;
	int retry_count;

	bool command(const uint8_t *cmd);
	bool read(int *pm2_5_val, int *pm10_val);

public:
	// constructor
	PLANTOWER(int tx_io, int rx_io);
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
	int get_pm2_5(void);
	int get_pm10(void);
};

#endif
