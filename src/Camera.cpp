// David Sami 2015

#include "Camera.h"

Camera::Camera(Math::Transform& aCameraToWorld, double aFov):
    mCameraToWorld(aCameraToWorld),
    mScreenToCamera(PerspectiveTransform(aFov, 1e-2f, 1000.))
{
}

Camera* Camera::CreateCamera(Settings* aSettings){
    Camera* out = NULL;

    bool fovResult;
    double fov;
    fovResult = aSettings->GetDouble(Settings::kFOV, &fov);

    bool xCamResult, yCamResult, zCamResult;
    double xCam, yCam, zCam;
    xCamResult = aSettings->GetDouble(Settings::kXCamera, &xCam);
    yCamResult = aSettings->GetDouble(Settings::kYCamera, &yCam);
    zCamResult = aSettings->GetDouble(Settings::kZCamera, &zCam);

    bool yawCamResult, pitchCamResult, rollCamResult;
    double yawCam, pitchCam, rollCam;
    yawCamResult = aSettings->GetDouble(Settings::kYawCamera, &yawCam);
    pitchCamResult = aSettings->GetDouble(Settings::kPitchCamera, &pitchCam);
    rollCamResult = aSettings->GetDouble(Settings::kRollCamera, &rollCam);

    if(fovResult &&
       xCamResult &&
       yCamResult &&
       zCamResult &&
       yawCamResult &&
       pitchCamResult &&
       rollCamResult)
    {
        Eigen::Affine3d cameraPosition;
        cameraPosition = Eigen::Translation3d(xCam, yCam, zCam);

        Eigen::Affine3d cameraRotation;
        cameraRotation = 
              Eigen::AngleAxisd(yawCam, Eigen::Vector3d::UnitZ())
            * Eigen::AngleAxisd(pitchCam, Eigen::Vector3d::UnitY())
            * Eigen::AngleAxisd(rollCam, Eigen::Vector3d::UnitX());

        Eigen::Affine3d t = cameraPosition * cameraRotation;
        Math::Transform transform(t);

        out = new Camera(transform, fov);
    }

    return out;
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
