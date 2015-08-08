// David Sami 2015

#include <Triangle.h>

Triangle::Triangle(std::shared_ptr<Colour> aColour, std::shared_ptr<Material> aMaterial, std::array<std::shared_ptr<Vertex>,3> aVertices):
    Shape(aColour, aMaterial, std::make_shared<Math::Transform>()),
    mVertices(aVertices),
    mNormal(Triangle::NormalFromPoints(aVertices))
{
}

Triangle::Triangle(std::array<std::shared_ptr<Vertex>,3> aVertices):
    Shape(),
    mVertices(aVertices),
    mNormal(Triangle::NormalFromPoints(aVertices))
{
}

Math::Normal Triangle::GetNormal(const Math::Point&){
    return mNormal;
}

bool Triangle::Intersect(const Math::Ray& aRay, double* aIntersection){
    Math::Point a, b, c;
    a = (*mTransform)(mVertices[0]->p);
    b = (*mTransform)(mVertices[1]->p);
    c = (*mTransform)(mVertices[2]->p);

    Math::Vector e1 = b - a;
    Math::Vector e2 = c - a;
    Math::Vector p = aRay.d.Cross(e2);
    double det = p.Dot(e1);

    if(det == 0.)
        return false;

    double invDet = 1 / det;
    Math::Vector T = aRay.o - a;
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

Math::Normal Triangle::NormalFromPoints(std::array<std::shared_ptr<Vertex>,3> aVertices){
    Math::Vector e1 = aVertices[1]->p - aVertices[0]->p;
    Math::Vector e2 = aVertices[2]->p - aVertices[0]->p;
    return Math::Normal(e1.Cross(e2));
}
