// David Sami 2015

#include "Camera.h"

Camera::Camera(Math::Transform& aCameraToWorld, double aFov, uint32_t xDim, uint32_t yDim):
    mCameraToWorld(aCameraToWorld),
    mScreenToCamera(PerspectiveTransform(aFov, 1e-2f, 1000., xDim, yDim)),
    mX(xDim),
    mY(yDim)
{
}

Math::Transform Camera::PerspectiveTransform(double aFov, double n, double f, uint32_t xDim, uint32_t yDim){
    double x = xDim;
    double y = yDim;
    // Normalized screen dimensions
    double aspectRatio = x / y;

    Math::Transform s = Math::Transform::Scaling(2./x, -2./y, 1.);
    s *= Math::Transform::Scaling(aspectRatio, 1., 1.);
    s *= Math::Transform::Translation(-x/2., -y/2., 0);

    // Perspective transform
    double scale = 1. / tanh(M_PI*aFov/2./180.);
    Math::Transform pers = Math::Transform::Scaling(scale, scale, 1.);

    double m = f / (f - n);
    Eigen::Matrix4d t;
    t << 1,   0,   0,   0,
         0,   1,   0,   0,
         0,   0,   m,-n*m,
         0,   0,   1,   0;
    pers *= Math::Transform(t);

    return pers.Inverse() * s;
}

Math::Ray Camera::GenerateRay(double x, double y) const{
    Math::Point screenPoint(x,y,0);
    Math::Point cameraPoint = mScreenToCamera(screenPoint);

    Math::Ray ray(Math::Point(0,0,0), Math::Vector(cameraPoint));

    return mCameraToWorld(ray);
}
