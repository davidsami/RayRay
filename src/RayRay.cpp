// David Sami 2015

#include <limits>
#include "FileOutput.h"
#include "RayRay.h"
#include "Sphere.h"

RayRay::RayRay(Settings* aSettings): 
    mSettings(aSettings),
    mScreen(NULL),
    mCamera(NULL)
{
}

RayRay::~RayRay(){
    delete mScreen;
    delete mCamera;
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
    Math::Point p(0,0,2);
    Sphere* test = new Sphere(c, p, 1);
    mObjects.push_back(test);

    Colour c2(0,255,0);
    Math::Point p2(0,1,2);
    Sphere* test2 = new Sphere(c2, p2, 1);
    mObjects.push_back(test2);
}

void RayRay::InitScene(){
}

void RayRay::InitSampler(){
    mScreen = Screen::CreateScreen(mSettings);
    mCamera = Camera::CreateCamera(mSettings, mScreen);
    std::unique_ptr<PixelBuffer> pixels(new PixelBuffer(mScreen->GetY(), mScreen->GetX()));
    mPixels = std::move(pixels);
}

void RayRay::Loop(){
    for(uint32_t y = 0; y < mScreen->GetY(); y++){
        for(uint32_t x = 0; x < mScreen->GetX(); x++){
            Math::Ray ray = mCamera->GenerateRay(x, y);
            Intersection intersect = Intersect(ray);
            mPixels->Get(x,y) = intersect.mColour;
        }
    }
}

Intersection RayRay::Intersect(Math::Ray aRay){
    double minIntersection = std::numeric_limits<double>::infinity();
    Shape* intersectionShape = NULL;
    for(auto it = mObjects.begin(); it != mObjects.end(); it++){
        double intersection;
        bool doesIntersect = (*it)->Intersect(aRay, &intersection);

        if(doesIntersect &&
               intersection < minIntersection &&
               intersection > 0){
            minIntersection = intersection;
            intersectionShape = *it;
        }
    }

    Intersection ret;
    ret.mIntersects = false;

    if (minIntersection != std::numeric_limits<double>::infinity()){
        ret.mIntersects = true;
        ret.mPoint = aRay.GetPoint(minIntersection);
        ret.mColour = intersectionShape->GetColour();
    } else {
        ret.mColour = Colour(0,0,0);
    }
    return ret;
}

void RayRay::Output(){
    std::string filename;
    bool filenameResult = mSettings->GetString(Settings::kOutputFile, &filename);
    if(filenameResult){
        FileOutput output;
        output.OutputPPM(*mPixels, filename);
    }
}
