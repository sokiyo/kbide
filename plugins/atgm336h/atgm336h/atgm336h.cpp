#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "atgm336h.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "TinyGPSPlus.h"

#define UART_NUM UART_NUM_1
#define UART_BAUDRATE 9600
#define UART_LINETERM '\n'
#define TX_BUF_SIZE 1024
#define RX_BUF_SIZE 1024
#define HPM_MAX_RESP_SIZE 8

enum STATUS1
{
	STATUS_WAITING,
	STATUS_OK
};

STATUS1 _status;
uint8_t _index = 0;
uint16_t _calculatedChecksum;
uint16_t _frameLen = 0;
uint16_t _checksum = 0;
uint8_t _payload[12];

struct DATA
{
	// Standard Particles, CF=1
	uint16_t PM_SP_UG_1_0;
	uint16_t PM_SP_UG_2_5;
	uint16_t PM_SP_UG_10_0;

	// Atmospheric environment
	uint16_t PM_AE_UG_1_0;
	uint16_t PM_AE_UG_2_5;
	uint16_t PM_AE_UG_10_0;
};

DATA _data;

TinyGPSPlus gps;

unsigned int makeWord(unsigned char h, unsigned char l)
{
	return (h << 8) | l;
}

void loop(void)
{
	int len, index;
	uint8_t old_byte = 0;
	_status = STATUS_WAITING;
	// vTaskDelay(100 / portTICK_RATE_MS);
	uint8_t respBuf; ///
	// stream.available()
	/// available() gets the number of bytes available in the stream. This is only for bytes that have already arrived.
	len = uart_read_bytes(UART_NUM, &respBuf, 1, (20 / portTICK_RATE_MS));
	if (len > 0)
	{
		printf("%c", respBuf);
		gps.encode(respBuf);
		// uint8_t ch = respBuf[0];
	} // end of if(len>0)
}

void vATGM336HTask(void *pvParameters)
{
	atgm336h *pmx = (atgm336h *)pvParameters;

	vTaskDelay(500 / portTICK_RATE_MS);

	while (1)
	{
		loop();
	}
	vTaskDelete(NULL);
}

atgm336h::atgm336h(int tx_io, int rx_io) /// int tx_io, int rx_io){
{
	// tx = OUT2_GPIO;
	// rx = GPIO_NUM_18;

	tx_pin = tx_io;
	rx_pin = rx_io;
}

void atgm336h::init(void)
{
	// uart init
	uart_config_t uart_config = {
		.baud_rate = UART_BAUDRATE,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
		.rx_flow_ctrl_thresh = 0,
		.use_ref_tick = true};

	// uart config
	uart_param_config(UART_NUM, &uart_config);
	// set uart pins   tx=GPIO_NUM_22 rx=GPIO_NUM_23
	uart_set_pin(UART_NUM, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

	uart_set_line_inverse(UART_NUM, UART_INVERSE_TXD);

	// install uart driver
	uart_driver_install(UART_NUM, (RX_BUF_SIZE * 2), (TX_BUF_SIZE * 2), 0, NULL, 0);
	// uart task
	xTaskCreatePinnedToCore(vATGM336HTask, "atgm336h Task", IO_DEV_STACK_SIZE_MIN, this, IO_DEV_TASK_PRIORITY, NULL, KIDBRIGHT_RUNNING_CORE);

	initialized = true;
	error = false;
}

int atgm336h::prop_count(void)
{
	return 2;
}

bool atgm336h::prop_name(int index, char *name)
{
	if (index == 0)
	{
		snprintf(name, DEVICE_PROP_NAME_LEN_MAX, "%s", "latitude");
		return true;
	}
	else if (index == 1)
	{
		snprintf(name, DEVICE_PROP_NAME_LEN_MAX, "%s", "longitude");
		return true;
	}

	// not supported
	return false;
}

bool atgm336h::prop_unit(int index, char *unit)
{
	if (index == 0)
	{
		snprintf(unit, DEVICE_PROP_UNIT_LEN_MAX, "%s", "degree");
		return true;
	}
	else if (index == 1)
	{
		snprintf(unit, DEVICE_PROP_UNIT_LEN_MAX, "%s", "degree");
		return true;
	}

	// not supported
	return false;
}

bool atgm336h::prop_attr(int index, char *attr)
{
	if ((index == 0) || (index == 1))
	{
		get_attr_str(attr, PROP_ATTR_READ_FLAG | PROP_ATTR_TYPE_NUMBER_FLAG); // read only, number
		return true;
	}

	// not supported
	return false;
}

bool atgm336h::prop_read(int index, char *value)
{
	if (index == 0)
	{
		snprintf(value, DEVICE_PROP_VALUE_LEN_MAX, "%f", latitude);
		return true;
	}
	else if (index == 1)
	{
		snprintf(value, DEVICE_PROP_VALUE_LEN_MAX, "%f", longitude);
		return true;
	}

	// not supported
	return false;
}

bool atgm336h::prop_write(int index, char *value)
{
	// not supported
	return false;
}

void atgm336h::process(Driver *drv)
{
}

double atgm336h::get_lat(void)
{
	if (gps.location.isValid())
		latitude = gps.location.lat();
	else
		latitude = 0;
	return latitude;
}

double atgm336h::get_lng(void)
{
	if (gps.location.isValid())
		longitude = gps.location.lng();
	else
		longitude = 0;
	return longitude;
}

int atgm336h::get_year(void)
{
	if (gps.date.isValid())
		year = gps.date.year();
	else
		year = 0;
	return year;
}

int atgm336h::get_month(void)
{
	if (gps.date.isValid())
		month = gps.date.month();
	else
		month = 0;
	return month;
}

int atgm336h::get_day(void)
{
	if (gps.date.isValid())
		day = gps.date.day();
	else
		day = 0;
	return day;
}

int atgm336h::get_hour(void)
{
	if (gps.time.isValid())
		hour = gps.time.hour();
	else
		hour = 0;
	return hour;
}

int atgm336h::get_minute(void)
{
	if (gps.time.isValid())
		minute = gps.time.minute();
	else
		minute = 0;
	return minute;
}

int atgm336h::get_second(void)
{
	if (gps.time.isValid())
		second = gps.time.second();
	else
		second = 0;
	return second;
}