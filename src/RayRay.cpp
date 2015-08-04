// David Sami 2015

#include <iostream>
#include "BlinnPhongShader.h"
#include "FileOutput.h"
#include "RayRay.h"
#include "Sphere.h"
#include "Triangle.h"

RayRay::RayRay(std::unique_ptr<Scene> aScene):
    mScene(std::move(aScene)),
    mPixels(mScene->mCamera.GetY(), mScene->mCamera.GetX())
{
}

void RayRay::Run(){
    Init();

    Loop();

    Output();
}

void RayRay::Init(){
    mShader = BlinnPhongShader::CreateBlinnPhongShader(mScene->mSettings);
}

void RayRay::Loop(){
    for(uint32_t y = 0; y < mScene->mCamera.GetY(); y++){
        for(uint32_t x = 0; x < mScene->mCamera.GetX(); x++){
            mPixels.Get(x,y) = mShader->ShadePixel(x, y, *mScene);
        }
    }
}

void RayRay::Output(){
    std::string filename;
    bool filenameResult = mScene->mSettings.GetString(Settings::kOutputFile, &filename);
    if(filenameResult){
        FileOutput output;
        output.OutputPPM(mPixels, filename);
    }
}
