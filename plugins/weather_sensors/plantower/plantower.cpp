#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "plantower.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"

#define PLANTOWER_UART_NUM UART_NUM_2
#define PLANTOWER_UART_BAUDRATE 9600
#define PLANTOWER_TX_BUF_SIZE 128
#define PLANTOWER_RX_BUF_SIZE 128

#define PLANTOWER_PWR_CTRL GPIO_NUM_23

#define PLANTOWER_TX_BUF_SIZE 1024
#define PLANTOWER_RX_BUF_SIZE 1024

const uint8_t plantower_passive_mode[] = {0x42, 0x4d, 0xe1, 0x00, 0x00, 0x01, 0x70};
const uint8_t plantower_read[] = {0x42, 0x4d, 0xe2, 0x00, 0x00, 0x01, 0x71};

#define __DEBUG__
// #undef __DEBUG__

#ifdef __DEBUG__
#include "esp_log.h"
static const char *TAG = "plantower";
#endif

PLANTOWER::PLANTOWER(int tx_io, int rx_io)
{
	tx_pin = tx_io;
	// tx_pin = GPIO_NUM_18;
	rx_pin = rx_io;
	// rx_pin = GPIO_NUM_19;
	polling_ms = PLANTOWER_POLLING_MS;
}

void PLANTOWER::init(void)
{
	gpio_config_t io_conf;

#ifdef __DEBUG__
	esp_log_level_set(TAG, ESP_LOG_VERBOSE);
#endif

	pm2_5 = 0;
	pm10 = 0;

	// // outputs init
	// io_conf.intr_type = GPIO_INTR_DISABLE; // disable interrupt
	// io_conf.mode = GPIO_MODE_OUTPUT;	   // set as output mode
	// // io_conf.pin_bit_mask = (1ULL << PLANTOWER_PWR_CTRL); // pin bit mask
	// io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // disable pull-down mode
	// io_conf.pull_up_en = GPIO_PULLUP_DISABLE;	  // disable pull-up mode
	// // gpio_set_level(PLANTOWER_PWR_CTRL, 1);				 // active low
	// gpio_config(&io_conf);

	// uart init
	uart_config_t uart_config = {
		.baud_rate = PLANTOWER_UART_BAUDRATE,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
		.rx_flow_ctrl_thresh = 0,
		.use_ref_tick = true};

	// uart config
	uart_param_config(PLANTOWER_UART_NUM, &uart_config);
	// set uart pins
	uart_set_pin(PLANTOWER_UART_NUM, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	// inverse tx polarity (open-drain output)
	uart_set_line_inverse(PLANTOWER_UART_NUM, UART_INVERSE_TXD);
	// install uart driver
	uart_driver_install(PLANTOWER_UART_NUM, (PLANTOWER_RX_BUF_SIZE * 2), (PLANTOWER_TX_BUF_SIZE * 2), 0, NULL, 0);

	state = s_detect;
}

int PLANTOWER::prop_count(void)
{
	return 2;
}

bool PLANTOWER::prop_name(int index, char *name)
{
	if (index == 0)
	{
		snprintf(name, DEVICE_PROP_NAME_LEN_MAX, "%s", "pm2.5");
		return true;
	}
	else if (index == 1)
	{
		snprintf(name, DEVICE_PROP_NAME_LEN_MAX, "%s", "pm10");
		return true;
	}

	// not supported
	return false;
}

bool PLANTOWER::prop_unit(int index, char *unit)
{
	if ((index == 0) || (index == 1))
	{
		snprintf(unit, DEVICE_PROP_UNIT_LEN_MAX, "%sg/m%s", "\xc2\xb5", "\xc2\xb3");
		return true;
	}

	// not supported
	return false;
}

bool PLANTOWER::prop_attr(int index, char *attr)
{
	if ((index == 0) || (index == 1))
	{
		get_attr_str(attr, PROP_ATTR_READ_FLAG | PROP_ATTR_TYPE_NUMBER_FLAG); // read only, number
		return true;
	}

	// not supported
	return false;
}

bool PLANTOWER::prop_read(int index, char *value)
{
	if (index == 0)
	{
		snprintf(value, DEVICE_PROP_VALUE_LEN_MAX, "%d", pm2_5);
		return true;
	}
	else if (index == 1)
	{
		snprintf(value, DEVICE_PROP_VALUE_LEN_MAX, "%d", pm10);
		return true;
	}

	// not supported
	return false;
}

bool PLANTOWER::prop_write(int index, char *value)
{
	// not supported
	return false;
}

bool PLANTOWER::command(const uint8_t *cmd)
{
	uint8_t buf[8];
	bool ret = false;
	int len;

#ifdef __DEBUG__
	ESP_LOGI(TAG, "MODE TX: %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X", cmd[0], cmd[1], cmd[2], cmd[3], cmd[4], cmd[5], cmd[6]);
#endif

	uart_write_bytes(PLANTOWER_UART_NUM, (const char *)cmd, 7);
	if ((len = (uart_read_bytes(PLANTOWER_UART_NUM, (uint8_t *)buf, 8, (100 / portTICK_RATE_MS)))) == 8)
	{

#ifdef __DEBUG__
		ESP_LOGI(TAG, "MODE RX: %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
#endif

		if ((buf[0] == 0x42) && (buf[1] == 0x4d) && (buf[2] == 0x00) && (buf[3] == 0x04) && (buf[4] == 0xe1) && (buf[5] == 0x00) && (buf[6] == 0x01) && (buf[7] == 0x74))
		{
			ret = true;
		}
		// ret = true;
	}
	else
	{

#ifdef __DEBUG__
		ESP_LOGI(TAG, "MODE %s", "timeout!");
#endif
	}

	// flush uart rx buffer
	// uart_flush(PLANTOWER_UART_NUM);
	return ret;
}

bool PLANTOWER::read(int *pm2_5_val, int *pm10_val)
{
	const uint8_t *cmd = plantower_read;
	uint8_t buf[32], *ptr;
	int len, i;
	uint chksum;
	char str[110], temp_str[4];

#ifdef __DEBUG__
	ESP_LOGI(TAG, "READ TX: %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X", cmd[0], cmd[1], cmd[2], cmd[3], cmd[4], cmd[5], cmd[6]);
#endif

	// flush uart rx buffer
	uart_flush(PLANTOWER_UART_NUM);

	uart_write_bytes(PLANTOWER_UART_NUM, (const char *)cmd, 7);
	if ((len = uart_read_bytes(PLANTOWER_UART_NUM, (uint8_t *)buf, 32, (200 / portTICK_RATE_MS))) == 32)
	{

		strcpy(str, "READ RX: ");
		for (i = 0; i < len; i++)
		{
			if (i == 0)
			{
				snprintf(temp_str, 4, "%2.2X", buf[i]);
			}
			else
			{
				snprintf(temp_str, 4, " %2.2X", buf[i]);
			}
			strcat(str, temp_str);
		}

#ifdef __DEBUG__
		ESP_LOGI(TAG, "%s", str);
#endif
		chksum = 0;
		for (i = 0; i < len - 2; i++)
		{
			chksum += buf[i];
		}

		if (chksum == ((int)(buf[30] << 8) | buf[31]))
		{
			*pm2_5_val = (buf[6] << 8) | buf[7];
			*pm10_val = (buf[8] << 8) | buf[9];
			return true;
		}
	}

	return false;
}

void PLANTOWER::process(Driver *drv)
{
	switch (state)
	{
	case s_detect:

#ifdef __DEBUG__
		ESP_LOGI(TAG, "%s", "power off");
#endif

		// set sensor power to off state
		gpio_set_level(PLANTOWER_PWR_CTRL, 1); // active low
		// get current tickcnt
		tickcnt = get_tickcnt();
		state = s_power_on;
		break;

	case s_power_on:
		if (is_tickcnt_elapsed(tickcnt, 1000))
		{

#ifdef __DEBUG__
			ESP_LOGI(TAG, "%s", "power on");
#endif

			// set sensor power to on state
			gpio_set_level(PLANTOWER_PWR_CTRL, 0); // active low
			// get current tickcnt
			tickcnt = get_tickcnt();
			state = s_change_passive_mode;
		}
		break;
	case s_change_passive_mode:
		if (command(plantower_passive_mode))
		{
			// clear error flag
			error = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			state = s_read;
		}
		else
		{
			state = s_error;
		}
		break;

	case s_read:
		if (is_tickcnt_elapsed(tickcnt, polling_ms))
		{
			if (read(&pm2_5, &pm10))
			{

#ifdef __DEBUG__
				ESP_LOGI(TAG, "pm2.5 = %d, pm10 = %d", pm2_5, pm10);
#endif

				// read once
				initialized = true;
				// get current tickcnt
				tickcnt = get_tickcnt();
			}
			else
			{

#ifdef __DEBUG__
				ESP_LOGI(TAG, "%s", "sensor error!");
#endif

				state = s_error;
			}
		}
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
		if (is_tickcnt_elapsed(tickcnt, 1000))
		{
			// flush uart rx buffer
			uart_flush(PLANTOWER_UART_NUM);
			state = s_detect;
		}
		break;

	case s_idle:
		break;
	}
}

int PLANTOWER::get_pm2_5(void)
{
	return pm2_5;
}

int PLANTOWER::get_pm10(void)
{
	return pm10;
}