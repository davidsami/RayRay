// David Sami 2015

#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <vector>
#include "Parser.h"

enum OBJKeyword{
    // Comment
    kComment,

    // Vertex data
    kVertex,

    // Elements
    kFace,

    // Unknown
    kNone,
    kUnhandled,
    kUnknown,
};

struct ParserOBJPrimitive {
    std::vector<std::shared_ptr<Vertex>> mVertices;
    std::vector<std::unique_ptr<Shape>> mObjects;
};

class OBJParser {
public:
    static ParserResult ParseOBJFile(const std::string& aFilename, ParserOBJPrimitive& aResult);
private:
    static OBJKeyword ParseKeyword(const std::string& aString);
    static ParserResult ParseVertex(std::stringstream& aStream, ParserOBJPrimitive& aResult);
    static ParserResult ParseFace(std::stringstream& aStream, ParserOBJPrimitive& aResult);
};

#endif
