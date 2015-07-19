// David Sami 2015

#ifndef SPHERE_H
#define SPHERE_H

#include "Math.h"
#include "Shape.h"

class Sphere: public Shape {
public:
    Sphere(const Colour& aColour, const Math::Point& aCenter, double aRadius);
    virtual bool Intersect(const Math::Ray& aRay, double* aIntersection);
private:
    double mRadius;
    static Math::Transform TransformationFromPoint(const Math::Point& aCenter);
};

#endif
