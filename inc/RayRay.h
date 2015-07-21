// David Sami 2015

#ifndef RAYRAY_H
#define RAYRAY_H

#include <memory>
#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "PixelBuffer.h"
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
};

struct LightIntersection : public Intersection {
    Math::Ray mLightRay;
    // Colour mLightColour;
    // Math::Vector mHalfAngle;
    double mAttenuation;
    double mIntensity;
};

class RayRay {
public:
    RayRay(std::unique_ptr<Settings> aSettings);
    void Run();
private:
    void Init();
    void InitScene();
    void InitSampler();

    void Loop();
    Colour CastRay(Math::Ray aRay);
    ObjectIntersection IntersectObjects(Math::Ray aRay);
    std::vector<LightIntersection> IntersectLights(Math::Point aOrigin, Math::Normal aNormal);

    void Output();

    std::unique_ptr<Settings> mSettings;
    std::unique_ptr<Screen> mScreen;
    std::unique_ptr<Camera> mCamera;
    std::unique_ptr<PixelBuffer> mPixels;

    Colour mAmbient;
    std::vector<Shape*> mObjects;
    std::vector<Light*> mLights;
    std::vector<Material*> mMaterials;
};

#endif
