#ifndef __atgm336h_H__
#define __atgm336h_H__

#include "driver.h"
#include "device.h"

// #define atgm336h_POLLING_MS         1000

class atgm336h : public Device
{
public:
	/// bool read(DATA& data);

	// constructor
	atgm336h(int tx_io, int rx_io);
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
	double get_lat(void);
	double get_lng(void);
	int get_year(void);
	int get_month(void);
	int get_day(void);
	int get_hour(void);
	int get_minute(void);
	int get_second(void);

	/// mmm-->
	static const uint16_t SINGLE_RESPONSE_TIME = 1000;
	static const uint16_t TOTAL_RESPONSE_TIME = 1000 * 10;
	static const uint16_t STEADY_RESPONSE_TIME = 1000 * 30;

	static const uint16_t BAUD_RATE = 9600;

private:
	TickType_t tickcnt, polling_tickcnt;
	int tx_pin;
	int rx_pin;
	double latitude;
	double longitude;
	int year, month, day, hour, minute, second;
};

#endif
