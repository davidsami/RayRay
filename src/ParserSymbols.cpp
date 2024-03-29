// David Sami 2015

#include <iostream>
#include "Misc.h"
#include "OBJParser.h"
#include "ParserSymbols.h"
#include "Sphere.h"

// Simple macro for dealing with return of Get calls
#define REQUIRE_PARSE_SUCCESS(cond) \
    do { \
        if(!cond) \
            return kParseMalformedLine; \
    } while(0)

bool CommentSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0][0] == '#');
}

ParserResult CommentSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    return kParseSuccess;
}


bool SettingSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("set") == 0);
}

ParserResult SettingSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    if(aParameters.size() != 3){
        return kParseMalformedLine;
    }

    aOutput.mSettings.AddSetting(aParameters[1], aParameters[2]);
    return kParseSuccess;
}


bool TransformSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("t") == 0);
}

ParserResult TransformSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    if(aParameters.size() != 10){
        return kParseMalformedLine;
    }
    Math::Transform t;

    double x, y, z;
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[1], &x));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[2], &y));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[3], &z));
    t  = Math::Transform::Translation(x, y, z);

    double xs, ys, zs;
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[4], &xs));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[5], &ys));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[6], &zs));
    t *= Math::Transform::Scaling(xs, ys, zs);

    double yaw, pitch, roll;
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[7], &yaw));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[8], &pitch));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[9], &roll));
    t *= Math::Transform::Rotation(yaw, pitch, roll);

    aOutput.mTransforms.push_back(t);
    return kParseSuccess;
}


bool CameraSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("cam") == 0);
}

ParserResult CameraSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    if(aParameters.size() != 5){
        return kParseMalformedLine;
    }

    uint32_t transformIdx;
    REQUIRE_PARSE_SUCCESS(Misc::GetUnsigned(aParameters[1], &transformIdx));
    if(transformIdx > aOutput.mTransforms.size() || transformIdx < 1) 
        return kParseNonExistantReference;
    // Convert from 1 indexed
    transformIdx--;

    double fov;
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[2], &fov));

    uint32_t width, height;
    REQUIRE_PARSE_SUCCESS(Misc::GetUnsigned(aParameters[3], &width));
    REQUIRE_PARSE_SUCCESS(Misc::GetUnsigned(aParameters[4], &height));

    aOutput.mCamera.Init(aOutput.mTransforms[transformIdx], fov, width, height);

    return kParseSuccess;
}


bool MaterialSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("mat") == 0);
}

ParserResult MaterialSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    if(aParameters.size() != 6){
        return kParseMalformedLine;
    }

    double se, diffuse, specular, shininess, reflectivity;
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[1], &se));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[2], &diffuse));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[3], &specular));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[4], &shininess));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[5], &reflectivity));

    aOutput.mMaterials.push_back(Material(se, diffuse, specular, shininess, reflectivity));

    return kParseSuccess;
}


bool VertexSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("v") == 0);
}

ParserResult VertexSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    if(aParameters.size() != 4){
        return kParseMalformedLine;
    }

    double x, y, z;
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[1], &x));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[2], &y));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[3], &z));

    Math::Point p(x,y,z);
    aOutput.mVertices.push_back(Vertex(p));

    return kParseSuccess;
}


bool LightSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("l") == 0);
}

ParserResult LightSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    if(aParameters.size() != 5){
        return kParseMalformedLine;
    }

    double intensity, x, y, z;
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[1], &intensity));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[2], &x));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[3], &y));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[4], &z));

    Math::Point p(x,y,z);
    aOutput.mLights.push_back(Light(intensity, p));

    return kParseSuccess;
}


bool ColourSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("c") == 0);
}

ParserResult ColourSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    if(aParameters.size() != 4){
        return kParseMalformedLine;
    }

    double r, g, b;
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[1], &r));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[2], &g));
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[3], &b));

    aOutput.mColours.push_back(Colour(r, g, b));

    return kParseSuccess;
}


