// David Sami 2015

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>
#include "Math.h"
#include "Shape.h"

struct Vertex {
    Vertex():p(0,0,0) {}
    Vertex(Math::Point aP):p(aP) {}
    Math::Point p;
};

class Triangle: public Shape {
public:
    Triangle(Colour aColour, Material aMaterial, std::array<Vertex,3>& aVertices);
    Triangle(std::array<Vertex,3>& aVertices);
    virtual bool CheckIntersect(const Math::Ray& aRay, double* aIntersection);
    virtual Math::Normal GetNormal(const Math::Point&);

protected:
    virtual void OnTransformChange();

private:
    std::array<Vertex,3> mVertices;

    // Precompute
    void CalculateBoundingBox(std::array<Vertex,3>& aVertices);

    void CalculateNormal(std::array<Vertex,3>& aVertices);
    Math::Normal mNormal;

    void CalculateEdgeVectors(std::array<Vertex,3>& aVertices);
    Math::Vector mEdge1;
    Math::Vector mEdge2;
};

#endif
