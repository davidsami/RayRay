// David Sami 2015

#include "Settings.h"

void Settings::AddSetting(const std::string& aKey, const std::string& aValue){
    mSettings[aKey] = aValue;
}

bool Settings::GetString(const std::string& aKey, std::string* aOut){
    bool result = true;
    std::string out;

    try{
        out = mSettings.at(aKey);
    } catch (std::exception e){
        result = false;
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

