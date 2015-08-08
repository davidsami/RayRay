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

struct ParserOBJPrimitive;

struct Scene {
    // Objects used by all shapes
    std::vector<std::shared_ptr<Math::Transform>> mTransforms;
    std::vector<std::shared_ptr<Material>> mMaterials;
    std::vector<std::shared_ptr<Colour>> mColours;

    // Vertices for Triangles
    std::vector<std::shared_ptr<Vertex>> mVertices;

    // Scene
    std::vector<std::shared_ptr<Shape>> mObjects;
    std::vector<std::unique_ptr<Light>> mLights;

    // Globals
    Camera mCamera;
    Settings mSettings;

    void MergeOBJ(const ParserOBJPrimitive& aPrimitive);
};

#endif
