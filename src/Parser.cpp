// David Sami 2015

#include "Parser.h"
#include "ParserSymbols.h"

Parser::Parser(const std::string& aFilename):
    mFilename(aFilename)
{
}

ParserResult Parser::ParseFile(Scene& aOutput){
    std::fstream fin(mFilename, std::ios_base::in);

    std::cout << "Opening file: " << mFilename << std::endl;
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
            ret = kParseIgnore;
        }

        if(ret != ParserResult::kParseSuccess && ret != ParserResult::kParseIgnore){
            std::cout << "Error on line " << counter << ": " << line << std::endl;
            std::cout << "Error: " << ret << std::endl;
            return ret;
        }
        counter++;
    }

    std::cout << "Results:" << std::endl;
    std::cout << "    Transforms: " << aOutput.mTransforms.size() << std::endl;
    std::cout << "    Materials: " << aOutput.mMaterials.size() << std::endl;
    std::cout << "    Vertices: " << aOutput.mVertices.size() << std::endl;
    std::cout << "    Colours: " << aOutput.mColours.size() << std::endl;
    std::cout << "    Shapes: " << aOutput.mObjects.size() << std::endl;
    std::cout << "    Lights: " << aOutput.mLights.size() << std::endl;

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


