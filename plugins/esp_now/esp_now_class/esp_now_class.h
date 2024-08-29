#ifndef __PCA9634_H__
#define __PCA9634_H__

#include <stdio.h>
#include <string.h>

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "kidbright32.h"
#include "esp_wifi.h"
#include "esp_now.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "tcpip_adapter.h"

typedef void(*ESPNOWRecvCallback)();
static ESPNOWRecvCallback recv_cb = NULL;
static char recv_buff[256];

class ESP_NOW_CLASS : public Device {
	private:		
		uint8_t broadcastMACAddr[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
		char myMAC[20] ;
		esp_now_peer_info_t slave;
		
	public:
		// constructor
		ESP_NOW_CLASS() ;
		
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
		char* getMAC() ;
		void send(char*) ;
		void send(float) ;
		void send(char*, char*) ;
		void send(char*, float) ;
		void onRecv(ESPNOWRecvCallback fn) ;
		char* readString() ;
		float readNumber() ;
		
};

#endif