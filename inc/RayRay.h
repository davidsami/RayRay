// David Sami 2015

#ifndef RAYRAY_H
#define RAYRAY_H

#include <vector>
#include "Camera.h"
#include "Screen.h"
#include "Settings.h"
#include "Shape.h"

class RayRay {
public:
    RayRay(Settings* aSettings);
    ~RayRay();
    void Run();
private:
    void Init();
    void InitScreen();
    void Loop();

    Settings* mSettings;
    Screen* mScreen;
    Camera* mCamera;

    std::vector<Shape> mObjects;
};

#endif
