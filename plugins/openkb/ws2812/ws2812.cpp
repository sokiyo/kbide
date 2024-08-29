#ifndef __WS2812_CPP__
#define __WS2812_CPP__

#include "ws2812.h"

WS2812::WS2812(int pin) {
	this->pin = pin;
	
	// Set up RMT
	this->config.rmt_mode = RMT_MODE_TX;
	this->config.channel = (rmt_channel_t)KB_RMT_CH_NEXT;
	KB_RMT_CH_NEXT++;
	// this->config.gpio_num = (gpio_num_t)pin;
	this->config.mem_block_num = 1;
	this->config.tx_config.loop_en = 0;
	
	this->config.tx_config.idle_output_en = 1;
	// this->config.tx_config.idle_level = RMT_IDLE_LEVEL_HIGH;
	
	this->config.tx_config.carrier_en = 0;
	this->config.tx_config.carrier_duty_percent = 0;
	this->config.tx_config.carrier_freq_hz = 0;
	this->config.tx_config.carrier_level = RMT_CARRIER_LEVEL_LOW;
	
	this->config.clk_div = 1; // APB use 80MHz per 1 clock and 2 clock APB for 1 clock RMT so clk_div = 1 is 40MHz
	
	this->brightness = 50; // Set brightness to 50%
}

void WS2812::init(void) { 
	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
	
	// Enable log
	// esp_log_level_set("*", ESP_LOG_INFO); 
}

int WS2812::prop_count(void) {
	return 0;
}

bool WS2812::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool WS2812::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool WS2812::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool WS2812::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool WS2812::prop_write(int index, char *value) {
	// not supported
	return false;
}

void WS2812::process(Driver *drv) { }

void WS2812::init(int length, uint8_t mode) {
	this->length = length;
	
	// GPIO config
	gpio_pad_select_gpio((gpio_num_t)pin);
	gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT);
	
	// Create color buffer
	if (this->colorBlock) {
		free(this->colorBlock);
	}
	this->colorBlock = (uint8_t*)malloc(length * 3);
	memset(this->colorBlock, 0, length * 3);
	
	// Config RMT pin
	this->config.gpio_num = (gpio_num_t)pin;
	/* if ((pin == 26) || (pin == 27)) {
		this->config.tx_config.idle_level = RMT_IDLE_LEVEL_HIGH;
	} else {*/
		this->config.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
	//}
	
	// Setup RMT
	rmt_config(&this->config);
	rmt_driver_install(this->config.channel, 0, 0);
	rmt_set_source_clk(this->config.channel, RMT_BASECLK_APB); // Use clock from APB 80MHz
	
	this->setColorMode(mode);
	
	this->clear();
}

void WS2812::setColorMode(uint8_t mode) {
	if (mode > 1) mode = 1;
	
	this->colorMode = mode;
}

void WS2812::setBrightness(double brightness) {
	this->brightness = fmin(brightness, 100);
	this->brightness = fmax(brightness, 0);
	
	this->brightness = brightness;
}

void WS2812::setPixel(int n, uint32_t color) {
	if (n >= this->length) return;
	
	uint8_t r = (color>>16)&0xFF;
	uint8_t g = (color>>8)&0xFF;
	uint8_t b = color&0xFF;
	
	r = (float)r * (float)this->brightness / 100.0;
	g = (float)g * (float)this->brightness / 100.0;
	b = (float)b * (float)this->brightness / 100.0;
	
	int inx = n * 3;
	if (this->colorMode == 0) { // mode GRB
		this->colorBlock[inx + 0] = g;
		this->colorBlock[inx + 1] = r;
		this->colorBlock[inx + 2] = b;
	} else {
		this->colorBlock[inx + 0] = r;
		this->colorBlock[inx + 1] = g;
		this->colorBlock[inx + 2] = b;
	}
}

void WS2812::setPixel(int n, uint8_t r, uint8_t g, uint8_t b) {
	if (n >= this->length) return;
	
	r = (float)r * (float)this->brightness / 100.0;
	g = (float)g * (float)this->brightness / 100.0;
	b = (float)b * (float)this->brightness / 100.0;
	
	int inx = n * 3;
	if (this->colorMode == 0) { // mode GRB
		this->colorBlock[inx + 0] = g;
		this->colorBlock[inx + 1] = r;
		this->colorBlock[inx + 2] = b;
	} else {
		this->colorBlock[inx + 0] = r;
		this->colorBlock[inx + 1] = g;
		this->colorBlock[inx + 2] = b;
	}
}

