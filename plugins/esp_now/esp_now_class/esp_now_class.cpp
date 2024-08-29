#ifndef __ESP_NOW_CPP__
#define __ESP_NOW_CPP__

#include "esp_now_class.h"

static void ESPNOWOnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
	ESP_LOGI("ESP-NOW", "Received from: %02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);


	memset(recv_buff, 0, sizeof(recv_buff));
	memcpy(recv_buff, data, data_len);

	ESP_LOGI("ESP-NOW", "Received :  %s", recv_buff);

	if (recv_cb) {
		recv_cb();
	}
}

void ESPNOWOnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  ESP_LOGI("ESP-NOW", "Send to %02x:%02x:%02x:%02x:%02x:%02x, Status: %s",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5], status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

ESP_NOW_CLASS::ESP_NOW_CLASS() { }

void ESP_NOW_CLASS::init(void) {
	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
	
	// Debug
	esp_log_level_set("*", ESP_LOG_INFO);
	
	// Setup WiFi
	tcpip_adapter_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_start() );

	// Init
	ESP_ERROR_CHECK(esp_now_init());
	
	// Add peer
	slave.channel = 1;
	slave.encrypt = 0;
	memcpy(slave.peer_addr, broadcastMACAddr, 6);
	ESP_ERROR_CHECK(esp_now_add_peer(&slave));
	
	// Register callback
	esp_now_register_recv_cb(ESPNOWOnDataRecv);
	ESP_LOGI("ESP-NOW", "register callback");
	
	uint8_t mac[6];
	esp_efuse_mac_get_default(mac);
	sprintf(myMAC, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

int ESP_NOW_CLASS::prop_count(void) {
	// not supported
	return 0;
}

bool ESP_NOW_CLASS::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool ESP_NOW_CLASS::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool ESP_NOW_CLASS::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool ESP_NOW_CLASS::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool ESP_NOW_CLASS::prop_write(int index, char *value) {
	// not supported
	return false;
}
// --------------------------------------

void ESP_NOW_CLASS::process(Driver *drv) {

}

// Method
char* ESP_NOW_CLASS::getMAC() {
	return myMAC;
}

void ESP_NOW_CLASS::send(char* str) {
	esp_err_t result = esp_now_send(broadcastMACAddr, (uint8_t*)str, strlen(str));
	if (result == ESP_OK) {
		ESP_LOGI("ESP-NOW", "Send OK");
	} else {
		ESP_LOGI("ESP-NOW", "Send fail");
	}
}

void ESP_NOW_CLASS::send(float n) {
	char s_buff[255];
	sprintf(s_buff, "%f", n);
	send(s_buff);
}

void ESP_NOW_CLASS::send(char* mac, char* str) {
	uint8_t macAddr[6];
	uint8_t i = sscanf(mac, "%x:%x:%x:%x:%x:%x", (unsigned int*)&macAddr[0], (unsigned int*)&macAddr[1], (unsigned int*)&macAddr[2], (unsigned int*)&macAddr[3], (unsigned int*)&macAddr[4], (unsigned int*)&macAddr[5]);
	if (i != 6) {
		ESP_LOGI("ESP-NOW", "Convert MAC address in string to byte fail!");
		return;
	}
	// ESP_LOGI("ESP-NOW", "Send to %02x:%02x:%02x:%02x:%02x:%02x", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
	if (!esp_now_is_peer_exist(macAddr)) {
		// Add peer
		memcpy(slave.peer_addr, macAddr, 6);
		ESP_ERROR_CHECK(esp_now_add_peer(&slave));
	}
	
	esp_err_t result = esp_now_send(macAddr, (uint8_t*)str, strlen(str));
	if (result == ESP_OK) {
		ESP_LOGI("ESP-NOW", "Send OK");
	} else {
		ESP_LOGI("ESP-NOW", "Send fail");
	}
}

void ESP_NOW_CLASS::send(char* mac, float n) {
	char s_buff[255];
	sprintf(s_buff, "%f", n);
	send(mac, s_buff);
}

void ESP_NOW_CLASS::onRecv(ESPNOWRecvCallback fn) {
	recv_cb = fn;
}

char* ESP_NOW_CLASS::readString() {
	return recv_buff;
}

float ESP_NOW_CLASS::readNumber() {
	float n = 0;
	sscanf(recv_buff, "%f", &n);
	return n;
}

#endif