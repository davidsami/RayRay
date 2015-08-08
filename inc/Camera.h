// David Sami 2015

#ifndef CAMERA_H
#define CAMERA_H

#include "Math.h"
#include "Settings.h"

class Camera {
public:
    Camera();
    void Init(Math::Transform aCameraToWorld, double aFov, uint32_t xDim, uint32_t yDim);
    Math::Ray GenerateRay(double x, double y) const;

    uint32_t GetX() const{
        return mX;
    }
    uint32_t GetY() const{
        return mY;
    }
protected:
    static Math::Transform PerspectiveTransform(double aFov, double n, double f, uint32_t xDim, uint32_t yDim);
    Math::Transform mCameraToWorld;
    Math::Transform mScreenToCamera;
    double mFov;

private:
    uint32_t mX;
    uint32_t mY;
};

#endif
