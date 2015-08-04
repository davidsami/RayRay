// David Sami 2015

#ifndef SPHERE_H
#define SPHERE_H

#include "Math.h"
#include "Shape.h"

class Sphere: public Shape {
public:
    Sphere(std::shared_ptr<Colour> aColour, std::shared_ptr<Material> aMaterial, std::shared_ptr<Math::Transform> aTransform, double aRadius);
    virtual bool Intersect(const Math::Ray& aRay, double* aIntersection);
    virtual Math::Normal GetNormal(const Math::Point& aPoint);
private:
    double mRadius;
    static Math::Transform TransformationFromPoint(const Math::Point& aCenter);
};

#endif
