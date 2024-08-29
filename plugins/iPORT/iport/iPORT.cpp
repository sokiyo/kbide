#ifndef __IPORT_CPP__
#define __IPORT_CPP__

#include "iPORT.h"

iPORT::iPORT(void) { }

void iPORT::init(void) {
	// Config Timer0 to use PWM
	ledc_timer_config_t timer_conf;
	timer_conf.duty_resolution = LEDC_TIMER_16_BIT;
	timer_conf.freq_hz = 500; // 500Hz
	timer_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
	timer_conf.timer_num = LEDC_TIMER_0;
	ledc_timer_config(&timer_conf);

	// Config Timer1 to use Servo
	ledc_timer_config_t timer_conf2;
	timer_conf2.duty_resolution = LEDC_TIMER_16_BIT;
	timer_conf2.freq_hz = 50; // 50Hz
	timer_conf2.speed_mode = LEDC_HIGH_SPEED_MODE;
	timer_conf2.timer_num = LEDC_TIMER_1;
	ledc_timer_config(&timer_conf2);

	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
}

int iPORT::prop_count(void) {
	// not supported
	return 0;
}

bool iPORT::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool iPORT::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool iPORT::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool iPORT::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool iPORT::prop_write(int index, char *value) {
	// not supported
	return false;
}

void iPORT::process(Driver *drv) { }

int iPORT::digitalRead(int pin) {
	gpio_set_direction(static_cast<gpio_num_t>(pin), GPIO_MODE_INPUT);

	return gpio_get_level(static_cast<gpio_num_t>(pin));
}

void iPORT::digitalWrite(int pin, int value) {
	gpio_set_direction(static_cast<gpio_num_t>(pin), GPIO_MODE_OUTPUT);
	gpio_set_level(static_cast<gpio_num_t>(pin), value);
}

int iPORT::analogRead(int pin) {
	// Pin to ADC1 channel
	adc1_channel_t adc1_ch;
	switch (pin) {
		case 32:
			adc1_ch = ADC1_CHANNEL_4;
			break;
		case 33:
			adc1_ch = ADC1_CHANNEL_5;
			break;
		case 34:
			adc1_ch = ADC1_CHANNEL_6;
			break;
		case 35:
			adc1_ch = ADC1_CHANNEL_7;
			break;
		default:
			adc1_ch = ADC1_CHANNEL_0;
			break;
		
	}

	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(adc1_ch, ADC_ATTEN_DB_11);

	return adc1_get_raw(adc1_ch);
}

// analog write, copy from PWM plugin
uint8_t iPORT::getIndexFromPin(uint8_t pin, bool isServo) {
	uint8_t index = getLEDCChannelFromPin(pin);
	if (index == 255) {
		index = setupLEDCFromPin(pin, isServo);
	}
	return index;
}

uint8_t iPORT::getLEDCChannelFromPin(uint8_t pin) {
	uint8_t index = 255;
	for (int i=0;i<nextPointPWMConfigState;i++) {
		if (pwmConfigState[i].pin == pin) {
			index = i;
			break;
		}
	}
	return index;
}

uint8_t iPORT::setupLEDCFromPin(uint8_t pin, bool isServo) {
	uint8_t index = nextPointPWMConfigState++;
	
	struct configState &config = pwmConfigState[index];

	config = {
		.pin = pin,
		.ledc_ch = index,
		.duty = {
			.min = SERVO_DUTY_MIN,
			.max = SERVO_DUTY_MAX
		}
	};
	
	ledc_channel_config_t ledc_conf;
	ledc_conf.channel = static_cast<ledc_channel_t>(config.ledc_ch);
	ledc_conf.duty = 0;
	ledc_conf.gpio_num   = config.pin;
	ledc_conf.intr_type  = LEDC_INTR_DISABLE;
	ledc_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
	ledc_conf.timer_sel  = !isServo ? LEDC_TIMER_0 : LEDC_TIMER_1;
	ledc_channel_config(&ledc_conf);
	
	return index;
}

void iPORT::analogWrite(int pin, int value) {
	if (value > 1023) value = 1023;
	
	uint8_t index = getIndexFromPin(pin);
	
	uint16_t realDuty = value * (double)0xFFFF / 1023.0;
	
	ledc_set_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(pwmConfigState[index].ledc_ch), realDuty);
	ledc_update_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(pwmConfigState[index].ledc_ch));
}

void iPORT::servoSetAngle(int pin, int angle) {
	angle = angle < 0 ? 0 : angle;
	angle = angle > 180 ? 180 : angle;
	
	int index = getIndexFromPin(pin, true); // isServo = true
	
	// Cal duty
	int min = pwmConfigState[index].duty.min;
	int max = pwmConfigState[index].duty.max;
	int duty = angle * (max - min) / 180.0 + min;

	ledc_set_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(pwmConfigState[index].ledc_ch), duty);
	ledc_update_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(pwmConfigState[index].ledc_ch));
}

void iPORT::servoCalibrate(int pin, float min, float max) {
	int index = getIndexFromPin(pin, true);
	pwmConfigState[index].duty.min = 0xFFFF * min / 20.0;
	pwmConfigState[index].duty.max = 0xFFFF * max / 20.0;
}

void iPORT::usbWrite(int value) {
	digitalWrite(25, !value);
	usbLastValue = value;
}

int iPORT::usbRead() {
	return usbLastValue;
}

void iPORT::usbToggle() {
	usbLastValue = !usbLastValue;
	digitalWrite(25, !usbLastValue);
}

void iPORT::usbAnalogWrite(int value) {
	analogWrite(25, 1023 - value);
	usbLastValue = value > 512;
}

#endif
