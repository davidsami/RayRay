// David Sami 2015

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "Scene.h"

enum ParserResult{
    // Success
    kParseSuccess,

    // Error with opening file
    kParseFileError,

    // Unknown symbol at start of line
    kParseUnknownSymbol,

    // Line uses non-existant object
    kParseNonExistantReference,

    // Wrong parameter type
    kParseMalformedLine,

    // Global setting error
    kParseGlobalError,

    // Unhandled symbol
    kParseUnhandled,

    // Symbol correctly ignored
    kParseIgnore,

    // Unknown error
    kParseUnknown,
};

struct ParserCollection {
    // Intermediate collections
    std::vector<Math::Transform> mTransforms;
    std::vector<Material> mMaterials;
    std::vector<Colour> mColours;

    Scene mScene;
};

class Symbol {
public:
    virtual bool CheckSymbol(const std::vector<std::string>& aParameters)=0;
    virtual ParserResult ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput)=0;
protected:
    static bool GetInt(const std::string& aString, int* aOut);
    static bool GetUnsigned(const std::string& aString, uint32_t* aOut);
    static bool GetDouble(const std::string& aString, double* aOut);
};

class Parser {
public:
    Parser();
    ParserResult ParseRayFile(const std::string& aFilename, ParserCollection& aOutput);
    static std::vector<std::string> SplitLine(std::stringstream& aLine, char aDelim);
private:
    std::vector<std::unique_ptr<Symbol>> mSymbolParsers;
};

#endif
