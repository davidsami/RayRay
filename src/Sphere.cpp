// David Sami 2015

#include "Sphere.h"

Sphere::Sphere(Math::Transform& aTransform, double aRadius):
    Shape(aTransform),
    mRadius(aRadius)
{
}

bool Sphere::Intersect(Math::Ray& aRay, double* aIntersection){
    // Bring the ray to the object's space
    Math::Ray r = mTransform.reverse(aRay);

    // Solve quadratic by subbing in d + t * o in X^2 + Y^2 + Z^2 = R^2
    // and solving for t
    double a, b, c;
    a = r.d(0) * r.d(0)
      + r.d(1) * r.d(1)
      + r.d(2) * r.d(2);

    b = 2 * (r.d(0) * r.o(0)
           + r.d(1) * r.o(1)
           + r.d(2) * r.o(2));

    c = r.o(0) * r.o(0)
      + r.o(1) * r.o(1)
      + r.o(2) * r.o(2)
      - mRadius * mRadius;

    double t0 = 0, t1 = 0;
    Math::SolveQuadratic(a,b,c,&t0,&t1);

    if (t0 > 0){
       *aIntersection = t0;
    } else if (t1 > 0){
       *aIntersection = t1;
    } else {
        return false;
    }
    return true;
}