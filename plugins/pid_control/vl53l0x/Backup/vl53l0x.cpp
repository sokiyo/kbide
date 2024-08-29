/*
	VL53L0X Plugin for KidBright developed by Dusadee Treeumnuk EDT/NECTEC/NSTDA 
	Released: May 9, 2023
	Derived from Pololu, ESP32, and ST VL53L0X libraries 
*/
#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "vl53l0x.h"
#include <math.h>
#include "esp_log.h"

#define millis() (esp_timer_get_time()/1000LL)
// Record the current time to check an upcoming timeout against
#define startTimeout() (timeout_start_ms = millis())	
// Check if timeout is enabled (set to nonzero value) and has expired
#define checkTimeoutExpired() (io_timeout > 0 && ((uint16_t)(millis() - timeout_start_ms)) > io_timeout)
#define calcMacroPeriod(vcsel_period_pclks) ((((uint32_t)2304 * (vcsel_period_pclks) * 1655) + 500) / 1000)
#define decodeVcselPeriod(reg_val)      (((reg_val) + 1) << 1)


VL53L0X::VL53L0X(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = VL53L0X_POLLING_MS;
}

void i2c_setClock(uint32_t clock) {
	// Reset speed of I2C
	i2c_config_t conf;

	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = CHAIN_SDA_GPIO;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_io_num = CHAIN_SCL_GPIO;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = clock;

	i2c_param_config(I2C_NUM_1, &conf);
}

void VL53L0X::init(void) {

	//i2c_setClock(100E3);
	
	esp_log_level_set("VL53L0X", ESP_LOG_VERBOSE);
	//state = s_test;
	state = s_detect;

	tickcnt = get_tickcnt();
}

int VL53L0X::prop_count(void) {
	return 0;
}

bool VL53L0X::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool VL53L0X::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool VL53L0X::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool VL53L0X::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool VL53L0X::prop_write(int index, char *value) {
	// not supported
	return false;
}

//-----------------------------------------------------------------------------

void VL53L0X::write1byte(uint8_t c, uint8_t d) {
	uint8_t cmd[2] = {c,d};
	i2c->write(channel, address, cmd, 2);
}

void VL53L0X::write2bytes(uint8_t c, uint16_t d) {
	uint8_t cmd[3] = {c, (uint8_t)(d >> 8), (uint8_t)(d)};
	i2c->write(channel, address, cmd, 3);
}

void VL53L0X::write4bytes(uint8_t c, uint32_t d) {
	uint8_t cmd[5] = {c, (uint8_t)(d >> 24), (uint8_t)(d >> 16), (uint8_t)(d >> 8), (uint8_t)(d)};
	i2c->write(channel, address, cmd, 5);
}

bool VL53L0X::writemultibytes (uint8_t reg, uint8_t *src, uint8_t cnt) {
	uint8_t cmd[50];

	if (cnt<50) { 
		cmd[0]=reg;
		for (int i=0;i<cnt;i++) cmd[i+1]=src[i];
		i2c->write(channel, address, cmd, cnt+1);
	} else return false;
	return true;
}

uint8_t VL53L0X::read1byte(uint8_t c) {
	uint8_t d;
	//i2c->write(channel, address,&c,1);
	i2c->read(channel, address, &c, 1, &d, 1);
	return d;
}

uint16_t VL53L0X::read2bytes(uint8_t c) {
	uint8_t d[2];
	uint16_t dd;

	i2c->read(channel, address, &c, 1, d, 2);
	dd = (uint16_t)((d[0]<<8) + d[1]);
	return dd;
}

void VL53L0X::readmultibytes (uint8_t c, uint8_t *dst, uint8_t cnt) {
	i2c->read(channel, address, &c, 1, dst, cnt);
}

bool VL53L0X::setSignalRateLimit(float limit_Mcps) {
	if (limit_Mcps < 0 || limit_Mcps > 511.99) { return false; }

	// Q9.7 fixed point format (9 integer bits, 7 fractional bits)
	write2bytes(FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, limit_Mcps * (1 << 7));
	return true;
}

