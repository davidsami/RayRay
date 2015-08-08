// David Sami 2015

#ifndef SHAPE_H
#define SHAPE_H

#include "BoundingBox.h"
#include "Intersectable.h"
#include "Material.h"
#include "Math.h"
#include "Colour.h"

class Shape: Intersectable {
public:
    Shape(Colour aColour, Material aMaterial, Math::Transform aTransform): 
        mColour(aColour),
        mMaterial(aMaterial),
        mTransform(aTransform)
    {
    }

    Shape(): 
        mColour(Colour(0,0,0)),
        mMaterial(Material()),
        mTransform(Math::Transform())
    {
    }

    bool Intersect(const Math::Ray& aRay, double* aIntersection){
        bool doesIntersect = false;

        // Check the bounding box first, then call CheckIntersect from subclass
        if(mBox.DoesIntersect(aRay)){
            doesIntersect = CheckIntersect(aRay, aIntersection);
        }

        return doesIntersect;
    }
    bool DoesIntersect(const Math::Ray& aRay){
        double temp;
        return Intersect(aRay, &temp);
    }
    virtual Math::Normal GetNormal(const Math::Point& aPoint) = 0;
    void SetColour(Colour aColour){
        mColour = aColour;
        OnColourChange();
    }
    void SetMaterial(Material aMaterial){
        mMaterial = aMaterial;
        OnMaterialChange();
    }
    void SetTransform(Math::Transform aTransform){
        mTransform = aTransform;
        OnTransformChange();
    }
    Colour GetColour(){
        return mColour;
    }
    Material GetMaterial(){
        return mMaterial;
    }
protected:
    Colour mColour;
    Material mMaterial;
    Math::Transform mTransform;
    virtual void OnColourChange() {}
    virtual void OnMaterialChange() {}
    virtual void OnTransformChange() {}

    BoundingBox mBox;
    virtual bool CheckIntersect(const Math::Ray& aRay, double* aIntersection) = 0;
};

#endif
