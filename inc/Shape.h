// David Sami 2015

#ifndef SHAPE_H
#define SHAPE_H

#include "Math.h"

class Shape {
public:
    Shape(Math::Transform& aTransform): mTransform(aTransform) {}
    virtual bool Intersect(Math::Ray& aRay, double* aIntersection) = 0;
protected:
    Math::Transform mTransform;
};

#endif
