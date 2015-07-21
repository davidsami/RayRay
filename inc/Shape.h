// David Sami 2015

#ifndef SHAPE_H
#define SHAPE_H

#include "Math.h"
#include "Colour.h"

class Shape {
public:
    Shape(const Math::Transform& aTransform, const Colour& aColour): mTransform(aTransform), mColour(aColour) {}
    virtual bool Intersect(const Math::Ray& aRay, double* aIntersection) = 0;
    virtual Math::Normal GetNormal(const Math::Point& aPoint) = 0;
    Colour GetColour(){
        return mColour;
    }
protected:
    Math::Transform mTransform;
    // Temporary. Single colour shapes
    Colour mColour;
};

#endif
