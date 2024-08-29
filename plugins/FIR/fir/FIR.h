#ifndef __FIR_H__
#define __FIR_H__

#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include <cstdint>
#include <cassert>
#include <iostream>

#include "esp_http_client.h"

#include "esp_event_loop.h"
// #include "esp_event_private.h"
#include "esp_event.h"

#include "driver.h"
#include "device.h"

#include <map>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/error.h"
#include "rapidjson/error/en.h"
using namespace rapidjson;

using namespace std;

#define FIR_POLLING_MS         1000

#define HOST_SIZE 128
#define SECRET_KEY_SIZE 128
#define DATA_SIZE 200
#define DATA_SIZE_MAX 500
#define DATA_NUMBER_SIZE 64
#define URL_SIZE 100
#define MAX_HTTP_RECV_BUFFER 512
#define MAX_DATA_BUFFER_SIZE 16384
#define BEGIN_DATA_STREAM_TEXT_LENGTH 16
#define MAX_LENGTH_DATA 1000

typedef void(*Callback_firebase_event)();
typedef struct Value_firebase_event
{
    Callback_firebase_event callback;
    string data;
};

class FIR : public Device {
    private:
        enum { s_detect } state;
        TickType_t tickcnt, polling_tickcnt;

        bool initial_wifi = false;
        bool initial_on_change_value = false;
        char host[HOST_SIZE];
        char secret_key[SECRET_KEY_SIZE];

    public:
        // constructor
        FIR();
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
        char* random();
        void begin(char* _host, char* _key);
        char* get_string(char *path);
        void set(char *path, char *data);
        void set(char *path, double data);
        void remove(char *path);
        static esp_err_t _firebase_on_value_event(esp_http_client_event_t *evt);
        static void start_stream_data(void * pvParameters);
        void on_values(char *path, Callback_firebase_event statement);
        char* value_string(char *path);
        double convert(char *data);
        char* concat(char *left, char *right);
        char* concat(char *left, double _right);
        char* concat(double _left, char* right);
        char* concat(double _left, double _right);
        char* _http(char *path, esp_http_client_method_t method, bool check_wifi);
        void _http_data(char *path, char *_data);
        // void debug();
        char* to_char_array(double num_double, int decimal_place);
        bool is_connected_wifi();
        bool is_valid_firebase_data(char *data);

};

#endif
