#ifndef __IPORT_H__
#define __IPORT_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "driver/ledc.h"

#define SERVO_DUTY_MIN 1638 // 0.5mS
#define SERVO_DUTY_MAX 8191 // 2.5mS

class iPORT : public Device {
	private:

		// PWM
		struct configState {
			uint8_t pin;
			uint8_t ledc_ch;
			struct {
				int min;
				int max;
				int current;
			} duty;
		} pwmConfigState[5];
		uint8_t nextPointPWMConfigState = 0;
		
		uint8_t getIndexFromPin(uint8_t pin, bool isServo = false) ;
		uint8_t getLEDCChannelFromPin(uint8_t pin) ;
		uint8_t setupLEDCFromPin(uint8_t pin, bool isServo = false) ;

		bool usbLastValue = false;

	public:
		// constructor
		iPORT(void);
		
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
		int digitalRead(int pin) ;
		void digitalWrite(int pin, int value) ;
		int analogRead(int pin) ;
		void analogWrite(int pin, int value) ;

		void usbWrite(int value) ;
		int usbRead() ;
		void usbToggle() ;
		void usbAnalogWrite(int value) ;
		
		// Servo
		void servoSetAngle(int pin, int angle) ;
		void servoCalibrate(int pin, float min, float max) ;
		
};

#endif
