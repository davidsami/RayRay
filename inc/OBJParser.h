// David Sami 2015

#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "Parser.h"

class OBJParser: public Parser {
public:
    OBJParser(const std::string& aFilename, uint32_t aPrintIndent);
};

#endif
