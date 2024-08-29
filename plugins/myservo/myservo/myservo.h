#ifndef __MYSERVO_H__
#define __MYSERVO_H__

/*
  DEV By IOXhop : www.ioxhop.com
  Sonthaya Nongnuch : fb.me/maxthai
*/

#include "driver.h"
#include "device.h"
#include "driver/uart.h"
#include "driver/ledc.h"
#include "kidbright32.h"

#define DUTY_MIN 1638 // 0.5mS
#define DUTY_MAX 8191 // 2.5mS

class myServo : public Device {
	private:		
		struct configState {
			uint8_t pin;
			struct {
				int min;
				int max;
				int current;
			} duty;
			uint8_t ledc_ch;
			bool used;
		} servoConfigState[5];
		uint8_t nextPointServoConfigState = 0;
		
		uint8_t getIndexFromPin(uint8_t pin) ;
		uint8_t getLEDCChannelFromPin(uint8_t pin) ;
		uint8_t setupLEDCFromPin(uint8_t pin) ;

	public:
		// constructor
		myServo() ;
		
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
		void setAngle(uint8_t pin, uint8_t angle) ;
		void calibrate(uint8_t pin, float min, float max) ;
		
};

#endif
