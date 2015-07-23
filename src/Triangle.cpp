// David Sami 2015

#include <Triangle.h>

Triangle:: Triangle(const Colour& aColour, const size_t aMaterialId, std::array<std::shared_ptr<Vertex>,3> aVertices):
    Shape(Math::Transform(), aColour, aMaterialId),
    mVertices(aVertices),
    mNormal(Triangle::NormalFromPoints(aVertices))
{
}

Math::Normal Triangle::GetNormal(const Math::Point&){
    return mNormal;
}

bool Triangle::Intersect(const Math::Ray& aRay, double* aIntersection){
    Eigen::Vector3d e1 = mVertices[1]->p.d - mVertices[0]->p.d;
    Eigen::Vector3d e2 = mVertices[2]->p.d - mVertices[0]->p.d;
    Eigen::Vector3d p = aRay.d.d.cross(e2);
    double det = p.dot(e1);

    if(det == 0.)
        return false;

    double invDet = 1 / det;
    Eigen::Vector3d T = aRay.o.d - mVertices[0]->p.d;
    double u = T.dot(p) * invDet;

    if(u < 0 || u > 1)
        return false;

    Eigen::Vector3d q = T.cross(e1);
    double v = aRay.d.d.dot(q) * invDet;

    if(v < 0 || (u + v) > 1)
        return false;

    double t = e2.dot(q) * invDet;

    if(t > 0){
        *aIntersection = t;
        return true;
    }
    return false;
}

Math::Normal Triangle::NormalFromPoints(std::array<std::shared_ptr<Vertex>,3> aVertices){
    Eigen::Vector3d e1 = aVertices[1]->p.d - aVertices[0]->p.d;
    Eigen::Vector3d e2 = aVertices[2]->p.d - aVertices[0]->p.d;
    Eigen::Vector3d vec = e1.cross(e2).normalized();
    return Math::Normal(vec);
}
