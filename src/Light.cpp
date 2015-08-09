// David Sami 2015

#include <Light.h>

Math::Ray Light::CreateRay(Math::Point aOrigin) const{
    Math::Vector v = mCenter - aOrigin;
    Math::Ray ray = Math::Ray(aOrigin, v.Normal());
    ray.maxt = v.d.norm();
    return ray;
}

double Light::GetAttenuation(Math::Point aOrigin) const{
    Math::Vector v = mCenter - aOrigin;
    return v.d.squaredNorm();
}

double Light::GetIntensity() const{
    return mIntensity;
}
