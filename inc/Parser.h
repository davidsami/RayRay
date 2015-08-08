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
    kParseSuccess = 1,

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

class Symbol {
public:
    virtual bool CheckSymbol(const std::vector<std::string>& aParameters)=0;
    virtual ParserResult ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput)=0;
};

class Parser {
public:
    Parser(const std::string& aFilename, uint32_t aPrintIndent);
    ParserResult ParseFile(Scene& aOutput);
protected:
    std::vector<std::unique_ptr<Symbol>> mSymbolParsers;
    std::string mFilename;
    std::string mIndentString;
    uint32_t mPrintIndent;
};

#endif
