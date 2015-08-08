// David Sami 2015

#ifndef SHADER_H
#define SHADER_H

#include "Camera.h"
#include "Colour.h"
#include "Light.h"
#include "Material.h"
#include "PixelBuffer.h"
#include "Scene.h"
#include "Settings.h"
#include "Shape.h"

struct Intersection {
    bool mIntersects;
};

struct ObjectIntersection : public Intersection {
    // Initial Ray
    Math::Ray mRay;

    // Intersection point
    Math::Point mPoint;

    // Object properties
    Colour mColour;
    Math::Normal mNormal;
    // Math::Ray mReflection;
    Material mMaterial;
};

struct LightIntersection : public Intersection {
    // Ray to light
    Math::Ray mLightRay;

    // Light properties
    double mAttenuation;
    double mIntensity;
};

class Shader {
public:
    Colour CastRay(Math::Ray aRay, const Scene& aScene);

protected:
    // Implementation specific
    virtual Colour CalculateColour(ObjectIntersection& aObject, std::vector<LightIntersection>& aLights, const Scene& aScene)=0;

    // Intersection functions
    ObjectIntersection IntersectObjects(Math::Ray aRay, const Scene& aScene);
    std::vector<LightIntersection> IntersectLights(Math::Point aOrigin, Math::Normal aNormal, const Scene& aScene);
};

#endif