bool VL53L0X::getSpadInfo(uint8_t * count, bool * type_is_aperture) {
	uint8_t tmp;

	write1byte(0x80, 0x01);
	write1byte(0xFF, 0x01);
	write1byte(0x00, 0x00);

	write1byte(0xFF, 0x06);
	write1byte(0x83, read1byte(0x83) | 0x04);
	write1byte(0xFF, 0x07);
	write1byte(0x81, 0x01);

	write1byte(0x80, 0x01);

	write1byte(0x94, 0x6b);
	write1byte(0x83, 0x00);
	startTimeout();
	while (read1byte(0x83) == 0x00) {
		if (checkTimeoutExpired()) { return false; }
	}
	write1byte(0x83, 0x01);
	tmp = read1byte(0x92);

	*count = tmp & 0x7f;
	*type_is_aperture = (tmp >> 7) & 0x01;

	write1byte(0x81, 0x00);
	write1byte(0xFF, 0x06);
	write1byte(0x83, read1byte(0x83)  & ~0x04);
	write1byte(0xFF, 0x01);
	write1byte(0x00, 0x01);

	write1byte(0xFF, 0x00);
	write1byte(0x80, 0x00);

	return true;
}

void VL53L0X::getSequenceStepEnables(SequenceStepEnables * enables) {
	uint8_t sequence_config = read1byte(SYSTEM_SEQUENCE_CONFIG);

	enables->tcc          = (sequence_config >> 4) & 0x1;
	enables->dss          = (sequence_config >> 3) & 0x1;
	enables->msrc         = (sequence_config >> 2) & 0x1;
	enables->pre_range    = (sequence_config >> 6) & 0x1;
	enables->final_range  = (sequence_config >> 7) & 0x1;
}

uint8_t VL53L0X::getVcselPulsePeriod(vcselPeriodType type) {
  if (type == VcselPeriodPreRange) {
    return decodeVcselPeriod(read1byte(PRE_RANGE_CONFIG_VCSEL_PERIOD));
  } else if (type == VcselPeriodFinalRange) {
    return decodeVcselPeriod(read1byte(FINAL_RANGE_CONFIG_VCSEL_PERIOD));
  } else { return 255; }
}

uint32_t VL53L0X::timeoutMclksToMicroseconds(uint16_t timeout_period_mclks, uint8_t vcsel_period_pclks) {
  uint32_t macro_period_ns = calcMacroPeriod(vcsel_period_pclks);

  return ((timeout_period_mclks * macro_period_ns) + 500) / 1000;
}

uint32_t VL53L0X::timeoutMicrosecondsToMclks(uint32_t timeout_period_us, uint8_t vcsel_period_pclks) {
  uint32_t macro_period_ns = calcMacroPeriod(vcsel_period_pclks);

  return (((timeout_period_us * 1000) + (macro_period_ns / 2)) / macro_period_ns);
}

uint16_t VL53L0X::decodeTimeout(uint16_t reg_val) {
  // format: "(LSByte * 2^MSByte) + 1"
  return (uint16_t)((reg_val & 0x00FF) << (uint16_t)((reg_val & 0xFF00) >> 8)) + 1;
}

void VL53L0X::getSequenceStepTimeouts(SequenceStepEnables const * enables, SequenceStepTimeouts * timeouts) {
	timeouts->pre_range_vcsel_period_pclks = getVcselPulsePeriod(VcselPeriodPreRange);

	timeouts->msrc_dss_tcc_mclks = read1byte(MSRC_CONFIG_TIMEOUT_MACROP) + 1;
	timeouts->msrc_dss_tcc_us = timeoutMclksToMicroseconds(timeouts->msrc_dss_tcc_mclks, timeouts->pre_range_vcsel_period_pclks);

	timeouts->pre_range_mclks = decodeTimeout(read2bytes(PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI));
	timeouts->pre_range_us = timeoutMclksToMicroseconds(timeouts->pre_range_mclks, timeouts->pre_range_vcsel_period_pclks);

	timeouts->final_range_vcsel_period_pclks = getVcselPulsePeriod(VcselPeriodFinalRange);

	timeouts->final_range_mclks = decodeTimeout(read2bytes(FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI));

	if (enables->pre_range) {
		timeouts->final_range_mclks -= timeouts->pre_range_mclks;
	}

	timeouts->final_range_us = timeoutMclksToMicroseconds(timeouts->final_range_mclks, timeouts->final_range_vcsel_period_pclks);
}

