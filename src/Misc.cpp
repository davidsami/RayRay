// David Sami 2015

#include "Misc.h"

std::vector<std::string> Misc::SplitLine(std::stringstream& aLine, char aDelim){
    std::vector<std::string> out;

    std::string piece;
    while(getline(aLine, piece, aDelim)){
        if(!piece.empty())
            out.push_back(piece);
    }

    return out;
}

bool Misc::GetInt(const std::string& aString, int* aOut){
    bool result = true;
    int out;

    try{
        out = stoi(aString);
    } catch (std::exception e){
        result = false;
    }

    if(result)
        *aOut = out;

    return result;
}

bool Misc::GetUnsigned(const std::string& aString, uint32_t* aOut){
    bool result = true;
    uint32_t out;

    try{
        out = stoul(aString);
    } catch (std::exception e){
        result = false;
    }

    if(result)
        *aOut = out;

    return result;
}

bool Misc::GetDouble(const std::string& aString, double* aOut){
    bool result = true;
    double out;

    try{
        out = stod(aString);
    } catch (std::exception e){
        result = false;
    }

    if(result)
        *aOut = out;

    return result;
}

