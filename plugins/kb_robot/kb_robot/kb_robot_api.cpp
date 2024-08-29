#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "kb_robot_api.h"
#include "esp_log.h"

KB_ROBOT::KB_ROBOT(int bus_ch, int dev_addr) {
	polling_ms = KB_ROBOT_POLLING_MS;
	channel = bus_ch;
	address = 0;
}

void KB_ROBOT::init(void) {

	initialized = true;
	error = false;

	for (int i = 0; i < 4; i++)
	{
		// servo_tmp[i] = servo[i];
		// motor_tmp[i] = motor[i];
		// mac_v_tmp[i] = mac_v[i];
		servo[i] = 0;
		motor[i] = 0;
		mac_v[i] = 0;
	}

}

int KB_ROBOT::prop_count(void) {
	return 0;
}

bool KB_ROBOT::prop_name(int index, char* name) {
	// not supported
	return false;
}

bool KB_ROBOT::prop_unit(int index, char* unit) {
	// not supported
	return false;
}

bool KB_ROBOT::prop_attr(int index, char* attr) {
	// not supported
	return false;
}

bool KB_ROBOT::prop_read(int index, char* value) {
	// not supported
	return false;
}

bool KB_ROBOT::prop_write(int index, char* value) {
	// not supported
	return false;
}


void KB_ROBOT::process(Driver* drv) {
	i2c_p = (I2CDev*)drv;


	if (lib_setup == false) {
		lib_setup = true;

		robot_mode = 0;

		float prescaleval = ((27000000 / (400 * 4096.0)) + 0.5) - 1;
		if (prescaleval < PCA9685_PRESCALE_MIN)
			prescaleval = PCA9685_PRESCALE_MIN;
		if (prescaleval > PCA9685_PRESCALE_MAX)
			prescaleval = PCA9685_PRESCALE_MAX;

		uint8_t prescale = (uint8_t)prescaleval;

		uint8_t oldmode = read8(PCA9685_MODE1);
		oldmode = 0;
		uint8_t newmode = (oldmode & ~MODE1_RESTART) | MODE1_SLEEP; // sleep
		write8(PCA9685_MODE1, newmode);                             // go to sleep

		write8(PCA9685_PRESCALE, prescale); // set the prescaler
		write8(PCA9685_MODE1, oldmode);

		tickcnt = get_tickcnt();
		while (!is_tickcnt_elapsed(tickcnt, 5))
		{
			asm("nop");
		}

		// This sets the MODE1 register to turn on auto increment.
		write8(PCA9685_MODE1, oldmode | MODE1_RESTART | MODE1_AI);

		for (int i = 0; i < 4; i++)
		{
			setMotor(i, 0);
			setPWM(11 + i, 0, 0);
		}

		for (int i = 0; i < 4; i++)
		{

			servo[i] = 0;
			motor[i] = 0;
			mac_v[i] = 0;

			servo_tmp[i] = servo[i];
			motor_tmp[i] = motor[i];
			mac_v_tmp[i] = mac_v[i];
		}

	}




	for (int i = 0; i < 4; i++)
	{
		if (servo[i] != servo_tmp[i])
		{
			servo_tmp[i] = servo[i];
			if ((int)servo_tmp[i] * 1.638f < 0)  servo_tmp[i] = 0;
			if ((int)servo_tmp[i] * 1.638f > 4095)  servo_tmp[i] = 4095 / 1.638f;
			setPWM(11 + i, 0, (float)servo_tmp[i] * 1.638f);
		}
	}

	if (robot_mode == 0) {

		for (int i = 0; i < 4; i++)
		{
			if (motor[i] != motor_tmp[i])
			{
				motor_tmp[i] = motor[i];
				setMotor(i, motor[i]);
			}
		}
	}
	else {

		if (mac_v[0] != mac_v_tmp[0] || mac_v[1] != mac_v_tmp[1] || mac_v[2] != mac_v_tmp[2])
		{
			for (int i = 0; i < 3; i++)
			{
				mac_v_tmp[i] = mac_v[i];
			}

			float speed_x = mac_v_tmp[1];
			float speed_y = mac_v_tmp[0];

			float speed_omega = mac_v_tmp[2];

			motor[0] = speed_y - speed_x - speed_omega;
			motor[1] = speed_y + speed_x - speed_omega;
			motor[2] = speed_y - speed_x + speed_omega;
			motor[3] = speed_y + speed_x + speed_omega;

			for (int i = 0; i < 4; i++)
			{
				setMotor(i, motor[i]);
			}
		}

	}

	// if (is_update2 == true) {

	// 	for (int i = 0; i < 4; i++)
	// 	{
	// 		mac_v_tmp[i] = mac_v[i];
	// 	}

	// }


	if (wdt_cnt >= 0) {
		wdt_cnt--;
		if (wdt_cnt == 0) {
			for (int i = 0; i < 4; i++)
			{
				servo[i] = 0;
				motor[i] = 0;
				mac_v[i] = 0;
			}
		}
	}

	if (robot_mode == 1) {

	}

}

