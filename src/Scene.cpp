// David Sami 2015

#include <algorithm>
#include <memory>
#include "OBJParser.h"
#include "Scene.h"

void Scene::MergeOBJ(const ParserOBJPrimitive& aPrimitive){
    mVertices.insert(
        mVertices.end(),
        aPrimitive.mVertices.begin(),
        aPrimitive.mVertices.end());

    mObjects.insert(
        mObjects.end(),
        aPrimitive.mObjects.begin(),
        aPrimitive.mObjects.end());
}
