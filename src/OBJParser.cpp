// David Sami 2015

#include "OBJParser.h"
#include "ParserSymbols.h"

OBJParser::OBJParser(const std::string& aFilename):
    Parser(aFilename)
{
    mSymbolParsers.push_back(std::make_unique<CommentSymbol>());
    mSymbolParsers.push_back(std::make_unique<VertexSymbol>());
    mSymbolParsers.push_back(std::make_unique<FaceSymbol>());
    mSymbolParsers.push_back(std::make_unique<MiscSymbol>());
}
