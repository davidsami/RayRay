// David Sami 2015

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <map>

class Settings {
public:
    Settings() = default;

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
};

#endif
