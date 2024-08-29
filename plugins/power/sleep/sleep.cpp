#include "esp_system.h"
#include "esp_sleep.h"
#include "kidbright32.h"
#include "sleep.h"

#undef __DEBUG__
//#define __DEBUG__

#ifdef __DEBUG__
#include "esp_log.h"
const char *TAG = "sleep";
#endif

SLEEP::SLEEP(void) {
	//
}

void SLEEP::init(void) {
#ifdef __DEBUG__
	esp_log_level_set(TAG, ESP_LOG_VERBOSE);
#endif

	state = s_detect;
}

int SLEEP::prop_count(void) {
	// not supported
	return 0;
}

bool SLEEP::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool SLEEP::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool SLEEP::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool SLEEP::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool SLEEP::prop_write(int index, char *value) {
	// not supported
	return false;
}

void SLEEP::process(Driver *drv) {
	switch (state) {
		case s_detect:
			// clear error flag
			error = false;
			// set initialized flag
			initialized = true;

			// go to idle state
			state = s_idle;
			break;

		case s_idle:
			//			
			break;
	}
}

void SLEEP::deep_gpio(gpio_num_t gpio) {
	#ifdef __DEBUG__
		ESP_LOGI(TAG, "enabling EXT0 wakeup on pins GPIO%d", gpio);
	#endif

	if (esp_sleep_enable_ext0_wakeup(gpio, 0) == ESP_OK) {
		#ifdef __DEBUG__
			ESP_LOGI(TAG, "%s", "esp_sleep_enable_ext0_wakeup setup ok.");
		#endif
	}

	#ifdef __DEBUG__
		ESP_LOGI(TAG, "%s", "start deep sleep...");
	#endif
	esp_deep_sleep_start();
}

void SLEEP::deep_timeout(uint32_t timeout_ms) {
	#ifdef __DEBUG__
		ESP_LOGI(TAG, "enabling wakeup on timeout %d ms", timeout_ms);
	#endif
	
	// esp_err_t esp_sleep_enable_timer_wakeup(uint64_t time_in_us);
	if (esp_sleep_enable_timer_wakeup(timeout_ms * 1000) == ESP_OK) {
		#ifdef __DEBUG__
			ESP_LOGI(TAG, "%s", "esp_sleep_enable_timer_wakeup setup ok.");
		#endif
	}
	
	#ifdef __DEBUG__
		ESP_LOGI(TAG, "%s", "start deep sleep...");
	#endif
	esp_deep_sleep_start();
}
		
void SLEEP::deep_gpio_timeout(gpio_num_t gpio, uint32_t timeout_ms) {	
	#ifdef __DEBUG__
		ESP_LOGI(TAG, "enabling EXT0 wakeup on pins GPIO%d", gpio);
	#endif
	if (esp_sleep_enable_ext0_wakeup(gpio, 0) == ESP_OK) {		
		#ifdef __DEBUG__
			ESP_LOGI(TAG, "%s", "esp_sleep_enable_ext0_wakeup setup ok.");
		#endif
	}

	#ifdef __DEBUG__
		ESP_LOGI(TAG, "enabling wakeup on timeout %d ms", timeout_ms);
	#endif
	// esp_err_t esp_sleep_enable_timer_wakeup(uint64_t time_in_us);
	if (esp_sleep_enable_timer_wakeup(timeout_ms * 1000) == ESP_OK) {
		#ifdef __DEBUG__
			ESP_LOGI(TAG, "%s", "esp_sleep_enable_timer_wakeup setup ok.");
		#endif
	}
	
	#ifdef __DEBUG__
		ESP_LOGI(TAG, "%s", "start deep sleep...");
	#endif
	esp_deep_sleep_start();	
}
