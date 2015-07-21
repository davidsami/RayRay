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
    Colour c(255,0,0);
    Math::Point p(0,0,5);
    Sphere* test = new Sphere(c, p, 1);
    mObjects.push_back(test);

    Colour c2(0,255,0);
    Math::Point p2(1,1,3);
    Sphere* test2 = new Sphere(c2, p2, 1);
    mObjects.push_back(test2);

    Math::Point p3(1,0,0);
    Light* light = new Light(7, p3);
    mLights.push_back(light);

    Math::Point p4(-1,0,0);
    Light* light2 = new Light(2.5, p4);
    mLights.push_back(light2);
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
        ret = objectIntersect.mColour;

        double intensity = 0;
        std::vector<LightIntersection> hitLights = IntersectLights(objectIntersect.mPoint, objectIntersect.mNormal);

        for(auto it = hitLights.begin(); it != hitLights.end(); it++){
            Math::Vector l = (*it).mLightRay.d;
            Math::Normal n = objectIntersect.mNormal;

            double lightIntensity = (*it).mIntensity;
            double attenuation = (*it).mAttenuation;
            double diffuse = 1 * l.Dot(n);
            intensity += lightIntensity / attenuation * (diffuse);
        }

        ret = ret * intensity;
    }

    return ret;
}

ObjectIntersection RayRay::IntersectObjects(Math::Ray aRay){
    double minIntersection = std::numeric_limits<double>::infinity();
    Shape* intersectionShape = NULL;
    for(auto it = mObjects.begin(); it != mObjects.end(); it++){
        double intersection;
        bool doesIntersect = (*it)->Intersect(aRay, &intersection);

        if(doesIntersect &&
               intersection < minIntersection &&
               intersection > 0.1)
        {
            minIntersection = intersection;
            intersectionShape = *it;
        }
    }

    ObjectIntersection ret;
    ret.mIntersects = false;

    if (minIntersection != std::numeric_limits<double>::infinity()){
        ret.mIntersects = true;
        ret.mPoint = aRay.GetPoint(minIntersection);
        ret.mColour = intersectionShape->GetColour();
        ret.mNormal = intersectionShape->GetNormal(ret.mPoint);
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