bool SphereSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("sph") == 0);
}

ParserResult SphereSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    if(aParameters.size() != 5){
        return kParseMalformedLine;
    }

    uint32_t mat, col, trans;
    REQUIRE_PARSE_SUCCESS(Misc::GetUnsigned(aParameters[1], &col));
    if(col > aOutput.mColours.size() || col < 1)
        return kParseNonExistantReference;
    // Convert from 1 indexed
    Colour colour = aOutput.mColours[col - 1];

    REQUIRE_PARSE_SUCCESS(Misc::GetUnsigned(aParameters[2], &mat));
    if(mat > aOutput.mMaterials.size() || mat < 1)
        return kParseNonExistantReference;
    // Convert from 1 indexed
    Material material = aOutput.mMaterials[mat - 1];

    REQUIRE_PARSE_SUCCESS(Misc::GetUnsigned(aParameters[3], &trans));
    if(trans > aOutput.mTransforms.size() || trans < 1)
        return kParseNonExistantReference;
    // Convert from 1 indexed
    Math::Transform transform = aOutput.mTransforms[trans - 1];

    double radius;
    REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[4], &radius));

    aOutput.mObjects.push_back(std::make_shared<Sphere>(colour, material, transform, radius));
    return kParseSuccess;
}


bool FaceSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("f") == 0);
}

ParserResult FaceSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    if(aParameters.size() != 4){
        return kParseMalformedLine;
    }

    std::array<Vertex,3> vertices;

    for (int i = 0; i < 3; i++){
        double vertIdx;
        REQUIRE_PARSE_SUCCESS(Misc::GetDouble(aParameters[i+1], &vertIdx));
        if(vertIdx > aOutput.mVertices.size() || vertIdx < 1)
            return kParseNonExistantReference;

        // OBJ format is 1 indexed
        vertices[i] = aOutput.mVertices[vertIdx - 1];
    }

    aOutput.mObjects.push_back(std::make_shared<Triangle>(vertices));

    return kParseSuccess;
}


bool ObjSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return (aParameters[0].compare("obj") == 0);
}

ParserResult ObjSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    if(aParameters.size() != 5){
        return kParseMalformedLine;
    }
    std::string filename = mDirectory + aParameters[1];

    uint32_t mat, col, trans;
    REQUIRE_PARSE_SUCCESS(Misc::GetUnsigned(aParameters[2], &col));
    if(col > aOutput.mColours.size() || col < 1)
        return kParseNonExistantReference;
    // Convert from 1 indexed
    Colour colour = aOutput.mColours[col - 1];

    REQUIRE_PARSE_SUCCESS(Misc::GetUnsigned(aParameters[3], &mat));
    if(mat > aOutput.mMaterials.size() || mat < 1)
        return kParseNonExistantReference;
    // Convert from 1 indexed
    Material material = aOutput.mMaterials[mat - 1];

    REQUIRE_PARSE_SUCCESS(Misc::GetUnsigned(aParameters[4], &trans));
    if(trans > aOutput.mTransforms.size() || trans < 1)
        return kParseNonExistantReference;
    // Convert from 1 indexed
    Math::Transform transform = aOutput.mTransforms[trans - 1];

    Scene primitive;

    OBJParser obj(filename, mPrintIndent + 1);
    ParserResult result;
    result = obj.ParseFile(primitive);

    if(result == kParseSuccess){
        // Apply the colour material and transform to the obj
        primitive.Apply(colour, material, transform);

        // Merge the obj into the output
        aOutput.Merge(primitive);
    }
    return result;
}

bool MiscSymbol::CheckSymbol(const std::vector<std::string>& aParameters){
    return true;
}

ParserResult MiscSymbol::ParseLine(const std::vector<std::string>& aParameters, Scene& aOutput){
    return kParseSuccess;
}

