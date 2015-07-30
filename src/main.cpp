// David Sami 2015

#include <iostream>
#include "RayRay.h"
#include "Settings.h"

#include "OBJParser.h"

int main(int argc, char* argv[]){
    ParserOBJPrimitive obj;
    ParserResult result = OBJParser::ParseOBJFile("test.obj", obj);
    /*
    std::unique_ptr<Scene> s(new Scene);
    RayRay r(std::move(s));
    r.Run();
    */
    return 0;
} 

