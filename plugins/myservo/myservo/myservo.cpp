#ifndef __MYSERVO_CPP__
#define __MYSERVO_CPP__

#include "myservo.h"

/*
  DEV By IOXhop : www.ioxhop.com
  Sonthaya Nongnuch : fb.me/maxthai
*/

myServo::myServo() {
	this->nextPointServoConfigState = 0;
}

void myServo::init(void) {
	// Config Timer3
	ledc_timer_config_t timer_conf;
	timer_conf.duty_resolution = LEDC_TIMER_16_BIT;
	timer_conf.freq_hz = 50;
	timer_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
	timer_conf.timer_num = LEDC_TIMER_3;
	ledc_timer_config(&timer_conf);
	
	// set initialized flag
	this->initialized = true;
	// clear error flag
	this->error = false;
}

int myServo::prop_count(void) {
	// not supported
	return 0;
}

bool myServo::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool myServo::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool myServo::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool myServo::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool myServo::prop_write(int index, char *value) {
	// not supported
	return false;
}

void myServo::process(Driver *drv) {
	
}
// --------------------------------------

// Start here
// Method
uint8_t myServo::getIndexFromPin(uint8_t pin) {
	uint8_t index = getLEDCChannelFromPin(pin);
	if (index == 255) {
		index = setupLEDCFromPin(pin);
	}
	return index;
}

uint8_t myServo::getLEDCChannelFromPin(uint8_t pin) {
	uint8_t index = 255;
	for (int i=0;i<nextPointServoConfigState;i++) {
		if (servoConfigState[i].pin == pin) {
			index = i;
			break;
		}
	}
	return index;
}

uint8_t myServo::setupLEDCFromPin(uint8_t pin) {
	uint8_t index = nextPointServoConfigState;
	
	struct configState &config = servoConfigState[nextPointServoConfigState];
	config.pin = pin;
	config.duty.min = DUTY_MIN;
	config.duty.max = DUTY_MAX;
	config.duty.current = 0xFFFF;
	config.ledc_ch = 7 - nextPointServoConfigState;
	config.used = true;
	nextPointServoConfigState++;
	
	ledc_channel_config_t ledc_conf;
	ledc_conf.channel = static_cast<ledc_channel_t>(config.ledc_ch);
	ledc_conf.duty = config.duty.current;
	ledc_conf.gpio_num   = config.pin;
	ledc_conf.intr_type  = LEDC_INTR_DISABLE;
	ledc_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
	ledc_conf.timer_sel  = LEDC_TIMER_3;
	ledc_channel_config(&ledc_conf);
	
	return index;
}

void myServo::setAngle(uint8_t pin, uint8_t angle) {
	angle = angle < 0 ? 0 : angle;
	angle = angle > 180 ? 180 : angle;
	
	int index = getIndexFromPin(pin);
	
	bool invert = (pin == 26 || pin == 27) ? true : false;
	
	// Cal duty
	int duty = angle * (servoConfigState[index].duty.max - servoConfigState[index].duty.min) / 180.0 + servoConfigState[index].duty.min;
	duty = invert ? 0xFFFF - duty : duty;

	ledc_set_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(servoConfigState[index].ledc_ch), duty);
	ledc_update_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(servoConfigState[index].ledc_ch));
}

void myServo::calibrate(uint8_t pin, float min, float max) {
	int index = getIndexFromPin(pin);
	servoConfigState[index].duty.min = 0xFFFF * min / 20.0;
	servoConfigState[index].duty.max = 0xFFFF * max / 20.0;
}

#endif
