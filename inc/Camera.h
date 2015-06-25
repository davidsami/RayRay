// David Sami 2015

#ifndef CAMERA_H
#define CAMERA_H

#include "Math.h"

class Camera {
public:
    Camera(Math::Transform& aCameraToWorld, Math::Transform mScreenToCamera, double aFov);
    static Math::Transform PerspectiveTransform(double aFov, double n, double f);
    Math::Ray GenerateRay(double x, double y);
protected:
    Math::Transform mCameraToWorld;
    Math::Transform mScreenToCamera;
    double mFov;
};

#endif
