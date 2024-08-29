/*
	Encoder written by Dusadee Treeumnuk
	V0.2 June 30, 2023
		- add a lowpass filter for estimating a speed (rpm)
		- clear direction when speed is read
	V0.3 October 2, 2023
		- add an input for the number of pulses per round	
*/
#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "quad_encoder.h"

#include "esp_log.h"


#define ESP_INTR_FLAG_DEFAULT 	0
//#define NUM_TRIG				100


static void IRAM_ATTR quad_encoder_gpio_isr_handler(void* arg) {
	QUAD_ENCODER *enc = (QUAD_ENCODER *)arg;

	enc->cur_ts = esp_timer_get_time();
	enc->clk_period = enc->cur_ts - enc->prv_ts;
	enc->prv_ts = enc->cur_ts;

	//---------------------------
	
	int b = gpio_get_level(enc->b_gpio);
	// check direction
	if (b) {	// ccw
		enc->direction = -1;
		enc->encoder_position--;
	} else {	// cw
		enc->direction = 1;
		enc->encoder_position++;
	}
}

QUAD_ENCODER::QUAD_ENCODER(int phase_a, int phase_b, int pulses) {
	a_gpio = (gpio_num_t)phase_a;
	b_gpio = (gpio_num_t)phase_b;
	if (pulses > 0) pulses_per_round = pulses; else pulses_per_round = 1;
}

void QUAD_ENCODER::init(void) {
	gpio_config_t io_conf;

	//printf("-----> A = %d, B = %d, Pulses =%d\n", (int)a_gpio, (int)b_gpio, pulses_per_round);
	
	esp_log_level_set("QUAD_ENCODER", ESP_LOG_VERBOSE);

	// Configure Phase A input
	io_conf.intr_type = GPIO_INTR_POSEDGE; // rising edge interrupt (GPIO_INTR_DISABLE | GPIO_INTR_POSEDGE | GPIO_INTR_NEGEDGE | GPIO_INTR_ANYEDGE | GPIO_INTR_LOW_LEVEL | GPIO_INTR_HIGH_LEVEL)
	io_conf.mode = GPIO_MODE_INPUT; // set as input mode
	io_conf.pin_bit_mask = (1ULL << a_gpio); // pin bit mask
	io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // disable pull-down mode
	io_conf.pull_up_en = GPIO_PULLUP_DISABLE; // enable pull-up mode
	gpio_config(&io_conf);

	// Configure Phase B input
	io_conf.intr_type = GPIO_INTR_DISABLE; // disable interrupt
	io_conf.mode = GPIO_MODE_INPUT; // set GPIO_MODE_OUTPUT as output mode or GPIO_MODE_INPUT_OUTPUT if want to read back
	io_conf.pin_bit_mask = (1ULL << b_gpio); // pin bit mask
	io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // disable pull-down mode
	io_conf.pull_up_en = GPIO_PULLUP_DISABLE; // disable pull-up mode
	gpio_config(&io_conf);

	// install gpio isr service
	gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
	// hook isr handler for specific gpio pin
	gpio_isr_handler_add(a_gpio, quad_encoder_gpio_isr_handler, (void *)this);

	tickcnt = get_tickcnt();

	// check pins
	if (a_gpio == b_gpio) state = s_idle; else state = s_detect;
}

int QUAD_ENCODER::prop_count(void) {
	return 0;
}

bool QUAD_ENCODER::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool QUAD_ENCODER::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool QUAD_ENCODER::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool QUAD_ENCODER::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool QUAD_ENCODER::prop_write(int index, char *value) {
	// not supported
	return false;
}

void QUAD_ENCODER::process(Driver *drv) {
	double res;
	int i;

	switch (state) {
		case s_detect:

			// clear error flag
			error = false;
			// set initialized flag
			initialized = true;

			tickcnt = get_tickcnt();
			//state = s_check;

			break;

		case s_check:

			break;

		case s_idle:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;

			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;

			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

		case s_wait:
			// delay 1000ms before retry detect
			if (is_tickcnt_elapsed(tickcnt, 1000)) {
				state = s_detect;
			}
			break;
	}
}

int64_t QUAD_ENCODER::get_position(void) {
	ESP_LOGI("QUAD_ENCODER", "get_position %lld", encoder_position);
	return encoder_position;
}

int8_t QUAD_ENCODER::get_direction(void) {
	ESP_LOGI("QUAD_ENCODER", "get_direction %d", direction);
	return direction;
}

float QUAD_ENCODER::get_speed(void) {	// rpm
	double	rpm, rpm_f;
	
	if (!initialized) return 0;

	//printf("------------> clk_period = %lld\n",clk_period);

	if (direction == 0) rpm = 0; else rpm = ((1000000 * 60.0) / clk_period / pulses_per_round)*direction;
	direction = 0; 			// clear direction to clear speed
	// Low-pass filter 25Hz cutoff freq 
	rpm_fil = 0.854*rpm_fil + 0.0728*rpm + 0.0728*rpm_prv;
	rpm_prv = rpm;

	//ESP_LOGI("QUAD_ENCODER", "get_speed %f ----------- %f", rpm, rpm_fil);
	
	return (float)rpm_fil;
	//return (float)rpm;
	//return abs(speed);
}
