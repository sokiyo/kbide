#ifndef __HX711_H__
#define __HX711_H__
#include <driver/gpio.h>
#include "driver.h"
#include "device.h"

class HX711 : public Device
{
private:
	enum
	{
		s_init,
		s_read,
		s_wait,
		s_error,
		s_aver
	} state;

	typedef enum
	{
		HX711_GAIN_A_128 = 0,
		HX711_GAIN_B_32,
		HX711_GAIN_A_64
	} hx711_gain_t;

	struct hx711_t
	{
		gpio_num_t dout;
		gpio_num_t pd_sck;
		hx711_gain_t gain;
	};

	hx711_t dev1;
	uint32_t get_time_ms();
	uint32_t read_raw(gpio_num_t dout, gpio_num_t pd_sck, hx711_gain_t gain);

public:
	double raw_weight;
	double SCALE = 1;
	double average = 0;
	double m = 0;
	int cout = 0;
	int OFFSET = 0;
	int32_t store[10];

	TickType_t tickcnt;
	// constructor
	HX711(void);
	HX711(gpio_num_t dout, gpio_num_t pd_sck);
	// override
	void init(void);
	void process(Driver *drv);
	int prop_count(void);
	bool prop_name(int index, char *name);
	bool prop_unit(int index, char *unit);
	bool prop_attr(int index, char *attr);
	bool prop_read(int index, char *value);
	bool prop_write(int index, char *value);

	int32_t get_raw_weight();
	double get_units();
	void set_scale(double scale = 1.f);
	void set_offset(int offset);
	void tare();
	void calibrate();

	esp_err_t hx711_init(hx711_t *dev);
	esp_err_t hx711_power_down(hx711_t *dev, bool down);
	esp_err_t hx711_set_gain(hx711_t *dev, hx711_gain_t gain);
	esp_err_t hx711_is_ready(hx711_t *dev, bool *ready);
	esp_err_t hx711_wait(hx711_t *dev, size_t timeout_ms);
	esp_err_t hx711_read_data(hx711_t *dev, int32_t *data);
};
#endif