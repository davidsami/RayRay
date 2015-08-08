// David Sami 2015

#include "BoundingBox.h"
#include "Triangle.h"

BoundingBox::BoundingBox():
    mP1(0,0,0),
    mP2(0,0,0)
{
}

BoundingBox::BoundingBox(std::array<Vertex,3>& aV){
    // Simplest way to find mins and maxes
    mP1[0] = std::min(aV[0].p[0], std::min(aV[1].p[0], aV[2].p[0]));
    mP1[1] = std::min(aV[0].p[1], std::min(aV[1].p[1], aV[2].p[1]));
    mP1[2] = std::min(aV[0].p[2], std::min(aV[1].p[2], aV[2].p[2]));

    mP2[0] = std::max(aV[0].p[0], std::max(aV[1].p[0], aV[2].p[0]));
    mP2[1] = std::max(aV[0].p[1], std::max(aV[1].p[1], aV[2].p[1]));
    mP2[2] = std::max(aV[0].p[2], std::max(aV[1].p[2], aV[2].p[2]));
}

BoundingBox::BoundingBox(Math::Point& aCenter, double aHalfWidth)
{
    double halfWidth = fabs(aHalfWidth);
    Math::Vector expand(halfWidth, halfWidth, halfWidth);
    mP1 = Math::Point(aCenter - expand);
    mP2 = Math::Point(aCenter + expand);
}

bool BoundingBox::Intersect(const Math::Ray& aRay, double* aIntersection){
    double tmin = -std::numeric_limits<double>::infinity();
    double tmax = std::numeric_limits<double>::infinity();

    for(int i = 0; i < 3; i++){
        double t1 = (mP1(i) - aRay.o(i)) / aRay.d(i);
        double t2 = (mP2(i) - aRay.o(i)) / aRay.d(i);
        tmin = std::max(tmin, std::min(t1, t2));
        tmax = std::min(tmax, std::max(t1, t2));
    }

    if ((tmax > 0) && (tmax > tmin)){
        *aIntersection = tmin;
        return true;
    }
    return false;
}

bool BoundingBox::DoesIntersect(const Math::Ray& aRay){
    double tmin = -std::numeric_limits<double>::infinity();
    double tmax = std::numeric_limits<double>::infinity();

    for(int i = 0; i < 3; i++){
        if(aRay.d(i) != 0){
            double t1 = (mP1(i) - aRay.o(i)) * aRay.dinv(i);
            double t2 = (mP2(i) - aRay.o(i)) * aRay.dinv(i);

            tmin = std::max(tmin, std::min(t1, t2));
            tmax = std::min(tmax, std::max(t1, t2));
        }
    }

    return ((tmax > 0) && (tmax > tmin));
}
