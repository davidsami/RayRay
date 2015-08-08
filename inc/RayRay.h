// David Sami 2015

#ifndef RAYRAY_H
#define RAYRAY_H

#include <memory>
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "PixelBuffer.h"
#include "Scene.h"
#include "Settings.h"
#include "Shader.h"
#include "Shape.h"

class RayRay {
public:
    RayRay(const Scene& aScene);
    void Run();
private:
    void Init();

    void Loop();

    void Output();

    std::shared_ptr<const Scene> mScene;

    PixelBuffer mPixels;

    std::unique_ptr<Shader> mShader;
};

#endif
