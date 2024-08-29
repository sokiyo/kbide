#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
#include "esp_spp_api.h"
#include "driver.h"
#include "device.h"
#include "driver/gpio.h"

#include "time.h"
#include "sys/time.h"

#define SPP_TAG "SPP_ACCEPTOR_DEMO"
#define SPP_SERVER_NAME "SPP_SERVER"

static const esp_spp_sec_t sec_mask = ESP_SPP_SEC_AUTHENTICATE;
static const esp_spp_role_t role_slave = ESP_SPP_ROLE_SLAVE;

void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) ;
void esp_bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) ;
void esp_bt_setup() ;

static bool bt_connected = false;
static uint32_t bt_handle = 0;
static char bt_password[10];
static char bt_device_name[30];
static char bt_data_received[100];

typedef void(*BTFcallback)(void);
static BTFcallback bt_callback = NULL;
static BTFcallback bt_auth_callback = NULL;

static uint8_t bt_data_next = 0;

class BT : public Device {
	private:


	public:
		// constructor
		BT();
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
		void setup(const char* name) ;
		
		void on_auth(BTFcallback c) ;
		void on_data(BTFcallback c) ;
		
		char* get_password() ;
		char* get_data() ;
		
		uint8_t available() ;
		char read() ;
		
		void send(char* data) ;
		void send(uint8_t data) ;
		void send(double data) ;
		void send(bool data) ;
		
};

