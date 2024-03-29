// David Sami 2015

#include <iostream>
#include <limits>
#include "Shader.h"

Colour Shader::CastRay(Math::Ray aRay, const Scene& aScene){
    return CastRay(aRay, aScene, 0);
}

Colour Shader::CastRay(Math::Ray aRay, const Scene& aScene, uint32_t aBounceNum){
    ObjectIntersection objectIntersect = IntersectObjects(aRay, aScene);

    Colour ret = mBackgroundColour;

    if(objectIntersect.mIntersects){
        std::vector<LightIntersection> hitLights = IntersectLights(objectIntersect.mPoint, objectIntersect.mNormal, aScene);

        ret = CalculateColour(objectIntersect, hitLights, aScene, aBounceNum);
    }

    return ret;
}

ObjectIntersection Shader::IntersectObjects(Math::Ray aRay, const Scene& aScene){
    double minIntersection = aRay.maxt;
    std::shared_ptr<Shape> intersectionShape;

    for(auto it = aScene.mObjects.begin(); it != aScene.mObjects.end(); it++){
        double intersection;
        bool doesIntersect = (*it)->Intersect(aRay, &intersection);

        if(doesIntersect &&
               intersection < minIntersection &&
               intersection > aRay.mint)
        {
            minIntersection = intersection;
            intersectionShape = *it;
        }
    }

    ObjectIntersection ret;
    ret.mIntersects = false;

    if (minIntersection != aRay.maxt){
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
