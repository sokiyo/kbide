#ifndef __BLDC_H__
#define __BLDC_H__

#include "driver.h"
#include "device.h"

class BLDC : public Device
{
private:
	enum
	{
		s_detect,
		s_idle
	} state;
	TickType_t tickcnt;
	int tx_pin;
	int rx_pin;
	int error_count;
	int error_clear_count;
	int retry_count;

	uint8_t *command(const uint8_t *cmd);

public:
	// constructor
	BLDC(void);
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
	void forward(void);
	void backward(void);
	void left(void);
	void right(void);
	void start(void);
	void stop(void);
	int getvelocity(void);
};

#endif