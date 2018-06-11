#ifndef SEMVER_HPP_
#define SEMVER_HPP_

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <utility>
#include <exception>
#include <stdexcept>

#include "c_semver.h"

class Semver {
  public:
    Semver(const std::string &version);
    virtual ~Semver();

    std::string string();

    inline bool operator !=(const Semver& rhs) const& {
        return !(*this == rhs);
    }

    inline bool operator <(const Semver& rhs) const& {
        bool compare_pre = _version.is_prerelease || rhs._version.is_prerelease;

        return _version.major < rhs._version.major || 
               _version.minor < rhs._version.minor || 
               _version.patch < rhs._version.patch ||
               (compare_pre ? (strcmp(_version.prerelease, rhs._version.prerelease) < 0) : false);
    }

    inline bool operator >(const Semver& rhs) const& {
        return rhs < *this;
    }

    inline bool operator ==(const Semver& rhs) const& {
        bool compare_pre = _version.is_prerelease || rhs._version.is_prerelease;

        return _version.major == rhs._version.major && 
               _version.minor == rhs._version.minor && 
               _version.patch == rhs._version.patch &&
               (compare_pre ? (strcmp(_version.prerelease, rhs._version.prerelease) == 0) : true);
    }

    inline bool operator >=(const Semver& rhs) const& {
        return !(*this < rhs);
    }

    inline bool operator <=(Semver rhs) const& {
        return !(rhs < *this);
    }
  private:
    struct semver_context _version;
    
    std::string _version_s;
};

#endif /* GUARD */