uint16_t VL53L0X::encodeTimeout(uint32_t timeout_mclks) {
  // format: "(LSByte * 2^MSByte) + 1"

  uint32_t ls_byte = 0;
  uint16_t ms_byte = 0;

  if (timeout_mclks > 0) {
    ls_byte = timeout_mclks - 1;

    while ((ls_byte & 0xFFFFFF00) > 0) {
      ls_byte >>= 1;
      ms_byte++;
    }

    return (ms_byte << 8) | (ls_byte & 0xFF);
  } else { return 0; }
}

bool VL53L0X::setMeasurementTimingBudget(uint32_t budget_us) {
	SequenceStepEnables enables;
	SequenceStepTimeouts timeouts;

	uint16_t const StartOverhead     = 1910;
	uint16_t const EndOverhead        = 960;
	uint16_t const MsrcOverhead       = 660;
	uint16_t const TccOverhead        = 590;
	uint16_t const DssOverhead        = 690;
	uint16_t const PreRangeOverhead   = 660;
	uint16_t const FinalRangeOverhead = 550;

	uint32_t used_budget_us = StartOverhead + EndOverhead;

	getSequenceStepEnables(&enables);
	getSequenceStepTimeouts(&enables, &timeouts);

	if (enables.tcc) {
		used_budget_us += (timeouts.msrc_dss_tcc_us + TccOverhead);
	}

	if (enables.dss) {
		used_budget_us += 2 * (timeouts.msrc_dss_tcc_us + DssOverhead);
	} else if (enables.msrc) {
		used_budget_us += (timeouts.msrc_dss_tcc_us + MsrcOverhead);
	}

	if (enables.pre_range) {
		used_budget_us += (timeouts.pre_range_us + PreRangeOverhead);
	}

	if (enables.final_range) {
		used_budget_us += FinalRangeOverhead;

		// "Note that the final range timeout is determined by the timing
		// budget and the sum of all other timeouts within the sequence.
		// If there is no room for the final range timeout, then an error
		// will be set. Otherwise the remaining time will be applied to
		// the final range."

		if (used_budget_us > budget_us) {
			// "Requested timeout too big."
			return false;
		}

		uint32_t final_range_timeout_us = budget_us - used_budget_us;

		// set_sequence_step_timeout() begin
		// (SequenceStepId == VL53L0X_SEQUENCESTEP_FINAL_RANGE)

		// "For the final range timeout, the pre-range timeout
		//  must be added. To do this both final and pre-range
		//  timeouts must be expressed in macro periods MClks
		//  because they have different vcsel periods."

		uint32_t final_range_timeout_mclks =
		timeoutMicrosecondsToMclks(final_range_timeout_us, timeouts.final_range_vcsel_period_pclks);

		if (enables.pre_range) {
			final_range_timeout_mclks += timeouts.pre_range_mclks;
		}

		write2bytes(FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI,
		encodeTimeout(final_range_timeout_mclks));

		// set_sequence_step_timeout() end

		measurement_timing_budget_us = budget_us; // store for internal reuse
	}
	return true;
}

uint32_t VL53L0X::getMeasurementTimingBudget(void) {
	SequenceStepEnables enables;
	SequenceStepTimeouts timeouts;

	uint16_t const StartOverhead     = 1910;
	uint16_t const EndOverhead        = 960;
	uint16_t const MsrcOverhead       = 660;
	uint16_t const TccOverhead        = 590;
	uint16_t const DssOverhead        = 690;
	uint16_t const PreRangeOverhead   = 660;
	uint16_t const FinalRangeOverhead = 550;

	// "Start and end overhead times always present"
	uint32_t budget_us = StartOverhead + EndOverhead;

	getSequenceStepEnables(&enables);
	getSequenceStepTimeouts(&enables, &timeouts);

	if (enables.tcc) {
		budget_us += (timeouts.msrc_dss_tcc_us + TccOverhead);
	}

	if (enables.dss) {
		budget_us += 2 * (timeouts.msrc_dss_tcc_us + DssOverhead);
	}
	else if (enables.msrc) {
		budget_us += (timeouts.msrc_dss_tcc_us + MsrcOverhead);
	}

	if (enables.pre_range) {
		budget_us += (timeouts.pre_range_us + PreRangeOverhead);
	}

	if (enables.final_range) {
		budget_us += (timeouts.final_range_us + FinalRangeOverhead);
	}

	measurement_timing_budget_us = budget_us; // store for internal reuse
	return budget_us;
}

