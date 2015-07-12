// David Sami 2015

#ifndef CAMERA_H
#define CAMERA_H

#include "Math.h"
#include "Settings.h"
#include "Screen.h"

class Camera {
public:
    Camera(Math::Transform& aCameraToWorld, double aFov, uint32_t xDim, uint32_t yDim);
    Math::Ray GenerateRay(double x, double y);
    static Camera* CreateCamera(Settings* aSettings, Screen* aScreen);
protected:
    static Math::Transform PerspectiveTransform(double aFov, double n, double f, uint32_t xDim, uint32_t yDim);
    Math::Transform mCameraToWorld;
    Math::Transform mScreenToCamera;
    double mFov;
};

#endif
