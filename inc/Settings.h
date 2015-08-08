// David Sami 2015

#ifndef SETTINGS_H
#define SETTINGS_H

#include <map>
#include <string>
#include "Colour.h"

class Settings {
public:
    Settings() = default;

    // Constants for ease
    static const std::string kAmbientIntensity;
    static const std::string kBackgroundColour;
    static const std::string kOutputFile;
    static const std::string kNumThreads;
    static const std::string kMaxReflectBounces;

    // If setting exists, will replace
    void AddSetting(const std::string& aKey, const std::string& aValue);

    // Parse setting for type
    // Returns true for success, false for failure
    bool GetString(const std::string& aKey, std::string* aOut) const;
    bool GetInt(const std::string& aKey, int* aOut) const;
    bool GetUnsigned(const std::string& aKey, uint32_t* aOut) const;
    bool GetDouble(const std::string& aKey, double* aOut) const;
    bool GetColour(const std::string& aKey, Colour* aOut) const;

private:
    std::map<std::string, std::string> mSettings;
    static const std::map<std::string, std::string> kDefaults;
};

#endif