bool VL53L0X::performSingleRefCalibration(uint8_t vhv_init_byte) {
  write1byte(SYSRANGE_START, 0x01 | vhv_init_byte); // VL53L0X_REG_SYSRANGE_MODE_START_STOP

  startTimeout();
  while ((read1byte(RESULT_INTERRUPT_STATUS) & 0x07) == 0) {
    if (checkTimeoutExpired()) { return false; }
  }

  write1byte(SYSTEM_INTERRUPT_CLEAR, 0x01);

  write1byte(SYSRANGE_START, 0x00);

  return true;
}

bool VL53L0X::device_init(void) {
	// check model ID register (value specified in datasheet)

	//ESP_LOGI("VL53L0X", "device_init IDENTIFICATION *****");

	// uint8_t er = read1byte(IDENTIFICATION_MODEL_ID);
	// ESP_LOGI("VL53L0X", "device_init IDENTIFICATION = %d *****", er);
	// printf("device_init IDENTIFICATION = %d *****\n\n", er);
	// //gpio_set_level(IOT_LED_GPIO, 0);
	// return false;

	if (uint8_t er = read1byte(IDENTIFICATION_MODEL_ID) != 0xEE) { 
		ESP_LOGI("VL53L0X", "device_init IDENTIFICATION = %d *****", er);

		//gpio_set_level(IOT_LED_GPIO, 0);

		return false; 
	}

		//return false;

	//gpio_set_level(IOT_LED_GPIO, 0);

	// VL53L0X_DataInit() begin ****************

	// sensor uses 1V8 mode for I/O by default; switch to 2V8 mode if necessary
	// if (io_2v8) {
	// 	write1byte(VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV,
	// 	read1byte(VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV) | 0x01); // set bit 0
	// }

	// "Set I2C standard mode"
	write1byte(0x88, 0x00);

	write1byte(0x80, 0x01);
	write1byte(0xFF, 0x01);
	write1byte(0x00, 0x00);
	stop_variable = read1byte(0x91);
	write1byte(0x00, 0x01);
	write1byte(0xFF, 0x00);
	write1byte(0x80, 0x00);

	// disable SIGNAL_RATE_MSRC (bit 1) and SIGNAL_RATE_PRE_RANGE (bit 4) limit checks
	write1byte(MSRC_CONFIG_CONTROL, read1byte(MSRC_CONFIG_CONTROL) | 0x12);

	// set final range signal rate limit to 0.25 MCPS (million counts per second)
	setSignalRateLimit(0.25);

	write1byte(SYSTEM_SEQUENCE_CONFIG, 0xFF);

	// VL53L0X_DataInit() end *******************

	// VL53L0X_StaticInit() begin ***************

	uint8_t spad_count;
	bool spad_type_is_aperture;
	if (!getSpadInfo(&spad_count, &spad_type_is_aperture)) { 
		ESP_LOGI("VL53L0X", "getSpadInfo fail!");
		printf("getSpadInfo fail!\r\n");

		//gpio_set_level(IOT_LED_GPIO, 0);

		return false; 
	}

	//gpio_set_level(IOT_LED_GPIO, 0);

	// The SPAD map (RefGoodSpadMap) is read by VL53L0X_get_info_from_device() in
	// the API, but the same data seems to be more easily readable from
	// GLOBAL_CONFIG_SPAD_ENABLES_REF_0 through _6, so read it from there
	uint8_t ref_spad_map[6];
	readmultibytes(GLOBAL_CONFIG_SPAD_ENABLES_REF_0, ref_spad_map, 6);

	// -- VL53L0X_set_reference_spads() begin (assume NVM values are valid)

	write1byte(0xFF, 0x01);
	write1byte(DYNAMIC_SPAD_REF_EN_START_OFFSET, 0x00);
	write1byte(DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C);
	write1byte(0xFF, 0x00);
	write1byte(GLOBAL_CONFIG_REF_EN_START_SELECT, 0xB4);

	uint8_t first_spad_to_enable = spad_type_is_aperture ? 12 : 0; // 12 is the first aperture spad
	uint8_t spads_enabled = 0;

	for (uint8_t i = 0; i < 48; i++) {
		if (i < first_spad_to_enable || spads_enabled == spad_count) {
			// This bit is lower than the first one that should be enabled, or
			// (reference_spad_count) bits have already been enabled, so zero this bit
			ref_spad_map[i / 8] &= ~(1 << (i % 8));
		} else if ((ref_spad_map[i / 8] >> (i % 8)) & 0x1) {
			spads_enabled++;
		}
	}

	writemultibytes(GLOBAL_CONFIG_SPAD_ENABLES_REF_0, ref_spad_map, 6);

	// -- VL53L0X_set_reference_spads() end

	// -- VL53L0X_load_tuning_settings() begin
	// DefaultTuningSettings from vl53l0x_tuning.h

	write1byte(0xFF, 0x01);
	write1byte(0x00, 0x00);

	write1byte(0xFF, 0x00);
	write1byte(0x09, 0x00);
	write1byte(0x10, 0x00);
	write1byte(0x11, 0x00);

	write1byte(0x24, 0x01);
	write1byte(0x25, 0xFF);
	write1byte(0x75, 0x00);

	write1byte(0xFF, 0x01);
	write1byte(0x4E, 0x2C);
	write1byte(0x48, 0x00);
	write1byte(0x30, 0x20);

	write1byte(0xFF, 0x00);
	write1byte(0x30, 0x09);
	write1byte(0x54, 0x00);
	write1byte(0x31, 0x04);
	write1byte(0x32, 0x03);
	write1byte(0x40, 0x83);
	write1byte(0x46, 0x25);
	write1byte(0x60, 0x00);
	write1byte(0x27, 0x00);
	write1byte(0x50, 0x06);
	write1byte(0x51, 0x00);
	write1byte(0x52, 0x96);
	write1byte(0x56, 0x08);
	write1byte(0x57, 0x30);
	write1byte(0x61, 0x00);
	write1byte(0x62, 0x00);
	write1byte(0x64, 0x00);
	write1byte(0x65, 0x00);
	write1byte(0x66, 0xA0);

	write1byte(0xFF, 0x01);
	write1byte(0x22, 0x32);
	write1byte(0x47, 0x14);
	write1byte(0x49, 0xFF);
	write1byte(0x4A, 0x00);

	write1byte(0xFF, 0x00);
	write1byte(0x7A, 0x0A);
	write1byte(0x7B, 0x00);
	write1byte(0x78, 0x21);

	write1byte(0xFF, 0x01);
	write1byte(0x23, 0x34);
	write1byte(0x42, 0x00);
	write1byte(0x44, 0xFF);
	write1byte(0x45, 0x26);
	write1byte(0x46, 0x05);
	write1byte(0x40, 0x40);
	write1byte(0x0E, 0x06);
	write1byte(0x20, 0x1A);
	write1byte(0x43, 0x40);

	write1byte(0xFF, 0x00);
	write1byte(0x34, 0x03);
	write1byte(0x35, 0x44);

	write1byte(0xFF, 0x01);
	write1byte(0x31, 0x04);
	write1byte(0x4B, 0x09);
	write1byte(0x4C, 0x05);
	write1byte(0x4D, 0x04);

	write1byte(0xFF, 0x00);
	write1byte(0x44, 0x00);
	write1byte(0x45, 0x20);
	write1byte(0x47, 0x08);
	write1byte(0x48, 0x28);
	write1byte(0x67, 0x00);
	write1byte(0x70, 0x04);
	write1byte(0x71, 0x01);
	write1byte(0x72, 0xFE);
	write1byte(0x76, 0x00);
	write1byte(0x77, 0x00);

	write1byte(0xFF, 0x01);
	write1byte(0x0D, 0x01);

	write1byte(0xFF, 0x00);
	write1byte(0x80, 0x01);
	write1byte(0x01, 0xF8);

	write1byte(0xFF, 0x01);
	write1byte(0x8E, 0x01);
	write1byte(0x00, 0x01);
	write1byte(0xFF, 0x00);
	write1byte(0x80, 0x00);

	// -- VL53L0X_load_tuning_settings() end

	// "Set interrupt config to new sample ready"
	// -- VL53L0X_SetGpioConfig() begin

	write1byte(SYSTEM_INTERRUPT_CONFIG_GPIO, 0x04);
	write1byte(GPIO_HV_MUX_ACTIVE_HIGH, read1byte(GPIO_HV_MUX_ACTIVE_HIGH) & ~0x10); // active low
	write1byte(SYSTEM_INTERRUPT_CLEAR, 0x01);

	// -- VL53L0X_SetGpioConfig() end

	measurement_timing_budget_us = getMeasurementTimingBudget();

	// "Disable MSRC and TCC by default"
	// MSRC = Minimum Signal Rate Check
	// TCC = Target CentreCheck
	// -- VL53L0X_SetSequenceStepEnable() begin

	write1byte(SYSTEM_SEQUENCE_CONFIG, 0xE8);

	// -- VL53L0X_SetSequenceStepEnable() end

	// "Recalculate timing budget"
	setMeasurementTimingBudget(measurement_timing_budget_us);

	// VL53L0X_StaticInit() end

	// VL53L0X_PerformRefCalibration() begin (VL53L0X_perform_ref_calibration())

	// -- VL53L0X_perform_vhv_calibration() begin

	write1byte(SYSTEM_SEQUENCE_CONFIG, 0x01);
	if (!performSingleRefCalibration(0x40)) { 
		ESP_LOGI("VL53L0X", "performSingleRefCalibration fail!");
		printf("performSingleRefCalibration fail!\n\n");

		//gpio_set_level(IOT_LED_GPIO, 0);
		return false; 
	}

	//gpio_set_level(IOT_LED_GPIO, 0);

	// -- VL53L0X_perform_vhv_calibration() end

	// -- VL53L0X_perform_phase_calibration() begin

	write1byte(SYSTEM_SEQUENCE_CONFIG, 0x02);
	if (!performSingleRefCalibration(0x00)) { return false; }

	// -- VL53L0X_perform_phase_calibration() end

	// "restore the previous Sequence Config"
	write1byte(SYSTEM_SEQUENCE_CONFIG, 0xE8);

	// VL53L0X_PerformRefCalibration() end

	return true;
}

