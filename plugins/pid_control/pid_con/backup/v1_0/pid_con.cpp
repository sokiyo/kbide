// PID Control V1.0 (this version works well with speed control)
// developed by Dusadee Treeumnuk/ July 25, 2023


#include <stdio.h>
#include <string.h>
#include <math.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "pid_con.h"
#include "esp_log.h"


//-----------------------------------------------------------------------------

float fIntegralBound(float a, float lower, float upper) {

	//if ((a > upper) || (a < lower)) return 0;
	if (a > upper) return upper;
	if (a < lower) return lower;
	return a;
}

float fActuatorBound(float a) {
	if (a < -100) return -100;
	if (a > 100) return 100;
	return a;
}

//-----------------------------------------------------------------------------


PID_CON::PID_CON(int dev_addr) {


}

void PID_CON::init(void) {

	esp_log_level_set("PID_CON", ESP_LOG_VERBOSE);


	state = s_detect;
}

int PID_CON::prop_count(void) {
	// not supported
	return 0;
}

bool PID_CON::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool PID_CON::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool PID_CON::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool PID_CON::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool PID_CON::prop_write(int index, char *value) {
	// not supported
	return false;
}


void PID_CON::process(Driver *drv) {

	switch (state) {
		case s_detect:
			//ESP_LOGI("PID_CON", "s_detect");


			error = false;
			initialized = true;

			state = s_idle;

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

float PID_CON::run(float kp, float ki, float kd, float setpnt, float procv) {
	double pid_drv;
	double delT;
 
	//ESP_LOGI("PID_CON", "Kp = %f, Ki = %f, Kd = %f", kp, ki, kd);

/*  	
	kp = 0.2;			//0.2, 0.01, 0.001
	ki = 0.05;			//0.05, 0.05 0.005
	kd = 0.0; 			//0, 0, 0 
*/

	cur_ts = esp_timer_get_time();
	delT = (cur_ts - prv_ts)*0.000001;
	prv_ts = cur_ts;

	pid_cur_error = setpnt - procv;
	pid_integral += pid_cur_error * delT;		
	pid_derivative = (pid_cur_error - pid_prv_error) / delT;
	pid_drv = (kp*pid_cur_error) + (ki*pid_integral) + (kd*pid_derivative);
	// integral part ---------------------------------------------------------
	// if (fabs(pid_cur_error) <= 0.1) pid_integral = 0;			// trial
	// if (fabs(pid_cur_error) >= 2000) pid_integral = 0;			// trial
	// pid_integral = fIntegralBound(pid_integral, -3000, 3000);	// trial
	//------------------------------------------------------------------------

	pid_prv_error = pid_cur_error;
	pid_drv = fActuatorBound(pid_drv);

//	printf("setpoint %f, speed %f , error %f , integral %f , derivative %f , drv %f\n", setpnt, procv, pid_cur_error, pid_integral, pid_derivative, pid_drv);		// debug
	printf("setpoint %f, speed %f , error %f, drv %f\n", setpnt, procv, pid_cur_error, pid_drv);		// debug
//	printf("setpoint %f, speed %f\n", setpnt, procv);	
	//ESP_LOGI("PID_CON", "pid_drv = %f", pid_drv);

	return (float)pid_drv;
	//return 0.1;
}

