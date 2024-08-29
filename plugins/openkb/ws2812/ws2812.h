#ifndef __WS2812_H__
#define __WS2812_H__

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_intr_alloc.h"
#include "esp_log.h"
#include "driver/rmt.h"
#include "kidbright32.h"
#include "driver.h"
#include "device.h"

static int KB_RMT_CH_NEXT = RMT_CHANNEL_0;

class WS2812 : public Device {
	private:
		uint8_t *colorBlock = NULL;
		int pin, length;
		rmt_config_t config;
		uint8_t brightness;
		uint8_t colorMode = 0; // 0 = GRB, 1 = RGB

		uint32_t Wheel(uint8_t WheelPos) ;
		uint32_t color(uint8_t r, uint8_t g, uint8_t b) ;

	public:
		// constructor
		WS2812(int pin) ;
		
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
		void init(int length, uint8_t mode = 0) ;
		void setColorMode(uint8_t mode) ;
		void setBrightness(double brightness) ;
		void setPixel(int n, uint32_t color) ;
		void setPixel(int n, uint8_t r, uint8_t g, uint8_t b) ;
		void fill(uint32_t color) ;
		void fill(uint8_t r, uint8_t g, uint8_t b) ;
		void show() ;
		void clear() ;

		void rainbow(uint32_t ms) ;
		void rainbowCycle(uint32_t ms) ;
		
};

#endif