void VL53L0X::startContinuous(uint32_t period_ms) {
	write1byte(0x80, 0x01);
	write1byte(0xFF, 0x01);
	write1byte(0x00, 0x00);
	write1byte(0x91, stop_variable);
	write1byte(0x00, 0x01);
	write1byte(0xFF, 0x00);
	write1byte(0x80, 0x00);

	if (period_ms != 0) {
		// continuous timed mode

		// VL53L0X_SetInterMeasurementPeriodMilliSeconds() begin

		uint16_t osc_calibrate_val = read2bytes(OSC_CALIBRATE_VAL);

		if (osc_calibrate_val != 0) {
			period_ms *= osc_calibrate_val;
		}

		write4bytes(SYSTEM_INTERMEASUREMENT_PERIOD, period_ms);

		// VL53L0X_SetInterMeasurementPeriodMilliSeconds() end

		write1byte(SYSRANGE_START, 0x04); // VL53L0X_REG_SYSRANGE_MODE_TIMED
	}
	else {
		// continuous back-to-back mode
		write1byte(SYSRANGE_START, 0x02); // VL53L0X_REG_SYSRANGE_MODE_BACKTOBACK
	}
}

// Stop continuous measurements
// based on VL53L0X_StopMeasurement()
void VL53L0X::stopContinuous(void) {
	write1byte(SYSRANGE_START, 0x01); // VL53L0X_REG_SYSRANGE_MODE_SINGLESHOT

	write1byte(0xFF, 0x01);
	write1byte(0x00, 0x00);
	write1byte(0x91, 0x00);
	write1byte(0x00, 0x01);
	write1byte(0xFF, 0x00);
}

