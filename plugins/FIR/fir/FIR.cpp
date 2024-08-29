#include <stdio.h>
#include <string.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include "nvs_flash.h"
#include "esp_system.h"
#include "kidbright32.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "FIR.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

std::map<std::string, Value_firebase_event> dict_firebase_onvalue = {};

// stream data
char fir_stream_data[MAX_DATA_BUFFER_SIZE];
bool is_fir_stream_data_packet_starting = false;
char current_fir_stream_data[550];
std::string fir_json_string;
// Document fir_json_document;
// Value fir_json_value;

FIR::FIR()
{
    polling_ms = FIR_POLLING_MS;
}

void FIR::init(void)
{
    state = s_detect;
    initialized = true;
}

int FIR::prop_count(void)
{
    // not supported
    return 0;
}

bool FIR::prop_name(int index, char *name)
{
    // not supported
    return false;
}

bool FIR::prop_unit(int index, char *unit)
{
    // not supported
    return false;
}

bool FIR::prop_attr(int index, char *attr)
{
    // not supported
    return false;
}

bool FIR::prop_read(int index, char *value)
{
    // not supported
    return false;
}

bool FIR::prop_write(int index, char *value)
{
    // not supported
    return false;
}

void FIR::process(Driver *drv)
{
    //  char buffer[64];
    //  sprintf(buffer, "%lldms\n", (esp_timer_get_time() / 1000));
    //  uart_write_bytes(UART_NUM_0, (const char*)buffer, strlen(buffer));
}

char *FIR::random()
{
    return "nat-random";
}

static const char *TAG = "firebase";

