// David Sami 2015

#include "Camera.h"

Camera::Camera(Math::Transform& aCameraToWorld, double aFov, uint32_t xDim, uint32_t yDim):
    mCameraToWorld(aCameraToWorld),
    mScreenToCamera(PerspectiveTransform(aFov, 1e-2f, 1000., xDim, yDim))
{
}

Camera* Camera::CreateCamera(Settings* aSettings, Screen* aScreen){
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
        Eigen::Projective3d cameraPosition;
        cameraPosition = Eigen::Translation3d(xCam, yCam, zCam);

        Eigen::Projective3d cameraRotation;
        cameraRotation = 
              Eigen::AngleAxisd(yawCam, Eigen::Vector3d::UnitZ())
            * Eigen::AngleAxisd(pitchCam, Eigen::Vector3d::UnitY())
            * Eigen::AngleAxisd(rollCam, Eigen::Vector3d::UnitX());

        Eigen::Projective3d t = cameraPosition * cameraRotation;
        Math::Transform transform(t);

        uint32_t xDim = aScreen->GetX();
        uint32_t yDim = aScreen->GetY();
        out = new Camera(transform, fov, xDim, yDim);
    }

    return out;
}

Math::Transform Camera::PerspectiveTransform(double aFov, double n, double f, uint32_t xDim, uint32_t yDim){
    double x = xDim;
    double y = yDim;
    // Normalized screen dimensions
    double aspectRatio = x / y;
    Eigen::Projective3d s;
    s = Eigen::Scaling(2./x, -2./y, 1.);
    s *= Eigen::Scaling(aspectRatio, 1., 1.);
    s *= Eigen::Translation3d(-x/2., -y/2., 0);

    // Perspective transform
    Eigen::Projective3d pers;
    double scale = 1. / tanh(M_PI*aFov/2./180.);
    pers = Eigen::Scaling(scale, scale, 1.);

    double m = f / (f - n);
    Eigen::Matrix4d t;
    t << 1,   0,   0,   0,
         0,   1,   0,   0,
         0,   0,   m,-n*m,
         0,   0,   1,   0;
    pers *= t;

    Eigen::Projective3d transform;
    transform = pers.inverse() * s;
    return Math::Transform(transform);
}

Math::Ray Camera::GenerateRay(double x, double y){
    Math::Point screenPoint(x,y,0);
    Math::Point cameraPoint = mScreenToCamera(screenPoint);

    Math::Ray ray(Math::Point(0,0,0), Math::Vector(cameraPoint));

    return mCameraToWorld(ray);
}
