// David Sami 2015

#ifndef LIGHT_H
#define LIGHT_H

#include "Colour.h"
#include "Math.h"

class Light {
public:
    Light(const double aIntensity, const Math::Point aCenter):mIntensity(aIntensity),mCenter(aCenter){}
    Math::Ray CreateRay(Math::Point aOrigin) const;
    double GetAttenuation(Math::Point aOrigin) const;
    double GetIntensity() const;
private:
    double mIntensity;
    Math::Point mCenter;
};
#endif
