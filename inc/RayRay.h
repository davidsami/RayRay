// David Sami 2015

#ifndef RAYRAY_H
#define RAYRAY_H

#include <vector>
#include <memory>
#include "Camera.h"
#include "PixelBuffer.h"
#include "Screen.h"
#include "Settings.h"
#include "Shape.h"

struct Intersection {
public:
    bool mIntersects;
    Math::Point mPoint;
    Colour mColour;
};

class RayRay {
public:
    RayRay(Settings* aSettings);
    ~RayRay();
    void Run();
private:
    void Init();
    void InitScene();
    void InitSampler();

    void Loop();
    Intersection Intersect(Math::Ray aRay);

    void Output();

    Settings* mSettings;
    Screen* mScreen;
    Camera* mCamera;
    std::unique_ptr<PixelBuffer> mPixels;

    Colour mAmbient;
    std::vector<Shape*> mObjects;
    //std::vector<Light*> mLights;
    //std::vector<Material*> mMaterials;
};

#endif
