// David Sami 2015

#include <Light.h>

Math::Ray Light::CreateRay(Math::Point aOrigin){
    Math::Vector v = mCenter - aOrigin;
    return Math::Ray(aOrigin, v.Normal());
}

double Light::GetAttenuation(Math::Point aOrigin){
    Math::Vector v = mCenter - aOrigin;
    return v.d.squaredNorm();
}

double Light::GetIntensity(){
    return mIntensity;
}
