#include "Semver.hpp"


#ifdef ESP32
#include <esp_log.h>
#else
#ifdef DEBUG
#define ESP_LOGD printf
#else
#define ESP_LOGD
#endif
#endif


static const char *TAG = "Semver";

Semver::Semver(const std::string &version)
    : _version_s(version) {
    ESP_LOGD(TAG, "Semver(%p)", static_cast<void *>(this));

    int32_t cres;

    semver_init(&_version, _version_s.c_str());

    cres = semver_parse(&_version);

    if (cres != SEMVER_PARSE_OK) {
        ESP_LOGD(TAG, "version parse failed: %d", cres);
        throw std::runtime_error("version check failed");
    }
}

std::string Semver::string() {
    char s[64];

    snprintf(s, sizeof(s), "%d.%d.%d", _version.major, _version.minor, _version.patch);

    return std::string(s);
}

Semver::~Semver() {
    ESP_LOGD(TAG, "~Semver(%p)", static_cast<void *>(this));
    semver_free(&_version);
}
