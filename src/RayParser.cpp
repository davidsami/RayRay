// David Sami 2015

#include "ParserSymbols.h"
#include "RayParser.h"

RayParser::RayParser(const std::string& aFilename):
    Parser(aFilename)
{
    std::string directory;
    size_t slashDirPos = aFilename.find_last_of('/');
    if(slashDirPos == std::string::npos)
        directory = "";
    else
        directory = aFilename.substr(0, slashDirPos+1);

    mSymbolParsers.push_back(std::make_unique<CommentSymbol>());
    mSymbolParsers.push_back(std::make_unique<SettingSymbol>());
    mSymbolParsers.push_back(std::make_unique<TransformSymbol>());
    mSymbolParsers.push_back(std::make_unique<CameraSymbol>());
    mSymbolParsers.push_back(std::make_unique<MaterialSymbol>());
    mSymbolParsers.push_back(std::make_unique<VertexSymbol>());
    mSymbolParsers.push_back(std::make_unique<LightSymbol>());
    mSymbolParsers.push_back(std::make_unique<ColourSymbol>());
    mSymbolParsers.push_back(std::make_unique<SphereSymbol>());
    mSymbolParsers.push_back(std::make_unique<FaceSymbol>());
    mSymbolParsers.push_back(std::make_unique<ObjSymbol>(directory));
}
