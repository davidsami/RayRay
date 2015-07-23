// David Sami 2015

#include <iostream>
#include "BlinnPhongShader.h"
#include "FileOutput.h"
#include "RayRay.h"
#include "Sphere.h"
#include "Triangle.h"

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
    mScreen = Screen::CreateScreen(*mSettings);
    mPixels = std::make_unique<PixelBuffer>(mScreen->GetY(), mScreen->GetX());
    mShader = BlinnPhongShader::CreateBlinnPhongShader(*mSettings);
    InitScene();

    //XXX: Test
    std::unique_ptr<Material> mat(new Material(0, 1, 1, 500));
    mScene.mMaterials.push_back(std::move(mat));

    Colour c(255,0,127);
    Math::Point p(0,0,5);
    std::unique_ptr<Sphere> test(new Sphere(c, 0, p, 1));
    mScene.mObjects.push_back(std::move(test));

    Colour c2(100,255,0);
    Math::Point p2(1,1,3);
    std::unique_ptr<Sphere> test2(new Sphere(c2, 0, p2, 1));
    mScene.mObjects.push_back(std::move(test2));

    Math::Point p3(1,0,0);
    std::unique_ptr<Light> light(new Light(3, p3));
    mScene.mLights.push_back(std::move(light));

    Math::Point p4(-1,-0.5,3);
    std::unique_ptr<Light> light2(new Light(1, p4));
    mScene.mLights.push_back(std::move(light2));

    Colour c3(255,255,255);
    std::shared_ptr<Vertex> v1 = std::make_shared<Vertex>(Math::Point(5,5,5));
    std::shared_ptr<Vertex> v2 = std::make_shared<Vertex>(Math::Point(5,-3,5));
    std::shared_ptr<Vertex> v3 = std::make_shared<Vertex>(Math::Point(-5,-3,5));
    std::shared_ptr<Vertex> v4 = std::make_shared<Vertex>(Math::Point(-5,5,5));

    std::array<std::shared_ptr<Vertex>,3> verts = {
        v1,v2,v3
    };
    std::unique_ptr<Triangle> tri(new Triangle(c3, 0, verts));
    mScene.mObjects.push_back(std::move(tri));

    std::array<std::shared_ptr<Vertex>,3> verts2 = {
        v3,v4,v1
    };
    std::unique_ptr<Triangle> tri2(new Triangle(c3, 0, verts2));
    mScene.mObjects.push_back(std::move(tri2));
}

void RayRay::InitScene(){
    mScene.mCamera = Camera::CreateCamera(*mSettings, *mScreen);
}

void RayRay::Loop(){
    for(uint32_t y = 0; y < mScreen->GetY(); y++){
        for(uint32_t x = 0; x < mScreen->GetX(); x++){
            mPixels->Get(x,y) = mShader->ShadePixel(x, y, mScene);
        }
    }
}

void RayRay::Output(){
    std::string filename;
    bool filenameResult = mSettings->GetString(Settings::kOutputFile, &filename);
    if(filenameResult){
        FileOutput output;
        output.OutputPPM(*mPixels, filename);
    }
}
