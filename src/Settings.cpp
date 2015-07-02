// David Sami 2015

#include "Settings.h"

const std::string Settings::kXPixels = "x_pixels";
const std::string Settings::kYPixels = "y_pixels";

const std::string Settings::kFOV = "fov";
const std::string Settings::kXCamera = "x_camera";
const std::string Settings::kYCamera = "y_camera";
const std::string Settings::kZCamera = "z_camera";
const std::string Settings::kYawCamera = "yaw_camera";
const std::string Settings::kPitchCamera = "pitch_camera";
const std::string Settings::kRollCamera = "roll_camera";

const std::map<std::string, std::string> Settings::kDefaults = {
    {Settings::kXPixels, "640"},
    {Settings::kYPixels, "480"},
    {Settings::kFOV, "90"},
    {Settings::kXCamera, "0"},
    {Settings::kYCamera, "0"},
    {Settings::kZCamera, "0"},
    {Settings::kYawCamera, "0"},
    {Settings::kPitchCamera, "0"},
    {Settings::kRollCamera, "0"},
};

void Settings::AddSetting(const std::string& aKey, const std::string& aValue){
    mSettings[aKey] = aValue;
}

bool Settings::GetString(const std::string& aKey, std::string* aOut){
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

bool Settings::GetInt(const std::string& aKey, int* aOut){
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

bool Settings::GetUnsigned(const std::string& aKey, uint32_t* aOut){
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

bool Settings::GetDouble(const std::string& aKey, double* aOut){
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

