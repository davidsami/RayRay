// David Sami 2015

#include "Misc.h"
#include "Parser.h"
#include "ParserSymbols.h"

Parser::Parser(const std::string& aFilename, uint32_t aPrintIndent):
    mFilename(aFilename),
    mIndentString(std::string(aPrintIndent * 4, ' ')),
    mPrintIndent(aPrintIndent)
{
}

ParserResult Parser::ParseFile(Scene& aOutput){
    std::fstream fin(mFilename, std::ios_base::in);

    std::cout << mIndentString << "Opening file: " << mFilename << std::endl;
    if(!fin.is_open())
        return kParseFileError;

    std::string line;
    int counter = 1;
    while(getline(fin, line)){
        std::stringstream linestream(line);
        std::vector<std::string> pieces = Misc::SplitLine(linestream, ' ');

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
            std::cout << mIndentString << "Error on line " << counter << ": " << line << std::endl;
            std::cout << mIndentString << "Error: " << ret << std::endl;
            return ret;
        }
        counter++;
    }

    std::cout << mIndentString << "Results:" << std::endl;
    std::cout << mIndentString << "Transforms: " << aOutput.mTransforms.size() << std::endl;
    std::cout << mIndentString << "Materials: " << aOutput.mMaterials.size() << std::endl;
    std::cout << mIndentString << "Vertices: " << aOutput.mVertices.size() << std::endl;
    std::cout << mIndentString << "Colours: " << aOutput.mColours.size() << std::endl;
    std::cout << mIndentString << "Shapes: " << aOutput.mObjects.size() << std::endl;
    std::cout << mIndentString << "Lights: " << aOutput.mLights.size() << std::endl;

    return kParseSuccess;
}

