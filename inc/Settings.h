// David Sami 2015

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <map>

class Settings {
public:
    Settings() = default;

    // Constants for ease
    static const std::string kXPixels;
    static const std::string kYPixels;
    static const std::string kFOV;
    static const std::string kXCamera;
    static const std::string kYCamera;
    static const std::string kZCamera;
    static const std::string kYawCamera;
    static const std::string kPitchCamera;
    static const std::string kRollCamera;
    static const std::string kAmbientLight;
    static const std::string kAmbientIntensity;
    static const std::string kBackgroundColour;
    static const std::string kOutputFile;

    // If setting exists, will replace
    void AddSetting(const std::string& aKey, const std::string& aValue);

    // Parse setting for type
    // Returns true for success, false for failure
    bool GetString(const std::string& aKey, std::string* aOut);
    bool GetInt(const std::string& aKey, int* aOut);
    bool GetUnsigned(const std::string& aKey, uint32_t* aOut);
    bool GetDouble(const std::string& aKey, double* aOut);

private:
    std::map<std::string, std::string> mSettings;
    static const std::map<std::string, std::string> kDefaults;
};

#endif
