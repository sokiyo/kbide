

#include "bt_i.h"

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

#include "time.h"
#include "sys/time.h"

BT::BT() {
	
}

void BT::init(void) {
	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
}

int BT::prop_count(void) {
	return 0;
}

bool BT::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool BT::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool BT::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool BT::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool BT::prop_write(int index, char *value) {
	// not supported
	return false;
}


void BT::process(Driver *drv) {

}

void BT::setup(const char* name) {
	memset(bt_device_name, 0, sizeof bt_device_name);
	strcpy(bt_device_name, name);
	
	esp_bt_setup();
}

void BT::on_auth(BTFcallback c) {
	bt_auth_callback = c;
}

void BT::on_data(BTFcallback c) {
	bt_callback = c;
}

char* BT::get_password() {
	return bt_password;
}

char* BT::get_data() {
	return bt_data_received;
}

uint8_t BT::available() {
	return strlen(bt_data_received) - bt_data_next;
}

char BT::read() {
	if (bt_data_next >= strlen(bt_data_received)) {
		return 0;
	}
	
	return bt_data_received[bt_data_next++];
}

void BT::send(char* data) {
	if (bt_connected) {
		esp_spp_write(bt_handle, strlen(data), (uint8_t*)data);
	}
}

void BT::send(uint8_t data) {
	send((double)data);
}

void BT::send(double data) {
	char buf[30];
	memset(buf, 0, sizeof buf);
	sprintf(buf, "%f", data);
	
	// check ending zero
	uint8_t i = strlen(buf) - 1;
	while (i >= 0) {
		if (buf[i] == '0') {
			buf[i] = '\x0';
		} else if (buf[i] == '.') {
			buf[i] = '\x0';
			break;
		} else {
			break; // first occurence of non-zero or dot
		}
		i--;
	}

	send(buf);
}

void BT::send(bool data) {
	if (data) {
		send("1");
	} else {
		send("0");
	}
}


void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    switch (event) {
		case ESP_SPP_INIT_EVT:
			ESP_LOGI(SPP_TAG, "ESP_SPP_INIT_EVT");
			// esp_bt_dev_set_device_name(EXCAMPLE_DEVICE_NAME);
			esp_bt_dev_set_device_name(bt_device_name);
			esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);
			esp_spp_start_srv(ESP_SPP_SEC_AUTHENTICATE, ESP_SPP_ROLE_SLAVE, 0, SPP_SERVER_NAME);
			break;
		case ESP_SPP_DISCOVERY_COMP_EVT:
			ESP_LOGI(SPP_TAG, "ESP_SPP_DISCOVERY_COMP_EVT");
			break;
		case ESP_SPP_OPEN_EVT:
			ESP_LOGI(SPP_TAG, "ESP_SPP_OPEN_EVT");
			break;
		case ESP_SPP_CLOSE_EVT:
			ESP_LOGI(SPP_TAG, "ESP_SPP_CLOSE_EVT");
			bt_connected = false;
			bt_handle = 0;
			break;
		case ESP_SPP_START_EVT:
			ESP_LOGI(SPP_TAG, "ESP_SPP_START_EVT");
			break;
		case ESP_SPP_CL_INIT_EVT:
			ESP_LOGI(SPP_TAG, "ESP_SPP_CL_INIT_EVT");
			break;
		case ESP_SPP_DATA_IND_EVT:
			ESP_LOGI(SPP_TAG, "ESP_SPP_DATA_IND_EVT len=%d handle=%d",
					 param->data_ind.len, param->data_ind.handle);
			esp_log_buffer_hex("",param->data_ind.data,param->data_ind.len);
			
			ESP_LOGI(SPP_TAG, "Data copy");
			memset(bt_data_received, 0, sizeof bt_data_received);
			memcpy(bt_data_received, param->data_ind.data, param->data_ind.len);
			bt_data_next = 0;
			
			if (bt_callback) {
				ESP_LOGI(SPP_TAG, "Call function");
				bt_callback();
			}
			break;
		case ESP_SPP_CONG_EVT:
			ESP_LOGI(SPP_TAG, "ESP_SPP_CONG_EVT");
			break;
		case ESP_SPP_WRITE_EVT:
			ESP_LOGI(SPP_TAG, "ESP_SPP_WRITE_EVT");
			break;
		case ESP_SPP_SRV_OPEN_EVT:
			ESP_LOGI(SPP_TAG, "ESP_SPP_SRV_OPEN_EVT");
			bt_connected = true;
			bt_handle = param->data_ind.handle;
			break;
		default:
			break;
    }
}

void esp_bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {
    switch (event) {
		case ESP_BT_GAP_AUTH_CMPL_EVT: {
			if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
				ESP_LOGI(SPP_TAG, "authentication success: %s", param->auth_cmpl.device_name);
				esp_log_buffer_hex(SPP_TAG, param->auth_cmpl.bda, ESP_BD_ADDR_LEN);
			} else {
				ESP_LOGE(SPP_TAG, "authentication failed, status:%d", param->auth_cmpl.stat);
			}
			break;
		}
		case ESP_BT_GAP_CFM_REQ_EVT:
			ESP_LOGI(SPP_TAG, "ESP_BT_GAP_CFM_REQ_EVT Please compare the numeric value: %d", param->cfm_req.num_val);
			
			sprintf(bt_password, "%d", param->cfm_req.num_val);
			if (bt_auth_callback) { // auth callback
				bt_auth_callback();
			}
			
			esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
			break;
		case ESP_BT_GAP_KEY_NOTIF_EVT:
			ESP_LOGI(SPP_TAG, "ESP_BT_GAP_KEY_NOTIF_EVT passkey:%d", param->key_notif.passkey);
			break;
		case ESP_BT_GAP_KEY_REQ_EVT:
			ESP_LOGI(SPP_TAG, "ESP_BT_GAP_KEY_REQ_EVT Please enter passkey!");
			break;
		default: {
			ESP_LOGI(SPP_TAG, "event: %d", event);
			break;
		}
    }
    return;
}

void esp_bt_setup() {
	// Show log
	esp_log_level_set("*", ESP_LOG_DEBUG);
	
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );


    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s enable controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_init()) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s initialize bluedroid failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_enable()) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s enable bluedroid failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_gap_register_callback(esp_bt_gap_cb)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s gap register failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_spp_register_callback(esp_spp_cb)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp register failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_spp_init(ESP_SPP_MODE_CB)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp init failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    esp_bt_sp_param_t param_type = ESP_BT_SP_IOCAP_MODE;
    esp_bt_io_cap_t iocap = ESP_BT_IO_CAP_IO;
    esp_bt_gap_set_security_param(param_type, &iocap, sizeof(uint8_t));
}
