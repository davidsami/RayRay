// David Sami 2015

#ifndef PARSERSYMBOLS_H
#define PARSERSYMBOLS_H

#include "Parser.h"

// Reducing copy and paste in declaration
// They'll all be the same anyway, and implemented in the cpp file
#define DEFINE_PARSER_SYMBOL(S) \
class S : public Symbol { \
public: \
    virtual bool CheckSymbol(const std::vector<std::string>& aParameters); \
    virtual ParserResult ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput); \
}

DEFINE_PARSER_SYMBOL(CommentSymbol);
DEFINE_PARSER_SYMBOL(SettingSymbol);
DEFINE_PARSER_SYMBOL(TransformSymbol);
DEFINE_PARSER_SYMBOL(CameraSymbol);
DEFINE_PARSER_SYMBOL(MaterialSymbol);
DEFINE_PARSER_SYMBOL(VertexSymbol);
DEFINE_PARSER_SYMBOL(LightSymbol);
DEFINE_PARSER_SYMBOL(ColourSymbol);
DEFINE_PARSER_SYMBOL(SphereSymbol);
DEFINE_PARSER_SYMBOL(FaceSymbol);

class ObjSymbol : public Symbol {
public:
    ObjSymbol(std::string aDirectory):mDirectory(aDirectory) {}
    virtual bool CheckSymbol(const std::vector<std::string>& aParameters);
    virtual ParserResult ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput);
private:
    std::string mDirectory;
};

// The catchall symbol for OBJ
// Don't want to implement all OBJ features yet
DEFINE_PARSER_SYMBOL(MiscSymbol);

#endif
