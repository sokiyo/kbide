#ifndef __BIGSTREAM_H__
#define __BIGSTREAM_H__

#include "driver.h"
#include "device.h"
#include "esp_log.h"

#include "esp_http_client.h"

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"

class BIGSTREAM : public Device
{
private:
	char value[1][100];

public:
	// constructor
	BIGSTREAM();
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
	void set(uint8_t n, char *value);
	void set(uint8_t n, double value);
	void set(uint8_t n, int value);
	void set(uint8_t n, bool value);

	bool send(char *url, char *data);
	bool sendSensor(char *host, char *type, double val);
	bool sendLocation(char *host, double lat, double lng);
};

#endif
