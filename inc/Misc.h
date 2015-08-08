// David Sami 2015

#ifndef MISC_H
#define MISC_H

#include <vector>
#include <string>
#include <sstream>

namespace Misc {
    std::vector<std::string> SplitLine(std::stringstream& aLine, char aDelim);
    bool GetInt(const std::string& aString, int* aOut);
    bool GetUnsigned(const std::string& aString, uint32_t* aOut);
    bool GetDouble(const std::string& aString, double* aOut);
};

#endif
