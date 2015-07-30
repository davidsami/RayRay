// David Sami 2015

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Shape.h"
#include "Triangle.h"

struct Scene {
    std::vector<std::shared_ptr<Vertex>> mVertices;
    std::vector<std::unique_ptr<Shape>> mObjects;
    std::vector<std::unique_ptr<Light>> mLights;
    std::vector<std::shared_ptr<Material>> mMaterials;
    std::unique_ptr<Camera> mCamera;
    Settings mSettings;
};

#endif
