// David Sami 2015

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.h"
#include "Matrix.h"

class Transform{
public:
    Transform(Matrix4& aMat);
    Transform()=default;

    Point operator()(const Point &aP);
    Vector operator()(const Vector &aV);

    static Transform TranslationTransform(const Vector &d);
    static Transform ScaleTransform(const Vector &d);
    static Transform RotateXTransform(const double theta);
    static Transform RotateYTransform(const double theta);
    static Transform RotateZTransform(const double theta);
    static Transform RotateTransform(const Vector &axis, const double theta);

protected:
    Matrix4 mat;
    Matrix4 inverse;
};

#endif