void FIR::begin(char *_host, char *_key)
{
    memset(this->host, 0, HOST_SIZE);
    strcpy(this->host, _host);

    memset(this->secret_key, 0, SECRET_KEY_SIZE);
    strcpy(this->secret_key, _key);

    is_connected_wifi();

    while (!this->initial_wifi)
    {
        this->initial_wifi = is_connected_wifi();
        printf("%s\n", this->initial_wifi ? "connected firebase" : "reconnecting firebase");
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    // esp_event_loop_deinit();
    // esp_event_loop_set_cb(&xxxevent_handler, NULL);
}

char *FIR::get_string(char *path)
{
    char *buffer = _http(path, HTTP_METHOD_GET, true);
    int len = strlen(buffer);
    printf("get data %s at %s\n", buffer, path);
    if (buffer[0] == '"' && buffer[len - 1] == '"')
    {
        buffer[len - 1] = '\0'; // remove first and last character (remove double quite["])
        buffer++;
    }
    // printf("get data %s at %s\n", buffer, path);
    dict_firebase_onvalue[path].data = buffer;
    return buffer;
}

void FIR::set(char *path, char *data)
{

    // Add double quote ("") to data;
    char *_data = (char *)malloc(strlen(data) + 2);
    strcpy(_data, "\"");
    strcat(_data, data);
    strcat(_data, "\"");
    printf("set text %s at %s\n", _data, path);
    _http_data(path, _data);
    free(_data);
}

void FIR::set(char *path, double data)
{

    int length = 40;
    char *_data = (char *)malloc(length);

    // toString
    snprintf(_data, length, "%f", data);
    printf("set number %s at %s\n", _data, path);
    _http_data(path, _data);
    free(_data);
}

void FIR::remove(char *path)
{
    printf("removing data at %s\n", path);
    _http(path, HTTP_METHOD_DELETE, true);
    printf("%s\n", "==removed data==");
}

esp_err_t FIR::_firebase_on_value_event(esp_http_client_event_t *evt)
{
    printf("%s\n", "firebase on value event");
    if (evt->event_id == HTTP_EVENT_ON_HEADER)
    {
        printf("%s\n", "HTTP_EVENT_ON_HEADER");
    }
    if (evt->event_id == HTTP_EVENT_ON_FINISH)
    {
        printf("%s\n", "HTTP_EVENT_ON_FINISH");
    }
    if (evt->event_id == HTTP_EVENT_HEADER_SENT)
    {
        printf("%s\n", "HTTP_EVENT_HEADER_SENT");
    }
    if (evt->event_id == HTTP_EVENT_HEADER_SENT)
    {
        printf("%s\n", "HTTP_EVENT_HEADER_SENT");
    }
    if (evt->event_id == HTTP_EVENT_ON_DATA)
    {

        // if (3 >= strlen(strand) && ( strncmp("aug",strand,3) == 0 )) {
        // do stuff
        // }

        if (evt->data_len >= 512)
        {
            printf("%s\n", "at the limit");
            return ESP_OK;
        }

        current_fir_stream_data[0] = 0;
        strcpy(current_fir_stream_data, (char *)(evt->data));
        current_fir_stream_data[evt->data_len] = '\0';

        if (strncmp(current_fir_stream_data, "data: event", strlen("data: event")) != 1)
        {
            printf("%s\n", "not start packet");
            return ESP_OK;
        }

        if (current_fir_stream_data[evt->data_len - 3] != '}')
        {
            printf("%s\n", "not end of json");

            // print lastest character
            printf("%c\n", current_fir_stream_data[evt->data_len - 3]);
            return ESP_OK;
        }

        printf("%s\n", "packet");
        printf("%s\n", current_fir_stream_data);

        for (int i = 0; i < evt->data_len - BEGIN_DATA_STREAM_TEXT_LENGTH; ++i)
        {
            current_fir_stream_data[i] = current_fir_stream_data[i + BEGIN_DATA_STREAM_TEXT_LENGTH + 1];
        }

        // current_fir_stream_data[evt->data_len-16] = '\0';
        current_fir_stream_data[evt->data_len - (BEGIN_DATA_STREAM_TEXT_LENGTH + 3)] = '\0';

        printf("%s\n", "success");
        printf("%s\n", current_fir_stream_data);
        printf("%s\n", "end success");

        fir_json_string = current_fir_stream_data;

        string::size_type loc = fir_json_string.find("\"path\"", 0);
        fir_json_string = fir_json_string.substr(loc + 7);
        string::size_type begin_key = fir_json_string.find("\"", 0);
        string::size_type last_key = fir_json_string.find("\"", 1);

        string path = fir_json_string.substr(begin_key + 1, last_key - 1);
        fir_json_string = fir_json_string.substr(last_key + 8);

        string::size_type begin_data = fir_json_string.find(":", 0);
        string::size_type last_data = fir_json_string.size() - 1;
        string data = fir_json_string.substr(begin_data + 1, last_data - 1);

        if (path.at(0) == '/')
        {
            path.erase(0, 1); // erase at position 0
        }

        printf("path: %s\n", path.c_str());
        printf("data: %s\n", data.c_str());

        // char *_data = (char *)malloc(data.size() + 10);
        // char *_data = new char[data.size() + 10];
        // strcpy(_data, data.c_str());

        std::map<std::string, Value_firebase_event>::iterator pos;
        for (pos = dict_firebase_onvalue.begin(); pos != dict_firebase_onvalue.end(); ++pos)
        {
            printf("key: %s ", pos->first.c_str());
            printf("value: %s\n", pos->second.data.c_str());
        }

        // strcpy(dict_firebase_onvalue[path].data, _data);
        dict_firebase_onvalue[path].data = data;
        printf("add data %s\n", data.c_str());

        printf("XdataX: %s\n", dict_firebase_onvalue[path].data.c_str());

        for (pos = dict_firebase_onvalue.begin(); pos != dict_firebase_onvalue.end(); ++pos)
        {
            printf("key: %s ", pos->first.c_str());
            printf("value: %s\n", pos->second.data.c_str());
        }

        if (dict_firebase_onvalue[path].callback)
        {
            printf("callback at path: %s\n", path.c_str());
            dict_firebase_onvalue[path].callback();
        }

        // printf("%s\n", data);
        printf("MALLOC_CAP_INTERNAL %d\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
        printf("MALLOC_CAP_8BIT %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
        printf("MALLOC_CAP_32BIT %d\n", heap_caps_get_free_size(MALLOC_CAP_32BIT));
    }
    printf("%s\n", "==END==");
    return ESP_OK;
}

void FIR::start_stream_data(void *pvParameters)
{
    FIR *fir = reinterpret_cast<FIR *>(pvParameters);
    if (fir->initial_on_change_value)
    {
        vTaskDelete(NULL);
        return;
    }

    fir->initial_on_change_value = true;

    while (!fir->initial_wifi)
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }

    printf("%s\n", "start stream data");

    char *url = (char *)malloc(URL_SIZE);
    strcpy(url, fir->host);
    // strcat(url, "/labs");
    strcat(url, ".json?auth=");
    strcat(url, fir->secret_key);

    esp_http_client_config_t config = {
        .url = url};
    config.event_handler = _firebase_on_value_event;

    printf("%s\n", "initing client...");

    esp_http_client_handle_t client = esp_http_client_init(&config);

    printf("%s\n", "inited client...");

    char *accept = (char *)malloc(18 + 10);
    strcpy(accept, "text/event-stream");

    char *cache = (char *)malloc(9 + 10);
    strcpy(cache, "no-cache");

    printf("%s\n", "setting header client...");

    esp_http_client_set_header(client, "Accept", accept);

    printf("%s\n", "accept");

    esp_http_client_set_header(client, "Cache-Control", cache);

    printf("%s\n", "cache");
    // esp_http_client_set_url(client, client->location);

    printf("%s\n", "opening client...");

    printf("MALLOC_CAP_8BIT %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    printf("MALLOC_CAP_32BIT %d\n", heap_caps_get_free_size(MALLOC_CAP_32BIT));

    // esp_err_t err;
    if (esp_http_client_open(client, 0) != ESP_OK)
    {
        // ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
        printf("%s\n", "Failed to open HTTP connection");
        return;
    }
    printf("%s\n", "whiling...");
    while (true)
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);
        printf("%s\n", "fetching..");
        esp_http_client_fetch_headers(client);
        printf("%s\n", "fetched");
    }
    vTaskDelete(NULL);
    // esp_http_client_close(client);
    // esp_http_client_cleanup(client);
}

void FIR::on_values(char *path, Callback_firebase_event statement)
{
    printf("Recieve value at path: %s\n", path);
    Value_firebase_event event;
    event.callback = statement;
    dict_firebase_onvalue[path] = event;

    xTaskCreate(start_stream_data, "STREAM_DATA", 2048 * 6, this, tskIDLE_PRIORITY, NULL);
}

char *FIR::value_string(char *path)
{
    printf("value_string\n");

    std::map<std::string, Value_firebase_event>::iterator pos;
    for (pos = dict_firebase_onvalue.begin(); pos != dict_firebase_onvalue.end(); ++pos)
    {
        printf("key: %s ", pos->first.c_str());
        printf("value: %s\n", pos->second.data.c_str());
    }

    char *_path = (char *)malloc(strlen(path) + 5);
    // strcpy(_path, "/");
    // strcat(_path, path);

    strcpy(_path, path);

    if (dict_firebase_onvalue[_path].data.size() > 0)
    {
        printf("dataX: %s\n", dict_firebase_onvalue[_path].data.c_str());
        printf("sizeX: %d\n", dict_firebase_onvalue[_path].data.size());
        char *data = (char *)malloc(dict_firebase_onvalue[_path].data.size() + 5);
        strcpy(data, dict_firebase_onvalue[_path].data.c_str());
        data[dict_firebase_onvalue[_path].data.size()] = '\0';
        if (data[0] == '"' && data[dict_firebase_onvalue[_path].data.size() - 1] == '"')
        {
            data[dict_firebase_onvalue[_path].data.size() - 1] = '\0'; // remove first and last character (remove double quite["])
            data++;
        }
        // char data[dict_firebase_onvalue[_path].data.size()];
        // strcpy(data, dict_firebase_onvalue[_path].data.c_str());
        return data;
    }
    return "0";
}

double FIR::convert(char *data)
{
    return atof(data);
}

char *FIR::concat(char *left, char *right)
{
    int len = strlen(left) + strlen(right);
    printf("concat char&char len %d\n", len);
    char *result = (char *)malloc(len + 10);
    strcpy(result, left);
    strcat(result, right);
    return result;
}

char *FIR::concat(char *left, double _right)
{
    char *right = FIR::to_char_array(_right, 0);
    int len = strlen(left) + strlen(right);
    printf("concat char&double len %d\n", len);
    char *result = (char *)malloc(len + 10);
    strcpy(result, left);
    strcat(result, right);
    return result;
}

char *FIR::concat(double _left, char *right)
{
    char *left = FIR::to_char_array(_left, 0);
    int len = strlen(left) + strlen(right);
    printf("concat double&char len %d\n", len);
    char *result = (char *)malloc(len + 10);
    strcpy(result, left);
    strcat(result, right);
    return result;
}

char *FIR::concat(double _left, double _right)
{
    char *left = FIR::to_char_array(_left, 0);
    char *right = FIR::to_char_array(_right, 0);
    int len = strlen(left) + strlen(right);
    printf("concat double&double len %d\n", len);
    char *result = (char *)malloc(len + 10);
    strcpy(result, left);
    strcat(result, right);
    return result;
}

esp_err_t _http_event_handle(esp_http_client_event_t *evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ERROR:
        ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
        printf("%s\n", "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
        printf("%s\n", "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
        printf("%s\n", "HTTP_EVENT_HEADER_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER");
        printf("%s\n", "HTTP_EVENT_ON_HEADER");
        printf("%.*s", evt->data_len, (char *)evt->data);
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        printf("HTTP_EVENT_ON_DATA, len=%d\n", evt->data_len);
        if (!esp_http_client_is_chunked_response(evt->client))
        {
            printf("%.*s", evt->data_len, (char *)evt->data);
        }

        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
        break;
    }
    return ESP_OK;
}

char *FIR::_http(char *path, esp_http_client_method_t method, bool check_wifi)
{

    printf("%s\n", "_http");

    if (check_wifi)
    {
        if (!this->initial_wifi)
        {
            return "CAN'T CONNECT HTTP";
        }

        while (!this->initial_wifi)
        {
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
    }

    int url_len = strlen(this->host) + strlen(path) + strlen(".json?auth=") + strlen(this->secret_key);
    char *url = (char *)malloc(url_len + 10);
    strcpy(url, this->host);
    strcat(url, path);
    strcat(url, ".json?auth=");
    strcat(url, this->secret_key);

    // // Use esp http api
    esp_http_client_config_t config = {
        .url = url};

    // config.event_handler = _http_event_handle;

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_method(client, method);

    esp_err_t err;
    err = esp_http_client_perform(client);

    if (err == ESP_OK)
    {
        if (!(method == HTTP_METHOD_GET))
        {
            esp_http_client_cleanup(client);
            return ""; // no need to get data
        }

        int len = esp_http_client_get_content_length(client);
        printf("%s content length = %d\n", "OK", len);

        if (len > MAX_LENGTH_DATA)
        {
            esp_http_client_cleanup(client);
            return "LIMIT LENGTH";
        }

        char *buffer = (char *)malloc(len + 2);
        esp_http_client_read(client, buffer, len);
        buffer[len] = '\0';

        printf("read: %s\n", buffer);
        esp_http_client_cleanup(client);

        if (is_valid_firebase_data(buffer))
        {
            return buffer;
        }

        return "CAN'T CONNECT FIREBASE";
    }
    else
    {
        printf("%s\n", "CAN'T CONNECT HTTP");
    }

    esp_http_client_cleanup(client);

    return "CAN'T CONNECT HTTP";
}

void FIR::_http_data(char *path, char *_data)
{
    printf("%s\n", _data);
    int url_len = strlen(this->host) + strlen(path) + strlen(".json?auth=") + strlen(this->secret_key);
    char *url = (char *)malloc(url_len + 10);
    strcpy(url, this->host);
    strcat(url, path);
    strcat(url, ".json?auth=");
    strcat(url, this->secret_key);

    esp_http_client_config_t config = {
        .url = url // URL_HTTP_DATA
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_method(client, HTTP_METHOD_PUT);

    char *data = (char *)malloc(strlen(_data) + 20);
    strcpy(data, _data);
    esp_http_client_set_post_field(client, data, strlen(data));

    printf("%s %s with %d length\n", "sending...", data, strlen(data));

    esp_http_client_perform(client);

    printf("MALLOC_CAP_8BIT %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    printf("MALLOC_CAP_32BIT %d\n", heap_caps_get_free_size(MALLOC_CAP_32BIT));

    esp_http_client_cleanup(client);
    free(url);
    free(data);
    // free(client);

    printf("%s\n", "====SUCCESS====");
}

char *FIR::to_char_array(double num_double, int decimal_place)
{
    int num_int = round(num_double * pow(10, decimal_place));
    int sign = num_int < 0 ? 1 : 0;
    num_int = abs(num_int);

    if (num_int == 0)
    {
        char *s = (char *)malloc(decimal_place + 3);
        s[0] = '0';
        s[1] = '.';
        for (int i = 2; i < decimal_place + 2; i++)
            s[i] = '0';
        s[decimal_place + 2] = '\0';
        return s;
    }

    int digit_count = 1;
    int n = num_int;
    if (n >= 100000000)
    {
        digit_count += 8;
        n /= 100000000;
    }
    if (n >= 10000)
    {
        digit_count += 4;
        n /= 10000;
    }
    if (n >= 100)
    {
        digit_count += 2;
        n /= 100;
    }
    if (n >= 10)
    {
        digit_count++;
    }

    int size = digit_count + 1 + (decimal_place > 0 ? 1 : 0) + sign;
    char *s = (char *)malloc(size);

    for (int i = 0, integer = num_int; integer != 0; integer /= 10)
    {
        s[size - 2 - i++] = integer % 10 + 48;
        if (decimal_place > 0 && i == decimal_place)
            s[size - 2 - i++] = '.';
    }
    s[size - 1] = '\0';
    if (sign)
        s[0] = '-';
    return s;

    // Fix when '.5' happened will become to 0.5

    if (s[0] == '.')
    {
        char *x = (char *)malloc(size + 1);
        x[0] = '0';
        for (int i = 0; i < strlen(s); i++)
        {
            x[i + 1] = s[i];
        }
        x[size + 1] = '\0';
        printf("%s\n", x);
        return x;
    }

    // Fix when '-.5' happened will become to -0.5

    if (s[0] == '-' && s[1] == '.')
    {
        char *x = (char *)malloc(size + 1);
        x[0] = '-';
        x[1] = '0';
        for (int i = 0; i < strlen(s) - 1; i++)
        {
            x[i + 2] = s[i + 1];
        }
        x[size + 1] = '\0';
        printf("%s\n", x);
        return x;
    }
}

bool FIR::is_connected_wifi()
{

    char *buffer = _http("", HTTP_METHOD_GET, false);

    if (strcmp(buffer, "CAN'T CONNECT HTTP") == 0)
    {
        return false;
    }

    if (strcmp(buffer, "CAN'T CONNECT FIREBASE") == 0)
    {
        return false;
    }

    // if(strcmp(buffer, "LIMIT LENGTH") == 0) {
    //   return false;
    // }

    this->initial_wifi = true;

    return true;
}

bool FIR::is_valid_firebase_data(char *data)
{
    std::string json_str(data);
    printf("is_valid: %s\n", json_str.c_str());
    string::size_type loc = json_str.find("\"error\"");
    printf("loc: %d\n", loc);
    printf("npos %d\n", std::string::npos);
    if (loc != std::string::npos)
    {
        return false;
    }
    // Document document;
    // ParseResult ok = document.Parse(json_str.c_str());
    // if (!ok) {
    //   return false; //not json
    // }

    // if (!document.IsObject()) {
    //   return true; //not object, must be valid value
    // }

    // if (document["error"].IsString()) {
    //   return false; //json has a error key; firebase wanna throw error;
    // }

    return true;
}
