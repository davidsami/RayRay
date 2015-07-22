// David Sami 2015

#ifndef SHADER_H
#define SHADER_H

#include "Camera.h"
#include "Colour.h"
#include "Light.h"
#include "Material.h"
#include "PixelBuffer.h"
#include "Scene.h"
#include "Screen.h"
#include "Settings.h"
#include "Shape.h"

struct Intersection {
    bool mIntersects;
};

struct ObjectIntersection : public Intersection {
    Math::Point mPoint;
    Colour mColour;
    Math::Normal mNormal;
    Math::Ray mReflection;
    size_t mMaterialId;
};

struct LightIntersection : public Intersection {
    Math::Ray mLightRay;
    double mAttenuation;
    double mIntensity;
};

class Shader {
public:
    Colour ShadePixel(uint32_t x, uint32_t y, Scene& aScene);

private:
    Colour CastRay(Math::Ray aRay, Scene& aScene);

protected:
    // Implementation specific
    virtual Colour CalculateColour(ObjectIntersection aObject, LightIntersection aLight)=0;

    // Intersection functions
    ObjectIntersection IntersectObjects(Math::Ray aRay, Scene& aScene);
    std::vector<LightIntersection> IntersectLights(Math::Point aOrigin, Math::Normal aNormal, Scene& aScene);
};

#endif