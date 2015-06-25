// David Sami 2015

#include "Camera.h"

Camera::Camera(Math::Transform& aCameraToWorld, Math::Transform aScreenToCamera, double aFov):
    mCameraToWorld(aCameraToWorld),
    mScreenToCamera(aScreenToCamera)
{
}

Math::Transform Camera::PerspectiveTransform(double aFov, double n, double f){
    double m = f / (f - n);
    Eigen::Matrix4d t;
    t << 1,   0,   0,   0,
         0,   1,   0,   0,
         0,   0,   m,-n*m,
         0,   0,   1,   0;

    double scale = 1 / tanf(aFov/2);

    Eigen::Affine3d s(t);
    s *= Eigen::Scaling(scale, scale, 1.);

    return Math::Transform(s);
}

Math::Ray Camera::GenerateRay(double x, double y){
    Math::Point screenPoint(x,y,0);
    Math::Point cameraPoint = mScreenToCamera(screenPoint);

    Math::Ray ray(Math::Point(0,0,0), Math::Vector(cameraPoint));

    return mCameraToWorld(ray);
}
