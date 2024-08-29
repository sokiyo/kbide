#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "hx711.h"

#define CHECK(x)                \
    do                          \
    {                           \
        esp_err_t __;           \
        if ((__ = x) != ESP_OK) \
            return __;          \
    } while (0)
#define CHECK_ARG(VAL)                  \
    do                                  \
    {                                   \
        if (!(VAL))                     \
            return ESP_ERR_INVALID_ARG; \
    } while (0)

HX711::HX711(void)
{
    //
}
HX711::HX711(gpio_num_t dout, gpio_num_t pd_sck)
{
    //
}

void HX711::init(void)
{
    dev1 = {
        .dout = SPIBUS_MISO_GPIO,
        .pd_sck = SPIBUS_CLK_GPIO,
        .gain = HX711_GAIN_A_64};
    state = s_init;
}

int HX711::prop_count(void)
{
    // not supported
    return 0;
}

bool HX711::prop_name(int index, char *name)
{
    // not supported
    return false;
}

bool HX711::prop_unit(int index, char *unit)
{
    // not supported
    return false;
}

bool HX711::prop_attr(int index, char *attr)
{
    // not supported
    return false;
}

bool HX711::prop_read(int index, char *value)
{
    // not supported
    return false;
}

bool HX711::prop_write(int index, char *value)
{
    // not supported
    return false;
}

void HX711::process(Driver *drv)
{
    switch (state)
    {
    case s_init:
        if (hx711_init(&dev1) == ESP_OK)
        {
            // clear error flag
            error = false;
            // set initialized flag
            initialized = true;
            // go to HX711 state
            state = s_wait;
        }
        // else {
        //     state = s_error;
        // }
        break;

    case s_wait:
        if (hx711_wait(&dev1, 500) != ESP_OK)
        {
            state = s_error;
        }
        else
        {
            state = s_read;
        }
        break;

    case s_read:
        int32_t data;
        if (hx711_read_data(&dev1, &data) != ESP_OK)
        {
            state = s_error;
        }
        else
        {
            raw_weight = data;
            state = s_aver;
        }
        break;

    case s_aver:
        if (cout < 10)
        {
            store[cout] = raw_weight;
            cout++;
            state = s_wait;
        }
        else
        {
            cout = 0;
            average = 0;
            for (int i = 0; i < 10; i++)
            {
                average += store[i];
            }
            average = average / 10;
            state = s_wait;
        }
        break;

    case s_error:
        tickcnt = get_tickcnt();
        if (is_tickcnt_elapsed(tickcnt, 500))
        {
            state = s_wait;
        }
        break;
    }
} // End of process

int32_t HX711::get_raw_weight()
{
    return raw_weight;
}
double HX711::get_units()
{
    return (raw_weight - OFFSET) * m;
}
void HX711::set_scale(double scale)
{
    SCALE = scale;
}
void HX711::set_offset(int offset)
{
    OFFSET = offset;
}
void HX711::tare()
{
    OFFSET = average;
}
void HX711::calibrate()
{
    m = (SCALE) / (raw_weight - OFFSET);
}

/*=================================================================
=================================================================*/
uint32_t HX711::get_time_ms()
{
    struct timeval time;
    gettimeofday(&time, 0);
    return time.tv_sec * 1000 + time.tv_usec / 1000;
}

uint32_t HX711::read_raw(gpio_num_t dout, gpio_num_t pd_sck, hx711_gain_t gain)
{
    portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
    portENTER_CRITICAL(&mux);

    // read data
    uint32_t data = 0;
    for (size_t i = 0; i < 24; i++)
    {
        gpio_set_level(pd_sck, 1);
        ets_delay_us(1);
        data |= gpio_get_level(dout) << (23 - i);
        gpio_set_level(pd_sck, 0);
        ets_delay_us(1);
    }

    // config gain + channel for next read
    for (size_t i = 0; i <= gain; i++)
    {
        gpio_set_level(pd_sck, 1);
        ets_delay_us(1);
        gpio_set_level(pd_sck, 0);
        ets_delay_us(1);
    }

    portEXIT_CRITICAL(&mux);

    return data;
}

esp_err_t HX711::hx711_init(hx711_t *dev)
{
    CHECK_ARG(dev);

    CHECK(gpio_set_direction(dev->dout, GPIO_MODE_INPUT));
    CHECK(gpio_set_direction(dev->pd_sck, GPIO_MODE_OUTPUT));

    CHECK(hx711_power_down(dev, false));

    return hx711_set_gain(dev, dev->gain);
}

esp_err_t HX711::hx711_power_down(hx711_t *dev, bool down)
{
    CHECK_ARG(dev);

    CHECK(gpio_set_level(dev->pd_sck, down));
    vTaskDelay(1);

    return ESP_OK;
}

esp_err_t HX711::hx711_set_gain(hx711_t *dev, hx711_gain_t gain)
{
    CHECK_ARG(dev);
    CHECK_ARG(gain <= HX711_GAIN_A_64);

    CHECK(hx711_wait(dev, 200)); // 200 ms timeout

    read_raw(dev->dout, dev->pd_sck, gain);
    dev->gain = gain;

    return ESP_OK;
}

esp_err_t HX711::hx711_is_ready(hx711_t *dev, bool *ready)
{
    CHECK_ARG(dev);
    CHECK_ARG(ready);

    *ready = !gpio_get_level(dev->dout);

    return ESP_OK;
}

esp_err_t HX711::hx711_wait(hx711_t *dev, size_t timeout_ms)
{
    uint32_t started = get_time_ms();
    while (get_time_ms() - started < timeout_ms)
    {
        if (!gpio_get_level(dev->dout))
            return ESP_OK;
        vTaskDelay(1);
    }

    return ESP_ERR_TIMEOUT;
}

esp_err_t HX711::hx711_read_data(hx711_t *dev, int32_t *data)
{
    CHECK_ARG(dev);
    CHECK_ARG(data);

    uint32_t raw = read_raw(dev->dout, dev->pd_sck, dev->gain);
    if (raw & 0x800000)
        raw |= 0xff000000;
    *data = (int32_t)raw;

    return ESP_OK;
}