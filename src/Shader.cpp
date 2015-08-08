// David Sami 2015

#include <iostream>
#include <limits>
#include "Shader.h"

Colour Shader::ShadePixel(uint32_t x, uint32_t y, const Scene& aScene){
    // Generate one ray for now
    Math::Ray ray = aScene.mCamera.GenerateRay(x, y);
    return CastRay(ray, aScene);
}

Colour Shader::CastRay(Math::Ray aRay, const Scene& aScene){
    ObjectIntersection objectIntersect = IntersectObjects(aRay, aScene);

    Colour ret = Colour(0,0,0);

    if(objectIntersect.mIntersects){
        std::vector<LightIntersection> hitLights = IntersectLights(objectIntersect.mPoint, objectIntersect.mNormal, aScene);

        ret = CalculateColour(objectIntersect, hitLights, aScene);
    }

    return ret;
}

ObjectIntersection Shader::IntersectObjects(Math::Ray aRay, const Scene& aScene){
    double minIntersection = std::numeric_limits<double>::infinity();
    std::shared_ptr<Shape> intersectionShape;

    for(auto it = aScene.mObjects.begin(); it != aScene.mObjects.end(); it++){
        double intersection;
        bool doesIntersect = (*it)->Intersect(aRay, &intersection);

        if(doesIntersect &&
               intersection < minIntersection &&
               intersection > 0.0001)
        {
            minIntersection = intersection;
            intersectionShape = *it;
        }
    }

    ObjectIntersection ret;
    ret.mIntersects = false;

    if (minIntersection != std::numeric_limits<double>::infinity()){
        ret.mIntersects = true;
        ret.mRay = aRay;
        ret.mPoint = aRay.GetPoint(minIntersection);
        ret.mColour = intersectionShape->GetColour();
        ret.mNormal = intersectionShape->GetNormal(ret.mPoint);
        ret.mMaterial = intersectionShape->GetMaterial();
    }
    return ret;
}

std::vector<LightIntersection> Shader::IntersectLights(Math::Point aOrigin, Math::Normal aNormal, const Scene& aScene){
    std::vector<LightIntersection> intersections;

    for(auto it = aScene.mLights.begin(); it != aScene.mLights.end(); it++){
        Math::Ray rayToLight = it->CreateRay(aOrigin);
        ObjectIntersection objectIntersect = IntersectObjects(rayToLight, aScene);

        if(!objectIntersect.mIntersects){
            LightIntersection intersect;
            intersect.mLightRay = rayToLight;
            intersect.mIntensity = it->GetIntensity();
            intersect.mAttenuation = it->GetAttenuation(aOrigin);

            intersections.push_back(intersect);
        }
    }
    return intersections;
}