// Returns a range reading in millimeters when continuous mode is active
// (readRangeSingleMillimeters() also calls this function after starting a
// single-shot range measurement)
uint16_t VL53L0X::readRangeContinuousMillimeters(void) {
	startTimeout();
	while ((read1byte(RESULT_INTERRUPT_STATUS) & 0x07) == 0) {
		if (checkTimeoutExpired()) {
			did_timeout = true;
			return 65535;
		}
	}

	// assumptions: Linearity Corrective Gain is 1000 (default);
	// fractional ranging is not enabled
	uint16_t range = read2bytes(RESULT_RANGE_STATUS + 10);

	write1byte(SYSTEM_INTERRUPT_CLEAR, 0x01);

	return range;
}


//-----------------------------------------------------------------------------

void VL53L0X::process(Driver *drv) {
	i2c = (I2CDev *)drv;

	switch (state) {
		case s_test:
			// if (!is_tickcnt_elapsed(tickcnt, 50)) break; 
			// tickcnt = get_tickcnt();

			//write1byte(0x88, 0x00);
			//read1byte(0x91);
			//read1byte(0x83);

			// uint8_t ref_spad_map[6];
			// readmultibytes(GLOBAL_CONFIG_SPAD_ENABLES_REF_0, ref_spad_map, 6);
			// writemultibytes(GLOBAL_CONFIG_SPAD_ENABLES_REF_0, ref_spad_map, 6);

			//read1byte(RESULT_INTERRUPT_STATUS);
			//uint16_t osc_calibrate_val; read2bytes(OSC_CALIBRATE_VAL);
			write4bytes(SYSTEM_INTERMEASUREMENT_PERIOD, 0x55FF0080);

			break;

		case s_detect:
			//ESP_LOGI("VL53L0X", "s_detect");

			// stamp polling tickcnt
			polling_tickcnt = get_tickcnt();

			//ESP_LOGI("VL53L0X", "s_detect channel = %d address = %d", channel, address);

			// int er;
			// er = i2c->detect(channel, address);
			// ESP_LOGI("VL53L0X", "s_detect error = %d, ESP_OK = %d", er, ESP_OK);

			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {	
				ESP_LOGI("VL53L0X", "s_detect ESP_OK *****");

				//gpio_set_level(IOT_LED_GPIO, 0);

				// if (device_init()) {

				// 	//ESP_LOGI("VL53L0X", "s_detect device_init successful");
				// 	//gpio_set_level(IOT_LED_GPIO, 0);

				// 	// get current tickcnt
				// 	tickcnt = get_tickcnt();

				// 	state = s_start;
				// } else {

				// 	//ESP_LOGI("VL53L0X", "s_detect device_init fail!!");
				// 	//gpio_set_level(IOT_LED_GPIO, 0);
					
				// 	state = s_error;
				// }

				tickcnt = get_tickcnt();
				state = s_start;

			} else {
				state = s_error;
			}

			break;

		case s_start:
			// if (!is_tickcnt_elapsed(tickcnt, 10)) break; 
			// tickcnt = get_tickcnt();
			if (device_init()) {
				gpio_set_level(IOT_LED_GPIO, 0);
			}

			//state = s_idle;

			// start measurement
			startContinuous(10);
			// clear error flag
			error = false;
			initialized = true;

			state = s_measure;


			break;

		case s_measure:

			distance = (float)readRangeContinuousMillimeters();

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
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;

	}
}


float VL53L0X::get_distance(uint8_t unit) {

	//ESP_LOGI("VL53L0X", "get_distance %d = %f", unit, distance);

	switch (unit) {
		case 0 : break;
		case 1 : distance = distance * 0.1; break;
		case 2 : distance = (distance * 10)/2.54; break;
	}

	return distance;
}
