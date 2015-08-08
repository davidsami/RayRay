// David Sami 2015

#include <Triangle.h>

Triangle::Triangle(Colour aColour, Material aMaterial, std::array<Vertex,3>& aVertices):
    Shape(aColour, aMaterial, Math::Transform()),
    mVertices(aVertices),
    mNormal(Triangle::NormalFromPoints(aVertices))
{
}

Triangle::Triangle(std::array<Vertex,3>& aVertices):
    Shape(),
    mVertices(aVertices),
    mNormal(Triangle::NormalFromPoints(aVertices))
{
}

Math::Normal Triangle::GetNormal(const Math::Point&){
    return mNormal;
}

bool Triangle::Intersect(const Math::Ray& aRay, double* aIntersection){
    Math::Vector e1 = mVertices[1].p - mVertices[0].p;
    Math::Vector e2 = mVertices[2].p - mVertices[0].p;
    Math::Vector p = aRay.d.Cross(e2);
    double det = p.Dot(e1);

    if(det == 0.)
        return false;

    double invDet = 1 / det;
    Math::Vector T = aRay.o - mVertices[0].p;
    double u = T.Dot(p) * invDet;

    if(u < 0 || u > 1)
        return false;

    Math::Vector q = T.Cross(e1);
    double v = aRay.d.Dot(q) * invDet;

    if(v < 0 || (u + v) > 1)
        return false;

    double t = e2.Dot(q) * invDet;

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
    //mNormal = mTransform(mNormal);
}

Math::Normal Triangle::NormalFromPoints(std::array<Vertex,3>& aVertices){
    Math::Vector e1 = aVertices[1].p - aVertices[0].p;
    Math::Vector e2 = aVertices[2].p - aVertices[0].p;
    return Math::Normal(e1.Cross(e2));
}
