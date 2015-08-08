// David Sami 2015

#include <Triangle.h>

Triangle::Triangle(Colour aColour, Material aMaterial, std::array<Vertex,3>& aVertices):
    Shape(aColour, aMaterial, Math::Transform()),
    mVertices(aVertices)
{
    OnTransformChange();
}

Triangle::Triangle(std::array<Vertex,3>& aVertices):
    Shape(),
    mVertices(aVertices)
{
    OnTransformChange();
}

Math::Normal Triangle::GetNormal(const Math::Point&){
    return mNormal;
}

bool Triangle::CheckIntersect(const Math::Ray& aRay, double* aIntersection){
    Math::Vector p = aRay.d.Cross(mEdge2);
    double det = p.Dot(mEdge1);

    if(det == 0.)
        return false;

    double invDet = 1 / det;
    Math::Vector T = aRay.o - mVertices[0].p;
    double u = T.Dot(p) * invDet;

    if(u < 0 || u > 1)
        return false;

    Math::Vector q = T.Cross(mEdge1);
    double v = aRay.d.Dot(q) * invDet;

    if(v < 0 || (u + v) > 1)
        return false;

    double t = mEdge2.Dot(q) * invDet;

    if(t > 0){
        *aIntersection = t;
        return true;
    }
    return false;
}

void Triangle::OnTransformChange(){
    mVertices[0] = mTransform(mVertices[0].p);
    mVertices[1] = mTransform(mVertices[1].p);
    mVertices[2] = mTransform(mVertices[2].p);

    CalculateBoundingBox(mVertices);
    CalculateEdgeVectors(mVertices);
    CalculateNormal(mVertices);
}

void Triangle::CalculateBoundingBox(std::array<Vertex,3>& aVertices){
    mBox = BoundingBox(aVertices);
}

void Triangle::CalculateNormal(std::array<Vertex,3>& aVertices){
    mNormal = Math::Normal(mEdge1.Cross(mEdge2));
}

void Triangle::CalculateEdgeVectors(std::array<Vertex,3>& aVertices){
    mEdge1 = aVertices[1].p - aVertices[0].p;
    mEdge2 = aVertices[2].p - aVertices[0].p;
}
