// David Sami 2015

#include "RayRay.h"

RayRay::RayRay(Settings* aSettings): 
    mSettings(aSettings),
    mScreen(NULL),
    mCamera(NULL)
{
}

RayRay::~RayRay(){
    if(mScreen)
        delete mScreen;

    if(mCamera)
        delete mCamera;
}

void RayRay::Run(){
    Init();

    Loop();
}

void RayRay::Init(){
    InitScreen();
}

void RayRay::InitScreen(){
    mScreen = Screen::CreateScreen(mSettings);
    mCamera = Camera::CreateCamera(mSettings, mScreen);
}

void RayRay::Loop(){
}
