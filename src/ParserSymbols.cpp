// David Sami 2015

#include <iostream>
#include "ParserSymbols.h"

#define REQUIRE_PARSE_SUCCESS(cond) \
    do { \
        if(!cond) \
            return kParseMalformedLine; \
    } while(0)

bool CommentSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0][0] == '#');
}

ParserResult CommentSymbol::ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput){
    return kParseSuccess;
}


bool TransformSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("t") == 0);
}

ParserResult TransformSymbol::ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput){
    std::cout << "Transform line" << std::endl;
    if(aParameters.size() != 10){
        return kParseMalformedLine;
    }
    Math::Transform t;

    double x, y, z;
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[1], &x));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[2], &y));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[3], &z));
    t  = Math::Transform::Translation(x, y, z);

    double xs, ys, zs;
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[4], &xs));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[5], &ys));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[6], &zs));
    t *= Math::Transform::Scaling(xs, ys, zs);

    double yaw, pitch, roll;
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[7], &yaw));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[8], &pitch));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[9], &roll));
    t *= Math::Transform::Rotation(yaw, pitch, roll);

    aOutput.mTransforms.push_back(t);
    return kParseSuccess;
}


bool CameraSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("cam") == 0);
}

ParserResult CameraSymbol::ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput){
    std::cout << "Camera line" << std::endl;
    if(aOutput.mScene.mCamera != NULL){
        return kParseGlobalError;
    }

    if(aParameters.size() != 5){
        return kParseMalformedLine;
    }

    uint32_t transformIdx;
    REQUIRE_PARSE_SUCCESS(Symbol::GetUnsigned(aParameters[1], &transformIdx));
    if(transformIdx >= aOutput.mTransforms.size())
        return kParseNonExistantReference;

    double fov;
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[2], &fov));

    uint32_t width, height;
    REQUIRE_PARSE_SUCCESS(Symbol::GetUnsigned(aParameters[3], &width));
    REQUIRE_PARSE_SUCCESS(Symbol::GetUnsigned(aParameters[4], &height));

    aOutput.mScene.mCamera = std::make_unique<Camera>(aOutput.mTransforms[transformIdx], fov, width, height);

    return kParseSuccess;
}


bool MaterialSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("mat") == 0);
}

ParserResult MaterialSymbol::ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput){
    std::cout << "Material line" << std::endl;
    if(aParameters.size() != 5){
        return kParseMalformedLine;
    }

    double se, diffuse, specular, shininess;
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[1], &se));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[2], &diffuse));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[3], &specular));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[4], &shininess));

    aOutput.mMaterials.push_back(Material(se, diffuse, specular, shininess));

    return kParseSuccess;
}


bool VertexSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("v") == 0);
}

ParserResult VertexSymbol::ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput){
    std::cout << "Vertex line" << std::endl;
    if(aParameters.size() != 4){
        return kParseMalformedLine;
    }

    double x, y, z;
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[1], &x));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[2], &y));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[3], &z));

    Math::Point p(x,y,z);
    aOutput.mScene.mVertices.push_back(std::make_shared<Vertex>(p));

    return kParseSuccess;
}


bool LightSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("l") == 0);
}

ParserResult LightSymbol::ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput){
    std::cout << "Light line" << std::endl;
    if(aParameters.size() != 5){
        return kParseMalformedLine;
    }

    double intensity, x, y, z;
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[1], &intensity));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[2], &x));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[3], &y));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[4], &z));

    Math::Point p(x,y,z);
    aOutput.mScene.mLights.push_back(std::make_unique<Light>(intensity, p));

    return kParseSuccess;
}


bool ColourSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("c") == 0);
}

ParserResult ColourSymbol::ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput){
    std::cout << "Colour line" << std::endl;
    if(aParameters.size() != 4){
        return kParseMalformedLine;
    }

    double r, g, b;
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[1], &r));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[2], &g));
    REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[3], &b));

    aOutput.mColours.push_back(Colour(r, g, b));

    return kParseSuccess;
}


bool SphereSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("sph") == 0);
}

ParserResult SphereSymbol::ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput){
    std::cout << "Sphere line" << std::endl;
    if(aParameters.size() != 4){
        return kParseMalformedLine;
    }

    uint32_t mat, col, trans;
    REQUIRE_PARSE_SUCCESS(Symbol::GetUnsigned(aParameters[1], &mat));
    if(mat >= aOutput.mMaterials.size())
        return kParseNonExistantReference;
    Material material = aOutput.mMaterials[mat];

    REQUIRE_PARSE_SUCCESS(Symbol::GetUnsigned(aParameters[2], &col));
    if(col >= aOutput.mColours.size())
        return kParseNonExistantReference;
    Colour colour = aOutput.mColours[col];

    REQUIRE_PARSE_SUCCESS(Symbol::GetUnsigned(aParameters[3], &trans));
    if(trans >= aOutput.mTransforms.size())
        return kParseNonExistantReference;
    Math::Transform transform = aOutput.mTransforms[trans];

    // TODO: Fix later
    //aOutput.mScene.mObjects.push_back(std::make_unique<Sphere>(material, colour, ));
    return kParseSuccess;
}


bool FaceSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("f") == 0);
}

ParserResult FaceSymbol::ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput){
    std::cout << "Face line" << std::endl;
    if(aParameters.size() != 4){
        return kParseMalformedLine;
    }

    std::array<std::shared_ptr<Vertex>,3> vertices;

    for (int i = 0; i < 3; i++){
        double vertIdx;
        REQUIRE_PARSE_SUCCESS(Symbol::GetDouble(aParameters[i+1], &vertIdx));
        if(vertIdx >= aOutput.mScene.mVertices.size())
            return kParseNonExistantReference;

        vertices[i] = aOutput.mScene.mVertices[vertIdx];
    }

    aOutput.mScene.mObjects.push_back(std::make_unique<Triangle>(vertices));

    return kParseSuccess;
}


bool ObjSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("obj") == 0);
}

ParserResult ObjSymbol::ParseLine(const std::vector<std::string>& aParameters, ParserCollection& aOutput){
    std::cout << "OBJ line" << std::endl;
    return kParseSuccess;
}

