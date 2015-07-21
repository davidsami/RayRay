// David Sami 2015

#ifndef SPHERE_H
#define SPHERE_H

#include "Math.h"
#include "Shape.h"

class Sphere: public Shape {
public:
    Sphere(const Colour& aColour, const size_t aMaterialId, const Math::Point& aCenter, double aRadius);
    virtual bool Intersect(const Math::Ray& aRay, double* aIntersection);
    virtual Math::Normal GetNormal(const Math::Point& aPoint);
private:
    double mRadius;
    static Math::Transform TransformationFromPoint(const Math::Point& aCenter);
};

#endif
