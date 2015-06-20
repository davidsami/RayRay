// David Sami 2015

#ifndef SPHERE_H
#define SPHERE_H

#include "Math.h"
#include "Shape.h"

class Sphere: Shape {
public:
    Sphere(Math::Transform& aTransform, double aRadius);
    virtual bool Intersect(Math::Ray& aRay, double* aIntersection);
private:
    Math::Point mCenter;
    double mRadius;
};

#endif
