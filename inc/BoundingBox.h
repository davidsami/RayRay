// David Sami 2015

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Intersectable.h"
#include "Math.h"

class Vertex;

class BoundingBox: Intersectable {
public:
    BoundingBox();
    BoundingBox(std::array<Vertex,3>& aVertices);
    BoundingBox(Math::Point& aCenter, double aHalfWidth);
    virtual bool Intersect(const Math::Ray& aRay, double* aIntersection);
    virtual bool DoesIntersect(const Math::Ray& aRay);
private:
    Math::Point mP1, mP2;
};

#endif
