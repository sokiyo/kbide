/*
	PWM BDC v0.0 developed by Dusadee Treeumnuk, EDT/NECTEC
		- V0.0 (Oct 2, 2023) derived from L298N, just to make it more general
*/
#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "driver/mcpwm.h"
//#include "soc/mcpwm_periph.h"
#include "pwm_bdc.h"
#include "esp_log.h"

//- Motor Channel 1
#define PWM0A_OUT GPIO_NUM_18   	//Set GPIO 18 as PWM0A
#define PWM0B_OUT GPIO_NUM_19   	//Set GPIO 19 as PWM0B
//- Motor Channel 2
#define PWM1A_OUT GPIO_NUM_26   	//Set GPIO 26 as PWM1A
#define PWM1B_OUT GPIO_NUM_27   	//Set GPIO 27 as PWM1B

#define MCPWM_UNIT 	MCPWM_UNIT_1


//-----------------------------------------------------------------------------

PWM_BDC::PWM_BDC(int dev_addr) {

	//ESP_LOGI("PWM_BDC", "dev_addr = %d", dev_addr);

	motor_num = dev_addr;

}

void PWM_BDC::init(void) {
    mcpwm_config_t pwm_config;

	esp_log_level_set("PWM_BDC", ESP_LOG_VERBOSE);

	switch (motor_num) {
		case 1 : 
			timer_num = MCPWM_TIMER_0;
			mcpwm_gpio_init(MCPWM_UNIT, MCPWM0A, PWM0A_OUT);
			mcpwm_gpio_init(MCPWM_UNIT, MCPWM0B, PWM0B_OUT);
			break;
		case 2 :
			timer_num = MCPWM_TIMER_1;
			mcpwm_gpio_init(MCPWM_UNIT, MCPWM1A, PWM1A_OUT);
			mcpwm_gpio_init(MCPWM_UNIT, MCPWM1B, PWM1B_OUT);
			break;
	}


    pwm_config.frequency = 1000;    					//frequency = 1000Hz,
    pwm_config.cmpr_a = 0;    							//duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;   							//duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;			// active high
    mcpwm_init(MCPWM_UNIT, timer_num, &pwm_config);		//Configure above settings

	state = s_detect;
}

int PWM_BDC::prop_count(void) {
	// not supported
	return 0;
}

bool PWM_BDC::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool PWM_BDC::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool PWM_BDC::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool PWM_BDC::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool PWM_BDC::prop_write(int index, char *value) {
	// not supported
	return false;
}



void PWM_BDC::process(Driver *drv) {
    //mcpwm_config_t pwm_config;

	switch (state) {
		case s_detect:
			//ESP_LOGI("PWM_BDC", "s_detect");

			//state = s_idle;

			error = false;
			initialized = true;

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

void PWM_BDC::speed(uint8_t dir, int percent) {
    mcpwm_config_t pwm_config;

	//ESP_LOGI("PWM_BDC", "direction %d speed %d", dir, percent);

	if (percent > 100) percent = 100;
	if (percent < 0) percent *= -1;

	if (dir==1) {
		mcpwm_set_signal_low(MCPWM_UNIT, timer_num, MCPWM_OPR_B);
		mcpwm_set_duty(MCPWM_UNIT, timer_num, MCPWM_OPR_A, percent);
		mcpwm_set_duty_type(MCPWM_UNIT, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state

	} else {
		mcpwm_set_signal_low(MCPWM_UNIT, timer_num, MCPWM_OPR_A);
		mcpwm_set_duty(MCPWM_UNIT, timer_num, MCPWM_OPR_B, percent);
		mcpwm_set_duty_type(MCPWM_UNIT, timer_num, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state

	}

}

void PWM_BDC::stop(void) {
    mcpwm_set_signal_low(MCPWM_UNIT, timer_num, MCPWM_OPR_A);
    mcpwm_set_signal_low(MCPWM_UNIT, timer_num, MCPWM_OPR_B);
}
