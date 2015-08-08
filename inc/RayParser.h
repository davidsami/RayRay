// David Sami 2015

#ifndef RAYPARSER_H
#define RAYPARSER_H

#include "Parser.h"

class RayParser: public Parser {
public:
    RayParser(const std::string& aFilename, uint32_t aPrintIndent);
};

#endif
