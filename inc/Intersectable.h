// David Sami 2015

#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "Math.h"

class Intersectable {
public:
    virtual bool Intersect(const Math::Ray& aRay, double* aIntersection) = 0;
    virtual bool DoesIntersect(const Math::Ray& aRay) = 0;
};

#endif
