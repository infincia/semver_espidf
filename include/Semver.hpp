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
        bool pre_cmp = (rhs._version.is_prerelease && _version.is_prerelease);

        // prereleases are always considered less than normal releases, so assign numeric
        // values to compare in case only one of them is a prerelease
        int lhs_pre = 1;        
        if (_version.is_prerelease) {
            lhs_pre = 0;
        }

        int rhs_pre = 1;
        if (rhs._version.is_prerelease) {
            rhs_pre = 0;
        }

        return _version.major < rhs._version.major ||
               _version.minor < rhs._version.minor ||
               _version.patch < rhs._version.patch ||
                // if both are prereleases we compare the strings, otherwise we skip it to avoid
                // dereferencing a NULL pointer.
                //
                // if only one of them is a prerelease we always treat that one as lower 
                // regardless of the prerelease value itself
               (pre_cmp ? (strcmp(_version.prerelease, rhs._version.prerelease) < 0) : (lhs_pre < rhs_pre));
    }

    inline bool operator >(const Semver& rhs) const& {
        return rhs < *this;
    }

    inline bool operator ==(const Semver& rhs) const& {
        bool pre_cmp = (rhs._version.is_prerelease && _version.is_prerelease);

        // prereleases are always considered less than normal releases, so assign numeric
        // values to compare in case only one of them is a prerelease
        int lhs_pre = 1;        
        if (_version.is_prerelease) {
            lhs_pre = 0;
        }

        int rhs_pre = 1;
        if (rhs._version.is_prerelease) {
            rhs_pre = 0;
        }
        
        return _version.major == rhs._version.major && 
               _version.minor == rhs._version.minor && 
               _version.patch == rhs._version.patch &&
                // if both are prereleases we compare the strings, otherwise we skip it to avoid
                // dereferencing a NULL pointer.
                //
                // if they are not both prereleases, the only time lhs_pre and rhs_pre will be equal
                // is if they are both zero
               (pre_cmp ? (strcmp(_version.prerelease, rhs._version.prerelease) == 0) : (lhs_pre == rhs_pre));
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
