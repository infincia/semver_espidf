#include "Semver.hpp"

#include <sstream>


#ifdef ESP32
#include <esp_log.h>
#else
#ifdef DEBUG
#define ESP_LOGD( tag, format, ... ) printf( tag, format, ##__VA_ARGS__ )
#else
#define ESP_LOGD( tag, format, ... )
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
    std::stringbuf strbuf;
    std::ostream os(&strbuf);
    os << _version.major;
    os << ".";
    os << _version.minor;
    os << ".";
    os << _version.patch;

    if (_version.is_prerelease) {
        os << "-";
        os << _version.prerelease;
    }
    return strbuf.str();
}

Semver::~Semver() {
    ESP_LOGD(TAG, "~Semver(%p)", static_cast<void *>(this));
    semver_free(&_version);
}
