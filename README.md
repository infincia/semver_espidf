## A C library and C++ class for using semver in ESP32 IDF

A semver library packaged as an ESP IDF component for ESP32.

### Installation

#### ESP-IDF build system

Clone this repository into your `components` directory inside the project:

    cd components
    git clone https://github.com/infincia/semver_espidf.git


#### PlatformIO

Add this repository as a library in your `platformio.ini` file in the root of 
your project:

    [env:development]
    platform = espressif32
    board = esp32dev
    framework = espidf
    lib_deps =
      https://github.com/infincia/semver_espidf.git#v0.1.0

### Full example of usage

This is a bare minimum `main.cpp` file you can refer to when using this library. 

    #include <esp_err.h>
    #include <esp_log.h>
    static const char *TAG = "[MyProject]";

    #include <Semver.hpp>

    static char* CURRENT_VERSION = "1.1.0";
    static char* AVAILABLE_VERSION = "1.2.0";

    extern "C" {
    void app_main();
    }

    int app_main() {

        Semver current_version(CURRENT_VERSION);
        Semver available_version(AVAILABLE_VERSION);

        if (available_version > current_version) {
            ESP_LOGI(TAG, "update available: %s", AVAILABLE_VERSION);
        } else {
            ESP_LOGI(TAG, "no update available");
        }

        return 0;
    }
