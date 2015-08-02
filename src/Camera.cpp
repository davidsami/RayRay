// David Sami 2015

#include "Camera.h"

Camera::Camera(Math::Transform& aCameraToWorld, double aFov, uint32_t xDim, uint32_t yDim):
    mCameraToWorld(aCameraToWorld),
    mScreenToCamera(PerspectiveTransform(aFov, 1e-2f, 1000., xDim, yDim)),
    mX(xDim),
    mY(yDim)
{
}

std::unique_ptr<Camera> Camera::CreateCamera(const Settings& aSettings, uint32_t xDim, uint32_t yDim){
    std::unique_ptr<Camera> out;

    bool fovResult;
    double fov;
    fovResult = aSettings.GetDouble(Settings::kFOV, &fov);

    bool xCamResult, yCamResult, zCamResult;
    double xCam, yCam, zCam;
    xCamResult = aSettings.GetDouble(Settings::kXCamera, &xCam);
    yCamResult = aSettings.GetDouble(Settings::kYCamera, &yCam);
    zCamResult = aSettings.GetDouble(Settings::kZCamera, &zCam);

    bool yawCamResult, pitchCamResult, rollCamResult;
    double yawCam, pitchCam, rollCam;
    yawCamResult = aSettings.GetDouble(Settings::kYawCamera, &yawCam);
    pitchCamResult = aSettings.GetDouble(Settings::kPitchCamera, &pitchCam);
    rollCamResult = aSettings.GetDouble(Settings::kRollCamera, &rollCam);

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

        out = std::make_unique<Camera>(transform, fov, xDim, yDim);
    }

    return out;
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
