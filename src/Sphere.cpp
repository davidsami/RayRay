// David Sami 2015

#include "Sphere.h"

Sphere::Sphere(std::shared_ptr<Colour> aColour, std::shared_ptr<Material> aMaterial, std::shared_ptr<Math::Transform> aTransform, double aRadius):
    Shape(aColour, aMaterial, aTransform),
    mRadius(aRadius)
{
}

bool Sphere::Intersect(const Math::Ray& aRay, double* aIntersection){
    // Bring the ray to the object's space
    Math::Ray r = mTransform->reverse(aRay);

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

    if (t0 > 0 && t0 < t1){
       *aIntersection = t0;
    } else if (t1 > 0){
       *aIntersection = t1;
    } else {
        return false;
    }
    return true;
}

Math::Normal Sphere::GetNormal(const Math::Point& aPoint){
    return Math::Normal(mTransform->reverse(aPoint));
}

Math::Transform Sphere::TransformationFromPoint(const Math::Point& aCenter){
    double x = aCenter.d[0];
    double y = aCenter.d[1];
    double z = aCenter.d[2];
    return Math::Transform::Translation(x,y,z);
}
