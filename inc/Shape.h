// David Sami 2015

#ifndef SHAPE_H
#define SHAPE_H

#include "Ray.h"
#include "Transform.h"

class Shape {
public:
    Shape(Transform& aTransform): mTransform(aTransform) {}
    virtual double Intersect(Ray& ray)=0;
protected:
    Transform mTransform;
};

#endif
