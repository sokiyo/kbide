#ifndef __PID_CON_H__
#define __PID_CON_H__

#include "driver.h"
#include "device.h"


class PID_CON : public Device {
	private:
		enum {
			s_detect, s_idle, s_error, s_wait
		} state;
		TickType_t tickcnt;
		int64_t prv_ts = 0;
		int64_t	cur_ts;

		// double pid_cur_error;
		// double pid_prv_error = 0.0;
		// double pid_integral = 0.0;
		// double pid_derivative = 0.0;
		// double target_angle = 0.0;

		float pid_cur_error;
		float pid_prv_error = 0.0;
		float pid_integral = 0.0;
		float pid_derivative = 0.0;
		float target_angle = 0.0;

	public:
		// constructor
		PID_CON(int dev_addr);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		float run(float kp, float ki, float kd, float setpnt, float procv);
		void ser_print(char *buf, double val);
		void ser_print_1(double val);
};

#endif
