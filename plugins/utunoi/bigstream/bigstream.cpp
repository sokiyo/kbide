#ifndef __BIGSTREAM_CPP__
#define __BIGSTREAM_CPP__

#include "bigstream.h"

BIGSTREAM::BIGSTREAM() {}

void BIGSTREAM::init(void)
{
	esp_log_level_set("*", ESP_LOG_INFO);

	memset(this->value, 0, sizeof value);

	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
}

int BIGSTREAM::prop_count(void)
{
	return 0;
}

bool BIGSTREAM::prop_name(int index, char *name)
{
	// not supported
	return false;
}

bool BIGSTREAM::prop_unit(int index, char *unit)
{
	// not supported
	return false;
}

bool BIGSTREAM::prop_attr(int index, char *attr)
{
	// not supported
	return false;
}

bool BIGSTREAM::prop_read(int index, char *value)
{
	// not supported
	return false;
}

bool BIGSTREAM::prop_write(int index, char *value)
{
	// not supported
	return false;
}

void BIGSTREAM::process(Driver *drv)
{
}

void BIGSTREAM::set(uint8_t n, char *value)
{
	strcpy(this->value[n - 1], value);
}

void BIGSTREAM::set(uint8_t n, double value)
{
	sprintf(this->value[n - 1], "%0.1f", value);
}

void BIGSTREAM::set(uint8_t n, int value)
{
	itoa(value, this->value[n - 1], 10);
}

void BIGSTREAM::set(uint8_t n, bool value)
{
	this->value[n - 1][0] = value ? '1' : '0';
	this->value[n - 1][1] = 0;
}

bool BIGSTREAM::send(char *url, char *data)
{
	// Use esp http api
	esp_http_client_config_t config = {.url = url};
	esp_http_client_handle_t client = esp_http_client_init(&config);
	esp_http_client_set_method(client, HTTP_METHOD_POST);
	esp_http_client_set_post_field(client, data, strlen(data));
	esp_http_client_set_header(client, "Content-Type", "application/json");

	ESP_LOGI("BIGSTREAM", "Data: %s, len: %d", data, strlen(data));

	esp_err_t err = esp_http_client_perform(client);
	bool error;
	if (err == ESP_OK)
	{
		uint16_t len = esp_http_client_get_content_length(client);
		uint16_t code = esp_http_client_get_status_code(client);

		ESP_LOGI("BIGSTREAM", "HTTPS Status = %d, content_length = %d", code, len);
		error = false;
	}
	else
	{
		ESP_LOGE("BIGSTREAM", "Error perform http request %s", esp_err_to_name(err));
		error = true;
	}
	esp_http_client_cleanup(client);
	return error;
}

bool BIGSTREAM::sendSensor(char *host, char *type, double val)
{
	bool error;
	char *url = (char *)malloc(200);
	memset(url, 0, 200);

	sprintf(url, "https://kb.bigstream.cloud/io/stream");
	ESP_LOGI("BIGSTREAM", "Url: %s", url);

	char *data = (char *)malloc(320);
	sprintf(data, "{\"mac\":\"%s\",\"dtype\":\"%s\",\"value\":\"%0.1f\"}", host, type, val);
	error = send(url,data);
	free(url);
	free(data);
	return error;
}

bool BIGSTREAM::sendLocation(char *host, double lat, double lng)
{
	bool error;
	char *url = (char *)malloc(200);
	memset(url, 0, 200);

	sprintf(url, "https://kb.bigstream.cloud/io/stream");
	ESP_LOGI("BIGSTREAM", "Url: %s", url);

	char *data = (char *)malloc(320);
	sprintf(data, "{\"mac\":\"%s\",\"dtype\":\"gps\",\"value\":\"%f,%f\"}", host, lat, lng);
	error = send(url,data);
	free(url);
	free(data);
	return error;
}
#endif
