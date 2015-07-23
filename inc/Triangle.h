// David Sami 2015

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>
#include "Math.h"
#include "Shape.h"

struct Vertex {
    Vertex(Math::Point aP):p(aP) {}
    Math::Point p;
};

class Triangle: public Shape {
public:
    Triangle(const Colour& aColour, const size_t aMaterialId, std::array<std::shared_ptr<Vertex>,3> aVertices);
    virtual bool Intersect(const Math::Ray& aRay, double* aIntersection);
    virtual Math::Normal GetNormal(const Math::Point&);
private:
    std::array<std::shared_ptr<Vertex>,3> mVertices;

    static Math::Normal NormalFromPoints(std::array<std::shared_ptr<Vertex>,3> aVertices);
    Math::Normal mNormal;
};

#endif
