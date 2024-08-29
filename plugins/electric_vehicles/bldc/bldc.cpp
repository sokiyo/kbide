#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "bldc.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"

#define BLDC_UART_NUM UART_NUM_2
#define BLDC_UART_BAUDRATE 115200
#define BLDC_TX_BUF_SIZE 128
#define BLDC_RX_BUF_SIZE 128

#define BLDC_PWR_CTRL GPIO_NUM_23

#define BLDC_ACK 0xa5
#define BLDC_NACK 0x96

const uint8_t bldc_start[] = {"AE1\nBE1\nCE1\nDE1\n"};
const uint8_t bldc_stop[] = {"A0\nB0\nC0\nD0\n"};
const uint8_t bldc_forward[] = {"A-50\nB50\nC-50\nD50\n"};
const uint8_t bldc_backward[] = {"A50\nB-50\nC50\nD-50\n"};
const uint8_t bldc_left[] = {"A50\nB50\nC-50\nD-50\n"};
const uint8_t bldc_right[] = {"A-50\nB-50\nC50\nD50\n"};

const uint8_t bldc_FR[] = {"A-50\nB0\nC0\nD50\n"};
const uint8_t bldc_BR[] = {"A50\nB0\nC0\nD-50\n"};
const uint8_t bldc_FL[] = {"A0\nB50\nC-50\nD0\n"};
const uint8_t bldc_BR[] = {"A0\nB-50\nC50\nD0\n"};

const uint8_t bldc_getveloctiy[] = {"G\n"};

static uint8_t buf[12];
#define __DEBUG__
// #undef __DEBUG__

#ifdef __DEBUG__
#include "esp_log.h"
static const char *TAG = "bldc";
#endif

BLDC::BLDC(void)
{
	// Fix Communication Port
	tx_pin = OUT1_GPIO;
	rx_pin = IN1_GPIO;
}

void BLDC::init(void)
{
	// gpio_config_t io_conf;
	error_count = 0;
	error_clear_count = 0;

	// uart init
	uart_config_t uart_config = {
		.baud_rate = BLDC_UART_BAUDRATE,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
		.rx_flow_ctrl_thresh = 0,
		.use_ref_tick = true};

	// uart config
	uart_param_config(BLDC_UART_NUM, &uart_config);
	// set uart pins
	uart_set_pin(BLDC_UART_NUM, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	// install uart driver
	uart_driver_install(BLDC_UART_NUM, (BLDC_RX_BUF_SIZE * 2), (BLDC_TX_BUF_SIZE * 2), 0, NULL, 0);

	state = s_detect;
}

int BLDC::prop_count(void)
{
	return 0;
}

bool BLDC::prop_name(int index, char *name)
{
	// not supported
	return false;
}

bool BLDC::prop_unit(int index, char *unit)
{

	// not supported
	return false;
}

bool BLDC::prop_attr(int index, char *attr)
{
	// not supported
	return false;
}

bool BLDC::prop_read(int index, char *value)
{
	// not supported
	return false;
}

bool BLDC::prop_write(int index, char *value)
{
	// not supported
	return false;
}

uint8_t *BLDC::command(const uint8_t *cmd)
{
	uint8_t *p, buff_size;

	bool ret = false;

	uart_write_bytes(BLDC_UART_NUM, (const char *)cmd, strlen((const char *)cmd));
	ESP_LOGI("BLDC", "TX Drive : %s", cmd);
	if ((uart_read_bytes(BLDC_UART_NUM, (uint8_t *)buf, 12, (100 / portTICK_RATE_MS))) > 0) // Timeout 100ms
	{
		buff_size = 1;
		for (p = buf; *p != 0x0a; p++)
		{
			buff_size++;
		}
		// ESP_LOGI("BLDC", "RX Drive : %s",buf);
		// ESP_LOGI(TAG, "RX: %s", buf);
		// uart_write_bytes(BLDC_UART_NUM, (const char *)buf, buff_size);	//For Debug
	}
	else
	{
	}

	// flush uart rx buffer
	uart_flush(BLDC_UART_NUM);
	return buf;
}

void BLDC::process(Driver *drv)
{
	switch (state)
	{
	case s_detect:
		// clear error flag
		error = false;
		// set initialized flag
		initialized = true;

		state = s_idle;
		break;

	case s_idle:
		//
		break;
	}
}

void BLDC::forward(void)
{
	uint8_t *receivebyte;
	char cast[12];

	receivebyte = command(bldc_forward);
	ESP_LOGI("BLDC", "RX Drive : %s", buf);

	// snprintf(cast, "%x", buf);

	// return atof((char *)buf);

	// command(bldc_forward);
	// return 2.12;
}

void BLDC::backward(void)
{
	uint8_t *receivebyte;

	receivebyte = command(bldc_backward);
	ESP_LOGI("BLDC", "RX Drive : %s", receivebyte);
	// command(bldc_backward);
}

void BLDC::left(void)
{
	uint8_t *receivebyte;

	receivebyte = command(bldc_left);
	ESP_LOGI("BLDC", "RX Drive : %s", receivebyte);
	// command(bldc_backward);
}

void BLDC::right(void)
{
	uint8_t *receivebyte;

	receivebyte = command(bldc_right);
	ESP_LOGI("BLDC", "RX Drive : %s", receivebyte);
	// command(bldc_backward);
}

void BLDC::start(void)
{
	uint8_t *receivebyte;

	receivebyte = command(bldc_start);
	ESP_LOGI("BLDC", "RX Drive : %s", receivebyte);
	// command(bldc_start);
}

void BLDC::stop(void)
{
	uint8_t *receivebyte;

	receivebyte = command(bldc_stop);
	ESP_LOGI("BLDC", "RX Drive : %s", receivebyte);
	// command(bldc_stop);
}

int BLDC::getvelocity(void)
{
	uint8_t *receivebyte;

	receivebyte = command(bldc_getveloctiy);
	ESP_LOGI("BLDC", "RX Drive : %s", receivebyte);
	return abs(atof((char *)buf));
	// return 399;
}