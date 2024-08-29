#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"

// quadrature encoder
class ENCODER : public Device {
	private:
		enum {
			s_detect, s_check, s_idle, s_error, s_wait
		} state;
		int64_t	prv_pos = 0;
	public:
		TickType_t tickcnt;
		gpio_num_t a_gpio, b_gpio;
		volatile int64_t encoder_position = 0;
		volatile int64_t prv_ts = 0;
		volatile int64_t cur_ts;
		volatile int64_t clk_period;			// uS
		volatile int8_t direction = 0;			// 0=stop, 1=cc, -1=ccw
		double rpm_prv = 0;
		double rpm_fil = 0;

		// float speed, prv_speed;
		// float acc;		
			// constructor
		ENCODER(int phase_a, int phase_b);
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
		int64_t get_position(void);
		int8_t get_direction(void);
		float get_speed(void);
};

#endif
