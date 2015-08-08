// David Sami 2015

#include <algorithm>
#include <memory>
#include "OBJParser.h"
#include "Scene.h"

void Scene::Merge(const Scene& aPrimitive){
    mVertices.insert(
        mVertices.end(),
        aPrimitive.mVertices.begin(),
        aPrimitive.mVertices.end());

    mObjects.insert(
        mObjects.end(),
        aPrimitive.mObjects.begin(),
        aPrimitive.mObjects.end());
}

void Scene::Apply(Colour aColour, Material aMaterial, Math::Transform aTransform){
    for(auto it = mObjects.begin(); it != mObjects.end(); it++){
        (*it)->SetColour(aColour);
        (*it)->SetMaterial(aMaterial);
        (*it)->SetTransform(aTransform);
    }
}
