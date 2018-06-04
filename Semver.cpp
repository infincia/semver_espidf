#include "Semver.hpp"

#include <esp_log.h>

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

Semver::~Semver() {
    ESP_LOGD(TAG, "~Semver(%p)", static_cast<void *>(this));
    semver_free(&_version);
}
