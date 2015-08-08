// David Sami 2015

#ifndef SHAPE_H
#define SHAPE_H

#include "Material.h"
#include "Math.h"
#include "Colour.h"

class Shape {
public:
    Shape(std::shared_ptr<Colour> aColour, std::shared_ptr<Material> aMaterial, std::shared_ptr<Math::Transform> aTransform): 
        mColour(aColour),
        mMaterial(aMaterial),
        mTransform(aTransform)
    {
    }

    Shape(): 
        mColour(std::make_shared<Colour>(0,0,0)),
        mMaterial(std::make_shared<Material>()),
        mTransform(std::make_shared<Math::Transform>())
    {
    }

    virtual bool Intersect(const Math::Ray& aRay, double* aIntersection) = 0;
    virtual Math::Normal GetNormal(const Math::Point& aPoint) = 0;
    void SetColour(std::shared_ptr<Colour> aColour){
        mColour = aColour;
    }
    void SetMaterial(std::shared_ptr<Material> aMaterial){
        mMaterial = aMaterial;
    }
    void SetTransform(std::shared_ptr<Math::Transform> aTransform){
        mTransform = aTransform;
    }
    Colour GetColour(){
        return *mColour;
    }
    Material GetMaterial(){
        return *mMaterial;
    }
protected:
    // Temporary. Single colour shapes
    std::shared_ptr<Colour> mColour;
    std::shared_ptr<Material> mMaterial;

    std::shared_ptr<Math::Transform> mTransform;
};

#endif
