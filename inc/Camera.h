// David Sami 2015

#ifndef CAMERA_H
#define CAMERA_H

#include "Math.h"
#include "Settings.h"

class Camera {
public:
    Camera(Math::Transform& aCameraToWorld, double aFov);
    Math::Ray GenerateRay(double x, double y);
    static Camera* CreateCamera(Settings* aSettings);
protected:
    static Math::Transform PerspectiveTransform(double aFov, double n, double f);
    Math::Transform mCameraToWorld;
    Math::Transform mScreenToCamera;
    double mFov;
};

#endif
