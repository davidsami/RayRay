// David Sami 2015

#include "Misc.h"
#include "Settings.h"

const std::string Settings::kAmbientIntensity = "ambient_intensity";
const std::string Settings::kBackgroundColour = "background_colour";
const std::string Settings::kOutputFile = "output_file";
const std::string Settings::kNumThreads = "num_threads";
const std::string Settings::kMaxReflectBounces = "max_reflect_bounces";

const std::map<std::string, std::string> Settings::kDefaults = {
    {Settings::kAmbientIntensity, "0"},
    {Settings::kBackgroundColour, "0,0,0"},
    {Settings::kOutputFile, "out.ppm"},
    {Settings::kNumThreads, "1"},
    {Settings::kMaxReflectBounces, "5"},
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
    std::string val;

    result = GetString(aKey, &val);

    if(result)
        result = Misc::GetInt(val, aOut);

    return result;
}

bool Settings::GetUnsigned(const std::string& aKey, uint32_t* aOut) const{
    bool result = true;
    std::string val;

    result = GetString(aKey, &val);

    if(result)
        result = Misc::GetUnsigned(val, aOut);

    return result;
}

bool Settings::GetDouble(const std::string& aKey, double* aOut) const{
    bool result = true;
    std::string val;

    result = GetString(aKey, &val);

    if(result)
        result = Misc::GetDouble(val, aOut);

    return result;
}

bool Settings::GetColour(const std::string& aKey, Colour* aOut) const{
    bool result = true;
    std::string val;

    result = GetString(aKey, &val);

    if(result){
        std::stringstream str(val);
        std::vector<std::string> split = Misc::SplitLine(str, ',');
        if(split.size() != 3)
            result = false;
        
        double r, g, b;
        if(result)
            result = Misc::GetDouble(split[0], &r);

        if(result)
            result = Misc::GetDouble(split[1], &g);

        if(result)
            result = Misc::GetDouble(split[2], &b);

        if(result)
            *aOut = Colour(r, g, b);
    }

    return result;
}
