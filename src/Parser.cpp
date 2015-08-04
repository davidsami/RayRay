// David Sami 2015

#include "Parser.h"
#include "ParserSymbols.h"

Parser::Parser(){
    mSymbolParsers.push_back(std::make_unique<CommentSymbol>());
    mSymbolParsers.push_back(std::make_unique<TransformSymbol>());
    mSymbolParsers.push_back(std::make_unique<CameraSymbol>());
    mSymbolParsers.push_back(std::make_unique<MaterialSymbol>());
    mSymbolParsers.push_back(std::make_unique<VertexSymbol>());
    mSymbolParsers.push_back(std::make_unique<LightSymbol>());
    mSymbolParsers.push_back(std::make_unique<ColourSymbol>());
    mSymbolParsers.push_back(std::make_unique<SphereSymbol>());
    mSymbolParsers.push_back(std::make_unique<FaceSymbol>());
    mSymbolParsers.push_back(std::make_unique<ObjSymbol>());
}

ParserResult Parser::ParseRayFile(const std::string& aFilename, Scene& aOutput){
    std::fstream fin(aFilename, std::ios_base::in);

    std::cout << "Opening Ray file: " << aFilename << std::endl;
    if(!fin.is_open())
        return kParseFileError;

    std::string line;
    int counter = 1;
    while(getline(fin, line)){
        std::stringstream linestream(line);
        std::vector<std::string> pieces = SplitLine(linestream, ' ');

        ParserResult ret = kParseUnhandled;

        // Skip empty lines
        if(!pieces.empty()){
            for(auto it = mSymbolParsers.begin(); it != mSymbolParsers.end(); it++){
                if((*it)->CheckSymbol(pieces)){
                    ret = (*it)->ParseLine(pieces, aOutput);

                    break;
                }
            }
        } else {
            std::cout << "Ignored line" << std::endl;
            ret = kParseIgnore;
        }

        if(ret != ParserResult::kParseSuccess && ret != ParserResult::kParseIgnore){
            std::cout << "Error on line " << counter << ": " << line << std::endl;
            return ret;
        }
        counter++;
    }

    std::cout << "Transforms: " << aOutput.mTransforms.size() << std::endl;
    std::cout << "Materials: " << aOutput.mMaterials.size() << std::endl;
    std::cout << "Vertices: " << aOutput.mVertices.size() << std::endl;
    std::cout << "Colours: " << aOutput.mColours.size() << std::endl;
    std::cout << "Shapes: " << aOutput.mObjects.size() << std::endl;
    std::cout << "Lights: " << aOutput.mLights.size() << std::endl;
    return kParseSuccess;
}

std::vector<std::string> Parser::SplitLine(std::stringstream& aLine, char aDelim){
    std::vector<std::string> out;

    std::string piece;
    while(getline(aLine, piece, aDelim)){
        if(!piece.empty())
            out.push_back(piece);
    }

    return out;
}

bool Symbol::GetInt(const std::string& aString, int* aOut){
    bool result = true;
    int out;

    try{
        out = stoi(aString);
    } catch (std::exception e){
        result = false;
    }

    if(result)
        *aOut = out;

    return result;
}

bool Symbol::GetUnsigned(const std::string& aString, uint32_t* aOut){
    bool result = true;
    uint32_t out;

    try{
        out = stoul(aString);
    } catch (std::exception e){
        result = false;
    }

    if(result)
        *aOut = out;

    return result;
}

bool Symbol::GetDouble(const std::string& aString, double* aOut){
    bool result = true;
    double out;

    try{
        out = stod(aString);
    } catch (std::exception e){
        result = false;
    }

    if(result)
        *aOut = out;

    return result;
}


