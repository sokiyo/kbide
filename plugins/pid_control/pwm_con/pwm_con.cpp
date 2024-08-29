#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "driver/mcpwm.h"
//#include "soc/mcpwm_periph.h"
#include "pwm_con.h"
#include "esp_log.h"

//- Motor 
#define PWM0A_OUT GPIO_NUM_23   	//Set GPIO 23 as PWM0A (pwm pin)
#define PWM0B_OUT GPIO_NUM_26   	//Set GPIO 26 (OUT1) as PWM0B (direction pin)
#define MOTOR_STRT GPIO_NUM_27		//Set GPIO 27 (OUT2) as start/stop pin

#define MCPWM_UNIT 	MCPWM_UNIT_1


//-----------------------------------------------------------------------------

void init_gpio_output(gpio_num_t gpio, int val) {
	gpio_config_t io_conf;

	io_conf.intr_type = GPIO_INTR_DISABLE; // disable interrupt
	io_conf.mode = GPIO_MODE_OUTPUT; //set as output mode
	io_conf.pin_bit_mask = (1ULL << gpio); // bit mask of the pins that you want to set
	io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // disable pull-down mode
	//io_conf.pull_up_en = GPIO_PULLUP_DISABLE; // disable pull-up mode
	io_conf.pull_up_en = GPIO_PULLUP_ENABLE; // disable pull-up mode
	gpio_set_level(gpio, val); // load gpio value
	gpio_config(&io_conf);
}

PWM_CON::PWM_CON(int dev_addr) {

	//ESP_LOGI("PWM_CON", "dev_addr = %d", dev_addr);

	//motor_num = dev_addr;

}

void PWM_CON::init(void) {
    mcpwm_config_t pwm_config;

	esp_log_level_set("PWM_CON", ESP_LOG_VERBOSE);

	timer_num = MCPWM_TIMER_0;
	mcpwm_gpio_init(MCPWM_UNIT, MCPWM0A, PWM0A_OUT);
	mcpwm_gpio_init(MCPWM_UNIT, MCPWM0B, PWM0B_OUT);

	init_gpio_output(MOTOR_STRT,1);						// stop motor

    pwm_config.frequency = 20000;    					// frequency = 20kHz,
    pwm_config.cmpr_a = 0;    							// duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;   							// duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;			// active high
    mcpwm_init(MCPWM_UNIT, timer_num, &pwm_config);		//Configure above settings

	tickcnt = get_tickcnt();

	state = s_detect;
}

int PWM_CON::prop_count(void) {
	// not supported
	return 0;
}

bool PWM_CON::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool PWM_CON::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool PWM_CON::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool PWM_CON::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool PWM_CON::prop_write(int index, char *value) {
	// not supported
	return false;
}



void PWM_CON::process(Driver *drv) {
    //mcpwm_config_t pwm_config;

	switch (state) {
		case s_detect:
			//ESP_LOGI("PWM_CON", "s_detect");

			if (is_tickcnt_elapsed(tickcnt, 1000)) {
				//gpio_set_level(MOTOR_STRT, 1);

				error = false;
				initialized = true;

				state = s_idle;
			}

			break;

		case s_idle:
	
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

void PWM_CON::drive(uint8_t dir, float percent) {
    mcpwm_config_t pwm_config;

//	ESP_LOGI("PWM_CON", "direction %d speed %f", dir, percent);

	if (percent > 100) percent = 100;
	if (percent < 0) percent *= -1;

//	ESP_LOGI("PWM_CON", "direction %d speed %f", dir, percent);

	//- turn off motor for 10ms in order to eliminate back emf
	//gpio_set_level(MOTOR_STRT, 1);
	//tickcnt = get_tickcnt(); while (!is_tickcnt_elapsed(tickcnt, 10));
	gpio_set_level(MOTOR_STRT, 0);			// start motor
	if (dir==1) {	// counterclockwise
		mcpwm_set_signal_low(MCPWM_UNIT, timer_num, MCPWM_OPR_B);
	} else { 		// clockwise
		mcpwm_set_signal_high(MCPWM_UNIT, timer_num, MCPWM_OPR_B);
	}
	mcpwm_set_duty(MCPWM_UNIT, timer_num, MCPWM_OPR_A, percent);
	mcpwm_set_duty_type(MCPWM_UNIT, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_1); //MCPWM_DUTY_MODE_1 = Inverted

}

void PWM_CON::stop(void) {
    //mcpwm_set_signal_low(MCPWM_UNIT, timer_num, MCPWM_OPR_A);
    //mcpwm_set_signal_low(MCPWM_UNIT, timer_num, MCPWM_OPR_B);
	gpio_set_level(MOTOR_STRT, 1);
}