void KB_ROBOT::set_servo(int16_t m1, int16_t m2, int16_t m3, int16_t m4) {

	motor[0] = m1;
	motor[1] = m2;
	motor[2] = m3;
	motor[3] = m4;
	robot_mode = 0;
	wdt_feed();
}

void KB_ROBOT::set_motor(int16_t s1, int16_t s2, int16_t s3, int16_t s4) {
	servo[0] = s1;
	servo[1] = s2;
	servo[2] = s3;
	servo[3] = s4;
	robot_mode = 0;
	wdt_feed();
}

void KB_ROBOT::set_machanum(int16_t v1, int16_t v2, int16_t v3) {
	robot_mode = 1;
	mac_v[0] = v1;
	mac_v[0] = v1;
	mac_v[0] = v1;
	robot_mode = 1;
	wdt_feed();
}


void KB_ROBOT::wdt_feed() {
	wdt_cnt = 50;
}

void KB_ROBOT::setMotor(uint8_t num, float val) {

	if (abs(val)<=5) val = 0; 
	if (val > 100) val = 100;
	if (val < -100) val = -100;

	if (val == 0) {
		setPWM(num * 3 + 0, 0, 4096);
		setPWM(num * 3 + 1, 0, 4096);
		setPWM(num * 3 + 2, 0, 4096);
	}
	else if (val > 0)
	{
		setPWM(num * 3 + 0, 4096, 0);
		setPWM(num * 3 + 1, 0, 4096);
		setPWM(num * 3 + 2, 0, 40.95f * abs(val));
	}
	else if (val < 0)
	{
		setPWM(num * 3 + 0, 0, 4096);
		setPWM(num * 3 + 1, 4096, 0);
		setPWM(num * 3 + 2, 0, 40.95f * abs(val));
	}

}


void KB_ROBOT::setPWM(uint8_t num, uint16_t on, uint16_t off) {
	if (i2c_p == NULL)
		return;

	uint8_t tmp[5];
	tmp[0] = PCA9685_LED0_ON_L + 4 * num;
	tmp[1] = on;
	tmp[2] = on >> 8;
	tmp[3] = off;
	tmp[4] = off >> 8;

	i2c_p->write(0, kb_robot_addr, tmp, 5);
}

void KB_ROBOT::spit_data(char* text) {

	sscanf(text, "%d.%d.%d.%d.%d.%d", (int*)&data[0], (int*)&data[1], (int*)&data[2], (int*)&data[3], (int*)&data[4], (int*)&data[5]);
	ESP_LOGI("\nspit_data", "Received from: %02d,  %02d,  %02d,  %02d,  %02d,  %02d", data[0], data[1], data[2], data[3], data[4], data[5]);
}

/******************* Low level I2C interface */
uint8_t KB_ROBOT::read8(uint8_t addr) {
	uint8_t val = -1;
	uint8_t tmp[2];

	tmp[0] = addr;
	tmp[1] = 0;

	if (i2c_p->write(0, kb_robot_addr, tmp, 1) != ESP_OK) {
		return -1;
	}
	if (i2c_p->read(0, kb_robot_addr, NULL, 0, tmp, 1) == ESP_OK) {
		val = tmp[0];
	}
	return val;
}

void KB_ROBOT::write8(uint8_t addr, uint8_t d) {
	uint8_t tmp[2];
	tmp[0] = addr;
	tmp[1] = d;
	i2c_p->write(0, kb_robot_addr, tmp, 2);
}