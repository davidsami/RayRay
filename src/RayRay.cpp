// David Sami 2015

#include <iostream>
#include "BlinnPhongShader.h"
#include "FileOutput.h"
#include "RayRay.h"
#include "Sphere.h"
#include "Triangle.h"

RayRay::RayRay(const Scene& aScene):
    mScene(std::make_shared<const Scene>(aScene)),
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

    // Read number of threads from settings
    uint32_t numThreads = 0;
    bool result = mScene->mSettings.GetUnsigned(Settings::kNumThreads, &numThreads);
    if(result)
        mPool.Init(numThreads, mScene, mShader);
    else
        mPool.Init(1, mScene, mShader);
}

void RayRay::Loop(){
    // Crank out all of the Rays for each pixel;
    for(uint32_t y = 0; y < mScene->mCamera.GetY(); y++){
        for(uint32_t x = 0; x < mScene->mCamera.GetX(); x++){
            ThreadWork work;
            work.mPixel = & mPixels.Get(x,y);
            work.mRay = mScene->mCamera.GenerateRay(x,y);
            mPool.AddWork(work);
        }
    }

    // Wait for processing to finish
    // No point in busy waiting, might as well give up processor for a while
    while(mPool.WorkLeft())
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Signal to the pool that all work is finished
    mPool.StopThreads();
}

void RayRay::Output(){
    std::string filename;
    bool filenameResult = mScene->mSettings.GetString(Settings::kOutputFile, &filename);
    if(filenameResult){
        FileOutput output;
        output.OutputPPM(mPixels, filename);
    }
}
