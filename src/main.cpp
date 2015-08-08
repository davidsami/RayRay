// David Sami 2015

#include <iostream>
#include "RayRay.h"
#include "Settings.h"

#include "OBJParser.h"

int main(int argc, char* argv[]){
    Scene scene;

    if(argc >= 2) {
        Parser parse = Parser(std::string(argv[1]));
        ParserResult result;
        result = parse.ParseRayFile(scene);

        if(result == kParseSuccess){
            RayRay ray(scene);
            ray.Run();
        } else {
            std::cout << "Parse Error" << std::endl;
        }
    } else {
        std::cout << "No file Specified" << std::endl;
    }
    return 0;
} 

