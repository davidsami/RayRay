// David Sami 2015

#include <iostream>
#include <limits>
#include "FileOutput.h"
#include "RayRay.h"
#include "Sphere.h"

RayRay::RayRay(std::unique_ptr<Settings> aSettings):
    mSettings(std::move(aSettings))
{
}

void RayRay::Run(){
    Init();

    Loop();

    Output();
}

void RayRay::Init(){
    InitScene();
    InitSampler();

    //XXX: Test
    std::unique_ptr<Material> mat(new Material(0, 1, 1, 500));
    mMaterials.push_back(std::move(mat));

    Colour c(255,0,127);
    Math::Point p(0,0,5);
    std::unique_ptr<Sphere> test(new Sphere(c, 0, p, 1));
    mObjects.push_back(std::move(test));

    Colour c2(100,255,0);
    Math::Point p2(1,1,3);
    std::unique_ptr<Sphere> test2(new Sphere(c2, 0, p2, 1));
    mObjects.push_back(std::move(test2));

    Math::Point p3(1,0,0);
    std::unique_ptr<Light> light(new Light(3, p3));
    mLights.push_back(std::move(light));

    Math::Point p4(-1,-0.5,3);
    std::unique_ptr<Light> light2(new Light(1, p4));
    mLights.push_back(std::move(light2));

    Math::Point p5(2,0,7);
    std::unique_ptr<Light> light3(new Light(10, p5));
    mLights.push_back(std::move(light3));
}

void RayRay::InitScene(){
}

void RayRay::InitSampler(){
    mScreen = Screen::CreateScreen(*mSettings);
    mCamera = Camera::CreateCamera(*mSettings, *mScreen);
    std::unique_ptr<PixelBuffer> pixels(new PixelBuffer(mScreen->GetY(), mScreen->GetX()));
    mPixels = std::move(pixels);
}

void RayRay::Loop(){
    for(uint32_t y = 0; y < mScreen->GetY(); y++){
        for(uint32_t x = 0; x < mScreen->GetX(); x++){
            Math::Ray ray = mCamera->GenerateRay(x, y);
            mPixels->Get(x,y) = CastRay(ray);
        }
    }
}

Colour RayRay::CastRay(Math::Ray aRay){
    ObjectIntersection objectIntersect = IntersectObjects(aRay);

    Colour ret = Colour(0,0,0);

    if(objectIntersect.mIntersects){
        size_t materialId = objectIntersect.mMaterialId;

        std::vector<LightIntersection> hitLights = IntersectLights(objectIntersect.mPoint, objectIntersect.mNormal);

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
            double diffuseConstant = mMaterials[materialId]->mDiffuse;
            double diffuseDot = l.Normal().Dot(n);
            diffuse += lightIntensity / attenuation * diffuseConstant * ((diffuseDot > 0)?diffuseDot:0);

            // Calculate specular component
            double shininess = mMaterials[materialId]->mShininess;
            double specularConstant = mMaterials[materialId]->mSpecular;
            double specularDot = n.Dot(halfAngle);
            double specular = 255 * (lightIntensity / attenuation) * specularConstant * ((specularDot > 0)?pow(specularDot, shininess):0);
            specularColour = specularColour + Math::Vector(specular, specular, specular);
        }

        ret = objectIntersect.mColour * diffuse + Colour(specularColour);
    }

    return ret;
}

ObjectIntersection RayRay::IntersectObjects(Math::Ray aRay){
    double minIntersection = std::numeric_limits<double>::infinity();
    std::vector<std::unique_ptr<Shape>>::iterator intersectionShape;

    for(auto it = mObjects.begin(); it != mObjects.end(); it++){
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

std::vector<LightIntersection> RayRay::IntersectLights(Math::Point aOrigin, Math::Normal aNormal){
    std::vector<LightIntersection> intersections;

    for(auto it = mLights.begin(); it != mLights.end(); it++){
        Math::Ray rayToLight = (*it)->CreateRay(aOrigin);
        ObjectIntersection objectIntersect = IntersectObjects(rayToLight);

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

void RayRay::Output(){
    std::string filename;
    bool filenameResult = mSettings->GetString(Settings::kOutputFile, &filename);
    if(filenameResult){
        FileOutput output;
        output.OutputPPM(*mPixels, filename);
    }
}
