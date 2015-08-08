// David Sami 2015

#include "Settings.h"

const std::string Settings::kAmbientIntensity = "ambient_intensity";
const std::string Settings::kBackgroundColour = "background_colour";
const std::string Settings::kOutputFile = "output_file";
const std::string Settings::kNumThreads = "num_threads";

const std::map<std::string, std::string> Settings::kDefaults = {
    {Settings::kAmbientIntensity, "0"},
    {Settings::kBackgroundColour, "0,0,0"},
    {Settings::kOutputFile, "out.ppm"},
};

void Settings::AddSetting(const std::string& aKey, const std::string& aValue){
    mSettings[aKey] = aValue;
}

bool Settings::GetString(const std::string& aKey, std::string* aOut) const{
    bool result = true;
    std::string out;

    // Check in settings first
    try{
        out = mSettings.at(aKey);
        result = true;
    } catch (std::exception e){
        result = false;
    }

    // If none defined, check in defaults
    if(!result){
        try{
            out = kDefaults.at(aKey);
            result = true;
        } catch (std::exception e){
            result = false;
        }
    }

    if(result)
        *aOut = out;

    return result;
}

bool Settings::GetInt(const std::string& aKey, int* aOut) const{
    bool result = true;
    int out;
    std::string val;

    result = GetString(aKey, &val);

    if(result){
        try{
            out = stoi(val);
        } catch (std::exception e){
            result = false;
        }
    }

    if(result)
        *aOut = out;

    return result;
}

bool Settings::GetUnsigned(const std::string& aKey, uint32_t* aOut) const{
    bool result = true;
    uint32_t out;
    std::string val;

    result = GetString(aKey, &val);

    if(result){
        try{
            out = stoul(val);
        } catch (std::exception e){
            result = false;
        }
    }

    if(result)
        *aOut = out;

    return result;
}

bool Settings::GetDouble(const std::string& aKey, double* aOut) const{
    bool result = true;
    double out;
    std::string val;

    result = GetString(aKey, &val);

    if(result){
        try{
            out = stod(val);
        } catch (std::exception e){
            result = false;
        }
    }

    if(result)
        *aOut = out;

    return result;
}

