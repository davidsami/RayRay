// David Sami 2015

#ifndef SPHERE_H
#define SPHERE_H

#include "Math.h"
#include "Shape.h"

class Sphere: public Shape {
public:
    Sphere(Colour aColour, Material aMaterial, Math::Transform aTransform, double aRadius);
    virtual bool Intersect(const Math::Ray& aRay, double* aIntersection);
    virtual Math::Normal GetNormal(const Math::Point& aPoint);
private:
    double mRadius;
    static Math::Transform TransformationFromPoint(const Math::Point& aCenter);
};

#endif
