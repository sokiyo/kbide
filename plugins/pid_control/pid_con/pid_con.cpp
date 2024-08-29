// PID Control V1.1 : for reaction wheel - based self balancing
// developed by Dusadee Treeumnuk/ July 25, 2023
// Note: version 1.0 works well with speed control


#include <stdio.h>
#include <string.h>
#include <math.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "pid_con.h"
#include "esp_log.h"

#define	ANGLE_FIXRATE	1.0			// degrees/s
#define ANGLE_FIXRATE_2	0.1			


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
	kp = 12.0;			//0.2, 0.01, 0.001
	ki = 0.001;			//0.05, 0.05 0.005
	kd = 2.5; 	 		//0, 0, 0 
*/

	cur_ts = esp_timer_get_time();
	delT = (cur_ts - prv_ts)*0.000001;
	prv_ts = cur_ts;

	// Angle fix rate ---------------------	// trial
	//setpnt = target_angle;
	//-------------------------------------

	pid_cur_error = setpnt - procv;

	// Dithering --------------------------
	float angle_inc = 0.0000;
	if (pid_cur_error < 0) target_angle -= angle_inc; else target_angle += angle_inc;
	//-------------------------------------

	pid_integral += pid_cur_error * delT;		

	// integral part ---------------------------------------------------------
	// if (fabs(pid_cur_error) <= 0.1) pid_integral = 0;			// trial
	// if (fabs(pid_cur_error) >= 2000) pid_integral = 0;			// trial
	pid_integral = fIntegralBound(pid_integral, -60, 60);			// trial 
	//------------------------------------------------------------------------

	pid_derivative = (pid_cur_error - pid_prv_error) / delT;
	pid_prv_error = pid_cur_error;
	pid_drv = (kp*pid_cur_error) + (ki*pid_integral) + (kd*pid_derivative);

	// Angle fix rate ---------------------	// trial
//	if (procv < target_angle) target_angle += ANGLE_FIXRATE * delT; else target_angle -= ANGLE_FIXRATE * delT;
	//-------------------------------------

	pid_drv = fActuatorBound(pid_drv);

	//printf("setpoint %f procv %f  error %f  integral %f  derivative %f  drv %f\n", setpnt, procv, pid_cur_error, pid_integral, pid_derivative, pid_drv);		// debug
	//printf("%s %f \n","proc",pid_cur_error);
	//printf("%s %f \n","phong",pid_integral);
//	printf("setpoint %f, procv %f , error %f, drv %f\n", setpnt, procv, pid_cur_error, pid_drv);		// debug
//	printf("setpoint %f, speed %f\n", setpnt, procv);	
	//ESP_LOGI("PID_CON", "pid_drv = %f", pid_drv);

	return (float)pid_drv;
	//return 0.1;
}

void PID_CON::ser_print(char *buf, double val) {
	printf("%s:%f,", buf, val);
}

void PID_CON::ser_print_1(double val) {
	printf("%f,", val);
}