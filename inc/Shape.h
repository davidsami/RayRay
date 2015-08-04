// David Sami 2015

#ifndef SHAPE_H
#define SHAPE_H

#include "Material.h"
#include "Math.h"
#include "Colour.h"

class Shape {
public:
    Shape(const Math::Transform& aTransform, const Colour& aColour, const Material aMaterial): mTransform(aTransform), mColour(aColour), mMaterial(aMaterial) {}
    virtual bool Intersect(const Math::Ray& aRay, double* aIntersection) = 0;
    virtual Math::Normal GetNormal(const Math::Point& aPoint) = 0;
    void SetColour(const Colour& aColour){
        mColour = aColour;
    }
    void SetMaterial(const Material aMaterial){
        mMaterial = aMaterial;
    }
    Colour GetColour(){
        return mColour;
    }
    Material GetMaterial(){
        return mMaterial;
    }
protected:
    Math::Transform mTransform;
    // Temporary. Single colour shapes
    Colour mColour;
    Material mMaterial;
};

#endif