void WS2812::fill(uint32_t color) {
	for (int i=0;i<this->length;i++) {
		this->setPixel(i, color);
	}
}

void WS2812::fill(uint8_t r, uint8_t g, uint8_t b) {
	for (int i=0;i<this->length;i++) {
		this->setPixel(i, r, g, b);
	}
}

void WS2812::show() {
	/* 1 / 80MHz = 0.0000000125 = 12.5nS per tick
	 * WS2812 want 1.25uS so 12.5nS * 100 = 1.25uS
	 * Use 100 tick to get 1.25uS
	 *
	 * ======== Timing from Datasheets ========
	 * The T0H want 0.35uS so 350nS / 12.5nS = 28 tick
	 * The T0L want 0.8uS so 800nS / 12.5nS = 64 tick
	 * 
	 * The T1H want 0.7uS so 700nS / 12.5nS = 56 tick
	 * The T1L want 0.6uS so 600nS / 12.5nS = 48 tick
	 * 
	 * ======== Timing from ESP32 Core for Arduino ========
	 * The T0H want 0.4uS so 400nS / 12.5nS = 32 tick
	 * The T0L want 0.8uS so 800nS / 12.5nS = 64 tick
	 * 
	 * The T1H want 0.8uS so 800nS / 12.5nS = 64 tick
	 * The T1L want 0.4uS so 400nS / 12.5nS = 32 tick
	 * 
	 */
	
	// RGB use 3 Byte so 1 LED Use 24 bits
	uint32_t items_size = this->length * 24;
	rmt_item32_t items[items_size];
	rmt_item32_t bit0;
	rmt_item32_t bit1;
	/*
	// Timing from Datasheets
	if ((pin == 26) || (pin == 27)) {
		bit0 = {{{ 28, 0, 64, 1 }}};  //Logical 0
		bit1 = {{{ 56, 0, 48, 1 }}};  //Logical 1
	} else {
		bit0 = {{{ 28, 1, 64, 0 }}};  //Logical 0
		bit1 = {{{ 56, 1, 48, 0 }}};  //Logical 1
	}
	*/
	
	// Timing from ESP32 Core for Arduino
	/*
	if ((pin == 26) || (pin == 27)) {
		bit0 = {{{ 32, 0, 64, 1 }}};  //Logical 0
		bit1 = {{{ 64, 0, 32, 1 }}};  //Logical 1
	} else {*/
		bit0 = {{{ 32, 1, 64, 0 }}};  //Logical 0
		bit1 = {{{ 64, 1, 32, 0 }}};  //Logical 1
	//}
	
	uint32_t nex_item = 0;
	for (int inx=0;inx<(this->length * 3);inx++) {
		for (int i=7;i>=0;i--) {
			if (this->colorBlock[inx]&(1<<i)) {
				items[nex_item] = bit1;
			} else {
				items[nex_item] = bit0;
			}
			nex_item++;
		}
	}
	rmt_write_items(this->config.channel, items, items_size, true);
	
	rmt_wait_tx_done(this->config.channel, portMAX_DELAY);
}

void WS2812::clear() {
	memset(this->colorBlock, 0, this->length * 3);
	
	this->show();
}

uint32_t WS2812::Wheel(uint8_t WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return this->color(255 - WheelPos * 3, 0, WheelPos * 3);
	}

	if (WheelPos < 170) {
		WheelPos -= 85;
		return this->color(0, WheelPos * 3, 255 - WheelPos * 3);
	}

	WheelPos -= 170;
	return this->color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void WS2812::rainbow(uint32_t ms) {
	for (uint16_t j = 0; j < 256; j++) {
		for (uint16_t i = 0; i < this->length; i++) {
			this->setPixel(i, Wheel((i + j) & 255));
		}
		this->show();
		vTaskDelay(ms / portTICK_RATE_MS);
	}
}

void WS2812::rainbowCycle(uint32_t ms) {
	for (uint16_t m = 0; m < 256 * 5; m++) {  // 5 cycles of all colors on wheel
		for (uint16_t k = 0; k < this->length; k++) {
			this->setPixel(k, Wheel(((k * 256 / this->length) + m) & 255));
		}
		this->show();
		vTaskDelay(ms / portTICK_RATE_MS);
	}
}

uint32_t WS2812::color(uint8_t r, uint8_t g, uint8_t b) {
	return ((uint32_t) r << 16) | ((uint32_t) g << 8) | ((uint32_t) b);
}

#endif
