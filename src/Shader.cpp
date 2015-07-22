// David Sami 2015

#include <iostream>
#include <limits>
#include "Shader.h"

Colour Shader::ShadePixel(uint32_t x, uint32_t y, Scene& aScene){
    // Generate one ray for now
    Math::Ray ray = aScene.mCamera->GenerateRay(x, y);
    return CastRay(ray, aScene);
}

Colour Shader::CastRay(Math::Ray aRay, Scene& aScene){
    ObjectIntersection objectIntersect = IntersectObjects(aRay, aScene);

    Colour ret = Colour(0,0,0);

    if(objectIntersect.mIntersects){
        size_t materialId = objectIntersect.mMaterialId;

        std::vector<LightIntersection> hitLights = IntersectLights(objectIntersect.mPoint, objectIntersect.mNormal, aScene);

        double diffuse = 0;
        Math::Vector specularColour(0,0,0);
        for(auto it = hitLights.begin(); it != hitLights.end(); it++){
            // Values needed for next parts
            Math::Vector l = (*it).mLightRay.d;
            Math::Normal n = objectIntersect.mNormal;
            Math::Vector lPlusV = l + aRay.d;
            Math::Vector halfAngle = lPlusV.Normal();

            double lightIntensity = (*it).mIntensity;
            double attenuation = (*it).mAttenuation;

            // Calculate diffuse multiplier
            double diffuseConstant = aScene.mMaterials[materialId]->mDiffuse;
            double diffuseDot = l.Normal().Dot(n);
            diffuse += lightIntensity / attenuation * diffuseConstant * ((diffuseDot > 0)?diffuseDot:0);

            // Calculate specular component
            double shininess = aScene.mMaterials[materialId]->mShininess;
            double specularConstant = aScene.mMaterials[materialId]->mSpecular;
            double specularDot = n.Dot(halfAngle);
            double specular = 255 * (lightIntensity / attenuation) * specularConstant * ((specularDot > 0)?pow(specularDot, shininess):0);
            specularColour = specularColour + Math::Vector(specular, specular, specular);
        }

        ret = objectIntersect.mColour * diffuse + Colour(specularColour);
    }

    return ret;
}

ObjectIntersection Shader::IntersectObjects(Math::Ray aRay, Scene& aScene){
    double minIntersection = std::numeric_limits<double>::infinity();
    std::vector<std::unique_ptr<Shape>>::iterator intersectionShape;

    for(auto it = aScene.mObjects.begin(); it != aScene.mObjects.end(); it++){
        double intersection;
        bool doesIntersect = (*it)->Intersect(aRay, &intersection);

        if(doesIntersect &&
               intersection < minIntersection &&
               intersection > 0.0001)
        {
            minIntersection = intersection;
            intersectionShape = it;
        }
    }

    ObjectIntersection ret;
    ret.mIntersects = false;

    if (minIntersection != std::numeric_limits<double>::infinity()){
        ret.mIntersects = true;
        ret.mPoint = aRay.GetPoint(minIntersection);
        ret.mColour = (*intersectionShape)->GetColour();
        ret.mNormal = (*intersectionShape)->GetNormal(ret.mPoint);
        ret.mMaterialId = (*intersectionShape)->GetMaterialId();
    }
    return ret;
}

std::vector<LightIntersection> Shader::IntersectLights(Math::Point aOrigin, Math::Normal aNormal, Scene& aScene){
    std::vector<LightIntersection> intersections;

    for(auto it = aScene.mLights.begin(); it != aScene.mLights.end(); it++){
        Math::Ray rayToLight = (*it)->CreateRay(aOrigin);
        ObjectIntersection objectIntersect = IntersectObjects(rayToLight, aScene);

        if(!objectIntersect.mIntersects){
            LightIntersection intersect;
            intersect.mLightRay = rayToLight;
            intersect.mIntensity = (*it)->GetIntensity();
            intersect.mAttenuation = (*it)->GetAttenuation(aOrigin);

            intersections.push_back(intersect);
        }
    }
    return intersections;
}
