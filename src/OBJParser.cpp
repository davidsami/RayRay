// David Sami 2015

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "OBJParser.h"
#include "Triangle.h"

ParserResult OBJParser::ParseOBJFile(const std::string& aFilename, ParserOBJPrimitive& aResult){
    std::fstream fin(aFilename, std::ios_base::in);

    std::cout << "Opening OBJ file: " << aFilename << std::endl;
    if(!fin.is_open())
        return kParseFileError;

    std::string line;
    while(getline(fin, line)){
        std::stringstream linestream(line);
        std::string piece;

        if(!getline(linestream, piece, ' ')){
            // empty line
            continue;
        }

        OBJKeyword keyType = ParseKeyword(piece);
        ParserResult ret = kParseSuccess;
        switch(keyType){
            case kVertex:
                ret = ParseVertex(linestream, aResult);
                break;
            case kFace:
                ret = ParseFace(linestream, aResult);
                break;
            case kComment:
            case kNone:
            case kUnhandled:
                ret = ParserResult::kParseIgnore;
                break;
            case kUnknown:
            default:
                ret = ParserResult::kParseUnknown;
                break;
        }

        if(ret != ParserResult::kParseSuccess && ret != ParserResult::kParseIgnore){
            return ret;
        }
    }

    return kParseSuccess;
}

OBJKeyword OBJParser::ParseKeyword(const std::string& aString){
    if(aString.compare("") == 0)
        return OBJKeyword::kNone;
    else if(aString[0] == '#')
        return OBJKeyword::kComment;
    else if(aString.compare("v")==0)
        return OBJKeyword::kVertex;
    else if(aString.compare("f")==0)
        return OBJKeyword::kFace;

    // Just return unhandled for now.
    // Will support the rest of OBJ standard later, possibly
    return OBJKeyword::kUnhandled;
}

ParserResult OBJParser::ParseVertex(std::stringstream& aStream, ParserOBJPrimitive& aResult){
    std::vector<std::string> pieces = Parser::SplitLine(aStream, ' ');

    std::vector<double> coordinates;
    for(auto it = pieces.begin(); it != pieces.end(); it++){
        try{
            double a;
            a = stod(*it);
            coordinates.push_back(a);
        }catch(std::exception e){
            return kParseMalformedLine;
        }
    }

    if(coordinates.size() == 3){
        Math::Point p(coordinates[0], coordinates[1], coordinates[2]);
        std::shared_ptr<Vertex> v(new Vertex(p));
        aResult.mVertices.push_back(v);
        return kParseSuccess;
    } else {
        return kParseMalformedLine;
    }
}

ParserResult OBJParser::ParseFace(std::stringstream& aStream, ParserOBJPrimitive& aResult){
    std::vector<std::string> pieces = Parser::SplitLine(aStream, ' ');

    std::vector<uint32_t> indices;
    for(auto it = pieces.begin(); it != pieces.end(); it++){
        try{
            int a;
            a = stoul(*it);
            indices.push_back(a);
        }catch(std::exception e){
            return kParseMalformedLine;
        }
    }

    if(indices.size() == 3){
        std::array<std::shared_ptr<Vertex>,3> vertices;
        for(int i = 0; i < 3; i++){
            if(indices[i] > aResult.mVertices.size()){
                return kParseMalformedLine;
            } else {
                vertices[i] = aResult.mVertices[indices[i] - 1];
            }
        }
        std::unique_ptr<Triangle> t(new Triangle(vertices));
        aResult.mObjects.push_back(std::move(t));
        return kParseSuccess;
    } else {
        return kParseMalformedLine;
    }
}
